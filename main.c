#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "extra/functions.c"
#include <time.h>

/* 
As funçoes estao no arquivo de funçoes.

*/

/*
Para excutar o main use o gcc da seguinte forma: 
gcc main.c functions.c -o nomeDoExecutavel 

Mas talvez o GEAAAAAAAANy compile normalmente já que é uma IDE.
*/


int main(int argc, char* argv[0])
{
	if (argc != 2)
	{
		printf("Modo de uso: ./main [nomedoarquivo]\n");
		return 1;
	}
	//tamanho[i][j]
	//inicialização de variaveis
	char rawMaze[MAXSIZE][MAXSIZE];
	tile maze[MAXSIZE][MAXSIZE];
	tile tmp_maze[MAXSIZE][MAXSIZE];
	point start;					
	point end;
	int modo = 0;
	int modosec = 0;
	int tentativas;
	int porcentWin;						
	
	// Solicitar nome do arquivo ao usuário
	int rows, columns;

	// Ler o labirinto do arquivo
	readArchive(rawMaze, &rows, &columns, argv[1]);	// Tamanho dinamico

	// Traduzir de "char" para "tile" e definir start e end 
	charToTile(rawMaze, maze, &start, &end, rows, columns);
	
	//Printa o labirinto escolhido
	printSolvedMaze(maze, rows, columns);
	
	node array[rows][columns]; // i j, então rows columns

	
	//criar nodes, e "ativar" a no start (apenas para modo inteligente)
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
	
	//cria array que guardará os pontos até a saída, em ordem
	point pathArr[400];
	for (int i = 0; i < 400; i++)
	{
		pathArr[i].i = 0;
		pathArr[i].j = 0;
	}
	
	while (modo != 4){
	memcpy(tmp_maze, maze, sizeof(tmp_maze));
	printf ("Selecione o modo desejado:\n");
	printf ("Modo 1: Faz o labirinto escolhido uma vez.\n");
	printf ("Modo 2: Faz o labirinto escolhido ate resolve-lo.\n");
	printf ("Modo 3: Salva labirinto resolvido.\n");  
	printf ("Modo 4: Sair\n");
	
	if (!(scanf ("%i", &modo)) || ((modo > 4) || (modo < 0)))
	{
		printf("Utilize apenas numeros de 1 a 4!\n\n");
		modo = 0;
		continue;
	}

	if (modo == 1) { // Resolve e imprime a primeira vez
		porcentWin = 05;
			printf("Escolha o modo \"secundario\":\n1- Modo inteligente\n2- Modo normal\n");
			while (!(scanf ("%i", &modosec)) || ((modosec != 1) && (modosec != 2)))
		{
			printf("Utilize apenas 1 ou 2!\n");
			printf("Escolha o modo \"secundario\":\n1- Modo inteligente\n2- Modo normal\n");
		}
		if (modosec == 2)
		{
			solveMazeRand(pathArr, maze, rows, columns, 0, end, 0);
			if (pathArr[0].i == -1)
			{
			    printf("O personagem se perdeu...\n");
			    cleanerpath(pathArr, tmp_maze, porcentWin);
			    pathTileChar(pathArr, tmp_maze, rawMaze, rows, columns);
			    printSolvedMaze(tmp_maze, rows, columns);
			}
			else 
			{
				cleanerpath(pathArr, tmp_maze, porcentWin);
				pathTileChar(pathArr, tmp_maze, rawMaze, rows, columns);
				printSolvedMaze(tmp_maze, rows, columns);
			}
		}
		else
		{
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
		}
	
	if (modo == 2) {// Resolve e imprime quando da vitoria
		porcentWin = 10;// Para chegar mais rapido na vitória
		printf("Escolha o modo \"secundario\":\n1- Modo inteligente\n2- Modo normal\n");
			while (!(scanf ("%i", &modosec)) || ((modosec != 1) && (modosec != 2)))
		{
			printf("Utilize apenas 1 ou 2!\n");
			printf("Escolha o modo \"secundario\":\n1- Modo inteligente\n2- Modo normal\n");
		}
		if (modosec == 2) { 
			tentativas = 0;
		    int maxTentativas = 1000; 
		
		    for (int i = 0; i < maxTentativas; i++){
			 if (solveMazeRand(pathArr, maze, rows, columns, 0, end, i * rand()))
			 {
				 break;
			 }
			 tentativas++;
			}
			cleanerpath(pathArr, tmp_maze, porcentWin);
			pathTileChar(pathArr, tmp_maze, rawMaze, rows, columns);
			printSolvedMaze(tmp_maze, rows, columns);
			printf("%i tentativas\n", tentativas);
		}
		else 
		{
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
	}
	
	if (modo == 3){
	
	porcentWin = 10;
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
		
	saveSolvedMaze(tmp_maze, rows, columns, outFilename); // Função criada para salvar o labirinto resolvido 
	}
}	
}
