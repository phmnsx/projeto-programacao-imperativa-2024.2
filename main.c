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
int parede = 0;
int chao = 0;
int inimigo = 0;
int inicio = 0;
int chegada = 0;
int andou = 0;
int morreu = 0;
int matou = 0;
int vitoria = 0;
} tile;


int main()
{
	//ler modo
	//abrir arquivo e ler labirinto (saber tamanho?)
	//tamanho[i][j]
	
	//determinar posição inicial, em (i j) e criar node
	//determinar posição final
	//ler os espaços que tem em volta da primeira node;
	
	//caso espaço seja andável, criar node nele;
	//repete para todos os nodes
	
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
