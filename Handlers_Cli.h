#ifndef HANDLERS_CLI_H
#define HANDLERS_CLI_H

#include <stdio.h>
#include <signal.h>

// Handler pour le réveil du client suite à la réception du signal SIGUSR1
void hand_reveil(int sig) {
    // Par exemple, afficher un message indiquant que le client a été réveillé.
    printf("Client réveillé par %d\n",sig);
}

#endif // HANDLERS_CLI_H
