#include <stdio.h>
#include <string>
#include <string.h>

using namespace std;

#define APPLE 0
#define BANANA 1

#define SIZE 1505

int dp[SIZE][SIZE];

bool type[SIZE][SIZE];
short domain[SIZE][SIZE];

int horizon[SIZE][SIZE];
int vertical[SIZE][SIZE];

void input_domain(int R, int C){
    char c;
    int number;
    while((c = getchar()) != 'A' && c != 'B');

    if(c == 'A'){
        type[R][C] = APPLE;
    }
    else{
        type[R][C] = BANANA;
    }

    scanf("%d", &number);
    domain[R][C] = number;

}

void search_node(int r , int c){
    int tmp ;
    //아래
    tmp = dp[r][c] + vertical[r+1][c];
    if(dp[r+1][c] < tmp){
        dp[r+1][c] = tmp;
    }
    //오른쪽 아래
    tmp = dp[r][c] + vertical[r+1][c+1] + horizon[r+1][c+1];
    if(dp[r+1][c+1] < tmp){
        dp[r+1][c+1] = tmp;
    }
    //오른쪽
    tmp = dp[r][c] + horizon[r][c+1];
    if(dp[r][c+1] < tmp){
        dp[r][c+1] = tmp;
    }
}

int main(void){

    int R, C;
    int K ;

    memset(dp, 0 , sizeof(dp));
    scanf("%d %d", &R , &C);

    K = R < C ? R : C;
    
    for(int r = 0 ; r < R ; r ++){
        for(int c = 0 ; c < C ; c ++){
            input_domain(r,c);
            //printf("%c%-2d ",type[r][c] == APPLE ? 'A' : 'B', domain[r][c]);
        }
        //printf("\n");
    }

    domain[0][0] = 0;

    dp[0][0] = 0;

    for(int r = 0 ; r < R ; r ++){
        int sum = 0;
        for(int c = 0 ; c < C ; c++){
            vertical[r][c] = sum;
            if(type[r][c] == APPLE)
                sum += domain[r][c];
        }
    }
    
    
    for(int c = 0 ; c < C ; c ++){
        int sum = 0;
        for(int r = 0 ; r < R ; r++){
            horizon[r][c] = sum;
            if(type[r][c] == BANANA)
                sum += domain[r][c];
        }
    }

    for(int k = 0 ; k < K ; k ++){
         // vertical : c = k
        int c= k;
        for(int r = k ; r < R ; r ++){
            search_node(r,c);
        }

        // horizon : r = k
        int r = k;
        for(int c = k ; c < C ; c++){
            search_node(r,c);
        }
    }

    printf("%d",dp[R-1][C-1]);
    

    return 0;
}