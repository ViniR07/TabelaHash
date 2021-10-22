/* 

Autor: Vinicius Matheus Romualdo Santos - RA: 801258
Data: 22/10/2021
Objetivo: Implementar uma Tabela Hash na linguagem C.

*/

// Bibliotecas
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Hash.h"

// Função Principal
int main(){

    int tamanho_tabela, repeticoes;
    printf("Informe o tamanho do hash: ");
    scanf("%d", &tamanho_tabela);

  // Alocação dinâmica de memória para a tabela Hash 
    tab = malloc(tamanho_tabela * sizeof(celula));

    limpa_hash(tamanho_tabela);    
    insere_hash(tamanho_tabela);
    escreve_hash(tamanho_tabela); 
    consulta_hash(tamanho_tabela);

    free(tab);

    return 0;
}

// Limpa o buffer para leitura de strings com espaço
void flush_in() {
    int ch;
    do {
        ch = fgetc(stdin);
    } while (ch != EOF && ch != '\n');
}

// Limpa o Hash e faz atribuicoes necessárias para o cálculo
void limpa_hash(int tamanho_tabela){
    for(int i = 0; i < tamanho_tabela; i++){
        tab[i].chave = -1;
        tab[i].ocorr = 0;
        strcpy(tab[i].nome, "Vazio");
    }
}

// Le e insere os produtos no Hash
void insere_hash(int tamanho_tabela){
    int repeticoes;
    printf("Quantos produtos quer colocar no Hash? ");
    scanf("%d", &repeticoes);

    for (int i = 0; i < repeticoes; i++){
        char nome_produto[50];
        float preco;
        printf("Digite o nome do produto: ");
        flush_in();
 	    scanf("%[^\n]", nome_produto); // Leitura expecífica para suportar strings com espaço
        printf("Digite o valor em reais do produto: ");
        scanf("%f", &preco);

        contabiliza(valor_string(nome_produto), nome_produto, preco, tamanho_tabela);   
    }
}

// Retorna o valor da string dado uma formula
int valor_string(char* str){
    int i, valor = 0;
    int tam = strlen(str);
    for(i = 0; i < tam; i++){
        valor = (31 + valor) * (int)str[i];
    }
    return (valor & 0x7FFFFFFF); // Operador and bit-a-bit para "retirar" possíveis sinais
}

// Insere o produto em um compartimento (registro) vazio do Hash criado
// Atribui valores de preco, nome e chave (cada produto contem uma chave diferente)
void contabiliza (int ch, char str[], float preco, int tamanho) {
   int c, sonda, Nhash;
   Nhash = hash (ch, tamanho);
    for (sonda = 0; sonda < tamanho; sonda++) {
        c = tab[Nhash].chave;
        if (c == -1 || c == ch) break; 
        Nhash = (Nhash + 1) % tamanho;
    }
    if (sonda >= tamanho) 
        exit (EXIT_FAILURE);
    if (c == -1) 
        tab[Nhash].chave = ch;
    tab[Nhash].ocorr++;
    tab[Nhash].valor = preco;
    strcpy(tab[Nhash].nome, str);
}   

// Retorna um indice Hash para o produto entrado
int hash(int ch, int tamanho){
    return ch % tamanho;
}

// Escreve a tabela Hash completa no monitor 
void escreve_hash(int tamanho_tabela){
    printf("\n/*******************>Tabela Hash<******************/\n");
    for(int i = 0; i < tamanho_tabela; i++){
        printf("#0%d Produto = %s Preco = %.2f Chave = %d Ocorrencia = %d\n", i, tab[i].nome, tab[i].valor, tab[i].chave, tab[i].ocorr);
    }
    printf("\n");
}

// Consulta o Hash de diversas formas a escolher pelo usuário
void consulta_hash(int tamanho_tabela){
    int consulta;
    do {        
        printf("Deseja fazer alguma consulta?\n(0-Nao 1-Consultar Preco 2-Produto por Chave 3-Tabela de Produtos)\n R: ");
        scanf("%d", &consulta);

        switch (consulta){                
            int achoupreco, achouproduto, chave;       
            char produto[50];
            case 1: 
                do {
                    printf("Escreva o nome do produto corretamente: ");
                    flush_in();  // Limpeza do buffer
                    scanf("%[^\n]", produto); 
                    achoupreco = consulta_preco(tamanho_tabela, produto);
                } while(!achoupreco);
                break;
            case 2:
                do {
                    printf("Escreva a chave do produto corretamente: ");
                    scanf("%d", &chave);
                    achouproduto = procura_produto(tamanho_tabela, chave);
                } while(!achouproduto);
                break; 
            case 3:
                escreve_hash(tamanho_tabela);
                break;       
            default:
                break;            
        }

    } while(consulta);
}

// Procura produto no Hash dado a chave e imprime na tela
// Retorna 1 se achou e 0 se não achou
int procura_produto(int tamanho, int chave){
    int j, i;
    for(i = 0; i < tamanho; i++){
        if(tab[i].chave == chave){
            j = i;
            break;
        }
    }
    if(i < tamanho){
        printf("Produto: %s\n\n", tab[j].nome);
        return 1;
    }
    return 0;
}

// Consulta preço de produto no Hash e imprime na tela
// Retorna 1 se achou e 0 se não achou
int consulta_preco(int tamanho, char str[]){
    int j, i;
    for(i = 0; i < tamanho; i++){
        if(strcmp(tab[i].nome, str) == 0){
            j = i;
            break;
        }
    }
    if(i < tamanho){
        printf("O preco do produto %s eh R$ %.2f\n\n", tab[j].nome, tab[j].valor);
        return 1;
    }
    return 0;
}