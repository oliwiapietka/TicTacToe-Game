#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 3 // size of board

const char PLAYER = 'X';
const char COMPUTER = 'O';

void resetBoard(char board[][N], int n)
{
  for (int i = 0; i < n; ++i)
  {
    for (int j = 0; j < n; ++j)
    {
      board[i][j] = ' ';
    }
  }
}

void printBoard(char board[][N], int n)
{
  for (int i = 0; i < n; ++i)
  {
    printf(" %c | %c | %c", board[i][0], board[i][1], board[i][2]);
    if (i <= n - 1)
    {
      printf("\n---|---|---\n");
    }
    else
    {
      printf("\n");
    }
  }
}

int checkFreeSpaces(char board[][N], int n)
{
  int freeSpaces = N * N;
  for (int i = 0; i < n; ++i)
  {
    for (int j = 0; j < n; ++j)
    {
      if (board[i][j] != ' ')
      {
        freeSpaces--;
      }
    }
  }
  return freeSpaces;
}

int readInt(int x, int y)
{
  int number;
  while (scanf("%d", &number) != 1 || number < x || number > y || getchar() != '\n')
  {
    printf("\nIncorrect data, number should be in the range of %d and %d", x, y);
    // clear keyboard buffer
    while (getchar() != '\n')
      ;
  }
  return number;
}

void playerMove(char board[][N])
{
  int m;
  int n;
  do
  {
    printf("\nPick a row (1-3): ");
    m = readInt(1, N);
    m--;
    printf("\nPick a column (1-3): ");
    n = readInt(1, N);
    n--;
    if (board[m][n] != ' ')
    {
      printf("\nInvalid move!");
    }
    else
    {
      board[m][n] = PLAYER;
      break;
    }
  } while (board[m][n] != ' ');
}

char checkWinner(char board[][N], int n)
{
  // check rows
  for (int i = 0; i < n; ++i)
  {
    if (board[i][0] == board[i][1] && board[i][1] == board[i][2])
    {
      return board[i][0];
    }
  }
  // check columns
  for (int i = 0; i < n; ++i)
  {
    if (board[0][i] == board[1][i] && board[1][i] == board[2][i])
    {
      return board[0][i];
    }
  }
  // check diagonals
  if (board[0][0] == board[1][1] && board[1][1] == board[2][2])
  {
    return board[0][0];
  }
  if (board[0][2] == board[1][1] && board[0][2] == board[2][0])
  {
    return board[0][2];
  }
  // no winner
  return ' ';
}

void printWinner(char winner)
{
  if (winner == PLAYER)
  {
    printf("\nYOU WON THIS GAME!");
  }
  else if (winner == COMPUTER)
  {
    printf("\nYOU LOST THIS GAME!");
  }
  else
  {
    printf("\nIT'S A TIE!");
  }
}

void computerMove(char board[][N], char winner)
{
  srand((unsigned)time(NULL));
  int x;
  int y;
  if (checkFreeSpaces(board, N) > 0)
  {
    do
    {
      x = rand() % 3;
      y = rand() % 3;
    } while (board[x][y] != ' ');
    board[x][y] = COMPUTER;
  }
  else
  {
    printWinner(winner);
  }
}

int main()
{
  char winner = ' ';
  char board[N][N];
  char response = 'Y';
  do
  {
    resetBoard(board, N);
    while (winner == ' ' && checkFreeSpaces(board, N) != 0)
    {
      printBoard(board, N);
      // PLAYER
      playerMove(board);
      winner = checkWinner(board, N);
      if (winner != ' ' && checkFreeSpaces(board, N) == 0)
      {
        break;
      }
      // COMPUTER
      computerMove(board, winner);
      winner = checkWinner(board, N);
      if (winner != ' ' && checkFreeSpaces(board, N) == 0)
      {
        break;
      }
    };
    printBoard(board, N);
    printWinner(winner);

    while (winner != ' ')
    {
      printf("\nDo you want to continue the game (Y/N)?: ");
      while (scanf(" %c", &response) != 1 || (response != 'Y' && response != 'N' && response != 'y' && response != 'n') || getchar() != '\n')
      {
        printf("\nIncorrect data, your response should be Y or N.");
        while (getchar() != '\n')
          ;
      }
      winner = ' ';
    };
  } while (response == 'Y' || response == 'y');
  return 0;
}