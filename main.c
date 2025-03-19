#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.c"
#include <time.h>

/* 
As funçoes estao no arquivo de funçoes.

*/

/*
Para excutar o main use o gcc da seguinte forma: 
gcc main.c functions.c -o nomeDoExecutavel 

Mas talvez o GEAAAAAAAANy compile normalmente já que é uma IDE.
*/


int main()
{
	srand(time(NULL)); // deixando o rand aleatório
	//tamanho[i][j]
	char rawMaze[MAXSIZE][MAXSIZE];
	tile maze[MAXSIZE][MAXSIZE];
	tile tmp_maze[MAXSIZE][MAXSIZE];
	point start;					
	point end;						
	
	// Solicitar nome do arquivo ao usuário
	char archiveName[50];
	int rows, columns;
	printf("Digite o nome do arquivo do labirinto:\n");
	scanf("%s", archiveName);

	// Ler o labirinto do arquivo
	readArchive(rawMaze, &rows, &columns, archiveName);	// Tamanho dinamico

	// Traduzir de "char" para "tile" e definir start e end 
	charToTile(rawMaze, maze, &start, &end, rows, columns);
	
	//Printa o labirinto escolhido
	printSolvedMaze(maze, rows, columns);
	
	node array[rows][columns]; // i j, então rows columns

	
	//criar nodes, e "ativar" a no start
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			array[i][j] = makeNode(NULL, i, j); //crie uma node [i][j] andável
			if (maze[i][j].inimigo)
			{
				array[i][j].state = 5;
			}
			else if (!(maze[i][j].chao || maze[i][j].saida)) //caso não seja chão
			{
				array[i][j].state = -1;//faça ser não andável
			}

			if ((i == start.i) && (j == start.j))
			{
				array[i][j].state = 3; // node inicio   
			}
			if ((i == end.i) && (j == end.j))
			{
				array[i][j].state = 4;
			}
		}
	}
	
	point pathArr[400];
	for (int i = 0; i < 400; i++)
	{
		pathArr[i].i = 0;
		pathArr[i].j = 0;
	}
	
	 
	int modo = 0;
	
	while (modo != 4){
	memcpy(tmp_maze, maze, sizeof(tmp_maze));
	printf ("qual o modo?\n"); //da flush no terminal
	printf ("Modo 1: faz o labirinto escolhido uma vez.\n");
	printf ("Modo 2: faz o labirinto escolhido ate resolve-lo.\n");
	printf ("Modo 3: Salva labirinto resolvido.\n");
	printf ("Modo 4: Sair.\n");
	if (!(scanf ("%i", &modo)) || ((modo > 4) || (modo < 0)))
	{
		printf("Utilize apenas numeros de 1 a 4.");
		return 1;
	}
	if (modo == 1){
	int porcentWin = 5; // resolve apenas uma vez
	solveMaze(pathArr, array, rows, columns, 0 , end);
	if (pathArr[0].i == -1)
	{
		printf("Labirinto sem solucao.\n");
		return 0;
	}
	cleanerpath(pathArr, tmp_maze, porcentWin);
	pathTileChar(pathArr, tmp_maze, rawMaze, rows, columns);
	printSolvedMaze(tmp_maze, rows, columns);
	
	}
	
	if (modo == 2) {
	int porcentWin = 10; // Resolve e imprime quando da vitoria
	solveMaze(pathArr, array, rows, columns, 0 , end);
	if (pathArr[0].i == -1)
	{
		printf("Labirinto sem solucao.\n");
		return 0;
	}
	cleanerpath(pathArr, tmp_maze, porcentWin);
	pathTileChar(pathArr, tmp_maze, rawMaze, rows, columns);
	printSolvedMaze(tmp_maze, rows, columns);
	}
	
	
	if (modo == 3){
	
	int porcentWin = 10;
	solveMaze(pathArr, array, rows, columns, 0 , end);
	if (pathArr[0].i == -1)
	{
		printf("Labirinto sem solucao.\n");
		return 0;
	}
	cleanerpath(pathArr, tmp_maze, porcentWin);
	pathTileChar(pathArr, tmp_maze, rawMaze, rows, columns);

	char outFilename[50];
	printf("Digite o nome do arquivo:\n");
	scanf("%s", outFilename);
		
	saveSolvedMaze(tmp_maze, rows, columns, outFilename, 1); // Função criada para salvar o labirinto resolvido 
	}
}

	
}
 


/* Codigo antigo */

// void pathTileChar (point path [400], tile parte [MAXSIZE][MAXSIZE], char maze [MAXSIZE][MAXSIZE], int rows, int columns){
// int x, y, k, l;

// for (int p = 0; p < 400; p++){
// 		if ((path[p].i != -1) && (path[p].j != -1)){
// 		x = path[p].i;
// 		y = path[p].j;
// 	}
		
// 		if ((parte[x][y].matou != 1) || (parte[x][y].morreu != 1)){ // transforma o path em um tile
// 			parte[x][y].andou = 1;
// 			parte[x][y].chao = 0;
// 		}
		
// 		if ((parte[x][y].andou == 1) && (parte[x][y].saida == 1)){ // coloca o vitoria
// 			parte[x][y].andou = 0;
// 			parte[x][y].saida = 0;
// 			parte[x][y].vitoria=1;
// 		}
// 		for (int a = 0; a < rows; a++){
// 			for (int b = 0; b < columns; b++ ){}	
// 				if (parte[a][b].perdeu == 1){

// 				}
// 				if (parte[a][b].matou == 1){
// 					printf ("+");
// 				}
				
// 				}
// 				printf ("/n");
// 			}

// 		}

// 	}	
// }
				
// /* Codigo corrigido (Podem modificar!) no arquivo de funcoes */
// void pathTileChar(point path[400], tile parte[MAXSIZE][MAXSIZE], char maze[MAXSIZE][MAXSIZE], int rows, int columns) {
//     int x, y;

//     for (int p = 0; p < 400; p++) {
//         if (path[p].i != -1 && path[p].j != -1) {
//             x = path[p].i;
//             y = path[p].j;

//             if (parte[x][y].matou == 0 && parte[x][y].morreu == 0) { // Transforma o caminho em um tile
//                 parte[x][y].andou = 1;
//                 parte[x][y].chao = 0;
//             }

//             if (parte[x][y].andou == 1 && parte[x][y].saida == 1) { // Marca vitoria
//                 parte[x][y].andou = 0;
//                 parte[x][y].saida = 0;
//                 parte[x][y].vitoria = 1;
//             }
//         }
//     }

//     // Imprime o maze apos a transformação
//     for (int a = 0; a < rows; a++) {
//         for (int b = 0; b < columns; b++) {
//             if (parte[a][b].perdeu == 1) {
//                 printf("X");  // indicação de "perdeu" ---> nao sei qual é 
//             } else if (parte[a][b].matou == 1) {
//                 printf("+");
//             } else {
//                 printf("%c", maze[a][b]);
//             }
//         }
//         printf("\n");
//     }
// }
