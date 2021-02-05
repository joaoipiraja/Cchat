//
// Created by João Victor Ipirajá de Alencar on 31/01/21.
//


#include "json-c/json.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <uuid/uuid.h>
#include <time.h>


static struct json_object *usuarios;
static struct json_object *mensagens;

struct json_object* validarUsuario(const char *n,const char *p){

    struct json_object *usuario;
    struct json_object *nome;
    struct json_object *senha;

    size_t n_usuarios = json_object_array_length(usuarios);
    size_t i;

    for (i = 0; i<n_usuarios; i++){
        usuario = json_object_array_get_idx(usuarios,i);

        json_object_object_get_ex(usuario, "nome", &nome);
        json_object_object_get_ex(usuario, "senha", &senha);

        if(strcmp(json_object_get_string(nome),n) == 0 && strcmp(json_object_get_string(senha),p) == 0){
            return usuario;
        }

    }
    return NULL;
}


void showChat(struct json_object *usuario_atual){

    struct json_object *mensagem;
    struct json_object *id_atual;
    struct json_object *id_remetente;
    struct json_object *conteudo_mensagem;
    struct json_object *nome_usuario;
    struct json_object *tempo;

    char mensagem_string[1024] = "";


    if(usuario_atual != NULL){

        json_object_object_get_ex(usuario_atual, "id", &id_atual);
        json_object_object_get_ex(usuario_atual, "nome", &nome_usuario);


        size_t n_mensagens = json_object_array_length(mensagens);
        size_t i;

        for (i = 0; i<n_mensagens; i++){
            mensagem = json_object_array_get_idx(mensagens,i);

            json_object_object_get_ex(mensagem, "id", &id_remetente);
            json_object_object_get_ex(mensagem, "conteudo", &conteudo_mensagem);
            json_object_object_get_ex(mensagem, "tempo", &tempo);

            strcpy("\n",mensagem_string);
            strcat(json_object_get_string(tempo),mensagem_string);
            strcat("\n",mensagem_string);
            if(strcmp(json_object_get_string(id_remetente),json_object_get_string(id_atual)) == 0){
                strcat("Você:\n",mensagem_string);
            }else{
                strcat(json_object_get_string(nome_usuario),mensagem_string);
                strcat(":\n",mensagem_string);
            }
            strcat(json_object_get_string(conteudo_mensagem),mensagem_string);
            strcat("\n\t",mensagem_string);
            printf("%s",mensagem_string);

        }

    }


}
struct json_object* getRegistrosSalvos(const char *fileName){

    FILE *fp = NULL;
    struct json_object *parsed_json;
    char buffer[1024] = "";

    fp = fopen(fileName,"r");
    fread(buffer,sizeof(buffer),1,fp);
    fclose(fp);

    if(strlen(buffer) > 0){
        parsed_json = json_tokener_parse(buffer);
    }else{
        parsed_json = json_object_new_array();
    }


    return parsed_json;

}

void inicializar(){

    usuarios = getRegistrosSalvos("usuarios.json");
    mensagens = getRegistrosSalvos("mensagens.json");

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

int adicionarUsuario(const char *nome, const char *senha){
    struct json_object *usuario;
    char uuid_str[36];

    if(strlen(nome) > 0 && strlen(senha) > 0 && validarUsuario(nome,senha) == NULL){ //Validação

        usuario = json_object_new_object();
        gerarUUID(uuid_str);

        printf("%s\n",uuid_str);

        json_object_object_add(usuario, "id", json_object_new_string(uuid_str));
        json_object_object_add(usuario, "nome", json_object_new_string(nome));
        json_object_object_add(usuario, "senha", json_object_new_string(senha));

        json_object_array_add(usuarios,usuario);

        json_object_to_file("usuarios.json",usuarios);

        return 1;
    }

    return 0;


}



int adicionarMensagem(struct json_object *usuario,const char *conteudo){
    struct json_object *idRemetente;
    struct json_object *mensagem;
    char uuid_str[36];

    if(usuario != NULL){
        json_object_object_get_ex(usuario, "id", &idRemetente);
        mensagem = json_object_new_object();

        gerarUUID(uuid_str);

        printf("%s\n",json_object_get_string(idRemetente));

        json_object_object_add(mensagem, "id", json_object_new_string(uuid_str));
        json_object_object_add(mensagem, "idRemetente", idRemetente);
        json_object_object_add(mensagem, "conteudo", json_object_new_string(conteudo));
        json_object_object_add(mensagem, "tempo", gerarTempo());
        json_object_array_add(mensagens,mensagem);

        json_object_to_file("mensagens.json",mensagens);

        return 1;
    }
    return 0;

}





