//
// Created by João Victor Ipirajá de Alencar on 29/01/21.
//

#ifndef CCHAT_MODEL_H
#define CCHAT_MODEL_H
#endif //CCHAT_MODEL_H



struct usuario{
    int id;
    char nome[20];
    char senha[10];
};

struct mensagem{
    int id;
    int id_remetente;
    char mensagem[100];
    char tempo[17];
};

