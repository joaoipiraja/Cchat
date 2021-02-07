[<img src="logo.png" width="120" />](logo.png)
# Cchat
Projeto- Introdução à programação- semestre 2021.1
## Objetivo
Criar um chat utilizando o paradigma de um socket TCP/IP multithread (pthread/pthread_mutex_t)

### 💻 Executar
#### gcc servidor.c -ljson-c -luuid -o servidor 
#### gcc cliente.c -ljson-c -o cliente

## Dependências:
[json-c](https://github.com/json-c/json-c)
| [libuuid](https://linux.die.net/man/3/libuuid)

## 👨🏽‍💻 Entendendo o código

### Persistindo dados de autenticação
#### [<img src="explicacaoIlustrada/5.png"  />](5.png)

#### formato:
```json

{
"id":"baa5f4eb-1d99-48ad-853d-b417a1942952",
"nome":"joao",
"senha":"1234",
"instante":{
  "hora":11,
  "minuto":48,
  "dia":6,
  "mes":2,
  "ano":2021
  }
}

```

#### Recuperando dados do arquivo usuarios.json
```C
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

```
#### Validação usuário
- 1 > O usuario nao existe
- 2 > O usuario existe, mas a senha está incorreta
- 3 > O usuario existe e a senha está correta

```C
int validarUsuario(const char *jsonString){

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
```
#### Adicionando novos usuários

```C

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

```


#### [<img src="explicacaoIlustrada/1.png"/>](1.png)


#### Cliente:

Configura o socket preenchendo a struct sockaddr_in

```C
    descritorServidor = configurarSocket(&enderecoServidor, "127.0.0.1", 1247);
```

#### Servidor:
Configura o socket preenchendo a struct sockaddr_in

```C
  escutaDescritor = configurarSocket(&enderecoServidor, "127.0.0.1", 1247);
```

Vincular o socket à porta 
```C
 if(bind(escutaDescritor, (struct sockaddr*)&enderecoServidor, sizeof(enderecoServidor)) < 0) {
        perror("Não foi possivel vincular o socket à porta");
        return EXIT_FAILURE;
    }
```
3 - Colocar o socket em modo de espera para possíveis conexões
```C
 if (listen(escutaDescritor, 10) < 0) {
        perror("Não foi possivel em ativar espera por novas conexões");
        return EXIT_FAILURE;
    }
```

#### [<img src="explicacaoIlustrada/2.png"  />](2.png)
#### Cliente:
```C
if (conectar(&enderecoServidor,descritorServidor)) {
        printf("Houve um erro na conexão com o servidor\n");
        return EXIT_FAILURE;
    }
```
#### Servidor:

```C
typedef struct{
    int id;
    char nome[TAMANHO_NOME];
    struct sockaddr_in endereco;
    int descritor;
} usuario;

usuario *usuarios[MAXIMO_USUARIOS];

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
```

```C
int criarNovoDialogoSimultaneo(pthread_t *novaThread, void *usr){
    return (pthread_create(novaThread, NULL, &conversarComUsuario, usr) == 0);
}
```
```C
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

        adicionarUsuarioArray(usr);

        if(criarNovoDialogoSimultaneo(&thread,(void*)usr)){
            printf("Error em criar uma thread\n");
        }

        sleep(1); //reduz o uso da CPU
    }
    
```
#### [<img src="explicacaoIlustrada/3.png"  />](3.png)
#### Cliente:

```C
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
```
```C
    send(descritorServidor, solicitacaoJSON, TAMANHO_BUFFER, 0); //envia o nome para o servidor
```
#### Servidor:
```C
void enviarMensagemParticular(const char *mensagem, int descritor){
    pthread_mutex_lock(&UsuariosMutex);

    if(write(descritor, (char *) mensagem, strlen(mensagem)) < 0){
        perror("Erro ao enviar mensagem!\n");
    }

    pthread_mutex_unlock(&UsuariosMutex);
}

```
```C
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

```
```C
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
        printf("%s\n",autenticaoUsuario);

        int codigoValidacao = validarUsuario((const char *)&autenticaoUsuario);
        printf("%d\n",codigoValidacao);

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

```


#### [<img src="explicacaoIlustrada/4.png"  />](4.png)
#### Cliente:
```C
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
```
```C
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
```
```C
   if(criarThread(&enviarMensagemThread, (void *) enviarMensagem)){
        printf("Error em criar uma thread para enviar as mensagens\n");
        return EXIT_FAILURE;
    }

    if(criarThread(&receberMensagemThread, (void *)receberMensagem)){
        printf("Error em criar uma thread para receber as mensagens\n");
        return EXIT_FAILURE;
    }
    
```
#### Servidor:

```C
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


```
```C
void removerUsuario(usuario *usr){

    close(usr->descritor);
    removerUsuarioArray(usr->id);
    free(usr);
    contarUsuarios--;
    pthread_detach(pthread_self());
}

```
```C
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

```

## Screenshots

[<img src="screenshots/screenshot2.png" width="500" />](screenshot2.png)
[<img src="screenshots/screenshot1.png" width="500" />](screenshot1.png)
[<img src="screenshots/screenshot3.png" width="500" />](screenshot3.png)
