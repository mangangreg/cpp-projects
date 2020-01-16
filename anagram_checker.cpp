#include <iostream>
#include <string>
#include <vector>
using namespace std;

const int ALPHABET_LENGTH = 26;

void lower(string& word);
bool isLowerLetter(char c);
void updateCounters(string input, int letterCounts[]);
bool isAnagram(string string1, string string2);

int main(){

    // Read inputs and put them into lowercase
    string string1;
    cout << "Please enter the first string:" << endl;
    getline(cin, string1);
    lower(string1);

    string string2;
    cout << "Please enter the second string:" << endl;
    getline(cin, string2);
    lower(string2);

    // Check if anagrams
    if (isAnagram(string1, string2)){
        cout << endl << "Yes these are anagrams" << endl;
    }
    else{
        cout << endl << "No these are not anagrams" << endl;
    }
    return 0;
}

void lower(string& string){
    for(int i = 0; i < string.length(); i++){
        if( string[i] >= (int)'A' && string[i] <= (int)'Z'){
            string[i] += ('a' - 'A');
        }
    }
    return;
}

bool isLowerLetter(char c){
    if(c >= 'a' && c <= 'z') {
        return true;
    }
    else{
        return false;
    }
}

void updateCounters(string input, int letterCounts[]){
    for(int i = 0; i < input.length(); i++) {
        if(isLowerLetter(input[i])) {
            if(isLowerLetter(input[i])){
                letterCounts[input[i] - 'a']++;
            }
        }
    }
}
bool isAnagram(string string1, string string2){
    int letterCounts1[ALPHABET_LENGTH];
    for(int i = 0; i < ALPHABET_LENGTH; i++){
        letterCounts1[i] = 0;
    }
    updateCounters(string1, letterCounts1);

    int letterCounts2[ALPHABET_LENGTH];
    for(int i = 0; i < ALPHABET_LENGTH; i++){
        letterCounts2[i] = 0;
    }

    updateCounters(string2, letterCounts2);

    for (int i = 0; i < ALPHABET_LENGTH; i++){
        if (letterCounts1[i] != letterCounts2[i]){
            return false;
        }
    }
    return true;
}
