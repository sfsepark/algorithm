#include <stdio.h>
#include <string.h>
#include <string>
#include <iostream>
#include <stdint.h>

using namespace std;

unsigned short dp[2][17005];
char operator_dp[17005][4251];

void init_operator_dp(int i, int j , int op){
    int j_index = j / 4;
    int j_unit = j % 4;
    
    int shifted_op = op;

    while(j_unit > 0){
        shifted_op *= 4;
        j_unit  --;
    }

    operator_dp[i][j] += shifted_op;
}

int output_operator_dp(int i, int j){

}

int main(void){
    string a, b;
    int a_len, b_len;

    cin >> a;
    cin >> b;

    a_len = a.size();
    b_len = b.size();

    int prev_ptr = 1;

    for(int i = 0 ; i < a.size() ; i ++){
        dp[0][i] = i;
    }

    for(int i = 0 ; i < a_len ; i ++ ){

        int cur_ptr = (prev_ptr + 1) % 2;

        for(int j = 0 ; j < b_len ; j ++){
            int min = INT32_MAX;
            int tmp ;
            
            //case 'd'
            if(a[i - 1] == b[j]){
                tmp = dp[prev_ptr][j] + 1;
                if(tmp < min){
                    min = tmp;
                }
            }
            //case 'a'
            if(j > 0){
                tmp = dp[cur_ptr][i-1] + 1;
                if()
            }
        }

        prev_ptr = cur_ptr;
    }

    return 0;
}