#include <stdio.h>
#include <string.h>
#include <queue>
#include <utility>   

using namespace std;

#define SIZE 52
#define MAGIC_NUMBER 1000007

int dp[SIZE][SIZE][SIZE][SIZE]; // [N][M][최근 방문][오락실 갯수]
int node[SIZE][SIZE]; // [N][M]

bool visited[SIZE][SIZE];

int C;

void search(queue<pair<int,int>>& node_queue, int x, int y, int next_x, int next_y){
    int game = node[next_x][next_y];

    if(game == 0){
        for(int last = 0 ; last <= C ; last ++){
            for(int num = 0 ; num <= C ; num ++){
                dp[next_x][next_y][last][num] = 
                    (dp[next_x][next_y][last][num] % MAGIC_NUMBER +  dp[x][y][last][num] % MAGIC_NUMBER) % MAGIC_NUMBER;
            }
        }
    }
    else{
        for(int last = 0 ; last < game ; last ++){
            for(int num = 0 ; num <= game ; num ++){
                dp[next_x][next_y][game][num + 1] = 
                    (dp[next_x][next_y][game][num + 1] % MAGIC_NUMBER +  dp[x][y][last][num] % MAGIC_NUMBER) % MAGIC_NUMBER;
            }
        }
    }

    if(visited[next_x][next_y] == false){
        node_queue.push(make_pair(next_x,next_y));
        visited[next_x][next_y] = true;
    }

}

int main(void){
    int N,M;
    queue<pair<int,int>> node_queue;

    scanf("%d %d %d",&N, &M, &C);

    memset(dp,0,sizeof(dp));
    memset(node,0,sizeof(node));

    for(int i = 1 ; i <= C ; i ++){
        int n,m;
        scanf("%d %d",&n , &m);

        node[n -1][m-1] = i;
    }

    dp[0][0][node[0][0]][node[0][0] != 0 ? 1 : 0] = 1;

    node_queue.push(make_pair(0,0));

    while(!node_queue.empty()){
        pair<int,int> cur = node_queue.front();

        int x = cur.first;
        int y = cur.second;
        //printf("%d %d\n",x,y);

        int next_x = x + 1;
        int next_y = y ;

        if(next_x < N && next_y < M){
            search(node_queue,x,y,next_x,next_y);
        }

        next_x = x;
        next_y = y  + 1;

        if(next_x < N && next_y < M ){
            
            search(node_queue,x,y,next_x,next_y);
        }

        node_queue.pop();
    }

    for(int i = 0 ; i <= C ; i ++){
        int cur = 0;

        for(int j = 0 ; j <= C ; j ++){
            cur = ((cur % MAGIC_NUMBER ) + (dp[N-1][M-1][j][i] % MAGIC_NUMBER)) % MAGIC_NUMBER;
        }

        printf("%d ",cur);
    }
    
    return 0;
}