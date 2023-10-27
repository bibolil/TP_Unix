#ifndef HANDLERS_SERV_H
#define HANDLERS_SERV_H

#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/wait.h>
#include "serv_cli_fifo.h"

// Handler pour le réveil du serveur suite à la réception du signal SIGUSR1
void hand_reveil(int sig) {
    // Ce code sera exécuté lorsque le serveur reçoit un signal SIGUSR1.
    printf("Serveur réveillé par SIGUSR1\n");
}

// Handler pour la fin du serveur suite à la réception d'un signal quelconque
void fin_serveur(int sig) {
    // Ce code sera exécuté lorsque le serveur reçoit un signal quelconque pour terminer.
    printf("Serveur terminant sur signal %d\n", sig);

    // suppression des tubes créés
    pid_t child_pid;
    int status;

    // premiere tube 
    child_pid = fork();
    if (child_pid == 0) {
        // processus enfant
        execlp("rm", "rm", "-r", FIFO1, NULL);
        // en cas d'erreur
        perror("execlp");
        exit(1);
    } else if (child_pid < 0) {
        perror("fork");
        exit(1);
    }

    // attendre la fin du premier processus
    wait(&status);

    // deuxieme tube
    child_pid = fork();
    if (child_pid == 0) {
        // processus enfant
        execlp("rm", "rm", "-r", FIFO2, NULL);
        // en cas d'erreur
        perror("execlp");
        exit(1);
    } else if (child_pid < 0) {
        perror("fork");
        exit(1);
    }

    // attendre la fin du deuxieme processus
    wait(&status);

   
    // Terminer le processus serveur proprement.
    exit(0);
}

#endif // HANDLERS_SERV_H
