# Em manutenção! ⚠️
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


### Persistindo dados de autenticação
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

## 👨🏽‍💻 Entendendo o código

#### [<img src="explicacaoIlustrada/explicacao1.png"  />](explicacao1.png)

```C
int configurarSocket(struct sockaddr_in *enderecoSocket, const char *ip, int port){

    int aux = socket(AF_INET, SOCK_STREAM, 0);
    enderecoSocket->sin_family = AF_INET;
    enderecoSocket->sin_addr.s_addr = inet_addr(ip);
    enderecoSocket->sin_port = htons(port);
    return aux;
}
```
#### Servidor:
1 - Configura o socket preenchendo a struct sockaddr_in

```C
  escutaDescritor = configurarSocket(&enderecoServidor, "127.0.0.1", 1247);
```

2 - Vincular o socket à porta 
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
#### Cliente:

1- Configura o socket preenchendo a struct sockaddr_in

```C
    descritorServidor = configurarSocket(&enderecoServidor, "127.0.0.1", 1247);
```

#### [<img src="explicacaoIlustrada/explicacao2.png"/>](explicacao2.png)
#### Cliente:
```C
if (conectar(&enderecoServidor,descritorServidor)) {
        printf("Houve um erro na conexão com o servidor\n");
        return EXIT_FAILURE;
    }
```
#### Servidor:
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

        adicionarUsuarioNaFila(usr);

        if(criarNovoDialogoSimultaneo(&thread,(void*)usr)){
            printf("Error em criar uma thread\n");
        }

        sleep(1); //reduz o uso da CPU
    }
    
```


## Screenshots

[<img src="screenshots/screenshot2.png" width="500" />](screenshot2.png)
[<img src="screenshots/screenshot1.png" width="500" />](screenshot1.png)
[<img src="screenshots/screenshot3.png" width="500" />](screenshot3.png)
