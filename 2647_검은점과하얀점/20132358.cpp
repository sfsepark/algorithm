#include <iostream>
#include <stdio.h>
#include <string>
#include <string.h>
#include <stdint.h>
#include <vector>
#include <utility> 
#include <algorithm>

using namespace std;

#define LEFT 0
#define RIGHT 1

int dp[100][100][52];
int ptr_memory[100][100][52];
int height_memory[100][100][52][2];

void find_answer(vector<pair<int,int>>& answer_v , int i , int j, int h){
    int ptr = ptr_memory[i][j][h];


    if(ptr == -2){
        find_answer(answer_v, i +1 , j - 1 , h-1);
        
        answer_v.push_back(make_pair(i,j));
    }
    else if(ptr > 0){
        int l_h = height_memory[i][j][h][LEFT];
        int r_h = height_memory[i][j][h][RIGHT];

        find_answer(answer_v, i , ptr , l_h);
        find_answer(answer_v, ptr +1 , j , r_h );
    }
    else{
        answer_v.push_back(make_pair(i,j));
    }
}

int main(void){
    int N ;
    int min[52] ;
    char points[105];

    scanf("%d", &N);

    memset(dp, -1 , sizeof(dp));
    memset(ptr_memory, -1 , sizeof(ptr_memory));
    memset(height_memory, -1 , sizeof(height_memory));

    scanf("%s",points);


    for(int i = 0 ; i < N - 1 ; i ++){
        int j = i + 1;
        if(points[i] != points[j]){
            dp[i][j][1] = 3;
        }
    }


    for(int k = 2 ; k < N  ; k += 2){
        for(int i = 0 ; i < N - k ; i ++){
            int j = i + k +1;
            int max_height = 0;

            memset(min, -1 , sizeof(min));

            for(int ptr = i + 1 ; ptr < j ; ptr += 2 ){                
                for(int l_h = 1 ; l_h <= k /2 ; l_h ++){
                    for(int r_h = 1; r_h <= k / 2 ; r_h ++){
                        if(dp[i][ptr][l_h] != -1 && dp[ptr + 1][j][r_h] != -1){
                            int cur_height = l_h > r_h ? l_h : r_h;
                            int cur_dis =  dp[i][ptr][l_h] + dp[ptr + 1][j][r_h];
                            if(min[cur_height] == -1 || 
                                min[cur_height] > cur_dis){
                                    min[cur_height] = cur_dis;

                                    ptr_memory[i][j][cur_height] = ptr;
                                    height_memory[i][j][cur_height][LEFT] = l_h;
                                    height_memory[i][j][cur_height][RIGHT] = r_h;
                                }
                                
                        }
                    }
                }
            }


            if(points[i] != points[j]){
                for(int h = 1; h <= k / 2 ; h ++){
                    if(dp[i+1][j -1][h] != -1){
                        int cur_dis = dp[i+1][j-1][h] + (h +1 ) * 2 + (j - i); 
                        if(min[h + 1] == -1 || min[h +1] > cur_dis){
                            min[h + 1] = cur_dis;
                            ptr_memory[i][j][h+1] = -2;
                        }
                    }
                }
                }

            for(int h = 1 ; h <= 50 ; h ++){                
                dp[i][j][h] = min[h];
            }

            
        }
    }
    
    int answer = INT32_MAX ; 
    int answer_h;
    vector<pair<int,int>> answer_v;

    for(int h = 1 ; h <= N / 2 ; h ++ ){
        if(dp[0][N-1][h] != -1 &&  answer > dp[0][N-1][h]){
            answer = dp[0][N-1][h];
            answer_h = h;
        }
    }

    printf("%d\n",answer);

    find_answer(answer_v, 0, N-1 , answer_h);

    sort(answer_v.begin(), answer_v.end());

    for(auto it = answer_v.begin() ; it != answer_v.end() ; it++){
        printf("%d %d\n", it -> first + 1 , it ->second + 1);
    }
    

}