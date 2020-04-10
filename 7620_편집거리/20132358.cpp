#include <stdio.h>
#include <string.h>
#include <string>
#include <iostream>
#include <stdint.h>

using namespace std;

unsigned short dp[2][17005];

int main(void){
    string a, b;

    cin >> a;
    cin >> b;

    int prev_ptr = 1;

    for(int i = 0 ; i < a.size() ; i ++){
        dp[0][i] = i;
    }

    for(auto a_it = a.begin() ; a_it != a.end() ; a_it ++){

        char a_char = *a_it;

        int cur_ptr = (prev_ptr + 1) % 2;

        for(auto b_it = b.begin() ; b_it != b.end() ; b_it ++){
            int min = INT32_MAX;
            char b_char = *b_it;

            if(a_char != b_char){
                
            }
        }

        prev_ptr = cur_ptr;
    }

    return 0;
}