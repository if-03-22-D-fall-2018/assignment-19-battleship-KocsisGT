/*-----------------------------------------------------------------------------
 *				HTBLA-Leonding / Class: <your class name here>
 *-----------------------------------------------------------------------------
 * Exercise Number: #exercise_number#
 * File:			battleship.c
 * Author(s):		Peter Bauer
 * Due Date:		#due#
 *-----------------------------------------------------------------------------
 * Description:
 * <your description here>
 *-----------------------------------------------------------------------------
*/
#include <stdio.h>

#include "battleship.h"

FILE* myFd;
FILE* opFd;
CellContent myCell[FIELDSIZE][FIELDSIZE];
CellContent opCell[FIELDSIZE][FIELDSIZE];
CellContent guess[FIELDSIZE][FIELDSIZE];

void load_game()
{
  myFd = fopen("battleship.my", "r");
  opFd = fopen("battleship.op", "r");

  fread(&myCell, sizeof(myCell), 1, myFd);
  fread(&opCell, sizeof(opCell), 1, opFd);

  for (int i = 0; i < FIELDSIZE; i++)
  {
    for (int j = 0; j < FIELDSIZE; j++)
    {
      guess[i][j] = Unknown;
    }
  }
}

CellContent get_shot(int row, int col)
{
  if(row < 0 || row > FIELDSIZE-1 || col < 0 || col > FIELDSIZE-1)
  {
    return OutOfRange;
  }
  return myCell[row][col];
}

void fill_water(int row, int col);

bool shoot(int row, int col)
{
  if(row < 0 || row > FIELDSIZE-1 || col < 0 || col > FIELDSIZE-1){
    return false;
  }
  if(opCell[row][col] == Boat)
  {
    fill_water(row, col);
    return true;
  }
  else if(opCell[row][col] == Water)
  {
    guess[row][col] = Water;
    return true;
  }
  return false;

}

void fill_water(int row, int col)
{
  for (int i = -1; i <= 1; i++)
  {
    for (int j = -1; j <= 1; j++)
    {
      if((row-i >= 0 && row-i < FIELDSIZE) && (col-j >= 0 && col-j < FIELDSIZE))
      {
          guess[row-i][col-j] = Water;
      }
    }
  }
  guess[row][col] = Boat;
}

CellContent get_my_guess(int row, int col)
{
  if(row < 0 || row > FIELDSIZE-1 || col < 0 || col > FIELDSIZE-1)
  {
    return OutOfRange;
  }
  return guess[row][col];
}
