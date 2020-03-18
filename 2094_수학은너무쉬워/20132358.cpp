#include <iostream>
#include <string.h>
#include <set>
#include <unordered_map>

using namespace std;


int main(void){
    int N, number[100];
    unordered_map<int , int> totalBucket;
    unordered_map<int , int> bucket[100];
    int score = 1, move = 0;
    set<int> primeNumberSet ;

    cin >> N;

    for(int i = 0 ; i < N ; i ++){
        cin >> number[i];
    }

    for(int i = 0 ; i < N ; i ++){
        int primeNumber = 2;
        
        while(number[i] != 1){            
            if(number[i] % primeNumber == 0){

                primeNumberSet.insert(primeNumber);

                bucket[i][primeNumber] = 0;
                if(totalBucket.find(primeNumber) == totalBucket.end()){
                    totalBucket[primeNumber] = 0;
                }
            }

            while(number[i] % primeNumber == 0){
                number[i] /= primeNumber;

                bucket[i][primeNumber] ++;
                totalBucket[primeNumber] ++;
            }

            primeNumber ++;
        }
    }

    for(auto it = primeNumberSet.begin() ; it != primeNumberSet.end() ; it ++){
        int primeNumber = *it;
        totalBucket[primeNumber] /= N;
        int average = totalBucket[primeNumber];

        for(int j = 0 ; j < average ; j ++){
            score *= primeNumber;
        }

        for(int n = 0 ; n < N ; n ++){
            if(totalBucket[primeNumber] > bucket[n][primeNumber]){
                move += totalBucket[primeNumber] - bucket[n][primeNumber];
            }
        }
    }

    cout << score << " " << move ;
}