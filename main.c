#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "estruturas.h"
#define MAX 500

//------------------------------------------------- ESTATISTICAS -------------------------------------------------------


int percentagem_pdis(Lista_pdis_aluno viagem){
    int contador=0;
    Lista_pdis_aluno aux_pdi=viagem->next;
    while(aux_pdi!=NULL){
        contador+=aux_pdi->informacao->n_inscritos;
        aux_pdi=aux_pdi->next;
    }
    return contador;
}

int percentagem_favoritos(Lista_alunos alunos, Lista_locais_aluno locais_aluno){
    Lista_PdIs aux_pdis;
    Lista_locais_aluno aux_locais;
    int contador=0, ver;
    Lista_alunos aux_alunos=alunos->next;

    while(aux_alunos!=NULL) {
        aux_locais=locais_aluno->next;
        ver=0;
        while (aux_locais != NULL) {
            aux_pdis=aux_alunos->viagem->informacao->next;
            while(aux_pdis!=NULL){
                if(strcmp(aux_pdis->nome_local, aux_locais->informacao->nome)==0){
                    contador++;
                    ver=1;
                    break;
                }
                aux_pdis=aux_pdis->next;
            }
            if(ver==1)
                break;
            aux_locais=aux_locais->next;
        }
        aux_alunos=aux_alunos->next;
    }
    return contador;
}

double percentagem_pdi_hot(char hot[], char local[], Lista_alunos alunos){
    int contador=0;
    alunos=alunos->next;
    Lista_PdIs aux_pdis;
    while (alunos!=NULL){
        aux_pdis=alunos->viagem->informacao;
        if(pesquisa_lista_PdIs(aux_pdis, hot, local)!=NULL)
            contador++;
        alunos=alunos->next;
    }
    return contador;
}


//------------------------------------------------- PROTECOES -------------------------------------------------------

int verifica_strings_sem_numeros(char input[]){
    int i=0;
    while(input[i]!='\0'){
        if((input[i]<65 || input[i]>122) && input[i]!=' ')
            return 0;
        i++;
    }
    return 1;
}

int verifica_string(char input[]){
    int i=0;
    while(input[i]!='\0'){
        if((input[i]<48 || (input[i]>57 && input[i]<65) || input[i]>122) && input[i]!=' ')
            return 0;
        i++;
    }
    return 1;
}

int verifica_data(char input[]){
    int i=0;
    while(input[i]!='\0'){
        printf("%c\n", input[i]);
        if(i==2 || i==5){
            if(input[i]!='/')
                return 0;
        }
        else{
            if((input[i]<48 || input[i]>57) && input[i]!='\0'){
                return 0;
            }
        }
        i++;
    }
    if(i<10)
        return 0;
    return 1;
}

int verifica_telefone(char input[]){
    int i=0;
    while(input[i]!='\0'){
        if(input[i]<48 || input[i]>57)
            return 0;
        i++;
    }
    if(i<9)
        return 0;
    else
        return 1;
}

int verfica_inteiros(char input[]){
    int i=0;
    while(input[i]!='\0' && i!=1){
        if(input[i]<48 || input[i]>57)
            return 0;
        i++;
    }
    return 1;
}


//------------------------------------------------- FUNCOES AUXILIARES -------------------------------------------------------
char * fgets_aux(char * dados, int size, FILE *file){
    fflush(stdin);
    char *res = fgets(dados, size, file);
    if (res != NULL) {
        for (int i = 0; i < strlen(dados); ++i) {
            if (dados[i] == '\n') {
                dados[i] = '\0';
            }
        }
    }
    return res;
}

int get_n_utilizadores(Lista_alunos alunos){
    int contador=0;
    while(alunos->next!=NULL){
        contador++;
        alunos=alunos->next;
    }
    return contador;
}

int get_n_inscritos(Lista_locais locais){
    Lista_locais aux_local=locais->next;
    Lista_PdIs aux_pdi;
    int contador=0;
    while(aux_local!=NULL){
        aux_pdi=aux_local->lista_PdIs_locais;
        while(aux_pdi!=NULL){
            contador+=aux_pdi->n_inscritos;
            aux_pdi=aux_pdi->next;
        }
        aux_local=aux_local->next;
    }
}

//------------------------------------------------- FUNCOES SORT LOCAIS E PDIS -------------------------------------------------------

/* function to swap data of two nodes a and b*/
void swap_locais(Lista_locais a, Lista_locais b)
{
    Lista_locais temp = a;
    a=b;
    b=temp;
}

void bubbleSort_locais(Lista_locais inicio)
{
    int swapped, i;
    Lista_locais ptr1;
    Lista_locais lptr = NULL;

    /* Checking for empty list */
    if (inicio == NULL)
        return;

    do
    {
        swapped = 0;
        ptr1 = inicio;
        while (ptr1->next != lptr)
        {
            if (ptr1->n_inscritos > ptr1->next->n_inscritos)
            {
                swap_locais(ptr1, ptr1->next);
                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    }
    while (swapped);
}

/* function to swap data of two nodes a and b*/
void swap_pdis(Lista_PdIs a, Lista_PdIs b)
{
    Lista_PdIs temp = a;
    a=b;
    b=temp;
}

void bubbleSort_pdis(Lista_PdIs inicio)
{
    int swapped, i;
    Lista_PdIs ptr1;
    Lista_PdIs lptr = NULL;

    /* Checking for empty list */
    if (inicio == NULL)
        return;

    do
    {
        swapped = 0;
        ptr1 = inicio;
        while (ptr1->next != lptr)
        {
            if (ptr1->n_inscritos > ptr1->next->n_inscritos)
            {
                swap_pdis(ptr1, ptr1->next);
                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    }
    while (swapped);
}


//------------------------------------------------- FUNCOES ALUNOS -------------------------------------------------------
Lista_locais_aluno cria_lista_locais_alunos (void) {
    Lista_locais_aluno aux;
    aux = (Lista_locais_aluno) malloc (sizeof (Locais_aluno));
    Lista_locais loca_aux=(Lista_locais)malloc(sizeof(Local));
    if (aux != NULL) {
        strcpy(loca_aux->nome,"NULL");
        aux->informacao=loca_aux;
        aux->next=NULL;
    }
    return aux;
}

Lista_pdis_aluno cria_lista_pdis_alunos (void) {
    Lista_pdis_aluno aux;
    aux = (Lista_pdis_aluno) malloc (sizeof (Pdis_aluno));
    Lista_PdIs pdi_aux=(Lista_PdIs)malloc(sizeof(PdI));
    if (aux != NULL) {
        strcpy(pdi_aux->nome,"NULL");
        aux->informacao=pdi_aux;
        aux->next=NULL;
    }
    return aux;
}

Lista_alunos cria_lista_alunos (void) {
    Lista_alunos aux;
    aux = (Lista_alunos) malloc (sizeof (Aluno));
    if (aux != NULL) {
        strcpy(aux->nome, "NULL");
        strcpy(aux->morada, "NULL");
        strcpy(aux->data_nasc, "NULL");
        aux->telefone = 0;
        aux->lista_locais_alunos = NULL;
        aux->lista_PdIs_alunos = NULL;
        aux->n_locais = 0;
        strcpy(aux->PdI_hot, "NULL");
        aux->next = NULL;
    }
    return aux;
}

int procura_lista_alunos (Lista_alunos lista, char chave[], Lista_alunos *ant, Lista_alunos *actual) {
    *ant = lista;
    *actual = lista->next;
    while ((*actual) != NULL && strcmp((*actual)->nome, chave)<=0) {
        if(strcmp((*actual)->nome, chave)==0)
            return 1;
        *ant = *actual;
        *actual = (*actual)->next;
    }
    if ((*actual) != NULL && strcmp((*actual)->nome, chave)!=0) {
        *actual = NULL;   /* Se elemento nÃƒÂ£o encontrado*/
        return 0;
    }
}

int insere_lista_alunos (Lista_alunos lista, char nome[], char morada[], char data_nasc[], int telefone, char PdI_hot[], int n_locais) {
    Lista_alunos no;
    Lista_alunos ant, inutil;
    no = (Lista_alunos) malloc (sizeof (Aluno));
    if (no != NULL) {
        if(procura_lista_alunos (lista, nome, &ant, &inutil)==0){
            strcpy(no->nome,nome);
            strcpy(no->morada,morada);
            strcpy(no->data_nasc, data_nasc);
            no->telefone = telefone;
            no->n_locais=n_locais;
            strcpy(no->PdI_hot,"NULL");
            strcpy(no->local_hot,"NULL");
            no->lista_locais_alunos=cria_lista_locais_alunos();
            no->lista_PdIs_alunos=cria_lista_pdis_alunos();
            no->viagem=cria_lista_pdis_alunos();
            no->next = ant->next;
            ant->next = no;
            return 1;
        }
        else{
            free(no);
            return 0;
        }
    }
}

Lista_locais_aluno procura_lista_locais_aluno(Lista_locais_aluno lista_locais_aluno, char nome[], Lista_locais_aluno *ant, Lista_locais_aluno *actual){
    *ant = lista_locais_aluno;
    *actual = lista_locais_aluno->next;
    while ((*actual) != NULL && strcmp((*actual)->informacao->nome, nome)<=0){
        if(strcmp((*actual)->informacao->nome, nome)==0)
            return *actual;
        *ant = *actual;
        *actual = (*actual)->next;
    }
    if ((*actual) != NULL && strcmp((*actual)->informacao->nome, nome)!=0) {
        *actual = NULL;   /* Se elemento nÃƒÂ£o encontrado*/
        return *actual;
    }
}

int insere_locais_aluno(Lista_locais ponteiro_local, Lista_locais_aluno lista_locais_aluno, char nome[]){
    Lista_locais_aluno no;
    Lista_locais_aluno ant, inutil;
    no=(Lista_locais_aluno) malloc (sizeof(Locais_aluno));
    if(no!=NULL){
        if(procura_lista_locais_aluno(lista_locais_aluno, nome, &ant, &inutil)==NULL){
            ponteiro_local->n_inscritos++;
            no->informacao=ponteiro_local;
            no->next = ant->next;
            ant->next = no;
            return 1;
        }
        else{
            free(no);
            return 0;
        }
    }
}

int elimina_lista_locais_aluno (Lista_locais_aluno lista, char nome[]){
    Lista_locais_aluno ant;
    Lista_locais_aluno actual;
    procura_lista_locais_aluno (lista, nome, &ant, &actual);
    if (actual != NULL) {
        actual->informacao->n_inscritos--;
        ant->next = actual->next;
        free (actual);
        return 1;
    }
    return 0;
}

Lista_pdis_aluno procura_lista_Pdis_aluno(Lista_pdis_aluno lista_pdis_aluno, char nome[], char local[], Lista_pdis_aluno *ant, Lista_pdis_aluno *actual){
    *ant = lista_pdis_aluno;
    *actual = lista_pdis_aluno->next;
    while ((*actual) != NULL && strcmp((*actual)->informacao->nome, nome)<=0){
        if(strcmp((*actual)->informacao->nome, nome)==0 && strcmp((*actual)->informacao->nome_local, local)==0)
            return *actual;
        *ant = *actual;
        *actual = (*actual)->next;
    }
    if ((*actual) != NULL && strcmp((*actual)->informacao->nome, nome)!=0) {
        *actual = NULL;   /* Se elemento nÃƒÂ£o encontrado*/
        return *actual;
    }
}

int insere_pdis_aluno(Lista_PdIs ponteiro_pdi, Lista_pdis_aluno lista_pdIs_aluno, char nome[], char local[]){
    Lista_pdis_aluno no;
    Lista_pdis_aluno ant, inutil;
    no=(Lista_pdis_aluno) malloc(sizeof(Lista_PdIs));
    if(no!=NULL){
        if (procura_lista_Pdis_aluno(lista_pdIs_aluno, nome, local, &ant, &inutil)==NULL){
            ponteiro_pdi->n_inscritos++;
            no->informacao=ponteiro_pdi;
            no->next = ant->next;
            ant->next = no;
            return 1;
        } else{
            free(no);
            return 0;
        }
    }

}

int elimina_lista_pdis_aluno (Lista_pdis_aluno lista, char nome[], char local[])
{
    Lista_pdis_aluno ant;
    Lista_pdis_aluno actual;
    procura_lista_Pdis_aluno (lista, nome, local, &ant, &actual);
    if (actual != NULL) {
        actual->informacao->n_inscritos--;
        ant->next = actual->next;
        free (actual);
        return 1;
    }
    return 0;
}

int lista_vazia_alunos(Lista_alunos lista) {
    return (lista->next == NULL ? 1 : 0);
}

Lista_alunos destroi_lista_alunos (Lista_alunos lista) {
    Lista_alunos temp_ptr;
    while (lista_vazia_alunos (lista) == 0) {
        temp_ptr = lista;
        lista= lista->next;
        free (temp_ptr);
    }
    free(lista);
    return NULL;
}

Lista_alunos pesquisa_lista_alunos(Lista_alunos lista, char *nome) {
    Lista_alunos ant;
    Lista_alunos actual;
    procura_lista_alunos (lista, nome, &ant, &actual);
    return (actual);
}



void imprime_lista_alunos (Lista_alunos lista) {
    Lista_alunos l = lista->next; /* Salta o header */
    while (l) {
        printf("PRINT:  %s \n", l->nome);
        l=l->next;
    }
}

void insere_pdis_viagem(Lista_PdIs lista_pdis, Lista_pdis_aluno viagem, char pdi_hot[], char local[], int contador){
    if(strcmp(pdi_hot, "NULL")!=0)
        insere_pdis_aluno(lista_pdis, viagem, pdi_hot, local);
    Lista_PdIs aux=lista_pdis;
    bubbleSort_pdis(aux);
    while(contador!=3 && aux!=NULL){
        int res=insere_pdis_aluno(aux, viagem, aux->nome, aux->nome_local);
        if(res==1)
            contador++;
        aux=aux->next;
    }
}

void gera_viagem(Lista_locais_aluno locais_aluno, char pdi_hot[], char local[], Lista_pdis_aluno pdis_aluno, Lista_pdis_aluno viagem){
    Lista_locais_aluno aux_local=locais_aluno->next;
    Lista_locais_aluno local_hot=NULL;
    Lista_PdIs aux_pdis, pdis_locais, ant, actual, ver;
    int verifica;

    if(viagem->next!=NULL) {
        printf("entrou\n");
        if (strcmp(viagem->next->informacao->nome, pdi_hot) == 0)
            return;
    }

    //HOT
    if(strcmp(pdi_hot, "NULL")!=0){
        while(aux_local!=NULL){
            aux_pdis=procura_lista_PdIs(aux_local->informacao->lista_PdIs_locais, pdi_hot, local, &ant, &actual);
            if(aux_pdis!=NULL){
                local_hot=aux_local;
                break;
            }
            aux_local=aux_local->next;
        }
    }

    if(local_hot!=NULL){
        aux_pdis=local_hot->informacao->lista_PdIs_locais->next;
        bubbleSort_pdis(aux_pdis);
        insere_pdis_viagem(aux_pdis, viagem, pdi_hot, local_hot->informacao->nome, 0);
    }

    //favoritos
    int contador=0;
    aux_local=locais_aluno->next;

    while(aux_local!=NULL){
        if(local_hot==NULL  || strcmp(aux_local->informacao->nome,local_hot->informacao->nome)!=0){
            aux_pdis=pdis_aluno->informacao->next;
            while(aux_pdis!=NULL && contador!=3){
                pdis_locais=aux_local->informacao->lista_PdIs_locais->next;
                ver=procura_lista_PdIs(pdis_locais, aux_pdis->nome, aux_pdis->nome_local, &ant, &actual);
                if(ver!=NULL){
                    pdis_locais=aux_local->informacao->lista_PdIs_locais;
                    verifica=insere_pdis_aluno(pdis_locais, viagem, aux_pdis->nome, aux_pdis->nome_local);
                    if(verifica==1)
                        contador++;
                }
                aux_pdis=aux_pdis->next;
            }
            pdis_locais=aux_local->informacao->lista_PdIs_locais->next;
            insere_pdis_viagem(pdis_locais, viagem, "NULL", "NULL", contador);
        }
        aux_local=aux_local->next;
    }
    /*free(local_hot);
    free(aux_local);
    free(aux_pdis);
    free(aux_pdis);
    free(ant);
    free(actual);*/
}



//------------------------------------------------- FUNCOES LOCAIS -------------------------------------------------------

Lista_locais cria_lista_locais (void) {
    Lista_locais aux;
    aux = (Lista_locais) malloc (sizeof (Local));
    if (aux != NULL) {
        strcpy(aux->nome, "NULL");
        strcpy(aux->tipo, "NULL");
        aux->lista_PdIs_locais=NULL;
        aux->next = NULL;
    }
    return aux;
}

Lista_locais procura_lista_locais (Lista_locais lista, char chave[], Lista_locais *ant, Lista_locais *actual) {
    *ant = lista;
    *actual = lista->next;
    int res;
    while ((*actual) != NULL && (res = strcmp((*actual)->nome, chave))<=0) {
        if(res==0){
            return *actual;
        }
        *ant = *actual;
        *actual = (*actual)->next;
    }
    if ((*actual) != NULL && (*actual)->nome != chave)
        *actual = NULL;   /* Se elemento nÃƒÂ£o encontrado*/
    return *actual;
}

int insere_lista_locais (Lista_locais lista, char nome[], char tipo[], int n_inscritos) {
    Lista_locais no;
    Lista_locais ant, inutil;
    no = (Lista_locais) malloc (sizeof (Local));
    if (no != NULL) {
        strcpy(no->nome,nome);
        strcpy(no->tipo,tipo);
        no->n_inscritos=n_inscritos;
        no->lista_PdIs_locais=cria_lista_PdIs();
        if(procura_lista_locais (lista, nome, &ant, &inutil)==0) {
            no->next = ant->next;
            ant->next = no;
            return 1;
        }
        else{
            free(no);
            return 0;
        }
    }
}

Lista_locais pesquisa_lista_locais(Lista_locais lista, char nome[]) {
    Lista_locais ant;
    Lista_locais actual;
    procura_lista_locais (lista, nome, &ant, &actual);
    return (actual);
}

int lista_vazia_locais(Lista_locais lista) {
    return (lista->next == NULL ? 1 : 0);
}

Lista_locais destroi_lista_locais (Lista_locais lista) {
    Lista_locais temp_ptr;
    while (lista_vazia_locais (lista) == 0) {
        temp_ptr = lista;
        if (temp_ptr->lista_PdIs_locais){
            destroi_lista_PdIs(temp_ptr->lista_PdIs_locais);
        }
        lista= lista->next;
        free (temp_ptr);
    }
    free(lista);
    return NULL;
}


void imprime_lista_locais (Lista_locais lista) {
    Lista_locais l = lista->next; /* Salta o header */
    Lista_PdIs PdI;
    while (l) {
        PdI = l->lista_PdIs_locais;
        printf("%s\n", l->nome);
        if (PdI!=NULL){
            imprime_lista_PdIs(PdI, "NULL");
        }
        l=l->next;
    }
}

void imprime_lista_locais_aluno (Lista_locais_aluno lista) {
    Lista_locais_aluno l = lista->next; /* Salta o header */
    Lista_PdIs PdI;
    while (l) {
        PdI = l->informacao->lista_PdIs_locais;
        printf("%s\n", l->informacao->nome);
        if (PdI!=NULL){
            imprime_lista_PdIs(PdI, "NULL");
        }
        l=l->next;
    }
}


//------------------------------------------------- FUNCOES PONTOS DE INTERESSE -------------------------------------------------------

int lista_vazia_PdIs(Lista_PdIs lista) {
    return (lista->next == NULL ? 1 : 0);
}

Lista_PdIs cria_lista_PdIs (void) {
    Lista_PdIs aux;
    aux = (Lista_PdIs) malloc (sizeof (PdI));
    if (aux != NULL) {
        strcpy(aux->nome, "NULL");
        strcpy(aux->descricao, "NULL");
        strcpy(aux->horario, "NULL");
        aux->n_inscritos=0;
        aux->next = NULL;
    }
    return aux;
}

Lista_PdIs procura_lista_PdIs (Lista_PdIs lista, char chave[], char local[], Lista_PdIs *ant, Lista_PdIs *actual) {
    *ant = lista;
    *actual = lista;
    while ((*actual) != NULL && strcmp((*actual)->nome, chave)<=0) {
        if(strcmp((*actual)->nome, chave)==0 && strcmp((*actual)->nome_local, local)==0)
            return *actual;
        *ant = *actual;
        *actual = (*actual)->next;
    }
    if ((*actual) != NULL && (*actual)->nome != chave)
        *actual = NULL;   /* Se elemento nÃƒÂ£o encontrado*/
    return *actual;
}

int insere_lista_PdIs (Lista_PdIs lista, char nome[], char local[], char descricao[], char horario[]) {
    Lista_PdIs no;
    Lista_PdIs ant, inutil;
    no = (Lista_PdIs) malloc (sizeof (PdI));
    if (no != NULL) {
        strcpy(no->nome,nome);
        strcpy(no->descricao,descricao);
        strcpy(no->horario,horario);
        if(procura_lista_PdIs (lista, nome, local, &ant, &inutil)!=NULL){
            no->next = ant->next;
            ant->next = no;
            return 1;
        }
        else{
            free(no);
            return 0;
        }
    }
}

Lista_PdIs pesquisa_lista_PdIs(Lista_PdIs lista, char *nome, char *local) {
    Lista_PdIs ant;
    Lista_PdIs actual;
    procura_lista_PdIs (lista, nome, local, &ant, &actual);
    return (actual);
}

void insere_PdIs_local (Lista_locais locais, char nome_local[], char nome_PdI[], char descricao[], char horario[], int n_inscritos) {
    Lista_locais ant_local, atual;
    if (procura_lista_locais (locais, nome_local, &ant_local, &atual) == 0)
        return;
    Lista_PdIs no_atual = atual->lista_PdIs_locais;
    Lista_PdIs no;
    Lista_PdIs ant, inutil;
    no = (Lista_PdIs) malloc (sizeof (PdI));
    if (no != NULL) {
        strcpy(no->nome,nome_PdI);
        strcpy(no->nome_local,nome_local);
        strcpy(no->descricao,descricao);
        strcpy(no->horario,horario);
        no->n_inscritos=n_inscritos;
        if (lista_vazia_PdIs(no_atual)){
            no->next=NULL;
            no_atual->next = no;
        } else {
            if(procura_lista_PdIs (no_atual, nome_PdI, nome_local, &ant, &inutil) != NULL){
                free(no);
                return; //Ja existe o PdI
            }
            no->next = ant->next;
            ant->next = no;
        }
    }
}


Lista_PdIs destroi_lista_PdIs (Lista_PdIs lista) {
    Lista_PdIs temp_ptr;
    while (lista_vazia_PdIs (lista) == 0) {
        temp_ptr = lista;
        lista= lista->next;
        free (temp_ptr);
    }
    free(lista);
    return NULL;
}

void imprime_lista_PdIs (Lista_PdIs lista, char tipo[]) {
    Lista_PdIs aux=lista;
    if(strcmp(tipo, "NULL")!=0){
        while(aux!=NULL){
            if(strcmp(aux->nome, tipo)==0){
                printf("----> PdI:  %s  ----> Local:  %s\n", aux->nome, aux->nome_local);
                break;
            }
            aux=aux->next;
        }
    }
    Lista_PdIs l = lista; /* Salta o header */
    while (l) {
        if(strcmp(l->nome, tipo)!=0)
            printf("----> PdI:  %s  ----> Local:  %s\n", l->nome, l->nome_local);
        l=l->next;
    }
}

void imprime_lista_PdIs_aluno (Lista_pdis_aluno lista, char tipo[]) {
    Lista_pdis_aluno aux=lista;
    if(strcmp(tipo, "NULL")!=0){
        while(aux!=NULL){
            if(strcmp(aux->informacao->nome, tipo)==0){
                printf("----> PdI:  %s  ----> Local:  %s\n", aux->informacao->nome, aux->informacao->nome_local);
                break;
            }
            aux=aux->next;
        }
    }
    Lista_pdis_aluno l = lista; /* Salta o header */
    while (l) {
        if(strcmp(l->informacao->nome, tipo)!=0)
            printf("----> PdI:  %s  ----> Local:  %s\n", l->informacao->nome, l->informacao->nome_local);
        l=l->next;
    }
}

//------------------------------------FICHEIROS----------------------------------

void cria_fich_alunos(Lista_alunos list_alunos){
    FILE *alunos;
    alunos=fopen("alunos.txt", "w");
    Lista_alunos temp = list_alunos->next; //Passa o header
    Lista_pdis_aluno PdIs;
    Lista_locais_aluno locais;
    while(temp != NULL){
        fprintf(alunos, "%s\n", temp->nome);
        fprintf(alunos, "%s\n", temp->morada);
        fprintf(alunos, "%s\n", temp->data_nasc);
        fprintf(alunos, "%d\n", temp->telefone);
        fprintf(alunos, "%s\n", temp->PdI_hot);
        fprintf(alunos, "%d\n", temp->n_locais);
        locais = temp->lista_locais_alunos->next;
        for (int i = 0; i < temp->n_locais; ++i) {
            if (locais != NULL) {
                fprintf(alunos, "%s\n", locais->informacao->nome);
                locais = locais->next;
            }
        }
        PdIs = temp->lista_PdIs_alunos->next;
        while(PdIs){
            fprintf(alunos, "%s\n", PdIs);
            fprintf(alunos, "%s\n", PdIs->informacao->nome_local);
            PdIs=PdIs->next;
        }

        fprintf(alunos, "\n");
        temp=temp->next;
    }
    fclose(alunos);
}


void carrega_alunos(Lista_alunos list_alunos, Lista_locais lista_locais){
    FILE *alunos;
    alunos=fopen("alunos.txt", "r");
    Lista_locais ponteiro_local;
    Lista_PdIs ponteiro_PdI;
    Lista_locais_aluno locais_aluno_aux;
    Lista_pdis_aluno pdis_aluno_aux;
    Lista_alunos aluno;
    char str[MAX];
    char nome[MAX];
    char nome_PdI[MAX];
    char nome_local[MAX];
    char morada[MAX];
    char data_nasc[MAX];
    char PdI_hot[MAX];
    int telefone, n_locais;
    while(fgets_aux(str, MAX, alunos) != NULL){
        strcpy(nome, str);
        fgets_aux(morada, MAX, alunos);
        fgets_aux(data_nasc, MAX, alunos);
        fgets_aux(str, MAX, alunos);
        telefone=atoi(str);
        fgets_aux(PdI_hot, MAX, alunos);
        fgets_aux(str, MAX, alunos);
        n_locais=atoi(str);
        insere_lista_alunos(list_alunos, nome, morada, data_nasc, telefone, PdI_hot, n_locais);
        aluno = pesquisa_lista_alunos(list_alunos, nome);
        for (int j = 0; j < n_locais; ++j) {
            fgets_aux(str, MAX, alunos);
            ponteiro_local = pesquisa_lista_locais(lista_locais, str);
            if (ponteiro_local!=NULL)
                 insere_locais_aluno(ponteiro_local, aluno->lista_locais_alunos, str);
        }
        fgets_aux(nome_PdI, MAX, alunos);
        while (strcmp(nome_PdI, "\0") != 0) {
            fgets_aux(nome_local, MAX, alunos);
            ponteiro_local = pesquisa_lista_locais(lista_locais, nome_local);
            ponteiro_PdI = pesquisa_lista_PdIs(ponteiro_local->lista_PdIs_locais, nome_PdI, nome_local);
            if (ponteiro_PdI != NULL)
                insere_pdis_aluno(ponteiro_PdI, aluno->lista_PdIs_alunos, nome_PdI, nome_local);
            fgets_aux(nome_PdI, MAX, alunos);
        }
    }
    fclose(alunos);
}

void cria_fich_locais(Lista_locais list_locais){
    FILE *locais;
    locais=fopen("locais.txt", "w");
    Lista_locais temp_locais;
    Lista_PdIs temp_PdIs;
    temp_locais = list_locais->next; //Passa o header

    while(temp_locais != NULL){
        temp_PdIs = temp_locais->lista_PdIs_locais->next;
        fprintf(locais, "%s\n", temp_locais->nome);
        fprintf(locais, "%s\n", temp_locais->tipo);
        fprintf(locais, "%d\n", temp_locais->n_inscritos);

        //ADICIONAR LISTA DE PDIS
        while(temp_PdIs) {
            fprintf(locais, "%s\n", temp_PdIs->nome);
            fprintf(locais, "%s\n", temp_PdIs->descricao);
            fprintf(locais, "%s\n", temp_PdIs->horario);
            fprintf(locais, "%d\n", temp_PdIs->n_inscritos);
            fprintf(locais, "\n");
            temp_PdIs=temp_PdIs->next;
        }

        fprintf(locais, ";\n");
        temp_locais=temp_locais->next;
    }
    fclose(locais);
}

void carrega_locais(Lista_locais list_locais){
    FILE *locais;
    locais=fopen("locais.txt", "r");
    char str[MAX];
    char nome[MAX];
    char tipo[MAX];
    char nome_PdI[MAX];
    char descricao[MAX];
    char horario[MAX];
    int n_inscritos_local, n_inscritos_PdI;
    char *res;
    int i=0;
    while(fgets_aux(str, MAX, locais) != NULL){
        if(i==0) {
            strcpy(nome, str);
        }
        if(i==1){
            strcpy(tipo, str);
        }
        if(i==2){
            n_inscritos_local = atoi(str);
            insere_lista_locais(list_locais, nome, tipo, n_inscritos_local);
        }
        if (i==3){ //PdIs
            do {
                strcpy(nome_PdI, str);
                fgets_aux(str, MAX, locais);
                strcpy(descricao, str);
                fgets_aux(str, MAX, locais);
                strcpy(horario, str);
                fgets_aux(str, MAX, locais);
                n_inscritos_PdI = atoi(str);
                fgets_aux(str, MAX, locais);
                res = fgets_aux(str, MAX, locais);
                insere_PdIs_local(list_locais, nome, nome_PdI, descricao, horario, n_inscritos_PdI);
            }while (strcmp(res, ";"));
            i=-1;
        }
        i++;
    }
    fclose(locais);
}

void menu_locais(Lista_alunos lista_alunos, Lista_locais lista_locais, Lista_alunos aluno_atual){
    int escolha, ver, ver_input;
    char nome[MAX];
    char a[MAX];
    Lista_locais ant_l, inutil_l, ponteiro_local, aux;
    printf("Locais que tem adicionados:\n");
    imprime_lista_locais_aluno(aluno_atual->lista_locais_alunos);
    printf("1- Adicionar Local\n");
    printf("2- Remover Local\n");
    printf("3- Sair\n");
    do{
        fgets_aux(a, sizeof(a), stdin);
        ver=verfica_inteiros(a);
        if(ver==0)
            printf("input invalido.\n");
    }while (ver!=1);
    escolha=atoi(a);
    switch (escolha){
        case 1:
            if (aluno_atual->n_locais>= 3)
                printf("Atingiu o limite de locais\n");
            else {
                printf("Lista de locais:\n");
                imprime_lista_locais(lista_locais);
                printf("Digite o nome do local que pretende adicionar.\n");
                do {
                    fgets_aux(nome, sizeof(nome), stdin);
                    aux=lista_locais;
                    ponteiro_local = procura_lista_locais(aux, nome, &ant_l, &inutil_l);
                    if (ponteiro_local != NULL) {
                        ver = insere_locais_aluno(ponteiro_local, aluno_atual->lista_locais_alunos, nome);
                        if (ver == 1) {
                            printf("Local adicionado com sucesso.\n");
                            aluno_atual->n_locais++;
                        }
                        else
                            printf("O local que pretende adicionar ja se encontra na sua lista. Tente novamente.\n");
                    }
                    else
                        printf("O local que pretende adicionar não existe. Tente novamente\n");
                } while (ver != 1);
            }
            menu_locais(lista_alunos, lista_locais, aluno_atual);
            break;
        case 2:
            if(aluno_atual->lista_locais_alunos->next==NULL)
                printf("Nao tem locais associados.\n");
            else {
                printf("Os seus locais:\n");
                imprime_lista_locais_aluno(aluno_atual->lista_locais_alunos);
                printf("Digite o nome do ponto de interesse que pretende remover.\n");
                do {
                    do {
                        fgets_aux(nome, sizeof(nome), stdin);
                        ver_input = verifica_string(nome);
                        if (ver_input == 0)
                            printf("input invalido.\n");
                    } while (ver_input != 1);
                    ver = elimina_lista_locais_aluno(aluno_atual->lista_locais_alunos, nome);
                    if (ver == 1) {
                        aluno_atual->n_locais--;
                        printf("Removido com sucesso.\n");
                    }
                    else
                        printf("O que pretende remover nao existe.\n");
                } while (ver != 1);
            }
            menu_locais(lista_alunos, lista_locais, aluno_atual);
            break;
        case 3:
            menu_principal(lista_alunos, lista_locais, aluno_atual);
            break;
        default:
            printf("Comando invalido!\n");
            menu_locais(lista_alunos, lista_locais, aluno_atual);
            break;
    }
}

void imprime_pdis_locais(Lista_locais a){
    while (a!=NULL){
        imprime_lista_PdIs(a->lista_PdIs_locais, "NULL");
        a=a->next;
    }
}

void menu_pdis(Lista_alunos lista_alunos, Lista_locais lista_locais, Lista_alunos aluno_atual){
    int escolha, ver;
    char nome[MAX], local[MAX];
    char a[MAX];
    Lista_locais ponteiro_local;
    Lista_PdIs ponteiro_pdi, ant_p, inutil_p;
    Lista_pdis_aluno ponteiro_lista, ant, inutil;
    printf("Pontos de Interesse que tem adicionados:\n");
    imprime_lista_PdIs_aluno(aluno_atual->lista_PdIs_alunos, "NULL");
    printf("\n");
    printf("1- Adicionar Ponto de Interesse\n");
    printf("2- Remover Ponto de Interesse\n");
    printf("3- Definir PDI hot\n");
    printf("4- Sair\n");
    do{
        fgets_aux(a, sizeof(a), stdin);
        ver=verfica_inteiros(a);
        if(ver==0)
            printf("input invalido.\n");
    }while (ver!=1);
    escolha=atoi(a);
    switch (escolha) {
        case 1:
            do {
                imprime_lista_locais(lista_locais);
                printf("Digite o nome do local para vizualizar os seus pontos de interesse.\n");
                fgets_aux(local, sizeof(local), stdin);
                ponteiro_local = pesquisa_lista_locais(lista_locais, local);
                if (ponteiro_local==NULL){
                    printf("Local nao encontrado.");
                    break;
                }
                printf("Lista de Pontos de interesse do local %s:\n", ponteiro_local->nome);
                imprime_lista_PdIs(ponteiro_local->lista_PdIs_locais, "NULL");
                printf("Digite o nome do ponto de interesse que pretende adicionar.\n");
                fgets_aux(nome, sizeof(nome), stdin);
                ponteiro_pdi=procura_lista_PdIs(ponteiro_local->lista_PdIs_locais, nome, ponteiro_local->nome, &ant_p, &inutil_p);
                if(ponteiro_pdi!=NULL){
                    ver=insere_pdis_aluno(ponteiro_pdi, aluno_atual->lista_PdIs_alunos, nome, local);
                    if(ver==1) {
                        printf("Ponto de interesse adicionado com sucesso.\n");
                        break;
                    }
                    else
                        printf("O ponto de interesse que pretende adicionar ja se encontra na sua lista. Tente novamente.\n");
                }
                else
                    printf("O ponto de interesse ou não existe ou não se encontra dentro do leque de opcoes que pode escolher.\n");
            } while (ver != 1);
            menu_pdis(lista_alunos, lista_locais, aluno_atual);
            break;
        case 2:
            printf("Digite primeiro o local e de seguida o nome do ponto de interesse que pretende remover.\n");
            do {
                do{
                    fgets_aux(local, sizeof(local), stdin);
                    ver=verifica_string(nome);
                }while (ver!=1);
                do{
                    fgets_aux(nome, sizeof(nome), stdin);
                    ver=verifica_string(local);
                }while (ver!=1);
                ver=elimina_lista_pdis_aluno(aluno_atual->lista_PdIs_alunos, nome, local);
                if(ver==1)
                    printf("Removido com sucesso.\n");
                else
                    printf("O que pretende remover nao existe.\n");
            } while (ver != 1);
            menu_pdis(lista_alunos, lista_locais, aluno_atual);
            break;
        case 3:
            printf("Digite primeiro o nome do local e de seguido o ponto de interesse que pretende:\n");
            do {
                do{
                    fgets_aux(local, sizeof(local), stdin);
                    ver=verifica_string(nome);
                    if(ver==0)
                        printf("input para local invalido\n");
                }while (ver!=1);
                do{
                    fgets_aux(nome, sizeof(nome), stdin);
                    ver=verifica_string(nome);
                    if(ver==0)
                        printf("input para pdi invalido\n");
                }while (ver!=1);
                ponteiro_lista=procura_lista_Pdis_aluno(aluno_atual->lista_PdIs_alunos, nome, local, &ant, &inutil);
                
                if(ponteiro_pdi!=NULL){
                    if(strcmp(ponteiro_lista->informacao->nome, aluno_atual->PdI_hot)==0 && strcmp(ponteiro_lista->informacao->nome_local, aluno_atual->local_hot)==0)
                        printf("Esse já é o seu ponto de interesse hot.\n");
                    else {
                        strcpy(aluno_atual->PdI_hot, ponteiro_lista->informacao->nome);
                        strcpy(aluno_atual->local_hot, ponteiro_lista->informacao->nome_local);
                        printf("Ponto de Interesse definido com sucesso.\n");
                        ver = 1;
                    }
                }
                else{
                    printf("Esse ponto de interesse nao existe\n");
                }
            } while (ver != 1);
            menu_pdis(lista_alunos, lista_locais, aluno_atual);
            break;
        case 4:
            menu_principal(lista_alunos, lista_locais, aluno_atual);
            break;
    }
}

void menu_principal(Lista_alunos lista_alunos, Lista_locais lista_locais, Lista_alunos aluno_atual){
    int escolha, ver;
    double percentagem, r1, r2, r3, rf;
    char nome[MAX];
    Lista_alunos aux;
    char a[MAX];
    printf("1- Editar dados\n");
    printf("2- Menu Locais\n");
    printf("3- Menu Pontos de Interesse\n");
    printf("4- Vizualizer Locais/Pontos de interesse mais populares\n");
    printf("5- Gerar viagem automatica\n");
    printf("6- Estatisticas da viagem\n");
    printf("7- Sair\n");
    do{
        fgets_aux(a, sizeof(a), stdin);
        ver=verfica_inteiros(a);
        if(ver==0)
            printf("input invalido.\n");
    }while (ver!=1);
    escolha=atoi(a);
    switch (escolha){
        case 1:
            do {
                printf("Nome a registar:\n");
                fgets_aux(nome, sizeof(nome), stdin);
                ver=verifica_string(nome);
                if(ver==1){
                    aux = pesquisa_lista_alunos(lista_alunos, nome);
                    if(aux!=NULL)
                        printf("O utilizador ja existe. Tente novamente.\n");
                    else
                        strcpy(aluno_atual->nome, nome);
                }
                else
                    printf("input inválido.\n");
            }while(aux!=NULL);
            printf("Morada:\n");
            do{
                fgets_aux(aluno_atual->morada, sizeof(aluno_atual->morada), stdin);
                ver=verifica_string(aluno_atual->morada);
                if(ver==0)
                    printf("input invalido.\n");
            }while (ver!=1);
            printf("Data nascimento (dd/mm/aaaa):\n");
            do{
                fgets_aux(aluno_atual->data_nasc, sizeof(aluno_atual->data_nasc), stdin);
                ver=verifica_data(aluno_atual->data_nasc);
                if(ver==0)
                    printf("input invalido.\n");
            }while (ver!=1);
            printf("Telefone:\n");
            char n[MAX];
            do{
                fgets_aux(n, sizeof(n), stdin);
                ver=verifica_telefone(n);
                if(ver==0)
                    printf("input invalido.\n");
            }while(ver!=1);
            aluno_atual->telefone=atoi(n);
            //free(aux);
            menu_principal(lista_alunos, lista_locais, aluno_atual);
            break;
        case 2:
            menu_locais(lista_alunos, lista_locais, aluno_atual);
            break;
        case 3:
            menu_pdis(lista_alunos, lista_locais, aluno_atual);
            break;

        case 4:
            printf("Pontos de interesse mais populares:\n");
            Lista_PdIs aux1=cria_lista_PdIs();
            Lista_locais aux=lista_locais->next;
            Lista_PdIs a;
            while (aux!=NULL){
                a=aux->lista_PdIs_locais->next;
                while (a!=NULL){
                    insere_lista_PdIs(aux1, a->nome, a->descricao, a->horario, a->nome_local);
                    a=a->next;
                }
                aux=aux->next;
            }
            bubbleSort_pdis(aux1);
            imprime_lista_PdIs(aux1, "NULL");
            printf("Locais mais populares:\n");
            Lista_locais aux2=lista_locais;
            bubbleSort_locais(aux2);
            imprime_lista_locais(aux2);
            free(aux1);
            free(aux2);
            menu_principal(lista_alunos, lista_locais, aluno_atual);
            break;
        case 5:
            gera_viagem(aluno_atual->lista_locais_alunos, aluno_atual->PdI_hot, aluno_atual->local_hot, aluno_atual->lista_PdIs_alunos, aluno_atual->viagem);
            imprime_lista_PdIs_aluno(aluno_atual->viagem, "NULL");
            menu_principal(lista_alunos, lista_locais, aluno_atual);
            break;
        case 6:
            percentagem=percentagem_pdi_hot(aluno_atual->PdI_hot, aluno_atual->local_hot, lista_alunos);
            int n_users=get_n_utilizadores(lista_alunos);
            int total_inscritos=get_n_inscritos(lista_locais);
            r1=percentagem/n_users;
            percentagem=percentagem_favoritos(lista_alunos, aluno_atual->lista_locais_alunos);
            r2=percentagem/n_users;
            percentagem=percentagem_pdis(aluno_atual->viagem);
            r3;
            if(percentagem==0)
                r3=0;
            else
                r3=percentagem/total_inscritos;
            rf=r1+r2+r3;
            printf("Resultado da pontuacao da viagem na escala de 0 a 3: %lf\n", rf);
            menu_principal(lista_alunos, lista_locais, aluno_atual);
            break;
        case 7:
            printf("Ate a proxima.\n");
            menu_inicial(lista_alunos, lista_locais);
            break;
        default:
            printf("Comando invalido!\n");
            menu_principal(lista_alunos, lista_locais, aluno_atual);
            break;
    }

}

void menu_inicial(Lista_alunos lista_alunos, Lista_locais lista_locais){
    int escolha, ver;
    Aluno* aluno=malloc(sizeof(Aluno));
    Aluno* user;
    char username[MAX];
    int ver_insere=-1;
    char a[MAX];
    printf("1- Registo\n");
    printf("2- Login\n");
    printf("3- Sair\n");
    do{
        fgets_aux(a, sizeof(a), stdin);
        ver=verfica_inteiros(a);
        if(ver==0)
            printf("input invalido.\n");
    }while (ver!=1);
    escolha=atoi(a);
    switch (escolha){
        case 1:
            do{
                printf("Nome a registar:\n");
                do{
                    fgets_aux(aluno->nome, sizeof(aluno->nome), stdin);
                    ver=verifica_string(aluno->nome);
                    if(ver==0)
                        printf("input invalido.\n");
                }while (ver!=1);
                printf("Morada:\n");
                do{
                    fgets_aux(aluno->morada, sizeof(aluno->morada), stdin);
                    ver=verifica_string(aluno->morada);
                    if(ver==0)
                        printf("input invalido.\n");
                }while (ver!=1);
                printf("Data nascimento (dd/mm/aaaa):\n");
                do{
                    fgets_aux(aluno->data_nasc, sizeof(aluno->data_nasc), stdin);
                    ver=verifica_data(aluno->data_nasc);
                    if(ver==0)
                        printf("input invalido.\n");
                }while (ver!=1);
                printf("Telefone:\n");
                char n[MAX];
                do{
                    fgets_aux(n, sizeof(n), stdin);
                    ver=verifica_telefone(n);
                    if(ver==0)
                        printf("input invalido.\n");
                }while(ver!=1);
                aluno->telefone=atoi(n);
                ver_insere=insere_lista_alunos(lista_alunos, aluno->nome, aluno->morada, aluno->data_nasc, aluno->telefone, "NULL", 0);
                if (ver_insere ==0) {
                    printf("O username ja existe. Tente novamente\n");
                }
                else
                    printf("Registado com sucesso\n");
            }while(ver_insere!=1);
            free(aluno);
            menu_inicial(lista_alunos, lista_locais);
            break;
        case 2:
            do{
                printf("Nome:\n");
                do{
                    fgets_aux(username, sizeof(username), stdin);
                    ver=verifica_string(username);
                    if(ver==0)
                        printf("input invalido.\n");
                }while (ver!=1);
                user=pesquisa_lista_alunos(lista_alunos, username);
                if(user==NULL)
                    printf("O utilizador nao existe. Tente novamente.\n");
                else{
                    printf("Login efetuado com sucesso.\n");
                    menu_principal(lista_alunos, lista_locais, user);
                }
            }while(user==NULL);
            break;
        case 3:
            cria_fich_locais(lista_locais);
            cria_fich_alunos(lista_alunos);
            destroi_lista_alunos(lista_alunos);
            destroi_lista_locais(lista_locais);
            exit(0);
        default:
            printf("Comando invalido!\n");
            menu_inicial(lista_alunos, lista_locais);
            break;
    }
}


int main() {
    Lista_alunos lista_alunos = cria_lista_alunos();
    Lista_locais lista_locais = cria_lista_locais();
    carrega_locais(lista_locais);
    carrega_alunos(lista_alunos, lista_locais);
    menu_inicial(lista_alunos, lista_locais);
    return 0;
}

