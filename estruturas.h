//
// Created by Guilherme on 09/04/2019.
//

#ifndef PROJETO_ESTRUTURAS_H
#define PROJETO_ESTRUTURAS_H
#define MAX 500


typedef struct Aluno *Lista_alunos;
typedef struct PdI *Lista_PdIs;
typedef struct Local *Lista_locais;
typedef struct Pdis_aluno *Lista_pdis_aluno;
typedef struct Locais_aluno *Lista_locais_aluno;

typedef struct Aluno{
    char nome[MAX];
    char morada[MAX];
    char data_nasc[MAX];
    int telefone;
    int n_locais;
    char PdI_hot[MAX];
    char local_hot[MAX];
    Lista_locais_aluno lista_locais_alunos;
    Lista_pdis_aluno lista_PdIs_alunos;
    Lista_pdis_aluno viagem;
    Lista_alunos next;
} Aluno;

typedef struct PdI{
    char nome[MAX];
    char nome_local[MAX];
    char descricao[MAX];
    char horario[MAX];
    int n_inscritos;
    Lista_PdIs next;
} PdI;

typedef struct Local{
    char nome[MAX];
    char tipo[MAX];
    int n_inscritos;
    Lista_PdIs lista_PdIs_locais;
    Lista_locais next;
} Local;

typedef struct Pdis_aluno{
    Lista_PdIs informacao;
    Lista_pdis_aluno next;
}Pdis_aluno;

typedef struct Locais_aluno{
    Lista_locais informacao;
    Lista_locais_aluno next;
}Locais_aluno;

void menu_pdis(Lista_alunos lista_alunos, Lista_locais lista_locais, Lista_alunos aluno_atual);
void menu_locais(Lista_alunos lista_alunos, Lista_locais lista_locais, Lista_alunos aluno_atual);
void menu_principal(Lista_alunos lista_alunos, Lista_locais lista_locais, Lista_alunos aluno_atual);
void menu_inicial(Lista_alunos lista_alunos, Lista_locais lista_locais);
char * fgets_aux(char * dados, int size, FILE *file);
void imprime_lista_PdIs (Lista_PdIs lista, char tipo[]);
int insere_locais_aluno(Lista_locais ponteiro_local, Lista_locais_aluno lista_locais_aluno, char nome[]);
int insere_lista_alunos (Lista_alunos lista, char nome[], char morada[], char data_nasc[], int telefone, char PdI_hot[], int n_locais);
int insere_lista_locais (Lista_locais lista, char nome[], char tipo[], int n_inscritos);
int insere_pdis_aluno(Lista_PdIs ponteiro_pdi, Lista_pdis_aluno lista_pdIs_aluno, char nome[], char local[]);
void insere_PdIs_local (Lista_locais locais, char nome_local[], char nome_PdI[], char descricao[], char horario[], int n_inscritos);
int lista_vazia_PdIs(Lista_PdIs lista);
Lista_PdIs cria_lista_PdIs (void);
Lista_locais procura_lista_locais (Lista_locais lista, char chave[], Lista_locais *ant, Lista_locais *actual);
Lista_locais cria_lista_locais (void);
Lista_PdIs procura_lista_PdIs (Lista_PdIs lista, char chave[], char local[], Lista_PdIs *ant, Lista_PdIs *actual);
Lista_PdIs destroi_lista_PdIs (Lista_PdIs lista);
Lista_PdIs pesquisa_lista_PdIs(Lista_PdIs lista, char *nome, char *local);
Lista_alunos pesquisa_lista_alunos (Lista_alunos lista, char nome[]);

#endif //PROJETO_ESTRUTURAS_H
