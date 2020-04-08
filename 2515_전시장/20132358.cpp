#include <iostream>
#include <unordered_map>
#include <stdio.h>
#include <stdint.h>
#include <vector>
#include <algorithm>

using namespace std;

unordered_map<int, int> dp;

int main(void){

    int N, S;
    int H, C;

    int min = INT32_MAX;
    int max = INT32_MIN;

    int cur_max = 0;

    scanf("%d %d", &N, &S);

    vector<pair<int, int>> picture(N);

    for(int i = 0 ; i < N ; i ++){
        scanf("%d %d", &H, &C);

        picture.push_back(make_pair(H,C));
    }

    sort(picture.begin() , picture.end());

    if(min < S)
        min  = S;

    int ptr = 0;

    for(auto it = picture.begin() ; it != picture.end() ; it ++){
        
    }

        if(dp.find(i - S) != picture.end()){
            if(cur_max < dp[i-S]){
                cur_max = dp[i-S];
            }
        }

        if(picture.find(i) != picture.end()){
            dp[i] = picture[i] + cur_max;
        }




    return 0;
}