#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "functions.h"

#define MAXSIZE 10

/*
    Como usar o assert: 
   http://devfuria.com.br/linguagem-c/entendendo-o-assert-c/
    x = 7;
    assert(x == 7); ----> 
*/

void test_makeNode() {
    node parentNode = makeNode(NULL, 0, 0);
    node newNode = makeNode(&parentNode, 2, 3);
    
    assert(newNode.parent == &parentNode);
    assert(newNode.pos.i == 2);
    assert(newNode.pos.j == 3);
    assert(newNode.state == 0);

    printf("test_makeNode passou\n");
}

void test_readArchive() {
    char maze[MAXSIZE][MAXSIZE];
    int rows, columns;
    
    FILE *file = fopen("test_maze.txt", "w");
    fprintf(file, "3 3\n@.#\n.#.\n#$.\n");
    fclose(file);
    
    readArchive(maze, &rows, &columns, "test_maze.txt");

    assert(rows == 3);
    assert(columns == 3);

    printf("test_readArchive passou\n");
}

void test_solveMaze() {
    point pathArray[400];
    node array[MAXSIZE][MAXSIZE];
    
    for (int i = 0; i < MAXSIZE; i++){
        for (int j = 0; j < MAXSIZE; j++){
            array[i][j] = makeNode(NULL, i, j);
        }
    }
       
    
    point end = {2, 2};
    solveMaze(pathArray, array, 3, 3, 0, end);

   

    printf("test_solveMaze passou\n");
}

void test_getPoint() {
    node rootNode = makeNode(NULL, 1, 1);
    node childNode = makeNode(&rootNode, 2, 2);

    point result = getPoint(childNode, 0);
    assert(result.i == 2 && result.j == 2);


    printf("test_getPoint passou\n");
}

void test_charToTile() {
    char maze[MAXSIZE][MAXSIZE] = {
        {'@', '#', '.'},
        {'%', '$', '*'},
        {'+', '!', 'v'}
    };
    tile parte[MAXSIZE][MAXSIZE];
    point start, end;
    
    charToTile(maze, parte, &start, &end, 3, 3);

    assert(parte[0][0].inicio == 1);
    assert(parte[0][1].parede == 1);
    assert(parte[0][2].chao == 1);
    assert(parte[1][0].inimigo == 1);
    assert(parte[1][1].saida == 1);
    assert(parte[1][2].andou == 1);
    assert(parte[2][0].morreu == 1);
    assert(parte[2][1].matou == 1);
    assert(parte[2][2].vitoria == 1);
    assert(start.i == 0 && start.j == 0);
    assert(end.i == 1 && end.j == 1);

    printf("test_charToTile passou\n");
}

int main() {
    test_makeNode();
    test_readArchive();
    test_solveMaze();
    test_getPoint();
    test_charToTile();
    
    printf("Todos os testes passaram\n");
    return 0;
}
