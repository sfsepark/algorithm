#include <iostream>
#include <stdio.h>
#include <stack>
#include <vector>
#include <utility>
#include <algorithm>
#include <limits>

#define X second
#define Y first

using namespace std;

typedef  pair<int,int> coordinate;

coordinate base;

float slope(coordinate& p){
  if(p.Y - base.Y == 0){
    return numeric_limits<float>::max();
  }
  else{
    return ((float)(p.X - base.X)) /((float)(p.Y - base.Y));
  }
}

int lengthSquare(coordinate& p){
  return (p.X - base.X) + (p.Y - base.Y);
}

bool sortBySlope(coordinate& p1, coordinate& p2){
  float slope1,slope2;
  slope1 = slope(p1);
  slope2 = slope(p2);

  if(slope1 == slope2){
    return lengthSquare(p1) < lengthSquare(p2);
  }
  else{
    return slope1 > slope2;
  }
}

int ccw(coordinate& p1, coordinate& p2, coordinate& p3){
  return (p2.X - p1.X)*(p3.Y - p1.Y) - (p2.Y - p1.Y)*(p3.X - p1.X);
}

int getArea(stack<coordinate>& hull_stack){
  int area = 0;
  coordinate prev = base;
  coordinate cur;
  
  while(!hull_stack.empty()){
    cur = hull_stack.top();
    hull_stack.pop();

    area += (prev.X + cur.X)* (prev.Y - cur.Y);
    prev = cur;
  }

  return area /2;
}

int main() {
  int N ; 
  stack<coordinate> hull_stack;

  scanf("%d", &N);

  vector<coordinate> trees(N); //first : y , second : x

  for(int i = 0 ; i < N ; i ++){
    int x,y;

    scanf("%d %d", &x, &y);

    trees[i] = make_pair(y, x);
  }

  if(N <= 2){
    printf("%d",0);
    return 0;
  }

  sort(trees.begin(), trees.end());

  base = trees[0];

  sort(trees.begin() + 1, trees.end(), sortBySlope);


  hull_stack.push(trees[0]);
  hull_stack.push(trees[1]);
  hull_stack.push(trees[2]);

  for(int i = 3 ; i < N ; i ++){
    coordinate p3 = trees[i];
    coordinate p2 = hull_stack.top();
    hull_stack.pop();
    coordinate p1 = hull_stack.top();

    while(hull_stack.size() > 1 && ccw(p1,p2,p3) <= 0 ){
      hull_stack.pop();
      p2 = p1;
      p1 = hull_stack.top();
    }

    hull_stack.push(p2);
    hull_stack.push(p3);
  }

  printf("%d\n",getArea(hull_stack) / 50);
  

  return 0;
}