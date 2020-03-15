#include <iostream>
#include <vector>
#include <string.h>

#define LEFT 0
#define RIGHT 1

#define MIN 0
#define MAX 1

using namespace std;

int minmax[10005][2];
int max_level = 1;
int x = 0;

void change_minmax(int level){

    if(max_level < level) 
        max_level = level;

    if(minmax[level][MIN] == -1){
        minmax[level][MIN] = x;
    }
    else if(x < minmax[level][MIN]){
        minmax[level][MIN] = x;
    }

    if(minmax[level][MAX] == -1){
        minmax[level][MAX] = x;
    }
    else if(minmax[level][MAX] < x){
        minmax[level][MAX] = x;
    }

}

void inorder_search(vector<vector<int>>& tree, int node_index, int level){

    if(tree[node_index][LEFT] != -1){
        inorder_search(tree, tree[node_index][LEFT], level + 1);
    }

    x ++;
    change_minmax(level);

    if(tree[node_index][RIGHT] != -1){
        inorder_search(tree, tree[node_index][RIGHT], level + 1);
    }
}

int Find(vector<int>& root, int index){
    if(root[index] == index){
        return index;
    }
    else{
        return root[index] = Find(root, root[index]);

    }
}

void Union(vector<int>& root,int parent, int child){
    int p_root = Find(root, parent);
    int c_root = Find(root, child);
    

    root[c_root] = p_root;
}

int main(void){
    int N;
    cin >> N;

    vector<vector<int>> tree(N+1);
    vector<int> root(N + 1);

    memset(minmax, -1 , sizeof(minmax));

    for(int i = 1 ; i <= N ; i ++){
        root[i] = i;
    }

    for(int i = 0 ; i < N ;i ++) {
        int parent;
        cin >> parent;
        tree[parent].resize(2);

        int left, right;

        cin >> left;
        tree[parent][LEFT] = left;
        cin >> right;
        tree[parent][RIGHT] = right;

        if(left != -1)
            Union(root,parent, left);
        if(right != -1)
            Union(root,parent, right);
    }

    int root_index = root[1];

    inorder_search(tree, root_index, 1);

    int max_width = 1;
    int max_width_level = 1;

    for(int level = 2 ; level <= max_level ; level ++){
        int cur_width = minmax[level][MAX] - minmax[level][MIN] + 1;
        if(max_width < cur_width){
            max_width = cur_width;
            max_width_level = level;
        }
    }

    cout << max_width_level << " " << max_width;

}