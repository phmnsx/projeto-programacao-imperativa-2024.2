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
	int state; // -1 = não andável
			   // 0 = não andada,
			   // 1 = andada
			   // 2 = faz parte da solução
			   // 3 = início
			   // 4 = final
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
node makeNode(node* pai, int i, int j);
//void freeNodes(node* root);
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
	point start;
	point end;
	
	// Solicitar nome do arquivo ao usuário
	char archiveName[50];
	int rows, columns;
	printf("Digite o nome do arquivo do labirinto: ");
	scanf("%s", archiveName);

	// Ler o labirinto do arquivo
	readArchive(rawMaze, &rows, &columns, archiveName);	// Tamanho dinamico


	// Podemos substituir a var. TAMANHO_X por rows e TAMANHO_Y por columns (pois o valor de rows e columns é definido na funçao)
	
	/* 
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
	*/ 
	
	// Determinar posição inicial
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			if (rawMaze[i][j] == '@') {
				
			}
		}
	}

	
	
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
			//Inserir função q traduz char pra algum tile aí, e diz sua posição em (i, j)   ; será q precisa?
		}
	}
	node array[rows][columns]; // i j, então rows columns
	node tmp_array[rows][columns];
	//criar nodes, e "ativar" a no start
	for (int i = 0; i<rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			array[i][j] = makeNode(NULL, i, j); //crie uma node [i][j] andável
			if (!maze[i][j].chao) //caso não seja chão
			{
				array[i][j].state = -1; //faça ser não andável
			}

			if ((i == start.i) && (j == start.j))
			{
				array[i][j].state = 3; // node inicio
			}
		}
	}
	arraycpy(tmp_array, array); //criar função q (copia, copiado)
								//recebe pointer de array e tamanhos?
								
	//caso espaço seja andável, criar node nele;
	//repete para todos os nodes
	int endReached = 0;
	while(endReached == 0)
	{
	for (int i = 0; i < rows ; i++)
	{
		for (int j = 0 ; i < columns; j++)
		{
			if ((array[i][j].state == 3) || (array[i][j].state == 1)) // Se for inicio ou andado
			{
				for ( k = -1; k <= -1 ; k+2)
				{
					if (array[i + k][j].state == 0) // Se for andável
					{
						tmp_array[i + k][j].state = 1;
						tmp_array[i + k][j].parent = &array[i][j];
					}
					if (array[i][j + k].state == 0) // Se for andável
					{
						tmp_array[i][j + k].state = 1;
						tmp_array[i][j + k].parent = &array[i][j]; // endereço certo ??
					}
				}
			}
		}
	}
	arraycpy(array, tmp_array); // atualiza array pra ser tmp_array
	endReached = isEndReached(array);
	}
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

node makeNode(node *pai, int i, int j)
{
	node newNode;
	newNode.parent = pai;
	newNode.pos.i = i;
	newNode.pos.j = j;
	newNode.state = 0;
	return newNode;
}

// ver nos comentarios da linha 126
//Não usaremos as funções malloc() e free().
/*
void freeNodes(node* root) {
	if (root != NULL) {
		freeNodes(root->parent);
		free(root);
	}
}*/


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
