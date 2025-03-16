#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "functions.h"

void saveMaze(char maze[MAXSIZE][MAXSIZE], tile parte[MAXSIZE][MAXSIZE], int rows, int columns, char *arquivo_saida);

// testando funçao charToTile



int main() {
    srand(time(NULL));  // Inicializa a semente aleatória para batalhas com inimigos

    char rawMaze[MAXSIZE][MAXSIZE];  // Matriz do labirinto original
    tile maze[MAXSIZE][MAXSIZE];      // Matriz convertida para tiles
    point start, end;                 // Ponto de início e fim do labirinto
    point pathArray[400];             // Array que armazenará o caminho encontrado
    int rows, columns;                // Dimensões do labirinto
    int inimigosBool = 1;              // Permite passar por inimigos

    // 1. Solicitar nome do arquivo e ler o labirinto
    char archiveName[50];
    printf("Digite o nome do arquivo do labirinto:\n");
    scanf("%s", archiveName);
    readArchive(rawMaze, &rows, &columns, archiveName);

    // 2. Converter caracteres do labirinto em estrutura tile
    charToTile(rawMaze, maze, &start, &end, rows, columns);
    
    // 3. Criar matriz de nodes para resolver o labirinto
    node array[rows][columns];
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            array[i][j] = makeNode(NULL, i, j);
            if (!(maze[i][j].chao || maze[i][j].saida)) {  // Se não for chão ou saída, não é andável
                array[i][j].state = -1;
            }
            if ((i == start.i) && (j == start.j)) {
                array[i][j].state = 3;  // Início do caminho
            }
            if ((i == end.i) && (j == end.j)) {
                array[i][j].state = 4;  // Saída do caminho
            }
        }
    }

    // 4. Resolver o labirinto
    solveMaze(pathArray, array, rows, columns, inimigosBool, end);

    // 5. Se o caminho for encontrado, marcar no labirinto e imprimir
    if (pathArray[0].i != -1) {
        pathTileChar(pathArray, maze, rawMaze, rows, columns);
        printSolvedMaze(maze, rows, columns);  // Exibir o labirinto resolvido
    } else {
        printf("\nNenhum caminho encontrado!\n");
    }

    return 0;
}



//TODO terminar essa joça!
// // Função para salvar o labirinto resolvido em um arquivo
// void saveMaze(char maze[MAXSIZE][MAXSIZE], tile parte[MAXSIZE][MAXSIZE], int rows, int columns, char *arquivo_saida) {
//     FILE *file = fopen(arquivo_saida, "w");
//     if (file == NULL) {
//         printf("Erro ao abrir o arquivo de saída!\n");
//         return;
//     }

//     fprintf(file, "%d %d\n", rows, columns);
//     for (int i = 0; i < rows; i++) {
//         for (int j = 0; j < columns; j++) {
//             if (parte[i][j].vitoria == 1) {
//                 fprintf(file, "V ");
//             } else if (parte[i][j].matou == 1) {
//                 fprintf(file, "+ ");
//             } else if (parte[i][j].morreu == 1) {
//                 fprintf(file, "X ");
//             } else if (parte[i][j].andou == 1) {
//                 fprintf(file, "* ");
//             } else {
//                 fprintf(file, "%c ", maze[i][j]);
//             }
//         }
//         fprintf(file, "\n");
//     }
//     fclose(file);
// }
