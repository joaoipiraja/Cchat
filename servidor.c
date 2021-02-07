//
// Created by João Victor Ipirajá de Alencar on 07/02/21.
//

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <signal.h>
#include "json-c/json.h"
#include <uuid/uuid.h>
#include <time.h>

//gcc servidor.c -ljson-c -luuid -o servidor

#define MAXIMO_USUARIOS 100
#define TAMANHO_BUFFER 2048
#define TAMANHO_NOME 32

//struct para
typedef struct{
    int id;
    char nome[TAMANHO_NOME];
    struct sockaddr_in endereco; //endereco do usuario
    int descritor; //funciona como um arquivo
} usuario;

static _Atomic unsigned int contarUsuarios = 0;
static int id = 10;
usuario *usuarios[MAXIMO_USUARIOS];

pthread_mutex_t UsuariosMutex = PTHREAD_MUTEX_INITIALIZER; //evita que duas ou mais threads tenham acesso ao mesmo recurso compartilhado


//----MANIPULAÇÃO DO BANCO DE DADOS USANDO .JSON ----

static struct json_object *usuarios_salvos;

struct json_object* getRegistrosSalvos(const char *fileName){

    FILE *fp = NULL;
    struct json_object *parsed_json;
    char buffer[1024] = "";

    fp = fopen(fileName,"r");
    fread(buffer,sizeof(buffer),1,fp);
    fclose(fp);

    if(strlen(buffer) > 0){ //caso o arquivo não esteja vazio
        parsed_json = json_tokener_parse(buffer); //converte o buffer do arquivo para json_object
    }else{
        parsed_json = json_object_new_array(); //inicializa a variável json_object como array de json_objects
    }

    return parsed_json;

}

void inicializar_banco_de_dados(){
    usuarios_salvos = getRegistrosSalvos("usuarios.json");
}


const char * extrairInformacao(const char *jsonString,const char *atributo ){

    struct json_object *json_convertido = json_tokener_parse((char *)jsonString);
    struct json_object *json_atributo;
    json_object_object_get_ex(json_convertido, atributo, &json_atributo);
    return json_object_get_string(json_atributo);

}


int validarUsuario(const char *jsonString){
    //1- O usuario nao existe/ 2- O usuario existe, mas a senha está incorreta/ 3- o usuario existe e a senha está correta
    int resposta = 1;
    const char *n =  extrairInformacao(jsonString, "nome");
    const char *s = extrairInformacao(jsonString, "senha");

    struct json_object *usuario;
    struct json_object *nome;
    struct json_object *senha;

    size_t n_usuarios = json_object_array_length(usuarios_salvos);
    size_t i;

    for (i = 0; i<n_usuarios; i++){
        usuario = json_object_array_get_idx(usuarios_salvos,i);
        json_object_object_get_ex(usuario, "nome", &nome);
        json_object_object_get_ex(usuario, "senha", &senha);

        if(strcmp(json_object_get_string(nome),n) == 0){
            break;
        }
    }


    if (strcmp(json_object_get_string(nome),n) == 0 && strcmp(json_object_get_string(senha),s) != 0){
        resposta = 2;
    }else if (strcmp(json_object_get_string(nome),n) == 0 && strcmp(json_object_get_string(senha),s) == 0){
        resposta = 3;
    }

    return resposta;
}


struct json_object* gerarTempo(){

    struct tm * timeinfo;
    time_t my_time;
    time (&my_time);
    timeinfo = localtime (&my_time);

    struct json_object *tempo = json_object_new_object();

    json_object_object_add(tempo, "hora", json_object_new_int(timeinfo->tm_hour));
    json_object_object_add(tempo, "minuto", json_object_new_int(timeinfo->tm_min));
    json_object_object_add(tempo, "dia", json_object_new_int(timeinfo->tm_mday));
    json_object_object_add(tempo, "mes", json_object_new_int(timeinfo->tm_mon+1));
    json_object_object_add(tempo, "ano", json_object_new_int(timeinfo->tm_year+1900));


    return tempo;
}

void gerarUUID(char *uuid_str){
    uuid_t uuid;
    uuid_generate_random(uuid);
    uuid_unparse_lower(uuid, uuid_str);
}


int adicionarUsuario(const char *jsonString){

    //recebe um json do tipo { "nome": "NOMEUSUARIO", "senha": "SENHADOUSUARIO" }

    int resposta = 0;
    const char *nome =  extrairInformacao(jsonString, "nome");
    const char *senha = extrairInformacao(jsonString, "senha");

    struct json_object *usuario;
    char uuid_str[36];
    if(strlen(nome) > 0 && strlen(senha) > 0 && validarUsuario(jsonString) == 1){ //Validação

        usuario = json_object_new_object();
        gerarUUID(uuid_str);

        printf("%s\n",uuid_str);

        json_object_object_add(usuario, "id", json_object_new_string(uuid_str));
        json_object_object_add(usuario, "nome", json_object_new_string(nome));
        json_object_object_add(usuario, "senha", json_object_new_string(senha));
        json_object_object_add(usuario, "instante", gerarTempo());

        json_object_array_add(usuarios_salvos,usuario);
        json_object_to_file("usuarios.json",usuarios_salvos);

        resposta = 1;
    }

    return resposta;

}


//--- FERRAMENTAS ADICIONAIS ---

void sobrescrever_stdout() {
    printf("\r%s", "> ");
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

void mostrarEnderecoCliente(struct sockaddr_in endereco){
    printf("%d.%d.%d.%d",
           endereco.sin_addr.s_addr & 0xff,
           (endereco.sin_addr.s_addr & 0xff00) >> 8,
           (endereco.sin_addr.s_addr & 0xff0000) >> 16,
           (endereco.sin_addr.s_addr & 0xff000000) >> 24);
}


//--- GERIR OS USUÁRIOS DO CHAT ---


usuario * criarNovoUsuario(struct sockaddr_in endereco, int descritor){
    usuario *usr = (usuario *)malloc(sizeof(usuario));
    usr->endereco = endereco;
    usr->descritor = descritor;
    usr->id = id++;
    return usr;
}


void adicionarUsuarioArray(usuario *cl){

    pthread_mutex_lock(&UsuariosMutex);

    for(int i=0; i < MAXIMO_USUARIOS; ++i){
        if(!usuarios[i]){
            usuarios[i] = cl;
            break;
        }
    }

    pthread_mutex_unlock(&UsuariosMutex);
}

void removerUsuarioArray(int id){

    //remover usuario apartir do seu id

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


void enviarMensagemParticular(const char *mensagem, int descritor){
    pthread_mutex_lock(&UsuariosMutex);

    if(write(descritor, (char *) mensagem, strlen(mensagem)) < 0){
        perror("Erro ao enviar mensagem!\n");
    }

    pthread_mutex_unlock(&UsuariosMutex);
}


void enviarMensagemParaOutros(char *mensagem, int id){
    //Envia um mensagem a todos os usuarios conectados, menos o com id informado
    pthread_mutex_lock(&UsuariosMutex);

    for(int i=0; i<MAXIMO_USUARIOS; ++i){
        if(usuarios[i]){
            if(usuarios[i]->id != id){
                if(write(usuarios[i]->descritor, mensagem, strlen(mensagem)) < 0){
                    perror("Erro ao enviar mensagem!\n");
                    break;
                }
            }
        }
    }

    pthread_mutex_unlock(&UsuariosMutex);
}

void removerUsuario(usuario *usr){

    close(usr->descritor);
    removerUsuarioArray(usr->id);
    free(usr);
    contarUsuarios--;
    pthread_detach(pthread_self());
}

//--- ROTINA DE CONVERSA CRIADA PARA CADA USUÁRIO ---

void *conversarComUsuario(void *arg){
    char bufferSaida[TAMANHO_BUFFER];
    char autenticaoUsuario[TAMANHO_BUFFER];
    int sair = 0;

    contarUsuarios++;
    usuario *usr = (usuario *)arg;

    if(recv(usr->descritor,autenticaoUsuario, TAMANHO_BUFFER, 0) <= 0){
        printf("Houve um problema na autenticação do usuario!");
        sair = 1;
    } else{

        int codigoValidacao = validarUsuario((const char *)&autenticaoUsuario);

        strcpy(usr->nome,extrairInformacao((const char *)&autenticaoUsuario, "nome"));

        if(codigoValidacao  == 3){
            sprintf(bufferSaida, "%s entrou no chat\n", usr->nome);
            printf("%s", bufferSaida);
            enviarMensagemParaOutros(bufferSaida, usr->id);
        }else if(codigoValidacao  == 2){

            enviarMensagemParticular("A senha está incorreta!(ACESSO NEGADO)\n", usr->descritor);
            sair = 1;

        }else if(codigoValidacao  == 1){
            adicionarUsuario((const char *)&autenticaoUsuario);
            sprintf(bufferSaida, "%s, seja bem vindo(a)!\n", usr->nome);
            printf("%s", bufferSaida);
            enviarMensagemParaOutros(bufferSaida, usr->id) ;
        }

    }

    bzero(bufferSaida, TAMANHO_BUFFER); //limpa o buffer
    bzero(autenticaoUsuario, TAMANHO_BUFFER);

    while(1){
        if (sair) {
            break;
        }

        int recebido = recv(usr->descritor, bufferSaida, TAMANHO_BUFFER, 0);
        if (recebido > 0){
            if(strlen(bufferSaida) > 0){
                enviarMensagemParaOutros(bufferSaida, usr->id);
                removerQuebraDeLinha(bufferSaida, strlen(bufferSaida));
                printf("%s\n", bufferSaida);
            }
        } else if (recebido == 0 || strcmp(bufferSaida, "sair") == 0){
            sprintf(bufferSaida, "%s saiu do chat\n", usr->nome);
            printf("%s", bufferSaida);
            enviarMensagemParaOutros(bufferSaida, usr->id);
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

//--- CONFIGURAÇÕES INICIAIS ---

int criarNovoDialogoSimultaneo(pthread_t *novaThread, void *usr){
    return (pthread_create(novaThread, NULL, &conversarComUsuario, usr) == 0);
}

int aceitarConexao(int escutaDescritor, struct sockaddr_in *enderecoCliente){
    socklen_t t_aux = sizeof(enderecoCliente);
    return accept(escutaDescritor, (struct sockaddr*) enderecoCliente, &t_aux);
}

int configurarSocket(struct sockaddr_in *enderecoSocket, const char *ip, int port){
    enderecoSocket->sin_family = AF_INET;
    enderecoSocket->sin_addr.s_addr = inet_addr(ip);
    enderecoSocket->sin_port = htons(port);
    return socket(AF_INET, SOCK_STREAM, 0);
}


int main(){

    pthread_t thread;
    int escutaDescritor = 0, descritorNovaConexao = 0;
    struct sockaddr_in enderecoServidor;
    struct sockaddr_in enderecoCliente;

    inicializar_banco_de_dados();

    escutaDescritor = configurarSocket(&enderecoServidor, "127.0.0.1", 1254);
    signal(SIGPIPE, SIG_IGN);


    if(bind(escutaDescritor, (struct sockaddr*)&enderecoServidor, sizeof(enderecoServidor)) < 0) {
        perror("Não foi possivel vincular o socket à porta");
        return EXIT_FAILURE;
    }

    if (listen(escutaDescritor, 10) < 0) {
        perror("Não foi possivel em ativar espera por novas conexões");
        return EXIT_FAILURE;
    }

    printf("---\nC CHAT\n---\n");

    while(1){

        descritorNovaConexao = aceitarConexao(escutaDescritor,&enderecoCliente);

        if((contarUsuarios + 1) == MAXIMO_USUARIOS){
            printf("Número máximo de usuários atingido!");
            close(descritorNovaConexao);
            continue;
        }else{
            mostrarEnderecoCliente(enderecoCliente);
            printf(":%d\n", enderecoCliente.sin_port);
        }

        usuario *usr = criarNovoUsuario(enderecoCliente, descritorNovaConexao);

        adicionarUsuarioArray(usr);

        if(!criarNovoDialogoSimultaneo(&thread,(void*)usr)){
            printf("Error em criar uma thread\n");
        }

        sleep(1); //reduz o uso da CPU
    }

    return EXIT_SUCCESS;
}
