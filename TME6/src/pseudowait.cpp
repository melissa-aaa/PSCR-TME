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

void handlerALRM(int sig) {
    alarm(0);
}

void handlerCHLD(int sig) {
    pid_t f = 0;
    while(f != -1) {
        f = wait(NULL);
        /*
        if(f == pid) {
            return pid;
        }
        */
    }
}

int wait_till_pid2(pid_t pid, int sec) {

    // on active une alarme
    alarm(sec);

    // handler pour SIGALRM
    sigset_t sa;
    sigemptyset(&sa);
    struct sigaction acta;
    acta.sa_handler = handlerALRM;
    acta.sa_mask = sa;
    acta.sa_flags = 0;
    sigaction(SIGALRM, &acta, NULL);

    // handler pour SIGCHLD
    sigset_t sc;
    sigemptyset(&sc);
    struct sigaction actc;
    actc.sa_handler = handlerCHLD;
    actc.sa_mask = sc;
    actc.sa_flags = 0;
    sigaction(SIGALRM, &actc, NULL);

    // on attend SIGCHLD ou SIGALRM
    sigset_t set;
    sigfillset(&set);
    sigdelset(&set, SIGCHLD);
    sigdelset(&set, SIGALRM);
    sigsuspend(&set);
    return 0;
}

int main() {

    pid_t fils;
    if ((fils = fork()) == 0) {
        printf("coucou, je suis le fils %d\n", getpid());
        sleep(1); // à faire varier pour tester wait_till_pid2
    } else {
        printf("hello, je suis le père %d, je viens d'attendre mon fils %d\n", getpid(), wait_till_pid(fils));
        //printf("hello, je suis le père %d, je viens d'attendre mon fils %d\n", getpid(), wait_till_pid2(fils, 10));
    }

    return 0;
}