#include <queue>
#include <stdio.h>
#include <vector>
#include <utility>

#define Y first
#define X second

using namespace std;

bool bound_check(int M , int N, int y, int x){
    return y >= 0 && x >= 0 && y < M && x < N;
}

int diff[4][2] = {
    {-1,0},
    {1,0},
    {0,1},
    {0,-1}
};

int main(void){

    int N, M;
    int info,bit;;

    scanf("%d %d",&N,&M);

    vector<vector<int>> horizon(M + 1 , vector<int>(N + 1, 0));
    vector<vector<int>> vertical(M + 1 , vector<int>(N + 1, 0));

    vector<vector<int>> room_number(M, vector<int>(N,-1));
    vector<vector<bool>> near_check_visited(M, vector<bool>(N,false));


    for(int i  = 0 ; i < M ; i ++){
        for(int j = 0 ; j < N ; j ++){
            scanf("%d", &info);

            bit = info / 8;
            info %= 8;

            if(bit == 1){
                horizon[i+1][j] = 1;
            }
            
            bit = info / 4;
            info %= 4;

            if(bit == 1){
                vertical[i][j+1] = 1;
            }

            bit = info / 2;
            info %= 2;

            if(bit == 1){
                horizon[i][j] = 1;
            }

            bit = info ;

            if(bit == 1){
                vertical[i][j] = 1;
            }
        }
    }


    queue<pair<int,int>> bfs_queue;

    vector<int> room_size;
    int cur_room= 0;
    int cur_room_size;

    for(int i = 0 ; i < M ; i ++){
        for(int j = 0 ; j < N ; j ++){
            if(room_number[i][j] == -1){

                cur_room_size = 0;

                bfs_queue.push(make_pair(i,j));

                room_number[i][j] = cur_room;

                while(!bfs_queue.empty()){
                    pair<int,int> coor = bfs_queue.front();
                    bfs_queue.pop();

                    int cur_y = coor.Y;
                    int cur_x = coor.X;

                    cur_room_size ++;

                    if(bound_check(M, N, cur_y - 1, cur_x) 
                        && room_number[cur_y - 1][cur_x] == -1
                        && horizon[cur_y][cur_x] == 0){
                        room_number[cur_y - 1][cur_x] = cur_room;
                        bfs_queue.push(make_pair(cur_y - 1, cur_x));
                    }

                    if(bound_check(M, N, cur_y + 1, cur_x) 
                        && room_number[cur_y + 1][cur_x] == -1
                        && horizon[cur_y + 1][cur_x] == 0){
                        room_number[cur_y + 1][cur_x] = cur_room;
                        bfs_queue.push(make_pair(cur_y + 1, cur_x));
                    }

                    if(bound_check(M, N, cur_y, cur_x - 1) 
                        && room_number[cur_y][cur_x - 1] == -1
                        && vertical[cur_y][cur_x] == 0){
                        room_number[cur_y][cur_x - 1] = cur_room;
                        bfs_queue.push(make_pair(cur_y, cur_x -1));
                    }

                    if(bound_check(M, N, cur_y, cur_x + 1) 
                        && room_number[cur_y][cur_x + 1] == -1
                        && vertical[cur_y][cur_x + 1] == 0){
                        room_number[cur_y][cur_x + 1] = cur_room;
                        bfs_queue.push(make_pair(cur_y, cur_x + 1));
                    }

                }

                room_size.push_back(cur_room_size);

                cur_room ++;
            }
        }
    }

    
    vector<vector<bool>> near_edge(cur_room, vector<bool>(cur_room, false));


    for(int i = 0 ; i < M ; i ++){
        for(int j  = 0 ; j < N ; j ++){
            if(near_check_visited[i][j] == false){

                cur_room = room_number[i][j];

                bfs_queue.push(make_pair(i,j));

                near_check_visited[i][j] = true;

                while(!bfs_queue.empty()){
                    pair<int,int> coor = bfs_queue.front();
                    bfs_queue.pop();
                    int cur_y = coor.Y;
                    int cur_x = coor.X;
                    

                    for(int k = 0 ; k < 4 ; k ++){
                        int next_y = cur_y + diff[k][1];
                        int next_x = cur_x + diff[k][0];

                        if(bound_check(M, N, next_y, next_x)){
                            int next_room = room_number[next_y][next_x];

                            if(cur_room != next_room){
                                near_edge[cur_room][next_room] = true;
                                near_edge[next_room][cur_room] = true;
                            }
                            else{
                                if(near_check_visited[next_y][next_x] == false){
                                    bfs_queue.push(make_pair(next_y,next_x));
                                    near_check_visited[next_y][next_x] = true;
                                }
                                    
                            }
                        }
                    }
                }
            }
        }
    }

    

    printf("%d\n",near_edge.size());

    int max = 0;

    for(int i = 0; i < room_size.size() ; i ++){
        if(room_size[i] > max){
            max = room_size[i];
        }
    }

    printf("%d\n",max);

    max = 0;

    for(int i = 0 ; i < near_edge.size() ;i ++){
        for(int j = 0 ; j < near_edge.size() ;j ++){
            if(near_edge[i][j] == true){
                int integrate = room_size[i] + room_size[j];

                if(max < integrate){
                    max = integrate;
                }
            }
        }
    }

    printf("%d\n",max);

    
    return 0;
}