#include <stdio.h>
#include <stdlib.h>


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
	//ler modo
	int modo = 0;
	// diferente != 
	while (modo != 4){
	printf ("qual o modo?");
	scanf ("%i", &modo);
	if (modo == 1){
		
}
	
	if (modo == 2) {
		
	}
	
	if (modo == 3){
		
}

	}
	// MAXSIZE = 100, constante definida no inicio do código
	const int TAMANHO_X = MAXSIZE; //Placeholder de tamanho 
	const int TAMANHO_Y = MAXSIZE;
	

	//tamanho[i][j]
	char rawMaze[TAMANHO_X][TAMANHO_Y];
	tile maze[TAMANHO_X][TAMANHO_Y]; //tamanho ??
	node start;
	//determinar posição inicial, em (i j) e criar node
	for (int i = 0; i < TAMANHO_X; i++)
	{
		for (int j = 0; j < TAMANHO_Y; j++)
		{
			if(rawMaze[i][j] == '@')
			{
				
				start.pos.i = i;
				start.pos.j = j;
				start.parent = NULL;
			}
		}
	}
	
	// Solicitar nome do arquivo ao usuário
	char archiveName[50];
	int rows, columns;
	printf("Digite o nome do arquivo do labirinto: ");
	scanf("%s", archiveName);

	// Ler o labirinto do arquivo
	readArchive(rawMaze, &rows, &columns, archiveName);	// Tamanho dinamico


	// Podemos substituir a var. TAMANHO_X por rows e TAMANHO_Y por columns (pois o valor de rows e columns é definido na funçao)
	
	/* 
	
		// Determinar posição final
	for (int i = 0; i < linhas; i++) {
		for (int j = 0; j < colunas; j++) {
			if (rawMaze[i][j] == '$') {
				maze[i][j].saida = 1;
			}
		}
	}

	// Traduzir de "char" para "tile"
	for (int i = 0; i < linhas; i++) {
		for (int j = 0; j < colunas; j++) {
			// Inserir função para traduzir char para tile
		}
	}

	// Ler os espaços ao redor da posição inicial
	if (start != NULL) {
		readNode(*start, maze, linhas, colunas);
		freeNodes(start);
	}

	para usar essa condicional eu acho que temos que adicionar a seguinte linha :
	
	
	// Determinar posição inicial
	for (int i = 0; i < linhas; i++) {
		for (int j = 0; j < colunas; j++) {
			if (rawMaze[i][j] == '@') {
				start = makeNode(NULL, i, j);
			}
		}
	}

	
	*/
	//determinar posição final
	for (int i = 0 ; i < TAMANHO_X; i++){
	for (int j = 0; j < TAMANHO_Y; j++){
		if (rawMaze[i][j] == '$') {
			maze[i][j].saida = 1;
			}
			
	}
	}
	//traduzir de "char" pra "tile"
	for (int i = 0; i < TAMANHO_X; i++)
	{
		for (int j = 0; j < TAMANHO_Y; j++)
		{
			//Inserir função q traduz char pra algum tile aí, e diz sua posição em (i, j)
		}
	}

	//ler os espaços que tem em volta da node start;


	//caso espaço seja andável, criar node nele;
	//repete para todos os nodes
	readNode(start, maze, TAMANHO_X, TAMANHO_Y);
	//caso posição do node seja igual à posição final, considere node "completo"
	//array com nodes completas?
	
	//caso len(array) = 0, considere inimigos como não sendo paredes
	//caso len(array) = 0 de novo, não há solução :(
	
	//conte quantos inimigos tem nos caminhos e escolha os que tem menos (menor igual ao menor)
	
	//conte o tamanho dos caminhos válidos, e escolha o menor
	//pegue posição de cada node relacionada a node escolhida e substitua por caracteres apropriados
	
	//se modo for 1, escolha se perde; mostre na tela
	//se for modo 2, ignore; mostre na tela
	
	//se modo 4, return 0;
	//se modo 3 salve a solução em um arquivo;
	
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