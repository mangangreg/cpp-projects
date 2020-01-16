#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

const int NUMBER_OF_GUESSES = 5;

int main(){
    int secret;
    int boundLower = 1;
    int boundUpper = 100;

    srand(time(0));
    secret = (rand() % 100) + 1;

    cout << "I thought of a number between 1 and 100! Try to guess it." << endl;

    int guessesLeft = NUMBER_OF_GUESSES;

    while (guessesLeft > 0){

        cout << "Range: [" << boundLower << ", " << boundUpper << "]. Number of guesses left: " << guessesLeft << endl;

        int userGuess;
        cout << "Your guess:";
        cin >> userGuess;


        guessesLeft--;

        if( userGuess == secret){
            cout << "Congrats! You guessed my number in " << (NUMBER_OF_GUESSES - guessesLeft) << " guesses.";
            return 0;
        }
        else if (guessesLeft == 0){
                cout << "Out of guesses! My number is " << secret;
        }
        else if (userGuess < secret){
            cout << "Wrong! My number is bigger" << endl;
            boundLower = userGuess + 1;
        }
        else if (userGuess > secret){
            cout << "Wrong! My number is smaller" << endl;
            boundUpper = userGuess - 1;
        }

        cout << endl;
    }
    return 0;
}
