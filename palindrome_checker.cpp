#include <iostream>
#include <string>
using namespace std;

char lower(char letter);
bool isPalindrome(string str);

int main(){
    string word;
    cout << "Please enter a word:";
    cin >> word;

    if (isPalindrome(word)){
        cout << word << " is a palindrome" << endl;
    }
    else{
        cout << word << " is not a palindrome" << endl;
    }
    return 0;
}

char lower(char letter){
    if (letter >= 'A' && letter <= 'Z'){
        return letter + ('a' - 'A');
    }
    else{
        return letter;
    }
}

bool isPalindrome(string str){
    int n = str.length();
    int i = 0;

    while (i < n / 2 ){
        if(lower(str[i]) != lower(str[n - 1 - i])){
            return false;
        }
        i++;
    }
    return true;
}
