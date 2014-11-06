#include <stdio.h>

// Konstante für die Größe von der Matrix
#define SIZE 5

// Vordefinierte Funktionen
void printMatrix(int matrix[SIZE][SIZE]);
void rotateMatrixClockwise(int matrix[SIZE][SIZE]);
void rotateMatrixCounterClockwise(int matrix[SIZE][SIZE]);

int main(int argc, char **argv)
{
  // Erstelle eine matrix mit einer constanten Größe, z.B. SIZE
  /*int matrix[SIZE][SIZE] = {{0,1,0,0},
                            {0,2,3,0},
                            {0,0,4,0},
                            {0,0,5,0}};*/
  int matrix[SIZE][SIZE] = {{0,1,0,0,0},
                            {0,2,3,0,5},
                            {0,0,4,0,7},
                            {0,0,5,0,8},
                            {0,0,6,0,9}};
  // print die matrix mal aus
  printMatrix(matrix);
  // rotiere die matrix in Uhrzeigersinn
  rotateMatrixClockwise(matrix);
  printMatrix(matrix);
  rotateMatrixClockwise(matrix);
  printMatrix(matrix);
  // rotiere die matrix in gegen Uhrzeigersinn
  rotateMatrixCounterClockwise(matrix);
  printMatrix(matrix);
  return 0;
}

void printMatrix(int matrix[SIZE][SIZE])
{
  printf("Print of Matrix:\n");
  // Printen sollte eigenlich kein Problem sei ;)
  // Ist schaffbar ^^
  int x;
  int y;
  for (y = 0; y < SIZE; y++)
  {
    for (x = 0; x < SIZE; x++)
    {
      printf("%d ", matrix[y][x]);
    }
    printf("\n");
  }
  printf("\n");
}

void rotateMatrixClockwise(int matrix[SIZE][SIZE])
{
  printf("Rotation of Matrix Clockwise\n");
  // Das rotieren funktioniert nach dem folgenden Prinzip:
  // z.B.: Es ist ein Array gegeben mit den Elementen a = [1,2,3,4,5,6]
  // Nun ist gefragt, um das ganze array nach rechts zu verschieben,
  // Was heißt das jetzt?
  // Es muss nämlich das Array [6,1,2,3,4,5] rauskommen.
  /*
    
    Am besten ist es, man nimmt eine temp Variable, die nenne ich mal t.
    Um das ganze nach rechst zu verschieben, wird folgendes gemacht:
    Man speichere das letzte Element:           t = a[6]
    Setzte a[5] in a[6]:                        a[6] = a[5]
    Setzte a[4] in a[5]:                        a[5] = a[4]
    .......
    .......
    Setzte a[1] in a[2]:                        a[2] = a[1]
    Nun setzte t, was vorher a[6] war, in a[1]: a[1] = t

    Das man das Array nach links verschiebt, wird alles umgekehrt gemacht.
    t = a[1] und man geht nach rechts.
  */
  // Dass heißt, um ein Array nach links zu verschieben, muss man das verschieben
  // nach links machen, und umgekehrt.
  int x;
  int y;
  int temp;
  for (y = 0; y < (int)(SIZE / 2); y++)
  {
    for (x = 0; x < (int)((SIZE + 1) / 2); x++)
    {
      temp = matrix[y][x];
      matrix[y][x] = matrix[(SIZE - 1) - x][y];
      matrix[(SIZE - 1) - x][y] = matrix[(SIZE - 1) - y][(SIZE - 1) - x];
      matrix[(SIZE - 1) - y][(SIZE - 1) - x] = matrix[x][(SIZE - 1) - y];
      matrix[x][(SIZE - 1) - y] = temp;
    }
  }
  printf("\n");
}

void rotateMatrixCounterClockwise(int matrix[SIZE][SIZE])
{
  printf("Rotation of Matrix Counter Clockwise\n");
  int x;
  int y;
  int temp;
  for (y = 0; y < (int)(SIZE / 2); y++)
  {
    for (x = 0; x < (int)((SIZE + 1) / 2); x++)
    {
      temp = matrix[x][(SIZE - 1) - y];
      matrix[x][(SIZE - 1) - y] = matrix[(SIZE - 1) - y][(SIZE - 1) - x];
      matrix[(SIZE - 1) - y][(SIZE - 1) - x] = matrix[(SIZE - 1) - x][y];
      matrix[(SIZE - 1) - x][y] = matrix[y][x];
      matrix[y][x] = temp;
    }
  }
  printf("\n");
}