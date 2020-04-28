#include <stdio.h>
#include <iostream>
#include <queue>
#include <vector>
#include <string>
#include <utility>
#include <algorithm>

using namespace std;

int dis[4][2] = {
  {0,1},
  {0,-1},
  {1,0},
  {-1,0}
};
int N ;

bool checkThreshold(int i , int j){
  return 0 <= i && i < N && 0 <= j && j < N;
}

int main(void){

  vector<int> posts;
  queue<pair<int, int>> bfs_queue;

  scanf("%d",&N);

  vector<string> map(N);
  vector<vector<bool>> visited(N, vector<bool>(N,0));

  for(int i = 0 ; i < N ; i ++){
    cin >> map[i];
  }

  for(int i = 0 ; i < N ; i ++){
    for(int j = 0 ; j < N ; j ++){
      if(map[i][j] == '1' && visited[i][j] == 0){

        int post = 0;

        bfs_queue.push(make_pair(i,j));

        visited[i][j] = 1;

        while(!bfs_queue.empty()){
          pair<int,int> p = bfs_queue.front();

          for(int d = 0 ; d < 4 ; d ++){
            int next_i = p.first + dis[d][0];
            int next_j = p.second + dis[d][1];

            if(checkThreshold(next_i,next_j) 
              && map[next_i][next_j] == '1'
              && visited[next_i][next_j] == 0){
                bfs_queue.push(make_pair(next_i,next_j));
                visited[next_i][next_j] = 1;
              }
          }

          bfs_queue.pop();
          post ++;
        }

        posts.push_back(post);
      }
    }
  }

  sort(posts.begin(), posts.end());

  printf("%zu\n",posts.size());
  for(int i = 0 ; i < posts.size(); i ++){
    printf("%d\n", posts[i]);
  }

  return 0;
}