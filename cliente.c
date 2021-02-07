#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>
#include "json-c/json.h"

//gcc cliente.c -ljson-c -o cliente

#define TAMANHO_BUFFER 2048
#define TAMANHO_AUTENTICACAO 32

volatile sig_atomic_t isInterrompido = 0;
int descritorServidor = 0;
char solicitacaoJSON[TAMANHO_BUFFER];
char nome[32];

const char * extrairInformacao(char *jsonString,char *atributo ){

    struct json_object *json_convertido = json_tokener_parse(jsonString);
    struct json_object *json_atributo;
    json_object_object_get_ex(json_convertido, (const char *) atributo, &json_atributo);
    return json_object_get_string(json_atributo);
}


const char * gerarSolicitacao(char *n,char *s){
    struct json_object *jobj;
    jobj = json_object_new_object();
    json_object_object_add(jobj, "nome",json_object_new_string((const char *) n));
    json_object_object_add(jobj, "senha",json_object_new_string((const char *) s));
    return json_object_to_json_string(jobj);
}

void sair(int sig) {
    isInterrompido = 1;
}

void sobrescrever_stdout() {
    printf("%s", "> ");
    fflush(stdout);
}

void removerQuebraDeLinha (char* arr, int tamanho) {
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
        removerQuebraDeLinha(mensagem, TAMANHO_BUFFER);

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

int isDadosAutenticacaoCorreto(const char *nome, const char *senha){
    return ((strlen(nome) < TAMANHO_AUTENTICACAO || strlen(nome) > 2) && (strlen(senha) < TAMANHO_AUTENTICACAO || strlen(senha) > 2));
}




int main(){

    struct sockaddr_in enderecoServidor;
    pthread_t enviarMensagemThread;
    pthread_t receberMensagemThread;
    char nome_auth[TAMANHO_AUTENTICACAO];
    char senha_auth[TAMANHO_AUTENTICACAO];

    signal(SIGINT, sair); //permite que o processo seja interrompido através de um envio de um sinal

    printf("Digite o seu usuário >> ");
    fgets(nome_auth, TAMANHO_AUTENTICACAO], stdin);
    removerQuebraDeLinha(nome_auth, strlen(nome_auth));

    printf("Digite a sua senha >> ");
    fgets(senha_auth, TAMANHO_AUTENTICACAO], stdin);

    if (isDadosAutenticacaoCorreto(nome_auth,senha_auth)){
        strcpy(solicitacaoJSON,gerarSolicitacao(nome_auth,senha_auth));
        strcpy(nome,extrairInformacao(solicitacaoJSON,"nome"));
    }else{
        printf("Os dados de autenticacao estão incorretos!\n");
        return EXIT_FAILURE;
    }

    descritorServidor = configurarSocket(&enderecoServidor, "127.0.0.1", 1250);

    if (conectar(&enderecoServidor,descritorServidor)) {
        printf("Houve um erro na conexão com o servidor\n");
        return EXIT_FAILURE;
    }

    send(descritorServidor, solicitacaoJSON, TAMANHO_BUFFER, 0); //envia o nome para o servidor

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

