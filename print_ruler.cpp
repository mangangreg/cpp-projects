#include <iostream>
using namespace std;

void printRuler(int n){
    // Base step
    if (n == 1){
        cout << '-' << endl;
        return;
    }
    // Recursive step, call this function recursively twice, once before and once after step for this state
    else{
        printRuler(n-1);

        for (int i = 0; i < n; i++){
            cout << '-';
        }
        cout << endl;

        printRuler(n-1);
    }
}

int main(){
    int n;
    cout << endl << "To print a ruler of length 2^n-1, please enter an integer n:" << endl;
    cin >> n;
    printRuler(n);
}
