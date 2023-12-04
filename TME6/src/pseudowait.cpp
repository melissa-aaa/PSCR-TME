#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <signal.h>
#include <sys/wait.h>

int wait_till_pid(pid_t pid) {
    pid_t f = 0;
    while(f != -1) {
        f = wait(NULL);
        if(f == pid) {
            return pid;
        }
    }
    return -1;
}



int wait_till_pid3(pid_t pid, int sec) {

    // on active une alarme
    alarm(sec);

    // bloquer les signaux SIGCHLD et SIGALRM pour le traitement normal
    sigset_t s;
    sigemptyset(&s);
    sigaddset(&s, SIGCHLD);
    sigaddset(&s, SIGALRM);
    sigprocmask(SIG_SETMASK, &s, NULL);

    // on attend SIGCHLD ou SIGALRM avec sigwait
    int sig = 0;

    // on attend un SIGCHILD ou un SIGALRM
    while(sigwait(&s, &sig) == 0) {
        if(sig == SIGALRM) { // si on reçoit un SIGALRM, le temps imparti est terminé
            return -1;
        }
        else if(sig == SIGCHLD) { // si on reçoit un SIGCHLD, on regarde si le fils qu'on attend est terminé
            pid_t f = 0;
            while(f != -1) {
                f = wait(NULL);
                if(f == pid) { // le fils est terminé
                    alarm(0);
                    return pid;
                }
            }
        }
    }
    printf("coucou\n");

    return -1;
}



void handlerALRM(int sig) {
    printf("J'ai reçu SIGALRM\n");
}


void handlerCHLD(int sig) {
    printf("J'ai reçu SIGCHLD\n");
}


int wait_till_pid2(pid_t pid, int sec) {

    // on active une alarme
    alarm(sec);

    sigset_t s;
    sigemptyset(&s);

    /*
    // handler pour SIGALRM
    struct sigaction acta;
    acta.sa_handler = handlerALRM;
    acta.sa_mask = s;
    acta.sa_flags = 0;
    sigaction(SIGALRM, &acta, NULL);
    */

    // handler pour SIGCHLD
    struct sigaction actc;
    actc.sa_handler = handlerCHLD;
    actc.sa_mask = s;
    actc.sa_flags = 0;
    sigaction(SIGCHLD, &actc, NULL);

    // on attend SIGCHLD ou SIGALRM
    sigset_t set;
    sigfillset(&set);
    sigdelset(&set, SIGCHLD);
    sigdelset(&set, SIGALRM);

    while(sigsuspend(&set) == -1) {
        pid_t f = 0;
        while(f != -1) {
            f = wait(NULL);
            if(f == pid) {
                alarm(0);
                return pid;
            }
        }
    }

    return -1;
}


int main() {

    pid_t fils;
    if ((fils = fork()) == 0) {
        printf("coucou, je suis le fils %d\n", getpid());
        sleep(5); // à faire varier pour tester wait_till_pid3
        exit(EXIT_SUCCESS);
    } else {

        // pour Question 7
        //printf("hello, je suis le père %d, je viens d'attendre mon fils %d\n", getpid(), wait_till_pid(fils));


        // pour Question 8
        printf("hello, je suis le père %d\n", getpid());
        int f = wait_till_pid2(fils, 4);
        if(f != -1) {
            printf("Je viens d'attendre mon fils %d\n", f);
        } else {
            printf("Temps imparti terminé !\n");
        }

        // pour Question 8 : autre méthode
        /*
        printf("hello, je suis le père %d\n", getpid());
        int f = wait_till_pid3(fils, 4);
        if(f != -1) {
            printf("Je viens d'attendre mon fils %d\n", f);
        } else {
            printf("Temps imparti terminé !\n");
        }
        */

    }

    return 0;
}