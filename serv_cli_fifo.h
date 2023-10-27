#ifndef SERV_CLI_FIFO_H
#define SERV_CLI_FIFO_H

// Entêtes des fichiers systèmes nécessaires
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

// Constantes et macros communes
#define NMAX 10
#define FIFO1 "/tmp/tube1"
#define FIFO2 "/tmp/tube2"

// Structures des données
typedef struct {
    int client_num; //PID du client
    int n; // nombre de nombres à générer
} Question;

typedef struct {
    int server_pid; // PID du serveur
    int numbers[NMAX]; // taille maximale pour une réponse
    int count; // nombre réel de nombres dans la réponse
            
} Response;

#endif // SERV_CLI_FIFO_H
