#include <stdio.h>
#include <stdlib.h>

/*
use o gcc compilador  pff (Tem uma pasta so de testes)
como usar : 
gcc nomedoarquivo.c -o caminho do arquivo
gcc testeAqui.c -o testes/nomedoteste
*/

/* Constantes */
#define MAXSIZE 100

/*  Strutcts  */
typedef struct 
{
	int i;
	int j;
} point;

typedef struct node node;
struct node
{
	point pos;
	struct node* parent;
	int complete;
};
typedef struct
{
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

/* Funçoes */
node makeNode(node pai, int i, int j);
node* readNode(node nodulo, tile maze[100][100], int maxI, int maxJ);
void freeNodes(node* root);
void readArchive(char maze[MAXSIZE][MAXSIZE], int *rows, int *columns, char *archiveName); 



int main()
{
	// Ler modo
	int modo = 0;
	while (modo != 4){
		printf("Qual o modo? ");
		scanf("%i", &modo);
	}

	// Criar matriz para armazenar o labirinto
	char rawMaze[MAXSIZE][MAXSIZE];
	tile maze[MAXSIZE][MAXSIZE];
	node start;
	int rows, columns;
	char archiveName[50];

	// Solicitar nome do arquivo ao usuário
	printf("Digite o nome do arquivo do labirinto: ");
	scanf("%s", archiveName);

	// Ler o labirinto do arquivo
	readArchive(rawMaze, &rows, &columns, archiveName);

	// Teste: Exibir o labirinto lido
	printf("\nLabirinto carregado:\n");
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			printf("%c ", rawMaze[i][j]);
		}
		printf("\n");
	}

	// Determinar posição inicial
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

	// Determinar posição final
	int goalFound = 0;
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			if (rawMaze[i][j] == '$') {
				maze[i][j].saida = 1;
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



node makeNode(node pai, int i, int j)
{
	node newNode;
	newNode.parent = &pai;
	newNode.pos.i = i;
	newNode.pos.j = j;
	newNode.complete = 0;
	return newNode;
}

node* readNodes(node nodulo, tile** maze, int maxI, int maxJ, int inimigos)
{
	int flag = 0;
	if(maze[nodulo.pos.i][nodulo.pos.j].saida == 1)
	{
		nodulo.complete = 1;
		return &nodulo;
	}
	
	if(nodulo.pos.i + 1 < maxI)
	{
		if (maze[nodulo.pos.i + 1][nodulo.pos.j].chao || (inimigos && maze[nodulo.pos.i + 1][nodulo.pos.j].inimigo))
		{
			maze[nodulo.pos.i + 1][nodulo.pos.j].chao = 0;
			readNodes(makeNode(nodulo, nodulo.pos.i + 1, nodulo.pos.j), maze, maxI, maxJ, inimigos);
			flag++;
		}
	}
	if(nodulo.pos.i - 1 > 0)
	{
				if (maze[nodulo.pos.i - 1][nodulo.pos.j].chao || (inimigos && maze[nodulo.pos.i - 1][nodulo.pos.j].inimigo))
		{
			maze[nodulo.pos.i + 1][nodulo.pos.j].chao = 0;
			readNodes(makeNode(nodulo, nodulo.pos.i - 1, nodulo.pos.j), maze, maxI, maxJ, inimigos);
			flag++;
		}
	}

	if(nodulo.pos.j + 1 < maxJ)
	{
		if (maze[nodulo.pos.i][nodulo.pos.j + 1].chao || (inimigos && maze[nodulo.pos.i][nodulo.pos.j + 1].inimigo))
		{
			maze[nodulo.pos.i][nodulo.pos.j + 1].chao = 0;
			readNodes(makeNode(nodulo, nodulo.pos.i, nodulo.pos.j + 1), maze, maxI, maxJ, inimigos);
			flag++;
		}
	}
	if(nodulo.pos.j - 1 > 0)
	{
		if (maze[nodulo.pos.i][nodulo.pos.j -1].chao || (inimigos && maze[nodulo.pos.i][nodulo.pos.j - 1].inimigo))
		{
			maze[nodulo.pos.i][nodulo.pos.j - 1].chao = 0;
			readNodes(makeNode(nodulo, nodulo.pos.i, nodulo.pos.j - 1), maze, maxI, maxJ, inimigos);
			flag++;
		}
	}
	if (flag == 0)
	{
		return &nodulo;
	}
}

// ver nos comentarios da linha 126
void freeNodes(node* root) {
	if (root != NULL) {
		freeNodes(root->parent);
		free(root);
	}
}


void readArchive(char maze[MAXSIZE][MAXSIZE], int *rows, int *columns, char *archiveName){
	FILE *archive = fopen(archiveName,"r");  
	if(archive == NULL){
		printf("Erro ao abrir o arquivo!\n");
        exit(1);
	}

	fscanf(archive, "%d %d", rows, columns);

	for (int i = 0; i < *rows; i++)
	{
		for (int j = 0; j < *columns; j++)
		{
			fscanf(archive, " %c", &maze[i][j]);
		}
		
	}
	
	fclose(archive);

}