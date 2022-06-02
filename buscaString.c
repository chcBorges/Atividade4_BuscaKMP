/*
  Claudio Henrique Costa Borges
  
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define tBuffer 100
#define qtdNomes 1000

void calcPrefix(char p[], int lps[]) {
    lps[0] = 0;
    int i = 0, j = 1;
    while (j < strlen(p)) {
        if (p[i] == p[j]) {
            lps[j] = i + 1;
            i++;
            j++;
        } else if (p[i] != p[j] && i != 0) {
            i = lps[i - 1];
        } else if (p[i] != p[j]) {
            lps[j] = 0;
            j++;
        }
    }
}

int kmp(char t[], char p[]) {

    int lps[strlen(p)];
    calcPrefix(p, lps);

    int i = 0, j = 0, k, l = 0;

    while (i <= strlen(t)) {
        int r = i - j;
        k = j;
        for (l = i; j < strlen(p); j++, l++) {
            if (t[l] == p[j]) {
                k++;
            } else {
                j++;
                break;
            }
        }
        if (k == strlen(p)) {
            return r;
        }
        if (lps[j - 1] == 0) {
            i = l + 1;
        } else {
            i = l;
        }
        j = lps[j - 1];
    }

    return -1;
}

int main(){
    FILE *arquivo = fopen("nomes.txt", "r");

    char *buffer = malloc(sizeof(char) * tBuffer), **nomes = malloc(sizeof(char *) * qtdNomes);

    int posicao, nomesEncontrados = 0;

    for(int i = 0; i < qtdNomes; ++i){
        fscanf(arquivo, " %[^\n]\n", buffer);

        nomes[i] = malloc(sizeof(char) * strlen(buffer) + 1);

        strcat(buffer, "\0");

        strcpy(nomes[i], buffer);

        printf("%s\n", nomes[i]);
    }

    //printf("\n\n");
    //system("pause");


    do{
        printf("Digite o nome que voce busca ou 0 para sair: ");
        scanf(" %[^\n]", buffer);

        if(buffer[0] == '0'){
            break;
        }

        for(int i = 0; i < qtdNomes; ++i){
            posicao = kmp(nomes[i], buffer);

            if(posicao >= 0){
                nomesEncontrados++;

                printf("%d - %s\n", i, nomes[i]);
            }
        }

        if(nomesEncontrados == 0){
            printf("Nenhuma ocorrencia da string: %s\n\n", buffer);
        }

        nomesEncontrados = 0;
    } while(buffer[0] != '0');

    for(int i = 0; i < qtdNomes; ++i){
        free(nomes[i]);
    }

    free(nomes);

    free(buffer);

    fclose(arquivo);

    system("pause");

    return 0;
}
