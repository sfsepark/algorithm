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

    vector<pair<int, int>> picture;

    for(int i = 0 ; i < N ; i ++){
        scanf("%d %d", &H, &C);

        picture.push_back(make_pair(H,C));
    }

    sort(picture.begin() , picture.end());

    if(min < S)
        min  = S;

    int ptr = 0;
    int prev_height;
    int cur_height;

    for(auto it = picture.begin() ; it != picture.end() ; it ++){
        cur_height = it -> first;

        //printf("%d %d\n", it -> first, it -> second);

        while((prev_height = picture[ptr].first) <= cur_height - S){
            if(cur_max < dp[prev_height])
                cur_max = dp[prev_height];

                //printf("--- %d %d\n", prev_height, dp[prev_height]);

            ptr ++;
        }

        dp[cur_height] = it -> second + cur_max;

    }

    if(S > cur_height){
        printf("%d", 0);
    }
    else{
        cur_max = 0;

        for(auto it = picture.begin() ; it != picture.end() ; it ++){
            if(cur_max < dp[it -> first])
                cur_max = dp[it -> first];
        }

        printf("%d",cur_max);
    }


    return 0;
}