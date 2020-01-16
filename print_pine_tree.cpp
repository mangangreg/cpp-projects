#include <iostream>
using namespace std;

void printShiftedTriangle(int n, int m, char symbol){

    int maxLength = (2 * n) - 1 + m;
    int middle = n + m - 1;
    int left = middle;
    int right = middle;

    for(int i = 0; i < n; i++){
        for(int j = 0; j < maxLength; j++){
            if(j >= left){
                cout <<symbol;

                if(j == right){
                    break;
                }
            }
            else{
                cout << " ";
            }
        }
        cout << endl;
        left--;
        right++;
    }
}

void printPineTree(int n, char symbol){

    int height = 2;
    int offset = n - 1;

    while(offset >= 0){
        printShiftedTriangle(height,offset,symbol);
        height++;
        offset--;
    }
}
int main(){
    int n;
    char symbol;

    cout << "Please choose a number of triangles for your tree (a positive integer):";
    cin >> n;

    cout << "Please enter a character for your tree:";
    cin >> symbol;

    printPineTree(n, symbol);
    return 0;
}
