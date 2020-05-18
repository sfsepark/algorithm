#include <stdio.h>
#include <vector>
#include <queue>
#include <list>
#include <utility>
#include <unordered_map>
#include <stdint.h>

using namespace std;

typedef pair<int, pair<int, int>> Edge;

#define X second.first
#define Y second.second
#define WEIGHT first

int getRoot(vector<int> &parent, int node)
{
    if (parent[node] == node)
    {
        return node;
    }

    return getRoot(parent, parent[node]);
}

int unionParent(vector<int> &parent, int x, int y)
{
    int xRoot = getRoot(parent, x);
    int yRoot = getRoot(parent, y);

    if (xRoot < yRoot)
    {
        parent[yRoot] = xRoot;
        return xRoot;
    }
    else
    {
        parent[xRoot] = yRoot;
        return yRoot;
    }
}

int main(void)
{
    int N, M;
    int start, end;

    scanf("%d %d", &N, &M);

    priority_queue<Edge> edges;
    vector<unordered_map<int, int>> weightGraph(N);
    vector<int> parent(N);
    vector<bool> visited(N, false);

    for (int i = 0; i < N; i++)
    {
        parent[i] = i;
    }

    for (int i = 0; i < M; i++)
    {
        int weight, x, y;

        scanf("%d %d %d", &x, &y, &weight);

        edges.push(make_pair(weight, make_pair(x - 1, y - 1)));
    }

    scanf("%d %d", &start, &end);

    int num = 0;

    while (!edges.empty())
    {
        Edge edge = edges.top();

        int x = edge.X;
        int y = edge.Y;

        //printf("%d %d %d  ", x + 1, y + 1, edge.WEIGHT);

        if (getRoot(parent, x) != getRoot(parent, y))
        {
            unionParent(parent, x, y);
            weightGraph[x][y] = weightGraph[y][x] = edge.WEIGHT;

            num++;
            if (num == N - 1)
            {
                break;
            }
        }

        //printf("\n");

        edges.pop();
    }

    //printf("?");

    queue<pair<int, int>> bfs_queue;

    bfs_queue.push(make_pair(start - 1, INT32_MAX));

    while (!bfs_queue.empty())
    {
        pair<int, int> cur = bfs_queue.front();
        int x = cur.first;
        int min = cur.second;
        visited[x] = true;

        for (auto it = weightGraph[x].begin(); it != weightGraph[x].end(); it++)
        {
            int next = it->first;
            int next_min = min;
            int weight = it->second;

            //printf("%d %d %d\n", cur, next, weight);

            if (next_min > weight)
            {
                next_min = weight;
            }

            if (next == end - 1)
            {
                printf("%d\n", next_min);
                return 0;
            }

            if (visited[next] == false)
            {
                bfs_queue.push(make_pair(next, next_min));
            }
        }

        bfs_queue.pop();
    }

    return 0;
}