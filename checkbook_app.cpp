#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
using namespace std;

class Money{
    public:
    friend Money operator+(const Money& amount1, const Money& amount2);
    friend Money operator-(const Money& amount1, const Money& amount2);
    friend Money operator-(const Money& amount);
    friend bool operator==(const Money& amount1, const Money& amount2);
    friend bool operator <(const Money& amount1, const Money& amount2);
    Money(long dollars, int cents){all_cents = cents + 100*dollars;}
    Money(long dollars){all_cents = 100*dollars;}
    Money( ){all_cents = 0;}
    double get_value( ) const{return all_cents;}

    friend istream& operator >>(istream& ins, Money& amount);


    friend ostream& operator <<(ostream& outs, const Money& amount);

    private:
    long all_cents;
};

Money operator+(const Money& amount1, const Money& amount2) {
    return Money(0, amount1.all_cents + amount2.all_cents);
}

Money operator-(const Money& amount1, const Money& amount2) {
    return Money(0, amount1.all_cents - amount2.all_cents);
}
Money operator-(const Money& amount1) {
    return Money(0, amount1.all_cents * -1);
}

bool operator==(const Money& amount1, const Money& amount2) {
    if (amount1.get_value() == amount2.get_value()){
        return true;
    }
    else{
        return false;
    }
}
bool operator <(const Money& amount1, const Money& amount2){
    return amount1.get_value() < amount2.get_value();
}

istream& operator >>(istream& ins, Money& amount){
    bool isNegative = false;

    char prefix;
    ins >> prefix;

    if (prefix=='-'){
        isNegative = true;
        ins >> prefix; // Read in dollar sign, if first char was a minus sign
    }

    long dollars = 0;
    char period;
    int cents = 0;

    ins >> dollars >> period >> cents;

    if(prefix != '$' || period != '.' || !(cents >= 0 && cents <= 99)){
        cout << "Error illegal form for money input";
        exit(1);
    }

    if(isNegative){
        amount = -Money(dollars,cents);
    }
    else{
        amount = Money(dollars,cents);
    }

    return ins;
}
ostream& operator<<(ostream& outs, const Money& amount){
    if(amount.get_value() < 0){
        outs << "-" << -amount;
        return outs;
    }
    long totalInCents = amount.get_value();
    long dollars = totalInCents / 100;
    int cents = totalInCents % 100;

    outs << '$' << dollars << '.';

    if(cents < 10){
        outs << '0';
    }

    outs<< cents;

    return outs;
}


class Check{

private:
    int id;
    Money amount;
    bool cashed;

public:

    Check(int id, const Money &amount, bool cashed) : id(id), amount(amount), cashed(cashed) {};
    Check( ){
        id = -1;
        amount = Money();
        cashed = false;
    };

    int getId() const {
        return id;
    }

    const Money &getAmount() const {
        return amount;
    };

    bool isCashed() const {
        return cashed;
    };

    void setId(int id) {
        Check::id = id;
    };

    void setAmount(const Money &amount) {
        Check::amount = amount;
    };

    void setCashed(bool cashed) {
        Check::cashed = cashed;
    };

    friend istream& operator >>(istream& ins, Check& check);
    friend ostream& operator<< (ostream& outs, Check& check);
    friend bool operator< (const Check& check1, Check& check2);

};

ostream& operator<< (ostream& outs, Check& check) {
    outs <<"[#" << check.getId() << "]\t\t\t\t" << check.getAmount();
    if(check.isCashed()){
        outs << " (cashed)";
    }
    else{
        outs << " (not cashed)";
    }
    return outs;
};

bool operator< (const Check& check1, Check& check2){
    return check1.getId() < check2.getId();
}

Money readDeposits(){
    Money total;
    Money input;
    char enterMore = 'Y';

    cout << endl << "Please enter your deposits (in $):" << endl;

    while( enterMore=='Y' || enterMore=='y'){
        cin >> input;
        total= total + input;
        cout << "Would you like to enter another deposit? (Y/N)";
        cin >> enterMore;
    }

    return total;
}
istream& operator >>(istream& ins, Check& check){
    int id;
    Money amount;
    bool cashed;

    cout << "Please enter the following for your check:" << endl;

    cout << "[1/3] Check No.:";
    ins >> id;
    check.setId(id);

    cout << "[2/3] Amount(in $):";
    cin >> amount;
    check.setAmount(amount);

    cout << "[3/3] Cashed (1/0):";
    cin >> cashed;
    check.setCashed(cashed);

    return ins;
}

void printChecksByCashed(vector<Check> checks){
    cout << endl << "Cashed checks:" << endl;
    for(Check check: checks){
        if(check.isCashed()){
            cout  << check  << endl;
        }
    }

    cout <<  endl<< "Checks not cashed:" << endl;

    for(Check check: checks){
        if(!check.isCashed()){
            cout  << check << endl;
        }
    }
}

void checkBookApp(){
    cout << "#############################" << endl;
    cout << "###  CHECKBOOK APP" << endl;
    cout << "#############################" << endl << endl;

    cout << "Welcome to the checkbook app. Note, please enter all $ amounts in the format $d.cc" << endl << endl;
    cout << "STEP ONE: Please enter all your uncashed checks." << endl << endl;

    vector<Check> checks;
    Money totalCashed;

    char enterMore = 'y';
    Check checkInp;
    while(enterMore == 'Y' || enterMore == 'y'){
        cout << endl;
        cin >> checkInp;
        if(checkInp.isCashed()){
            totalCashed = totalCashed + checkInp.getAmount();
        }
        checks.push_back(checkInp);
        cout << "Thank you. Would you like to enter another check? (Y/N)";
        cin >> enterMore;
    }

    // Sort the checks
    sort(checks.begin(),checks.end());

    //Deposits/
    Money deposits = readDeposits();

    // Balances
    Money balPrevious, balCurrent;

    cout << endl << "Please enter your previous balance:";
    cin >> balPrevious;
    cout << "Please enter your current balance:";
    cin >> balCurrent;


    // Calculate
    Money balCalculated;
    balCalculated = balPrevious + deposits - totalCashed;

    // Outputs
    cout << endl << "Old Balance:\t\t\t" << balPrevious << endl;
    cout << "(-)Total cashed checks:\t\t" << totalCashed << endl;
    cout << "(+)Total deposits:\t\t" << deposits << endl ;

    cout << "(=)Calculated balance:\t\t" << balCalculated << endl << endl;
    cout << "(-)New Balance\t\t\t" << balCurrent << endl;
    cout << "(=)Difference:\t\t\t" << (balCalculated - balCurrent) << endl;

    printChecksByCashed(checks);
    cout << endl;
}

int main() {
   checkBookApp();
   return 0;
}
