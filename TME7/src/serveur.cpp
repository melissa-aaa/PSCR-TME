#include <cstring>
#include <signal.h>
#include "chat_common.h"



// gestion des connexions
int nbConnex = 0;
char* connexions[MAX_USERS] = {(char*)0}; // tableau des utilisateurs connectés
MySHM* shm_utili[MAX_USERS] = {(MySHM*)0}; // tableau des segments des utilisateurs


// handler de CTRL+C
void handler(int sig) {
	printf("J'ai reçu CTRL+C, libération des ressources puis exit\n");
}

// supprime le message lu et décale les autres
void suppMessage(struct message messages, int i) {
    messages[i] = NULL;
    for(int j=i; j<MAX_USERS; j++) {
        if(messages[j]->content == NULL) {
            continue;
        } else {
            messages[j]->content = messages[j+1]->content;
        }
    }
}


// connecte un utilisateur
// hypothèse : id est sous la forme "id"
void connexion(char* id) {
    if(id == NULL) {
        printf("connexion : id est NULL\n");
        return;
    }
    if(nbConnex == MAX_USERS) {
        printf("connexion : plus de place\n");
        return;
    }
    for(int i=0; i<MAX_USERS; i++) {
        if(connexions[i] == NULL) {
            connexions[i] = id;
            nbConnex++;

            int fd;
            if((fd = shm_open(id, O_RDWR, 0666)) == -1) {
                perror("shm_open connexion"); 
            }
            shmp = mmap(NULL, sizeof(MySHM), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
            shm_utili[i] = shmp;
            return;
        }
    }   
}


// déconnecte un utilisateur
// hypothèse : id est sous la forme "id"
void deconnexion(char* id) {
        if(id == NULL) {
        printf("deconnexion : id est NULL\n");
        return;
    }
    if(nbConnex == MAX_USERS) {
        printf("deconnexion : personne a deconnecter\n");
        return;
    }
    for(int i=0; i<MAX_USERS; i++) {
        if(strcmp(id, connexions[i]) == 0) {
            connexions[i] = NULL;
            nbConnex--;

            munmap(shm_utili[i], sizeof(MySHM));
	        shm_unlink(id);

            return;
        }
    } 
}


int main(int argc, char** argv) {

    // on lit l'identifiant en ligne de commande
    char* idServ = NULL;
    //int idServ = -1;
    if(argc == 2) {
        //idServ = atoi(argv[1]);
        idServ = argv[1];
    } else {
        printf("Il faut mettre l'identifiant du serveur en ligne de commande sous la forme /idServeur \n");
        exit(0);
    }

    // on crée un segment de mémoire partagée
	int fd;
	if((fd = shm_open(idServ, O_RDWR | O_CREAT | O_EXCL, 0666)) == -1) {
		perror("shm_open "); 
	}
	if(ftruncate(fd, sizeof(MySHM))) {
		perror("ftruncate ");
	}
	void* ptr = mmap(NULL, sizeof(MySHM), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	MySHM* shm = new (ptr) MySHM;
    sem_init(shm->sem, 1, 1); // mutex pour protéger les accès à shm

    /*
    struct myshm {
    int read; // nombre de messages retransmis par le serveur 
    int write; // nombre de messages non encore retransmis par le serveur 
    int nb; // nombre total de messages emis 
    sem_t sem;
    struct message messages[MAX_MESS];
    } MySHM;
    */

    // on traite les requêtes des clients
    while(1) {
        sem_wait(shm->sem);
        if(shm->write > 0) { // s'il reste des messages non traités
            // on traite le suivant
            struct message m = shm->messages[shm->read];
            switch(m->type) {
                case 0: // connexion
                    connexion(m->content);
                    break;

                case 1: // diffusion de message
                    for(int i=0; i<nbConnex; i++) {
                        MySHM* s = shm_utili[i];
                        s->messages[s->write]->content = m;
                    }
                    break;

                case 2: // déconnexion
                    deconnexion(m->content);
                    break;

                default:
                    printf("Type de la requête erroné\n");
                    exit(0);
            }

            shm->read++;
            shm->write--;
        }
        suppMessage(shm->messages, shm->read);
        shm->read;
        shm->write--;
        sem_post(shm->sem);
    }


    // handler de CTRL+C
    sigset_t set;
    sigemptyset(&set);
    struct sigaction act;
    act.sa_handler = handler;
    act.sa_mask = set;
    act.sa_flags = 0;
    sigaction(SIGINT, &act, NULL);

	// on attend CTRL+C
    sigset_t set2;
    sigfillset(&set2);
    sigdelset(&set2, SIGINT);
	sigsuspend(&set2);

	// on libère les ressources
    sem_destroy(shm->sem);
	free(shm);
	munmap(ptr, sizeof(MySHM));
	shm_unlink(idServ);

	return EXIT_SUCCESS;
}