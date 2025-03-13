#include <stdio.h>
#include <stdlib.h>
#include "functions.c"

/* Constantes */
#define MAXSIZE 20

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
	int inicio;
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

void solveMaze (point pathArray[400], node array[MAXSIZE][MAXSIZE], int rows, int columns, int inimigosBool, point end); // solveMaze resolve o labirinto e guarda o caminho em "PathArray", não sei fazer
																														  // tamanho dinâmico e recomendo q vc coloque esse msm tamanho aí na array q vc quer a
																														  // resposta qnd for usar. pathArray [point inicio .... point final, NULLPOINT]
																														  // NULLPOINT é (-1, -1) pq não tem esse espaço uma array ent da pra vc sempre falar
																														  // q n era pra ter nada ali (determinar o final da leitura talvez?)
																														  // se o ínicio for NULLPOINT não achou caminho.
																														  
void readArchive(char maze[MAXSIZE][MAXSIZE], int *rows, int *columns, char *archiveName); 							  
point getPoint(node currentNode, int ger); // função auxiliar pra a "lista" de parents de um node (vc não vai usar)
<<<<<<< Updated upstream
<<<<<<< Updated upstream
void charToTile (char maze[MAXSIZE][MAXSIZE], tile parte [MAXSIZE][MAXSIZE]); // função que transforma todos os chars do labirinto em tiles
=======
void charToTile (char maze[MAXSIZE][MAXSIZE], tile parte [MAXSIZE][MAXSIZE], point* start, point* end, int rows, int columns); // função que transforma todos os chars do labirinto em tiles   ; adicionado: pointer do ponto inicio e saída : )
>>>>>>> Stashed changes
=======
void charToTile (char maze[MAXSIZE][MAXSIZE], tile parte [MAXSIZE][MAXSIZE], point* start, point* end, int rows, int columns); // função que transforma todos os chars do labirinto em tiles   ; adicionado: pointer do ponto inicio e saída : )
>>>>>>> Stashed changes

int main()
{
	//ler modo
	int modo = 0;
	// diferente != 
	while (modo != 4){
	printf ("qual o modo?\n"); //da flush no terminal
	scanf ("%i", &modo);
	if (modo == 1){
		
		void solveMaze (point pathArray[400], node array[MAXSIZE][MAXSIZE], int rows, int columns, int inimigosBool, point end);
	}
	
	if (modo == 2) {
		
		
	}
	
	if (modo == 3){
		
	}



	if (modo == 4){
			//return 0;
	}
	

	//tamanho[i][j]
	char rawMaze[MAXSIZE][MAXSIZE];
	tile maze[MAXSIZE][MAXSIZE];
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
	
	node array[rows][columns]; // i j, então rows columns
	node tmp_array[rows][columns];
	
	//criar nodes, e "ativar" a no start
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			array[i][j] = makeNode(NULL, i, j); //crie uma node [i][j] andável
			if (!maze[i][j].chao) //caso não seja chão
			{
				array[i][j].state = -1;//faça ser não andável
			}

			if ((i == start.i) && (j == start.j))
			{
				array[i][j].state = 3; // node inicio   
			}
		}
	}
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns ; j++)
		{
			tmp_array[i][j] = makeNode(NULL, -1, -1);
		}
	}
	arraycpy(tmp_array, array, rows, columns); //criar função q (cópia, copiado)
								//recebe pointer de array e tamanhos?
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns ; j++)
		{
			printf("(%d %d) ", tmp_array[i][j].pos.i, tmp_array[i][j].pos.j);
		}
		printf("\n");
	}
	//caso espaço seja andável, criar node nele;
	//repete para todos os nodes
	point pathArr[400];
	int inimigos = 0;
	
	//função de (tile maze[][] -> node array[][]) !! 
	
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


void solveMaze(point pathArray[400], node array[MAXSIZE][MAXSIZE], int rows, int columns, int inimigosBool, point end)
{
	point NULLPOINT;
	NULLPOINT.i = -1;
	NULLPOINT.j = -1;
	
	point tmp_pathArray[400];
	node tmp_array[rows][columns];
	node endNode = makeNode(NULL, -1, -1);
	int flag;
	 
	while(endNode.parent == NULL)
	{
		flag = 0;
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0 ; j < columns; j++)
			{
				if (array[i][j].state == 4)
				{
					endNode = array[i][j];
				}
				if ((array[i][j].state == 3) || (array[i][j].state == 1) || (array[i][j].state == 6)) // Se for inicio ou andado ou inimigo andado
				{
					for (int k = -1; k < 2 ; k = k + 2)
					{
						if ((array[i + k][j].state == 0) || (inimigosBool && (array[i + k][j].state == 5))) // Se for andável
						{
							printf("%d %d", array[i][j].pos.i, array[i][j].pos.j);
							tmp_array[i + k][j].state = 1;
							tmp_array[i + k][j].parent = &array[i][j];
							flag++;	
						}
						if ((array[i][j + k].state == 0) || (inimigosBool && (array[i][j + k].state == 5))) // Se for andável
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
	for(size = 0; size < 400; size++)
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

<<<<<<< Updated upstream
<<<<<<< Updated upstream
void charToTile (char maze[MAXSIZE][MAXSIZE], tile parte[MAXSIZE][MAXSIZE]){
	for (int i =0; i< MAXSIZE; i++){
	for (int j = 0; j <MAXSIZE; j++){
=======
=======
>>>>>>> Stashed changes
void charToTile (char maze[MAXSIZE][MAXSIZE], tile parte [MAXSIZE][MAXSIZE], point* start, point* end, int rows, int columns){
	for (int i =0; i< rows; i++){
	for (int j = 0; j < columns; j++){
		if (maze[i][j] == '@'){
			parte[i][j].inicio = 1;
			start->i = i;
			start->j = j;
		}
<<<<<<< Updated upstream
>>>>>>> Stashed changes
=======
>>>>>>> Stashed changes
		if (maze[i][j] == '#'){ 
			parte[i][j].parede = 1;
		}
		if (maze[i][j] == '.'){ 
			parte[i][j].chao = 1 ;
		}
		if (maze[i][j] == '%'){ 
			parte[i][j].inimigo = 1;
		}
<<<<<<< Updated upstream
<<<<<<< Updated upstream
		if (maze[i][j] == '$'){ 
			parte[i][j].chegada = 1;
	}
		if (maze[i][j] == '*'){ 
			parte[i][j].andou = 1;
	}
		if (maze[i][j] == '+'){
			parte[i][j].morreu = 1;
	}
		if (maze[i][j] == '!'){
			parte[i][j].matou = 1;
	}
		if (maze[i][j] == '$'){
			parte[i][j].saida = 1 ;
	}
=======
=======
>>>>>>> Stashed changes

		if (maze[i][j] == '*'){ 
			parte[i][j].andou = 1;
	   }
		if (maze[i][j] == '+'){
			parte[i][j].morreu = 1;
	   }
		if (maze[i][j] == '!'){
			parte[i][j].matou = 1;
	   }
		if (maze[i][j] == '$'){
			parte[i][j].saida = 1 ;
			end->i = i;
			end->j = j;
	   }
<<<<<<< Updated upstream
>>>>>>> Stashed changes
=======
>>>>>>> Stashed changes
		if (maze[i][j] == 'v'){
			parte[i][j].vitoria=1 ;
	}
}
}
<<<<<<< Updated upstream
<<<<<<< Updated upstream
=======


>>>>>>> Stashed changes
=======


>>>>>>> Stashed changes
}
