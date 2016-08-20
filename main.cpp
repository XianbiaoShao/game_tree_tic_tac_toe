#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define NELEMENTS(array)	(sizeof(array) / sizeof(array[0]))

#define empty	0
#define x		1
#define o		2

#define DARW			0
#define INPORGRESS		1
#define INFINITY		0x1000
#define WIN				(INFINITY)
#define LOSE			(-INFINITY)


int gameState(char board[9])
{
	char tst[][3] = {
		{ 0, 1, 2, },
		{ 3, 4, 5, },
		{ 6, 7, 8, },
		{ 0, 3, 6, },
		{ 1, 4, 7, },
		{ 2, 5, 8, },
		{ 0, 4, 8, },
		{ 2, 4, 6, },
	};
	
	for (int i = 0; i < NELEMENTS(tst); i++) {
		char chess = board[tst[i][0]];
		for (int j = 1; j < 3; j++) {
			chess &= board[tst[i][j]];
		}
		if (chess == o)
			return WIN;
		else if (chess == x)
			return LOSE;
	}
	
	for (int i = 0; i < 9; i++) {
		if (board[i] == empty)
			return INPORGRESS;
	}
	
	return DARW;
}

int minSearch(char board[9]);

int maxSearch(char board[9])
{
	int i;
	int positionValue = gameState(board);
	if (positionValue == DARW)
		return 0;
	
	if (positionValue != INPORGRESS)
		return positionValue;
	
	int bestValue = -INFINITY;
	
	for (i = 0; i < 9; i++) {
		if (board[i] == empty) {
			board[i] = o;
			int value = minSearch(board);
			if (value < bestValue)
				bestValue = value;
			
			board[i] = empty;
		}
	}
	
	return bestValue;
}

int minSearch(char board[9])
{
	int i;
	int positionValue = gameState(board);
	if (positionValue == DARW)
		return 0;
	
	if (positionValue != INPORGRESS)
		return positionValue;
	
	int worstValue = INFINITY;
	
	for (i = 0; i < 9; i++) {
		if (board[i] == empty) {
			board[i] = x;
			int value = maxSearch(board);
			if (value < worstValue)
				worstValue = value;
			
			board[i] = empty;
		}
	}
	
	return worstValue;
}

int minmax(char board[9])
{
	int i;
	int bestValue = -INFINITY;
	int index = 0;
	char bestMoves[9] = { 0 };
	
	for (i = 0; i < 9; i++) {
		if (board[i] == empty) {
			
			board[i] = o;
			
			int value = minSearch(board);
			if (value > bestValue) {
				bestValue = value;
				index = 0;
				bestMoves[index] = i;
			} else if (value == bestValue) {
				bestMoves[index++] = i;
			}
			
			board[i] = empty;
		}
	}
	
	if (index > 0)
		index = rand() % index;
	
	return index;
}

void printBoard(char board[9])
{
	printf("\n");
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (board[i * 3 + j] == x)
				printf("x ");
			else if (board[i * 3 + j] == o)
				printf("o ");
			else
				printf("_ ");
		}
		printf("\n");
	}
	printf("\n");
}

int main(int argc, char *argv[])
{
	char board[9];
	
	memset(board, 0, sizeof(board));
	int state = gameState(board);
	while (state == INPORGRESS) {
		int index = minmax(board);
		board[index] = o;
		printf("After computer choice\n");
		printBoard(board);
		state = gameState(board);
		if (state != INPORGRESS)
			break;
		
		printf("Input your choice\n");
		scanf("%d", &index);
		board[index % 9] = x;
		printBoard(board);
		state = gameState(board);
	}
	
	if (state == WIN)
		printf("Compute win\n");
	else if (state == LOSE)
		printf("Compute lose\n");
	else
		printf("darw\n");
	
	return 0;
}
