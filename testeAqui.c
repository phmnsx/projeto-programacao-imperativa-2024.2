#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 100

/* Structs */
typedef struct {
    int i;
    int j;
} point;

typedef struct node node;
struct node {
    point pos;
    struct node* parent;
    int complete;
};

typedef struct {
    int parede;
    int chao;
    int inimigo;
    int chegada;
    int andou;
    int morreu;
    int matou;
    int vitoria;
    int saida;
    point pos;
} tile;

/* Funções */
node makeNode(node pai, int i, int j);
node* readNodes(node nodulo, tile maze[MAXSIZE][MAXSIZE], int maxI, int maxJ, int inimigos);
void freeNodes(node* root);
void readArchive(char maze[MAXSIZE][MAXSIZE], int *rows, int *columns, char *archiveName);

int main() {
    int modo = 0;
    while (modo != 4) {
        printf("Qual o modo? ");
        scanf("%i", &modo);
    }

    char rawMaze[MAXSIZE][MAXSIZE];
    tile maze[MAXSIZE][MAXSIZE];
    node start;
    int rows, columns;
    char archiveName[50];

    printf("Digite o nome do arquivo do labirinto: ");
    scanf("%s", archiveName);

    readArchive(rawMaze, &rows, &columns, archiveName);

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            printf(" %c", rawMaze[i][j]);
        }
    }

    printf("\nLabirinto carregado:\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            printf("%c ", rawMaze[i][j]);
        }
        printf("\n");
    }

    int startFound = 0;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            if (rawMaze[i][j] == '@') {
                start.pos.i = i;
                start.pos.j = j;
                start.parent = NULL;
                startFound = 1;
                printf("\nPosição inicial encontrada em: (%d, %d)\n", i, j);
            }
        }
    }
    if (!startFound) {
        printf("\nErro: Posição inicial '@' não encontrada!\n");
    }

    node* final = NULL;
    int goalFound = 0;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            if (rawMaze[i][j] == '$') {
                final = readNodes(start, maze, i, j, 0);
                goalFound = 1;
                printf("\nPosição final encontrada em: (%d, %d)\n", i, j);
            }
        }
    }
    if (!goalFound) {
        printf("\nErro: Posição final '$' não encontrada!\n");
    }

    return 0;
}

node makeNode(node pai, int i, int j) {
    node newNode;
    newNode.parent = &pai;
    newNode.pos.i = i;
    newNode.pos.j = j;
    newNode.complete = 0;
    return newNode;
}



//
node* readNodes(node nodulo, tile maze[MAXSIZE][MAXSIZE], int maxI, int maxJ, int inimigos) {
    if (maze[nodulo.pos.i][nodulo.pos.j].saida == 1) {
        nodulo.complete = 1;
        node* newNode = (node*)malloc(sizeof(node));
        *newNode = nodulo;
        return newNode;
    }

    if (nodulo.pos.i + 1 < maxI) {
        if (maze[nodulo.pos.i + 1][nodulo.pos.j].chao || (inimigos && maze[nodulo.pos.i + 1][nodulo.pos.j].inimigo)) {
            maze[nodulo.pos.i + 1][nodulo.pos.j].chao = 0;
            readNodes(makeNode(nodulo, nodulo.pos.i + 1, nodulo.pos.j), maze, maxI, maxJ, inimigos);
        }
    }

    return NULL;
}

void freeNodes(node* root) {
    if (root != NULL) {
        freeNodes(root->parent);
        free(root);
    }
}

void readArchive(char maze[MAXSIZE][MAXSIZE], int *rows, int *columns, char *archiveName) {
    FILE *archive = fopen(archiveName, "r");  
    if (archive == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        exit(1);
    }

    fscanf(archive, "%d %d", rows, columns);
    for (int i = 0; i < *rows; i++) {
        for (int j = 0; j < *columns; j++) {
            fscanf(archive, " %c", &maze[i][j]);
        }
    }
    fclose(archive);
}
