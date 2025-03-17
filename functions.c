#include "functions.h"

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


void solveMaze (point* pathArray, node (*array)[], int rows, int columns, int inimigosBool, point end)
{	
	point NULLPOINT;
	NULLPOINT.i = -1;
	NULLPOINT.j = -1;
	
	point tmp_pathArray[400];
	node tmp_array[rows][columns];
	node tmp_array2[rows][columns];
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns ; j++)
		{
			tmp_array[i][j] = makeNode(NULL, -1, -1);
			tmp_array2[i][j] = makeNode(NULL, -1, -1);
			
		}
	}
	memcpy(tmp_array, array, sizeof(tmp_array));
	memcpy(tmp_array2, array, sizeof(tmp_array2));
	
	node endNode = makeNode(NULL, -1, -1);
	int flag;
	 
	while(endNode.parent == NULL)
	{
		flag = 0;
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0 ; j < columns; j++)
			{
				if ((tmp_array2[i][j].state == 3) || (tmp_array2[i][j].state == 1) || (tmp_array2[i][j].state == 6)) // Se for inicio ou andado ou inimigo andado
				{
					for (int k = -1; k < 2 ; k = k + 2)
					{
						if (((i + k) >= 0) && ((i + k) < rows))
						{
							if (tmp_array2[i + k][j].state == 4)
							{
								tmp_array2[i + k][j].parent = &tmp_array2[i][j];
								endNode = tmp_array2[i + k][j];

							}
							else if ((tmp_array2[i + k][j].state == 0) || (inimigosBool && (tmp_array2[i + k][j].state == 5))) // Se for andável
							{
								tmp_array[i + k][j].state = 1;
								tmp_array[i + k][j].parent = &tmp_array2[i][j];
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
		memcpy(tmp_array2, tmp_array, sizeof(tmp_array)); // atualiza array pra ser tmp_array
		
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

point getPoint(node currentNode, int ger) {
    point NULLPOINT = {-1, -1};
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
    int x, y, p;

    for (p = 0; p < 400; p++) {
        if (path[p].i != -1 && path[p].j != -1) {
            x = path[p].i;
            y = path[p].j;

            if (parte[x][y].matou == 0 && parte[x][y].morreu == 0) { // Transforma o caminho em um tile
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
		if (parte[path[p].i][path[p].j].saida != 1){ // Detecta se o personagem se perdeu
			parte[path[p].i][path[p].j].perdeu = 1;
			parte[path[p].i][path[p].j].andou =0;
			
		}

   /* for (int a = 0; a < rows; a++) {
        for (int b = 0; b < columns; b++) {
            if (parte[a][b].morreu == 1) {
                printf("+");  // TODO ver qual eh o simbolo de perdeu...
            } else if (parte[a][b].matou == 1) {
                printf("!");
            } else {
                printf("%c", maze[a][b]);
            }
        }
        printf("\n");
    } */
}

 

void cleanerpath (point path[400], tile parte[MAXSIZE][MAXSIZE], int porcentWin){ // limpa o caminho ou mata o personagem
	int x, y;
	for (int p = 0; p < 400; p++){
		if ((path[p].i != -1) && (path[p].j !=-1)){
			x = path[p].i;
			y = path[p].j;
    	}else break;
		
		if (parte[x][y].inimigo == 1){ //tem inimigo
			
			if (porcentWin > rand() % 9){ //ganha a luta
				parte[x][y].matou = 1;
				parte[x][y].inimigo = 0;
				
				if (porcentWin <= 9){
					porcentWin++;
			 }	
		}
		else { //perde a luta
				parte[x][y].morreu = 1;
				parte[x][y].inimigo = 0;
				path[p+1].i = -1;
				path[p+1].j = -1;
				break;
			}	

		}
	}	
}


void printSolvedMaze(tile maze[MAXSIZE][MAXSIZE], int rows, int columns) {
    printf("\nLabirinto resolvido:\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            if (maze[i][j].inicio) printf("@ ");
            else if (maze[i][j].parede) printf("# ");
            else if (maze[i][j].inimigo) printf("%% ");
            else if (maze[i][j].saida) printf("$ ");
            else if (maze[i][j].vitoria) printf("V ");
            else if (maze[i][j].matou) printf("! ");
            else if (maze[i][j].morreu) printf("+ ");
            else if (maze[i][j].andou) printf("* ");
             else if (maze[i][j].perdeu) printf("? ");
            else printf(". ");
        }
        printf("\n");
    }
}


