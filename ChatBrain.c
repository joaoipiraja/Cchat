


#include "model.h"
#include <stdio.h>


// gcc -Imodel  ChatBrain.c -ljson-c -luuid -o chatBrain

int main() {
    printf("Teste\n");
    inicializar();

    /*if(adicionarUsuario("mario","1234")){
        printf("Seu registro foi salvo!\n");
    }else{
        printf("Houve um erro na hora de salvar!\n");
    }*/

    struct json_object *usuario = validarUsuario("joao","1234");

    if(adicionarMensagem(usuario,"Conteudo da mensagem")){
        printf("Sua mensagem foi enviada!\n");
    }

    showChat(usuario);

   /* char buffer[1024];

    struct json_object *parsed_json;
    struct json_object *name;
    struct json_object *age;
    struct json_object *friends;
    struct json_object *friend;

    size_t n_friends;
    size_t i;

    fp = fopen("test.json","r");
    fread(buffer,1024,1,fp);
    fclose(fp);

    parsed_json = json_tokener_parse(buffer);
    json_object_object_get_ex(parsed_json, "name", &name);
    json_object_object_get_ex(parsed_json, "age", &age);
    json_object_object_get_ex(parsed_json, "friends", &friends);

    printf("Name: %s\n", json_object_get_string(name));
    printf("Age: %d\n", json_object_get_int(age));

    n_friends = json_object_array_length(friends);

    for (i = 0; i<n_friends; i++){
        friend = json_object_array_get_idx(friends,i);
        printf("%lu. %s\n",i+1, json_object_get_string(friend));
    }


    struct json_object *jobj;
    const char *question = "Mum, clouds hide alien spaceships don't they ?";
    const char *answer = "Of course not! (\"sigh\")";
    json_object *jarray = json_object_new_array();

    uuid_t uuid;
    uuid_generate_random(uuid);
    char uuid_str[37];
    uuid_unparse_lower(uuid, uuid_str);



    json_object *jstring1 = json_object_new_string("c");
    json_object *jstring2 = json_object_new_string("c++");
    json_object *jstring3 = json_object_new_string("php");
    json_object_array_add(jarray,jstring1);
    json_object_array_add(jarray,jstring2);
    json_object_array_add(jarray,jstring3);

    jobj = json_object_new_object();
    json_object_object_add(jobj, "id", json_object_new_string(uuid_str));
    json_object_object_add(jobj, "question", json_object_new_string(question));
    json_object_object_add(jobj, "answer", json_object_new_string(answer));
    json_object_object_add(jobj,"Categories", jarray);

    json_object_to_file("test.json",jobj);

    */

}