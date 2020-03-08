#include <iostream>
#include <string.h>

using namespace std;

bool answer[1024 * 3][1024 * 6];

void removeCenter(int x, int y , int N){
    for(int h = N / 2 ; h < N ; h ++){
        for(int w = h ; w < 2* N - 1 - h ; w ++){
            answer[y + h][x + w] = 0;
        }
    }
}

void drawTriangle(int x, int y , int N){
    if(N == 3){
        answer[y + 1][x+2] = 0;
    }
    else{
        removeCenter(x,y,N);
        drawTriangle(x + N /2  , y ,N / 2 );
        drawTriangle(x, y + N / 2 ,N / 2 );
        drawTriangle(x + N, y + N / 2 ,N / 2 );
    }
}

int main(void){
    
    int N = 0;
    int w,h;

    memset(answer, 0 , sizeof(answer));

    cin >> N;

    h = N;
    w = h *2 - 1;

    for(int i = 0 ; i < h ; i ++){
        for(int j = i ; j <  w - i ; j ++){
            answer[h - i - 1][j] = 1;
        }
    }

    drawTriangle(0,0,N);


    for(int i = 0 ; i < h ; i ++){
        for(int j = 0 ; j < w ; j ++){
            cout << (answer[i][j] ? "*": " ");
        }
        cout << "\n";
    }
    
}