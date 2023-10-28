#include "serv_cli_fifo.h"
#include "Handlers_Cli.h"

int main() {
    // Déclarations
    int fd_fifo1, fd_fifo2;
    Question question;
    Response response;

    // Ouverture des tubes nommés
    fd_fifo1 = open(FIFO1, O_WRONLY);
    if (fd_fifo1 == -1) {
        perror("Erreur lors de l'ouverture de FIFO1");
        exit(1);
    }

    fd_fifo2 = open(FIFO2, O_RDONLY);
    if (fd_fifo2 == -1) {
        perror("Erreur lors de l'ouverture de fifo2");
        exit(1);
    }

    // Installation des Handlers
    signal(SIGUSR1, hand_reveil);
    
    // Initialisation du générateur de nombres aléatoires
    srand(getpid());

    // Construction et envoi d'une question
    question.client_num = getpid();

    question.n = rand() % NMAX + 1;

    write(fd_fifo1, &question, sizeof(Question));

    // Attente de la réponse (le handler s'occupera de la notification)
    pause();

    // Lecture de la réponse
    read(fd_fifo2, &response, sizeof(Response));

    // Envoi du signal SIGUSR1 au serveur pour notifier que la réponse a été lue
    kill(response.server_pid, SIGUSR1);

    // Traitement local de la réponse (ici, affichage des nombres reçus)
    printf("Nombres reçus : \n");
    for (int i = 0; i < response.count; i++) {
        printf("%d ", response.numbers[i]);
    }
    printf("\n");

    // Fermeture des tubes
    close(fd_fifo1);
    close(fd_fifo2);

    return 0;
}
