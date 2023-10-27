#include "serv_cli_fifo.h"
#include "Handlers_Serv.h"

void main() {
    // Déclarations
    int fd_fifol, fd_fifo2;
    Question question;
    Response response;
    
    // Création des tubes nommés
    if (mkfifo(FIFO1, 0666) == -1) {
        perror("Erreur lors de la création de fifol");
        exit(1);
    }

    if (mkfifo(FIFO2, 0666) == -1) {
        perror("Erreur lors de la création de fifo2");
        exit(1);
    }

    // Initialisation du générateur de nombres aléatoires
    srand(getpid());

    // Ouverture des tubes nommés
    fd_fifol = open(FIFO1,O_RDWR);
    if (fd_fifol == -1) {
        perror("Erreur lors de l'ouverture de fifol");
        exit(1);
    }

    fd_fifo2 = open(FIFO2,O_RDWR);
    if (fd_fifo2 == -1) {
        perror("Erreur lors de l'ouverture de fifo2");
        exit(1);
    }

    // Installation des Handlers
    signal(SIGUSR1, hand_reveil);
    signal(SIGINT, fin_serveur);  // Par exemple, finir le serveur sur Ctrl+C
    signal(SIGTERM, fin_serveur); // Ou sur un signal de terminaison

    int i=0;
    
    printf("entering loop\n");
    while (1) {
        // Lecture d'une question
        i+=1;
        printf("Serveur looping %d \n",i);

        read(fd_fifol, &question, sizeof(Question));

        // Construction de la réponse
        response.server_pid = getpid();
        response.count = question.n;
        
        printf("generating %d numbers\n",question.n);
        for (int i = 0; i < question.n; i++) {
            response.numbers[i] = rand() % NMAX + 1;
        }

        // Envoi de la réponse
        write(fd_fifo2, &response, sizeof(Response));

        // Envoi du signal SIGUSR1 au client concerné
        kill(question.client_num, SIGUSR1);
        
    }

    // Fermeture des tubes nommés et nettoyage (dans la pratique, ce code ne sera jamais atteint en raison de la boucle while(1))
    close(fd_fifol);
    close(fd_fifo2);
    unlink(FIFO1);
    unlink(FIFO2);

  
}
