#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "functions.h"

int main() {
    srand(time(NULL));

    char rawMaze[MAXSIZE][MAXSIZE];
    tile maze[MAXSIZE][MAXSIZE];
    point start, end;
    
    char archiveName[50];
    int rows, columns;

    printf("Digite o nome do arquivo do labirinto:\n");
    scanf("%s", archiveName);

    readArchive(rawMaze, &rows, &columns, archiveName);
    charToTile(rawMaze, maze, &start, &end, rows, columns);

    printf("Labirinto carregado com sucesso!\n");

    return 0;
}
