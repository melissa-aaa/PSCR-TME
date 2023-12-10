#include "Vec3D.h"
#include "Pool.h"
#include "Barrier.h" 
#include "Rayon.h"
#include "Scene.h"
#include <iostream> 
#include <algorithm> 
#include <fstream>
#include <limits>
#include <random>

using namespace std;
using namespace pr;

class JobConcret : public Job {
    private:
        const Vec3D& screenPoint;
        Color& pixel;
        const Scene& scene;
        const vector<Vec3D>& lights;
        Barrier* barrier;

    public:
        JobConcret(const Vec3D& screenPoint, Color& p, const Scene& s, const vector<Vec3D>& l, Barrier* b)
            : screenPoint(screenPoint), pixel(p), scene(s), lights(l), barrier(b) {}

        void run() override {
            // le rayon 
            Rayon ray(scene.getCameraPos(), screenPoint);
            Color finalcolor;
            auto minz = std::numeric_limits<float>::max();

            for (const auto& obj : scene) {
                // rend la distance de l’objet à la camera
                auto zinter = obj.intersects(ray);

                // si intersection plus proche
                if (zinter < minz) {
                    minz = zinter;

                    // pixel prend la couleur de l’objet
                    finalcolor = obj.getColor();

                    auto camera = scene.getCameraPos();

                    // calcul du rayon et de sa normale à la sphere
                    // on prend le vecteur de la camera vers le point de l’ecran (dest - origine)
                    // on le normalise à la longueur 1, on multiplie par la distance à l’intersection
                    Vec3D rayInter = (ray.dest - ray.ori).normalize() * zinter;

                    // le point d’intersection
                    Vec3D intersection = rayInter + camera;

                    // la normale à la sphere au point d’intersection donne l’angle pour la lumière
                    Vec3D normal = obj.getNormale(intersection);

                    // le niveau d’eclairage total contribue par les lumieres (0 sombre, 1 total lumiere)
                    double dt = 0;

                    // modifier par l’eclairage la couleur
                    for (const auto& light : lights) {
                        // le vecteur de la lumiere au point d’intersection
                        Vec3D tolight = (light - intersection);

                        // si on est du bon côté de la sphere, i.e. le rayon n’intersecte pas avant de l’autre côté
                        if (obj.intersects(Rayon(light, intersection)) >= tolight.length() - 0.05) {
                            // epsilon 0.05 for double issues
                            dt += tolight.normalize() & normal; // l’angle ( scalaire) donne la puissance de la lumiere réfléchie
                        }
                    }

                    // eclairage total
                    finalcolor = finalcolor * dt + finalcolor * 0.2; // *0.2 = lumiere speculaire ambiante
                }
            }

            // Attendre tous les jobs avant de mettre à jour le pixel
            barrier->jobWait();

            // MAJ pixel avec la couleur finale
            pixel = finalcolor;
        }

        ~JobConcret() {}
};

