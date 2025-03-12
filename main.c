#include <stdio.h>
#include <stdlib.h>

typedef struct 
{
	int i;
	int j;
} point;

typedef struct node node;
struct node
{
	point pos;
	struct node* origin;
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
	point pos;
} tile;

node gerarNode(node pai, int i, int j);

void readNode(node nodulo, tile maze[100][100], int maxI, int maxJ);


int main()
{
	//ler modo
	const int TAMANHO_X = 100; //Placeholder de tamanho
	const int TAMANHO_Y = 100;

	//abrir arquivo e ler labirinto (saber tamanho?)
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
				start.origin = NULL;
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

node gerarNode(node pai, int i, int j)
{
	node newNode;
	newNode.origin = &pai;
	newNode.pos.i = i;
	newNode.pos.j = j;
	return newNode;
}

void readNodes(node nodulo, tile** maze, int maxI, int maxJ, int inimigos)
{

	if(nodulo.pos.i + 1 < maxI)
	{
		if (maze[nodulo.pos.i + 1][nodulo.pos.j].chao || (inimigos && maze[nodulo.pos.i + 1][nodulo.pos.j].inimigo))
		{
			maze[nodulo.pos.i + 1][nodulo.pos.j].chao = 0;
			readNodes(gerarNode(nodulo, nodulo.pos.i + 1, nodulo.pos.j), maze, maxI, maxJ, inimigos);
		}
	}
	if(nodulo.pos.i - 1 > 0)
	{
				if (maze[nodulo.pos.i - 1][nodulo.pos.j].chao || (inimigos && maze[nodulo.pos.i - 1][nodulo.pos.j].inimigo))
		{
			maze[nodulo.pos.i + 1][nodulo.pos.j].chao = 0;
			readNodes(gerarNode(nodulo, nodulo.pos.i - 1, nodulo.pos.j), maze, maxI, maxJ, inimigos);
		}
	}

	if(nodulo.pos.j + 1 < maxJ)
	{
		if (maze[nodulo.pos.i][nodulo.pos.j + 1].chao || (inimigos && maze[nodulo.pos.i][nodulo.pos.j + 1].inimigo))
		{
			maze[nodulo.pos.i][nodulo.pos.j + 1].chao = 0;
			readNodes(gerarNode(nodulo, nodulo.pos.i, nodulo.pos.j + 1), maze, maxI, maxJ, inimigos);
		}
	}
	if(nodulo.pos.j - 1 > 0)
	{
		if (maze[nodulo.pos.i][nodulo.pos.j -1].chao || (inimigos && maze[nodulo.pos.i][nodulo.pos.j - 1].inimigo))
		{
			maze[nodulo.pos.i][nodulo.pos.j - 1].chao = 0;
			readNodes(gerarNode(nodulo, nodulo.pos.i, nodulo.pos.j - 1), maze, maxI, maxJ, inimigos);
		}
	}
}
