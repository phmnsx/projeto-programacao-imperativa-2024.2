#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <stdio.h>
#include <stdlib.h>

// Definições de constantes
#define MAXSIZE 20

// Definição de structs
typedef struct {
    int i;
    int j;
} point;

typedef struct node node;
struct node {
    point pos;
    struct node* parent;
    int state;
};

typedef struct {
    int inicio;
    int parede;
    int chao;
    int inimigo;
    int andou;
    int morreu;
    int matou;
    int vitoria;
    int perdeu;
    int saida;
    point pos;
} tile;

// Declaração das funções
node makeNode(node* pai, int i, int j);
void solveMaze(point* pathArray, node (*array)[], int rows, int columns, int inimigosBool, point end);
void readArchive(char maze[MAXSIZE][MAXSIZE], int *rows, int *columns, char *archiveName);
point getPoint(node currentNode, int ger);
void charToTile(char maze[MAXSIZE][MAXSIZE], tile parte[MAXSIZE][MAXSIZE], point* start, point* end, int rows, int columns);
void cleanerPath(point path[400], tile parte[MAXSIZE][MAXSIZE], int porcentWin);
void pathTileChar(point path[400], tile parte[MAXSIZE][MAXSIZE], char maze[MAXSIZE][MAXSIZE], int rows, int columns);
void printSolvedMaze(tile maze[MAXSIZE][MAXSIZE], int rows, int columns);

#endif
