#include <iostream>
using namespace std;

string MONDAY = "Mon";
string TUESDAY = "Tue";
string WEDNESDAY = "Wed";
string THURSDAY = "Thr";
string FRIDAY = "Fri";
string SATURDAY = "Sat";
string SUNDAY = "Sun";

string JANUARY = "January";
string FEBRUARY = "February";
string MARCH = "March";
string APRIL = "April";
string MAY = "May";
string JUNE = "June";
string JULY = "July";
string AUGUST = "August";
string SEPTEMBER = "September";
string OCTOBER = "October";
string NOVEMBER = "November";
string DECEMBER = "December";

int printMonthCalendar(int numOfDays, int startingDate){

    cout << MONDAY << "\t";
    cout << TUESDAY << "\t";
    cout << WEDNESDAY << "\t";
    cout << THURSDAY << "\t";
    cout << FRIDAY << "\t";
    cout << SATURDAY << "\t";
    cout << SUNDAY << "\t";
    cout << endl;

    for (int i = 0; i < startingDate - 1; i++){
        cout << "\t";
    }

    int dayCounter = 1;
    int dayOfWeek = startingDate;

    while (dayCounter <= numOfDays){
        cout << dayCounter;

        bool endOfWeek = dayOfWeek == 7;
        if (endOfWeek){
            dayOfWeek = 1;
        }
        else{
            dayOfWeek++;
        }

        if (dayCounter < numOfDays){
            if(endOfWeek){
                cout << endl;
            }
            else{
                cout << "\t";
            }
        }
        dayCounter++;
    }
    cout << endl << endl;
    return dayOfWeek;
}

bool isLeapYear(int year){
    return (year % 4 == 0 && year %100 != 0) || (year % 400 == 0);
}

void printYearCalendar(int year, int startingDate){
    int firstOfMonth = startingDate;

    cout << JANUARY << " " << year << endl;
    firstOfMonth = printMonthCalendar(31,firstOfMonth);

    cout << FEBRUARY << " " << year << endl;
    if (isLeapYear(year)){
        firstOfMonth = printMonthCalendar(29, firstOfMonth);
    }
    else {
        firstOfMonth = printMonthCalendar(28, firstOfMonth);
    }

    cout << MARCH << " " << year << endl;
    firstOfMonth = printMonthCalendar(31,firstOfMonth);

    cout << APRIL << " " << year << endl;
    firstOfMonth = printMonthCalendar(30,firstOfMonth);

    cout << MAY << " " << year << endl;
    firstOfMonth = printMonthCalendar(31,firstOfMonth);

    cout << JUNE << " " << year << endl;
    firstOfMonth = printMonthCalendar(30,firstOfMonth);

    cout << JULY << " " << year << endl;
    firstOfMonth = printMonthCalendar(31,firstOfMonth);

    cout << AUGUST << " " << year << endl;
    firstOfMonth = printMonthCalendar(31,firstOfMonth);

    cout << SEPTEMBER << " " << year << endl;
    firstOfMonth = printMonthCalendar(30,firstOfMonth);

    cout << OCTOBER << " " << year << endl;
    firstOfMonth = printMonthCalendar(31,firstOfMonth);

    cout << NOVEMBER << " " << year << endl;
    firstOfMonth = printMonthCalendar(30,firstOfMonth);

    cout << DECEMBER << " " << year << endl;
    printMonthCalendar(31,firstOfMonth);

    return;
}

int main() {
    int year;
    int firstDayOfYear;

    cout << "Please enter a year:" ;
    cin >> year;

    cout << "Please enter the first day of the year (1-7 corresponding to Mon-Sun):";
    cin >> firstDayOfYear;
    cout << endl;

    printYearCalendar(year,firstDayOfYear);
    return 0;

}
