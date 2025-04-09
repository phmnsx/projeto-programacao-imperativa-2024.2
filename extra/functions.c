#include "functions.h"
#include <time.h>


node makeNode(node* pai, int i, int j) {
    node newNode;
    newNode.parent = pai;
    newNode.pos.i = i;
    newNode.pos.j = j;
    newNode.state = 0;
    return newNode;
}

void readArchive(char maze[MAXSIZE][MAXSIZE], int* rows, int* columns, char* archiveName) {
    FILE* archive = fopen(archiveName, "r");  
    if (archive == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        exit(1);
    }

    fscanf(archive, "%d %d", rows, columns);

    for (int i = 0; i < *rows; i++) {
        for (int j = 0; j < *columns; j++) {
            fscanf(archive, " %c", &maze[i][j]);
        }
    }
    fclose(archive);
}


void solveMaze(point* pathArray, node (*array)[], int rows, int columns, int inimigosBool, point end)
{	
	point NULLPOINT;
	NULLPOINT.i = -1;
	NULLPOINT.j = -1;
	
	point tmp_pathArray[400];
	node tmp_array[rows][columns];
	node tmp_array2[rows][columns];
	
	//transforma as arrays temporarias igual a array de entrada
	memcpy(tmp_array, array, sizeof(tmp_array));
	memcpy(tmp_array2, array, sizeof(tmp_array2));
	
	//inicializa endNode
	node endNode = makeNode(NULL, -1, -1);
	int flag;
	 
	while(endNode.parent == NULL) //enquanto endNode não foi encontrada
	{
		flag = 0;
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0 ; j < columns; j++) //para todo "i" e "j"
			{
				if ((tmp_array2[i][j].state == 3) || (tmp_array2[i][j].state == 1) || (tmp_array2[i][j].state == 6)) // Se for inicio ou andado ou inimigo andado
				{
					for (int k = -1; k < 2 ; k = k + 2) //olha nas posições "-1" e "1" relativas a j e k, ou seja, olha nas quatro posições adjacentes à node atual
					{
						
						if (((i + k) >= 0) && ((i + k) < rows))
						{
							if (tmp_array2[i + k][j].state == 4) //caso seja o final
							{
								tmp_array2[i + k][j].parent = &tmp_array2[i][j]; //parent do final é a node atual
								endNode = tmp_array2[i + k][j];

							}
							else if ((tmp_array2[i + k][j].state == 0) || (inimigosBool && (tmp_array2[i + k][j].state == 5))) // caso contrario, se for andável
							{
								tmp_array[i + k][j].state = 1;
								tmp_array[i + k][j].parent = &tmp_array2[i][j]; //parent dessa node é a node atual
								flag++;	
							}
						}
						
						
						if (((j + k) >= 0) && ((j + k) < columns))
						{
							if (tmp_array2[i][j + k].state == 4)
							{
								tmp_array2[i][j + k].parent = &tmp_array2[i][j];
								endNode = tmp_array2[i][j + k];
							}
							else if ((tmp_array2[i][j + k].state == 0) || (inimigosBool && (tmp_array2[i][j + k].state == 5))) // Se for andável
							{
								tmp_array[i][j + k].state = 1;
								tmp_array[i][j + k].parent = &tmp_array2[i][j]; // endereço certo ??
								flag++;
							}
						}
					}
				}
			}
		}
		memcpy(tmp_array2, tmp_array, sizeof(tmp_array)); // atualiza tmp_array2 pra ser tmp_array
														  // são utilizadas duas arrays porque se uma array fosse lida e modificada ao mesmo tempo ocorreriam coisas 
														  // inesperadas e/ou inadequadas
		
		if (inimigosBool) //se não está considerando inimigos como paredes
		{
			inimigosBool = 0; //desconsidere como paredes
			if (flag == 0)    // porem, se desconsidera inimigos como paredes e não achou caminho, o labirinto não possui solução
			{
				pathArray[0] = NULLPOINT;
				return;
			}
		}
		if ((flag == 0)) //Se não fizer conexão nova e o fim não foi encontrado
		{
			inimigosBool = 1;
		}
	}
	int size;
	
	for(size = 0; size < 400; size++) //coloca os pontos, do fim ao inicio, na array, percorrendo os "parents"
	{
		pathArray[size] = getPoint(endNode, size);
		if ((pathArray[size].i == NULLPOINT.i) && (pathArray[size].j == NULLPOINT.j))
		{
			break;
		}
	}
	for (int i = 0; i < size; i++) //inverte a array
	{
		tmp_pathArray[i] = pathArray[size - i - 1];
	}
	for (int i = 0; i < size; i++)
	{
		pathArray[i] = tmp_pathArray[i];
	}
}

point getPoint(node currentNode, int ger) { //currentNode representa o node atual em "analise" e "ger" quantos mais faltam para chegar no "destino"
    point NULLPOINT = {-1, -1};				//a função utiliza de recursão pra encontrar a node com "ger" distância da ultima node.
    if (currentNode.parent == NULL) {
        return NULLPOINT;
    }
    return (ger == 0) ? currentNode.pos : getPoint(*currentNode.parent, ger - 1);
}

void charToTile(char maze[MAXSIZE][MAXSIZE], tile parte[MAXSIZE][MAXSIZE], point* start, point* end, int rows, int columns) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
			// Zera todos os campos da struct para evitar valores residuais
            parte[i][j] = (tile){0};
            switch (maze[i][j]) {
                case '@':
                    parte[i][j].inicio = 1;
                    start->i = i;
                    start->j = j;
					//printf("DEBUG: Start definido em (%d, %d)\n", start->i, start->j);
                    break;
                case '#':
                    parte[i][j].parede = 1;
                    break;
                case '.':
                    parte[i][j].chao = 1;
                    break;
                case '%':
                    parte[i][j].inimigo = 1;
                    break;
                case '$':
                    parte[i][j].saida = 1;
                    end->i = i;
                    end->j = j;
					//printf("DEBUG: end definido em (%d, %d)\n", end->i, end->j);
                    break;
                case '*':
                    parte[i][j].andou = 1;
                    break;
                case '+':
                    parte[i][j].morreu = 1;
                    break;
                case '!':
                    parte[i][j].matou = 1;
                    break;
                case 'v':
                    parte[i][j].vitoria = 1;
                    break;
                default:
                    printf("Erro: Caractere inválido '%c' na posição (%d, %d)\n", maze[i][j], i, j);
                    exit(1); 
            }
        }
    }
}


void pathTileChar(point path[400], tile parte[MAXSIZE][MAXSIZE], char maze[MAXSIZE][MAXSIZE], int rows, int columns) {
    int x, y, p, xf, yf;

    for (p = 0; p < 400; p++) {
        if (path[p].i != -1 && path[p].j != -1) {
            x = path[p].i;
            y = path[p].j;

            if (parte[x][y].matou != 1 && parte[x][y].morreu != 1) { // Transforma o caminho em um tile
                parte[x][y].andou = 1;
                parte[x][y].chao = 0;
            }

            if (parte[x][y].andou == 1 && parte[x][y].saida == 1) { // Marca vitoria
                parte[x][y].andou = 0;
                parte[x][y].saida = 0;
                parte[x][y].vitoria = 1;
            }
            
         
        } else break;  
    }
		p= p-1;
		xf = path[p].i;
		yf = path[p].j;
		
		if (parte[xf][yf].vitoria != 1 && parte[xf][yf].morreu != 1){ // Detecta se o personagem se perdeu
			parte[xf][yf].perdeu = 1;
			parte[xf][yf].andou =0;
			
		}
}

 

void cleanerpath(point path[400], tile parte[MAXSIZE][MAXSIZE], int porcentWin){ // limpa o caminho ou mata o personagem
	int x, y;
	for (int p = 0; p < 400; p++){
		if ((path[p].i != -1) && (path[p].j !=-1)){
			x = path[p].i;
			y = path[p].j;
    	}else { break; } 
		
		if (parte[x][y].inimigo == 1){ //tem inimigo
			
			if (porcentWin > rand() % 9){ //ganha a luta
				parte[x][y].matou = 1;
				
				if (porcentWin <= 9){
					porcentWin++;
			 }	
		}
		else { //perde a luta
				parte[x][y].morreu = 1;
				path[p+1].i = -1;
				path[p+1].j = -1;
				break;
			}	
		parte[x][y].inimigo = 0;
		
		}
	}	
}


void printSolvedMaze(tile maze[MAXSIZE][MAXSIZE], int rows, int columns) {
	int flag = 0;
	for (int i = 0; i < rows ; i++)
	{
		for ( int j = 0; j < columns; j++)
		{
			if (maze[i][j].morreu)
			{
				flag = 1;
			}
			
			if (maze[i][j].vitoria)
			{
				flag = -1;
			}
			if (maze[i][j].perdeu)
			{
				flag = 2;
			}
	}
}
	if (flag == 1)
	{
		printf("\nPersonagem Morreu:\n");
	}
	else if (flag == 2)
	{
		printf("\nO personagem se perdeu:\n");
	}
	else if ( flag == 0)
	{
		  printf ("\nLabirinto escolhido:\n");
	}
	else
    {
		printf("\nLabirinto resolvido:\n");
		
	}
	
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            if (maze[i][j].inicio) printf("@ ");
            else if (maze[i][j].parede) printf("# ");
            else if (maze[i][j].saida) printf("$ ");
            else if (maze[i][j].vitoria) printf("V ");
            else if (maze[i][j].matou) printf("! ");
            else if (maze[i][j].morreu) printf("+ ");
            else if (maze[i][j].andou) printf("* ");
            else if (maze[i][j].perdeu) printf("? ");
            else if (maze[i][j].inimigo) printf("%% ");
            else printf(". ");
        }
        printf("\n");
    }
    printf("\n");
}


void saveSolvedMaze(tile maze[MAXSIZE][MAXSIZE], int rows, int columns, const char *filename) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo %s para escrita.\n", filename);
        return;
    }

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            if (maze[i][j].inicio) fprintf(file, "@ ");
            else if (maze[i][j].parede) fprintf(file, "# ");
            else if (maze[i][j].saida) fprintf(file, "$ ");
            else if (maze[i][j].vitoria) fprintf(file, "V ");
            else if (maze[i][j].matou) fprintf(file, "! ");
            else if (maze[i][j].morreu) fprintf(file, "+ ");
            else if (maze[i][j].andou) fprintf(file, "* ");
            else if (maze[i][j].perdeu) fprintf(file, "? ");
            else if (maze[i][j].inimigo) fprintf(file, "%% ");
            else fprintf(file, ". ");
        }
        fprintf(file, "\n");
    }

    fclose(file);
    printf("Labirinto resolvido salvo no arquivo %s.\n", filename);
}

int solveMazeRand(point* pathArray, tile maze[MAXSIZE][MAXSIZE], int rows, int columns, int inimigosBool, point end, int tentativa) {
	srand(time(NULL) + tentativa); // deixando o rand aleatório
    point NULLPOINT = {-1, -1};
    point arraySec[4];       
    point arrayCaminhavel[4]; 
    int cont = 0;
    int p = 0;
    int i, j;

    for (i = 0; i < rows; i++) {
        for (j = 0; j < columns; j++) {
            if (maze[i][j].inicio == 1) {
                pathArray[p].i = i;
                pathArray[p].j = j;
                p++;
                break;
            }
        }
        if (p > 0) break; 
    }

    if (p == 0) { 
        pathArray[0] = NULLPOINT;
        return 0;
    }

    while (p < 400) {
        int ultimox = pathArray[p-1].i;
        int ultimoy = pathArray[p-1].j;

        if (maze[ultimox][ultimoy].saida == 1) {
			pathArray[p] = NULLPOINT;
            return 1;
        }

        arraySec[0].i = ultimox + 1;
        arraySec[0].j = ultimoy;
        
        arraySec[1].i = ultimox - 1;
        arraySec[1].j = ultimoy;
        
        arraySec[2].i = ultimox;
        arraySec[2].j = ultimoy + 1; 
        
        arraySec[3].i = ultimox;
        arraySec[3].j = ultimoy - 1;

        cont = 0;
        for (int n = 0; n < 4; n++) {

            if ((arraySec[n].i >= 0) && (arraySec[n].i < rows) &&
                (arraySec[n].j >= 0) && (arraySec[n].j < columns) &&
                (maze[arraySec[n].i][arraySec[n].j].parede != 1) && (maze[arraySec[n].i][arraySec[n].j].andou != 1)) {

                int passou = 0;
                for (int k = 0; k < p; k++) {
                    if ((pathArray[k].i == arraySec[n].i) && (pathArray[k].j == arraySec[n].j)) { //verifica se ele nao andou (?)
                        passou = 1;
                        break;
                    }
                }

                if (passou == 0) {
                    arrayCaminhavel[cont++] = arraySec[n]; 
                }
            }
        }

        if (cont > 0) {
            int escolha = rand() % cont;
            pathArray[p] = arrayCaminhavel[escolha];
            p++;
        } 

        else {
            pathArray[p] = NULLPOINT;
            return 0;
        }
    }

  return 0;
}
