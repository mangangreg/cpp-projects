#include <iostream>
using namespace std;

int lowestCost(int arr[], int arrSize, int* mem){
    // Always check memory first
    if (mem[arrSize-1]!= -1) {
        return mem[arrSize - 1];
    }
    // If only column, return that value
    else if (arrSize ==1){
        mem[0] = arr[0];
        return arr[0];
    }

    // If two columns, return first plus last, don't have choice of steps
    else if (arrSize==2){
        int cost = arr[1] + lowestCost(arr, arrSize - 1, mem);
        mem[1] = cost;
        return cost;
    }

    else{
        // Calculate the accumulated cost of landing one step from the end
        int oneStep = lowestCost(arr,arrSize - 1,mem);
        // Update the memory if necessary
        if (mem[arrSize-2]== -1){
            mem[arrSize-2] = oneStep;
        }
        // Calculate the accumulated cost of landing one two from the end
        int twoStep = lowestCost(arr,arrSize - 2,mem);
         // Update the memory if necessary
        if (mem[arrSize-3]== -1){
            mem[arrSize-3] = twoStep;
        }

        // If it's cheaper to get to two steps back, return last step plus cost
        if (oneStep < twoStep){
            return arr[arrSize - 1] + oneStep;
        }
        else{
            return arr[arrSize - 1] + twoStep;
        }
    }
}

int main(){
    int arr[6] = {0, 49, 50, 50, 48, 1};

    //Create a memory array to be able to use memoization
    int mem[6] = {};
    for(int i=0; i<6; i++){
        mem[i] = -1;
    }
    cout << lowestCost(arr, 6, mem) << endl;
    return 0;
}
