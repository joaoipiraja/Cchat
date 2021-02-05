#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <signal.h>

#define MAXIMO_USUARIOS 100
#define TAMANHO_BUFFER 2048
#define TAMANHO_NOME 32

static _Atomic unsigned int contarUsuarios = 0;
static int id = 10;

typedef struct{
    int id;
    char nome[TAMANHO_NOME];
    struct sockaddr_in endereco;
    int descritor;
} usuario;

usuario *usuarios[MAXIMO_USUARIOS];

//Multitasking = precisa utilizar uma fila
pthread_mutex_t UsuariosMutex = PTHREAD_MUTEX_INITIALIZER; //permite o processo de exclusão mutua das threads em fila

void sobrescrever_stdout() {
    printf("\r%s", "> ");
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

void mostrarEnderecoCliente(struct sockaddr_in endereco){
    printf("%d.%d.%d.%d",
           endereco.sin_addr.s_addr & 0xff,
           (endereco.sin_addr.s_addr & 0xff00) >> 8,
           (endereco.sin_addr.s_addr & 0xff0000) >> 16,
           (endereco.sin_addr.s_addr & 0xff000000) >> 24);
}

void adicionarUsuarioNaFila(usuario *cl){
    pthread_mutex_lock(&UsuariosMutex);

    for(int i=0; i < MAXIMO_USUARIOS; ++i){
        if(!usuarios[i]){
            usuarios[i] = cl;
            break;
        }
    }

    pthread_mutex_unlock(&UsuariosMutex);
}

void removerUsuariosFila(int id){

    //remover com o cliente com id da Fila

    pthread_mutex_lock(&UsuariosMutex);

    for(int i=0; i < MAXIMO_USUARIOS; ++i){
        if(usuarios[i]){
            if(usuarios[i]->id == id){
                usuarios[i] = NULL;
                break;
            }
        }
    }

    pthread_mutex_unlock(&UsuariosMutex);
}

void enviarMensagem(char *s, int id){
    //Envia um mensagem a todos os usuarios conectados, menos ao quem enviou
    pthread_mutex_lock(&UsuariosMutex);

    for(int i=0; i<MAXIMO_USUARIOS; ++i){
        if(usuarios[i]){
            if(usuarios[i]->id != id){
                if(write(usuarios[i]->descritor, s, strlen(s)) < 0){
                    perror("Houve um error em escrever no descritor");
                    break;
                }
            }
        }
    }

    pthread_mutex_unlock(&UsuariosMutex);
}




void removerUsuario(usuario *usr){

    close(usr->descritor);
    removerUsuariosFila(usr->id);
    free(usr);
    contarUsuarios--;
    pthread_detach(pthread_self());
}



void *conversarComUsuario(void *arg){
    char bufferSaida[TAMANHO_BUFFER];
    char nome[TAMANHO_NOME];
    int sair = 0;

    contarUsuarios++;
    usuario *usr = (usuario *)arg;

    if(recv(usr->descritor, nome, TAMANHO_NOME, 0) <= 0 || strlen(nome) <  2 || strlen(nome) >= TAMANHO_NOME-1){
        printf("Não colocou o nome.\n");
        sair = 1;
    } else{
        strcpy(usr->nome, nome);
        sprintf(bufferSaida, "%s entrou no chat\n", usr->nome);
        printf("%s", bufferSaida);
        enviarMensagem(bufferSaida, usr->id);
    }

    bzero(bufferSaida, TAMANHO_BUFFER); // coloca n bytes com valor zero

    while(1){
        if (sair) {
            break;
        }

        int recebido = recv(usr->descritor, bufferSaida, TAMANHO_BUFFER, 0);
        if (recebido > 0){
            if(strlen(bufferSaida) > 0){
                enviarMensagem(bufferSaida, usr->id);
                removerCaracteresVazios(bufferSaida, strlen(bufferSaida));
                printf("%s\n", bufferSaida);
            }
        } else if (recebido == 0 || strcmp(bufferSaida, "sair") == 0){
            sprintf(bufferSaida, "%s saiu do chat\n", usr->nome);
            printf("%s", bufferSaida);
            enviarMensagem(bufferSaida, usr->id);
            sair = 1;
        } else {
            printf("Error -1\n");
            sair = 1;
        }

        bzero(bufferSaida, TAMANHO_BUFFER);
    }

    //Exclui os usuarios da fila de execução paralela
    removerUsuario(usr);

    return NULL;
}

int criarNovoDialogoSimultaneo(pthread_t *novaThread, void *usr){
    return (pthread_create(novaThread, NULL, &conversarComUsuario, usr) != 0);
}

int aceitarConexao(int escutaDescritor, struct sockaddr_in *enderecoCliente){
    socklen_t t_aux = sizeof(enderecoCliente);
    return accept(escutaDescritor, (struct sockaddr*) enderecoCliente, &t_aux);
}


usuario * criarNovoUsuario(struct sockaddr_in endereco, int descritor){
    usuario *usr = (usuario *)malloc(sizeof(usuario));
    usr->endereco = endereco;
    usr->descritor = descritor;
    usr->id = id++;
    return usr;
}

int configurarSocket(struct sockaddr_in *enderecoSocket, const char *ip, int port){

    int aux = socket(AF_INET, SOCK_STREAM, 0);
    enderecoSocket->sin_family = AF_INET;
    enderecoSocket->sin_addr.s_addr = inet_addr(ip);
    enderecoSocket->sin_port = htons(port);
    return aux;
}


int main(){

    pthread_t thread;
    int escutaDescritor = 0, descritorNovaConexao = 0;
    struct sockaddr_in enderecoServidor;
    struct sockaddr_in enderecoCliente;

    escutaDescritor = configurarSocket(&enderecoServidor, "127.0.0.1", 1234);
    signal(SIGPIPE, SIG_IGN);


    if(bind(escutaDescritor, (struct sockaddr*)&enderecoServidor, sizeof(enderecoServidor)) < 0) {
        perror("ERROR: Socket binding failed");
        return EXIT_FAILURE;
    }

    if (listen(escutaDescritor, 10) < 0) {
        perror("ERROR: Socket listening failed");
        return EXIT_FAILURE;
    }

    printf("---\nC CHAT\n---\n");

    while(1){

        descritorNovaConexao = aceitarConexao(escutaDescritor,&enderecoCliente);

        if((contarUsuarios + 1) == MAXIMO_USUARIOS){
            printf("Número máximo de usuários atingido!");
            mostrarEnderecoCliente(enderecoCliente);
            printf(":%d\n", enderecoCliente.sin_port);
            close(descritorNovaConexao);
            continue;
        }

        usuario *usr = criarNovoUsuario(enderecoCliente, descritorNovaConexao);

        adicionarUsuarioNaFila(usr);

        if(criarNovoDialogoSimultaneo(&thread,(void*)usr)){
            printf("Error em criar uma thread\n");
        }

        sleep(1); //reduz o uso da CPU
    }

    return EXIT_SUCCESS;
}
