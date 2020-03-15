#include <iostream>
#include <string>
#include <vector>

int disp[4][2] = {
    {0,0},
    {1,0},
    {0,1},
    {1,1}
};

#define X 0
#define Y 1

using namespace std;

string compress(vector<string>& image , int level, int y, int x){
    if(level == 1){
        return image[y].substr(x,1);
    }
    else{
        vector<string> div_res(4);
        string result("");
        int state = 0;

        for(int i = 0 ; i < 4 ; i ++){
            int div_y = y + disp[i][Y] * level / 2;
            int div_x = x + disp[i][X] * level / 2;

            div_res[i] = compress(image, level /2 , div_y , div_x); 

            state += div_res[i][0] - '0';
        }

        if(state == 4 || state == 0){
            result = to_string(state / 4);
        }
        else{
            result += "(";
            for(int i = 0 ; i < 4 ; i ++){
                result += div_res[i];
            }
            result += ")";
        }

        return result;
    }
}


int main(void){

    int N ;
    
    cin >> N;

    vector<string> image(N);

    for(int i = 0 ; i < N ; i ++){
        cin >> image[i] ;
    }

    cout << compress(image,N, 0, 0);

    return 0;
}