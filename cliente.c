#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>

#define TAMANHO_BUFFER 2048
#define TAMANHO_NOME 32

volatile sig_atomic_t isInterrompido = 0;
int descritorServidor = 0;
char nome[TAMANHO_NOME];


void sair(int sig) {
    isInterrompido = 1;
}

void sobrescrever_stdout() {
    printf("%s", "> ");
    fflush(stdout);
}

void removerCaracteresVazios (char* arr, int tamanho) {
    int i;
    for (i = 0; i < tamanho; i++) {
        if (arr[i] == '\n') {
            arr[i] = '\0';
            break;
        }
    }
}


int criarThread(pthread_t *novaThread, void *(*rotina)(void *)){
    return (pthread_create(novaThread, NULL, rotina, NULL) != 0);
}


int configurarSocket(struct sockaddr_in *enderecoSocket, const char *ip, int port){
    enderecoSocket->sin_family = AF_INET;
    enderecoSocket->sin_addr.s_addr = inet_addr(ip);
    enderecoSocket->sin_port = htons(port);

    return socket(AF_INET, SOCK_STREAM, 0);
}

int conectar(struct sockaddr_in *enderecoSocket, int descritorSocket){
    return (connect(descritorSocket, (struct sockaddr *) enderecoSocket, sizeof(*enderecoSocket)) == -1);
}

void enviarMensagem() {
    char mensagem[TAMANHO_BUFFER] = {};
    char buffer[TAMANHO_BUFFER + 32] = {};

    while(1) {
        sobrescrever_stdout();
        fgets(mensagem, TAMANHO_BUFFER, stdin);
        removerCaracteresVazios(mensagem, TAMANHO_BUFFER);

        if (strcmp(mensagem, "sair") == 0) {
            break;
        } else {
            sprintf(buffer, "%s: %s\n", nome, mensagem);
            send(descritorServidor, buffer, strlen(buffer), 0);
        }

        bzero(mensagem, TAMANHO_BUFFER);
        bzero(buffer, TAMANHO_BUFFER + 32);
    }
    sair(2);
}

void receberMensagem() {
    char mensagem[TAMANHO_BUFFER] = {};
    while (1) {

        int recebido = recv(descritorServidor, mensagem, TAMANHO_BUFFER, 0);
        if (recebido > 0) {
            printf("%s", mensagem);
            sobrescrever_stdout();
        } else if (recebido == 0) {
            break;
        }

        memset(mensagem, 0, sizeof(mensagem));
    }
}

int isNomeCorreto(const char *nome){
    return (strlen(nome) < TAMANHO_NOME || strlen(nome) > 2);
}




int main(){

    struct sockaddr_in enderecoServidor;
    pthread_t enviarMensagemThread;
    pthread_t receberMensagemThread;

    signal(SIGINT, sair); //permite que o processo seja interrompido através de um envio de um sinal

    printf("Qual o seu nome? >> ");
    fgets(nome, TAMANHO_NOME, stdin);
    removerCaracteresVazios(nome, strlen(nome));

    if (!isNomeCorreto(nome)){
        printf("O nome está incorreto!\n");
        return EXIT_FAILURE;
    }

    descritorServidor = configurarSocket(&enderecoServidor, "127.0.0.1", 1235);

    if (conectar(&enderecoServidor,descritorServidor)) {
        printf("Houve um erro na conexão com o servidor\n");
        return EXIT_FAILURE;
    }

    send(descritorServidor, nome, TAMANHO_NOME, 0); //envia o nome para o servidor

    printf("---\nC CHAT\n---\n");

    if(criarThread(&enviarMensagemThread, (void *) enviarMensagem)){
        printf("Error em criar uma thread para enviar as mensagens\n");
        return EXIT_FAILURE;
    }

    if(criarThread(&receberMensagemThread, (void *)receberMensagem)){
        printf("Error em criar uma thread para receber as mensagens\n");
        return EXIT_FAILURE;
    }

    while (1){
        if(isInterrompido){
            break;
        }
    }

    close(descritorServidor);

    return EXIT_SUCCESS;
}

