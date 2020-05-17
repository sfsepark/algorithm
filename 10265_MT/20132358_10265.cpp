#include <stdio.h>
#include <list>
#include <vector>
#include <queue>

using namespace std;

priority_queue<int> cycle_size_queue;
int cycle_size;

int find_cycle(int cur_v, vector<bool>& visited, vector<queue<int>>& graph){
  visited[cur_v] = true;

  int cyclic_node = -1;

  queue<int>& edges = graph[cur_v];

  while(!edges.empty()){
    int next_v = edges.front();
    edges.pop();

    if(visited[next_v]){
      cyclic_node = next_v;
      cycle_size ++;
    }
    else{
      int res = find_cycle(next_v, visited, graph);

      if(res == cur_v){
        cyclic_node = -1;
        cycle_size_queue.push(cycle_size);
      }
      else{
        cyclic_node = res;
      }
    }
  }

  if(cyclic_node == -1){
    visited[cur_v] = false;
  }
  else{
    cycle_size ++;
  }

  return cyclic_node;
}

int main(void){
  int N, K;
  int remain = 0;

  scanf("%d %d", &N, &K);

  vector<bool> visited(N,false);
  vector<queue<int>> graph(N);

  for(int i = 0 ; i < N ; i ++){
    int j;
    scanf("%d", &j);

    graph[j-1].push(i);
  }

  for(int i = 0 ; i < N ; i ++){
    cycle_size = 0;
    find_cycle(i,visited, graph);
  }

  for(int i = 0 ; i < N ; i ++){
    if(visited[i] == false){
      remain ++;
    }
  }

  while(!cycle_size_queue.empty()){
    printf("%d ", cycle_size_queue.top());

    cycle_size_queue.pop();
  }

  printf("\n%d\n", remain);

}