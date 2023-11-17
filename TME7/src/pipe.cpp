#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int main(int argc, char** argv) {

    if(argc < 4) {
        perror("ERREUR");
    }

    int fd[2];

    pipe(fd);

    int cpt = 1;
    while (cpt < argc-1) {
        printf("cpt : %d\n", cpt);
        if (argv[cpt][0] == '|'){
            argv[cpt] = NULL;
            break;
        }
        cpt++;
    }

    if(fork() == 0){
        dup2(fd[1], STDOUT_FILENO);
        close(fd[0]);
        execv(argv[1], argv+1);
        perror("erreur"); 
        exit(1);

    }

    if(fork() == 0){
        close(fd[1]);
        dup2(fd[0], STDIN_FILENO);
        execv(argv[cpt+1], argv+(cpt+1));
        perror("erreur");
        exit(2);

    }

    close(fd[0]);
    close(fd[1]);

    return 0;

}