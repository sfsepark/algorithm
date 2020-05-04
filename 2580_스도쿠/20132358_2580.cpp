#include <stdio.h>
#include <vector>

using namespace std;

void fill_remain_horizon(vector<bool>& remain, vector<vector<int>>& sudoku, int x, int y){
  for(int i = 0 ; i < 9 ; i ++){
    if(sudoku[y][i] != 0){
      remain[sudoku[y][i] - 1] = 0;
    }
  }
}


void fill_remain_vertical(vector<bool>& remain,vector<vector<int>>& sudoku, int x, int y){
  for(int i = 0 ; i < 9 ; i ++){
    if(sudoku[i][x] != 0){
      remain[sudoku[i][x] - 1] = 0;
    }
  }
}

void fill_remain_square(vector<bool>& remain,vector<vector<int>>& sudoku, int x, int y){
  int square_x = x / 3 ;
  int square_y = y / 3;

  for(int i = square_y * 3 ; i < square_y * 3 + 3 ; i ++){
    for(int j = square_x * 3 ; j < square_x * 3 + 3 ; j ++){
      if(sudoku[i][j] != 0){
        remain[sudoku[i][j] -1] = 0;
      }
    }
  }
}

void print_sudoku(vector<vector<int>>& sudoku){
  
  for(int i = 0 ; i < 9 ; i ++){
    for(int j = 0 ; j < 9 ; j ++){
      printf("%d ", sudoku[i][j]);
    }
    printf("\n");
  }
}

bool fill_sudoku(vector<vector<int>>& sudoku, int x, int y){

  char tmp[9];
  vector<bool> remain(9,1);

  fill_remain_horizon(remain, sudoku, x, y);
  fill_remain_vertical(remain, sudoku, x, y);
  fill_remain_square(remain, sudoku, x, y);

  for(int r = 0 ; r < 9 ; r ++){
    if(remain[r] == 1){

      bool isFilled = true;

      sudoku[y][x] = r + 1;

      for(int i = 0 ; i < 9 ; i ++){
        for(int j = 0 ; j < 9 ; j ++){
          if(sudoku[i][j] == 0){
            isFilled = false;
            bool res;


            res = fill_sudoku(sudoku, j, i);

            if(res == true){
              return true;
            }
            else{
              goto escape;
            }
          }
        }
      }

escape:

      if(isFilled == true){
        return true;
      }

      sudoku[y][x] = 0;
    }
  }

  return false;
}

int main(void){

  vector<vector<int>> sudoku(9,vector<int>(9,0));


  int entry_y = -1;
  int entry_x = -1;
  
  for(int i = 0 ; i < 9 ; i ++){
    for(int j = 0 ; j < 9 ; j++){
      scanf("%d", &(sudoku[i][j]));

      if(sudoku[i][j] == 0){
        entry_y = i;
        entry_x = j;
      }
    }
  } 

  if(entry_y != -1 && entry_x != -1){
    fill_sudoku(sudoku, entry_x, entry_y);
  }

  print_sudoku(sudoku);

  return 0;
}