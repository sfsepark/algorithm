#include <stdio.h>
#include <unordered_map>
#include <vector>
#include <string.h>

using namespace std;

unordered_map<int,long long> * prev_dp;
unordered_map<int,long long> * cur_dp;

int main(void){
    int N ;
    int candy[10005];
    int max = 0;
    int tmp;
    bool not_prime[500005];
    long long answer = 0;

    scanf("%d", &N);

    memset(candy, 0 , sizeof(candy));
    memset(not_prime, 0 , sizeof(not_prime));

    for(int i = 0 ; i < N ; i ++){
        scanf("%d", &tmp);

        candy[tmp] ++;
        max += tmp;
    }

    prev_dp = new unordered_map<int,long long>;

    (*prev_dp)[0] = candy[0] + 1;

    for(int i = 1 ; i <= 10000 ; i ++){
        if(candy[i] == 0)
            continue;

        //printf("! %d %d\n",i, candy[i]);

        int cur_cost = i;

        cur_dp = new unordered_map<int,long long>;
        
        for(auto it = (*prev_dp).begin() ; it != (*prev_dp).end() ; it ++){

            int cost = it -> first;
            long long cases = it -> second;

            for(int sum = 0 ; sum <= cur_cost * candy[cur_cost] ; sum += cur_cost){
                int next_cost = cost + sum;

                if((*cur_dp).find(next_cost) == (*cur_dp).end()){
                    (*cur_dp)[next_cost] = cases;
                }
                else{
                    (*cur_dp)[next_cost] += cases;
                }

                //printf("- %d %lld\n", next_cost, (*cur_dp)[next_cost]);
            }

            (*cur_dp)[0] = candy[0] + 1;
        }                

        delete prev_dp;
        prev_dp = cur_dp;
    }

    for(int i = 2 ; i * i <= max ; i++){
        if(!not_prime[i]){
            int cur = i * 2;
            while(cur <= max){
                not_prime[cur] = 1;
                cur += i;
            }
        }
    }

    for(int i = 2 ; i <= max ; i ++){
        if(!not_prime[i])
            //printf("%d ", i);
        if(!not_prime[i] &&  (*prev_dp).find(i) !=  (*prev_dp).end()) {
            //printf("%lld ",(*prev_dp)[i] );
            answer += (*prev_dp)[i];
        }
        //printf("\n");
    }

    printf("%lld",answer);


    return 0;
}