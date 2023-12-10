#include <mutex>
#include <condition_variable>

namespace pr {

class Barrier {
    private:
        int count;               // nombre de jobs à attendre
        int completed;           // nombre de jobs finis
        std::mutex mutex;     
        std::condition_variable condition; 
public:
    Barrier(int count) : count(count), completed(0) {}

    void jobWait() {
        std::unique_lock<std::mutex> lock(mutex);
        if (++completed == count) {
            // tous les jobs ont finit => réveiller toutes les threads en attente
            condition.notify_all();
        } else {
            // attendre que tous les jobs terminent
            condition.wait(lock);
        }
    }


};

} // namespace pr