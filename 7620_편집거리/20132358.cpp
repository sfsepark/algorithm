#include <stdio.h>
#include <string.h>
#include <string>
#include <iostream>
#include <stdint.h>
#include <stack>

using namespace std;

unsigned short dp[2][17005];
unsigned char operator_dp[17005][4251];

#define C_OP 0
#define D_OP 1
#define A_OP 2
#define M_OP 3

void init_operator_dp(int i, int j , int op){
    int j_index = j / 4;
    int j_unit = j % 4;
    
    int shifted_op = op;

    while(j_unit > 0){
        shifted_op *= 4;
        j_unit  --;
    }

    operator_dp[i][j_index] |= shifted_op;
}

int output_operator_dp(int i, int j){
    int j_index = j / 4;
    int j_unit = j % 4;

    int op = operator_dp[i][j_index];

    while(j_unit > 0){
        op /= 4;
        j_unit--;
    }

    return op % 4;
}

int main(void){
    string a, b;
    int a_len, b_len;

    stack<char> op_stack;
    stack<char> operand_stack;

    cin >> a;
    cin >> b;


    a_len = a.size();
    b_len = b.size();

    int prev_ptr = 0;

    for(int i = 0 ; i <= b_len ; i ++){
        dp[0][i] = i;
        init_operator_dp(0,i,A_OP);
    }

    for(int i = 1 ; i <= a_len ; i ++ ){

        int cur_ptr = (prev_ptr + 1) % 2;

        for(int j = 0 ; j <= b_len ; j ++){
            int min = INT32_MAX;
            int tmp ;
            int op;
            int mcop;
            
            //case 'd'
            tmp = dp[prev_ptr][j] + 1;
            if(tmp < min){
                min = tmp;
                op = D_OP;
            }
            
            
            if(j > 0){
                //case 'a'
                tmp = dp[cur_ptr][j-1] + 1;
                if(tmp < min){
                    min = tmp;
                    op = A_OP;
                }

                //case 'c'
                if(a[i-1] == b[j-1]){
                    tmp = dp[prev_ptr][j-1];
                    mcop = C_OP;
                }
                //case 'm'
                else{
                    tmp = dp[prev_ptr][j-1] + 1;
                    mcop = M_OP;
                }
                
                if(tmp < min){
                    min = tmp;
                    op = mcop;
                }
            }

            dp[cur_ptr][j]= min;
            init_operator_dp(i,j,op);
        }


        prev_ptr = cur_ptr;
    }


    int i = a_len, j = b_len;

    while(!(i == 0 && j == 0)){
        int op = output_operator_dp(i,j);
        char op_char ;
        char operand ;

        if(op == D_OP)
            operand = a[i-1];
        else
            operand = b[j-1];

        switch (op)
        {
        case A_OP :
            j --;
            op_char = 'a';
            break;
        case M_OP : case C_OP :
            op_char = op == M_OP ? 'm' : 'c';
            i --;
            j --;
            break;
        case D_OP :
            op_char = 'd';
            i --;
            break;
        }

        op_stack.push(op_char);
        operand_stack.push(operand);
    }
    

    while(!op_stack.empty()){
        char op = op_stack.top();
        char operand = operand_stack.top();

        printf("%c %c\n",op,operand);

        op_stack.pop();
        operand_stack.pop();
    }


    return 0;
}