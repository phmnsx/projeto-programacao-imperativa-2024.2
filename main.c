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
			   // 5 = inimigo
			   // 6 = inimigo andado
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
node makeNode(node* pai, int i, int j); //cria node com esse parent nessa posição
void arraycpy(node copy[MAXSIZE][MAXSIZE], node original[MAXSIZE][MAXSIZE], int rows, int columns); //acho q funciona!!!! // copia de original pra copy, com essas dimensões (não retorno) (algm testa dps pfv)

void solveMaze (point pathArray[1000], node array[MAXSIZE][MAXSIZE], int rows, int columns, int inimigosBool, point end); // solveMaze resolve o labirinto e guarda o caminho em "PathArray", não sei fazer
																														  // tamanho dinâmico e recomendo q vc coloque esse msm tamanho aí na array q vc quer a
																														  // resposta qnd for usar. pathArray [point inicio .... point final, NULLPOINT]
																														  // NULLPOINT é (-1, -1) pq não tem esse espaço uma array ent da pra vc sempre falar
																														  // q n era pra ter nada ali (determinar o final da leitura talvez?)
																														  // se o ínicio for NULLPOINT não achou caminho.
																														  
void readArchive(char maze[MAXSIZE][MAXSIZE], int *rows, int *columns, char *archiveName); 							  
point getPoint(node currentNode, int ger); // função auxiliar pra a "lista" de parents de um node (vc não vai usar)

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
	arraycpy(tmp_array, array, rows, columns); //criar função q (cópia, copiado)
								//recebe pointer de array e tamanhos?
								
	//caso espaço seja andável, criar node nele;
	//repete para todos os nodes
	point pathArr[100];
	int inimigos = 0;
	solveMaze(pathArr, array, rows, columns, inimigos , end); //guarda resultado nessa array, de: array desses nodes, desse tamanho, e se ignora inimigos. e o end tb
	

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

void arraycpy(node copy[MAXSIZE][MAXSIZE], node original[MAXSIZE][MAXSIZE], int rows, int columns)
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			copy[i][j] = original[i][j];
		}
	}
}

void solveMaze(point pathArray[1000], node array[MAXSIZE][MAXSIZE], int rows, int columns, int inimigosBool, point end)
{
	point NULLPOINT;
	NULLPOINT.i = -1;
	NULLPOINT.j = -1;
	
	point tmp_pathArray[1000];
	node tmp_array[rows][columns];
	node endNode = makeNode(NULL, -1, -1);
	int flag;
	 
	while(endNode.parent == NULL)
	{
		flag = 0;
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0 ; i < columns; j++)
			{
				if (array[i][j].state == 4)
				{
					endNode = array[i][j];
				}
				if ((array[i][j].state == 3) || (array[i][j].state == 1) || (array[i][j].state == 6)) // Se for inicio ou andado ou inimigo andado
				{
					for (int k = -1; k <= -1 ; k = k + 2)
					{
						if (array[i + k][j].state == 0 || (inimigosBool && array[i + k][j].state == 5)) // Se for andável
						{
							tmp_array[i + k][j].state = 1;
							tmp_array[i + k][j].parent = &array[i][j];
							flag++;	
						}
						if (array[i][j + k].state == 0 || (inimigosBool && array[i][j + k].state == 5)) // Se for andável
						{
							tmp_array[i][j + k].state = 1;
							tmp_array[i][j + k].parent = &array[i][j]; // endereço certo ??
							flag++;
						}
					}
				}
			}
		}
	
		arraycpy(array, tmp_array, rows, columns); // atualiza array pra ser tmp_array
		if ((flag == 0) && (endNode.parent == NULL)) //Se não fizer conexão nova e o fim não foi encontrado
		{
			pathArray[0] = NULLPOINT;
			return;
		}
	}
	int size;
	for(size = 0; size < 1000; size++)
	{
		pathArray[size] = getPoint(endNode, size);
		if ((pathArray[size].i == NULLPOINT.i) && (pathArray[size].j == NULLPOINT.j))
		{
			break;
		}
	}
	for (int i = 0; i < size; i++)
	{
		tmp_pathArray[i] = pathArray[size - i - 1];
	}
	for (int i = 0; i < size; i++)
	{
		pathArray[i] = tmp_pathArray[i];
	}
}

point getPoint(node currentNode, int ger)
{
	point NULLPOINT;
	NULLPOINT.i = -1;
	NULLPOINT.j = -1;
	
	if (currentNode.parent == NULL)
	{
		return NULLPOINT;
	}
	if (ger == 0)
	{
		return currentNode.pos;
	}
	else 
	{
		return getPoint(*currentNode.parent, ger - 1);
	}
}
