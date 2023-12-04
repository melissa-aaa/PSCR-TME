#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <signal.h>
#include <sys/wait.h>
#include "rsleep.h"



int vies = 3;



void handler(int sig) {
    (vies)--;
    if(vies == 0) {
        printf("je suis %d, je suis mort\n", getpid());
        exit(1);
    }
    printf("je suis %d, vies restantes : %d\n", getpid(), vies);
}



void handlerLuke(int sig) {
    printf("je suis %d, coup paré\n", getpid());
}



void attaque(pid_t adversaire){
    // on met un handler pour SIGINT
    sigset_t set;
    sigemptyset(&set);
    struct sigaction act;
    act.sa_handler = handler;
    act.sa_mask = set; // signaux à bloquer pendant l'exécution du handler
    act.sa_flags = 0;
    sigaction(SIGINT, &act, NULL);

    // on envoie un SIGINT à l'adversaire
    if(kill(adversaire, SIGINT) == -1) { //l'adversaire est mort
        exit(0);
    }
    printf("kill envoye par %d\n", getpid());

    // dormir
    //int t = (int)((rand()/(double)RAND_MAX)*4);
    //sleep(t);
    randsleep();

}


void defense(){
    printf("%d se défend\n", getpid());
    // bloquer le signal SIGINT
    signal(SIGINT, SIG_IGN);

    // dormir
    //int t = (int)((rand()/(double)RAND_MAX)*4);
    //sleep(t);
    randsleep();

    // débloquer SIGINT
    signal(SIGINT, SIG_DFL);
}



void defenseLuke() {
    // on met un handler pour SIGINT
    sigset_t set;
    sigemptyset(&set);
    sigaddset(&set, SIGINT);
    struct sigaction act;
    act.sa_handler = handlerLuke;
    act.sa_mask = set; // signaux à bloquer pendant l'exécution du handler
    act.sa_flags = 0;
    sigaction(SIGINT, &act, NULL);

    // masquer SIGINT
    sigset_t s;
    sigemptyset(&s);
    sigaddset(&s, SIGINT);
    sigprocmask(SIG_SETMASK, &s, NULL);

    // dormir
    randsleep();

    // voir si on a été attaqué
    sigset_t setbis;
    sigfillset(&setbis);
    sigdelset(&setbis, SIGINT);
    sigsuspend(&setbis);

    // démasquer SIGINT
    sigemptyset(&s);
    sigprocmask(SIG_SETMASK, &s, NULL);
}

void combat(pid_t adversaire){
    while(1) {
        defense();
        attaque(adversaire);
    }
}

void combatLuke(pid_t adversaire){
    while(1) {
        defenseLuke();
        attaque(adversaire);
    }
}

int main() {
   
    pid_t luke = fork();

    if(luke == 0) {
        srand(time(NULL));
        printf("------ je suis Luke %d et mon père est %d\n", getpid(), getppid());
        combatLuke(getppid());
    }
    else { // je suis Vador
        printf("------ je suis Vador %d\n", getpid());
        srand(time(NULL));
        combat(luke);
    }

    return 0;
}