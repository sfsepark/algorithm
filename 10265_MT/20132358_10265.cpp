#include <stdio.h>
#include <list>
#include <vector>
#include <queue>
#include <utility>

using namespace std;

priority_queue<pair<int, int>> cycle_size_queue;

int find_cycle(int cur_v, vector<bool> &visited, vector<int> &related, vector<queue<int>> &graph, int level)
{
  visited[cur_v] = true;

  int cyclic_node = -1;

  queue<int> edges = graph[cur_v];

  while (!edges.empty())
  {
    int next_v = edges.front();
    edges.pop();

    if (visited[next_v])
    {
      cyclic_node = next_v;
      cycle_size_queue.push(make_pair(level + 1, next_v));
      related[cur_v] = next_v;
    }
    else
    {
      int res = find_cycle(next_v, visited, related, graph, level + 1);
      if (cyclic_node == -1)
      {
        cyclic_node = res;
      }

      if (res != -1)
      {
        related[cur_v] = res;
      }
    }
  }

  if (cyclic_node == -1)
  {
    visited[cur_v] = false;
  }

  return cyclic_node;
}

int main(void)
{
  int N, K;
  int remain = 0;

  scanf("%d %d", &N, &K);

  vector<int> related(N, -1);
  vector<bool> visited(N, false);
  vector<queue<int>> graph(N);
  vector<queue<int>> new_graph(N);

  vector<int> related_remain(N, 0);

  for (int i = 0; i < N; i++)
  {
    int j;
    scanf("%d", &j);

    graph[j - 1].push(i);
    new_graph[j - 1].push(i);
  }

  for (int i = 0; i < N; i++)
  {
    if (visited[i] == false)
      find_cycle(i, visited, related, graph, 0);
  }

  for (int i = 0; i < N; i++)
  {

    if (related[i] != -1 && visited[i] == true)
    {
      queue<int> bfs_queue;

      bfs_queue.push(i);

      related_remain[related[i]]--;
      while (!bfs_queue.empty())
      {
        int j = bfs_queue.front();

        related_remain[related[i]]++;

        queue<int> edges = graph[j];

        while (!edges.empty())
        {
          if (visited[edges.front()] == false && related[edges.front()] == -1)
          {
            related[edges.front()] = related[i];
            bfs_queue.push(edges.front());
          }
          edges.pop();
        }

        bfs_queue.pop();
      }
    }
  }

  int prev = 0, cur = 0;

  vector<vector<bool>> dp(N + 1, vector<bool>(K + 1, false));

  int level = 0;

  dp[0][0] = true;

  while (!cycle_size_queue.empty())
  {
    level++;
    pair<int, int> p = cycle_size_queue.top();
    cycle_size_queue.pop();

    int cycle_size = p.first;
    int remain_size = related_remain[p.second];
    //printf("%d %d\n", cycle_size, remain_size);

    for (int j = 0; j < K + 1; j++)
    {
      if (dp[level - 1][j] == true)
      {
        dp[level][j] = true;
        if (j + cycle_size <= K)
        {
          for (int i = 0; i <= remain_size; i++)
          {
            if (j + cycle_size + i <= K)
            {
              dp[level][j + cycle_size + i] = true;
            }
            else
            {
              break;
            }
          }
        }
      }
    }
  }
  /*
  for (int i = 0; i <= level; i++)
  {
    for (int j = 0; j <= K; j++)
    {
      printf("%d ", dp[i][j] ? 1 : 0);
    }
    printf("\n");
  }
  */

  for (int i = K; i >= 0; i--)
  {
    if (dp[level][i] == true)
    {
      printf("%d\n", i);
      break;
    }
  }

  return 0;
}
