/**
* Name: Hrishikesh Vyas,
* Student #: 100271549
* Class: CPSC 1160
* Assignment #4
* Description: Program to print current GMT time
*
* I pledge that I have completed the programming assignment independently.
* I have not copied the code from a student or any other source.
* I have not given my code to any student.
* Hrishikesh Vyas, May 23, 2017
*/

#include <iostream>
#include <ctime>

using namespace std;

//number of days in one week
const int DAYS_PER_WEEK = 7;
//number of days in one year
const int DAYS_PER_YEAR = 365;
//number of days in one leap year
const int DAYS_PER_LEAP_YEAR = 366;
//number of seconds in one day
const int SECS_PER_DAY = 24 * 60 * 60;
//number of seconds in one hour
const int SECS_PER_HOUR = 60 * 60;
//number of seconds in one minute
const int SECS_PER_MIN = 60;
//number of days in every month assuming it's not leap year
const int DAYS_IN_MONTH[12] = {
	31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31
};

// An array of c-strings for storing months
const char months[][12] = { "January", "February", "March", "April", "May", "June", "July",
"August", "September", "October", "November", "December" };
//prototype for leap year function
void leapYear(unsigned year, bool& leap);
//prototype of current date function
void currDate(unsigned seconds, char month[], unsigned & day, unsigned & year,
	unsigned & hour, unsigned & min, unsigned & sec);

int main() {
	// seconds store number of seconds passed since midnight of Jan 1,1970
	unsigned seconds = time(0);
	//c-string month variable 
	char month[20];
	//unsigned integers to store days, years, hours, minutes and seconds
	unsigned int day, year, hour, min, sec;
	//calling currDate and passing the variables as parameters
	currDate(seconds, month, day, year, hour, min, sec);
	//Displays result of current time and date
	cout << "Current date and time is " << month << " " << day << ", "
		<< year << " " << hour << ":" << min << ":" << sec << " GMT" << endl;
	system("pause");
	return 0;
}
/**
* Parameters of currDate: seconds- number of seconds passed since midnight of Jan 1,1970
*								   month[]- c-string month 
*								   & day - reference of the address of variable day
*								   & year - reference of the address of variable year
*								   & hour- reference of the address of variable hour
*								   & min- reference of the address of the
*
* Purpose of currDate: to change the value in the address of  month,day,year,hour,min,sec to get current date and time
* 
* Algorithm to implement currDate:
* START
* 1) numDays<-seconds/SECS_PER_DAY
* 2) seconds<- seconds - (numDays x SECS_PER_DAY)
* 3) numYearsPassed<- numDays / DAYS_PER_YEAR
* 4) numDaysLeft<-numDays-(numYearsPassed x DAYS_PER_YEAR)
* 5) FOR  i<-0 REPEAT until i<numYearsPassed
*	5.1) check if each year after 1970 is a leap year
*	5.2) call leapYear function to check each year
*	5.3) If the year is leap
*		5.3.1) numDaysLeft<-numDaysLeft-1
*	5.4) i<-i+1
* 6) year<- 1970+numYearsPassed
* 7) FOR i<-0 REPEAT until i < 12
*	7.1) If numDaysLeft < = DAYS_IN_MONTH[i]
*      7.1.1) numMonth<-i
*	   7.1.2) Break FOR loop
*	7.2) ELSE
*		7.2.1) numDaysLeft<- numDaysLeft-DAYS_IN_MONTH[i]
*	7.3) i<-i+1
* 8) COPY (Length of months[numMonth]+1 to variable month)
* 9) day<-numDaysLeft + 1
* 10) hour<- seconds/SECS_PER_HOUR
* 11) seconds<-seconds-(hour x SECS_PER_HOUR)
* 12) min <- seconds / SECS_PER_MIN
* 13) seconds <- seconds- (min*SECS_PER_MIN)
* 14) sec <- seconds
*
*/

void currDate(unsigned seconds, char month[], unsigned & day, unsigned & year,
	unsigned & hour, unsigned & min, unsigned & sec) {

	int numDays = seconds / SECS_PER_DAY;
	cout<<"numDays:"<<numDays<<endl;
	//seconds remaining after counting number of days
	seconds =seconds- (numDays*SECS_PER_DAY);
	//number of years passed since 1970
	int numYearsPassed = numDays / DAYS_PER_YEAR;
	//number of days left after counting number of years
	int numDaysLeft = numDays - numYearsPassed * DAYS_PER_YEAR;
	
	//for loop to check if the year is leap year
	for (int i = 0; i<numYearsPassed; i++) {
		bool isleap;
		leapYear(1970 + i, isleap);
		if (isleap) {
			numDaysLeft--;
		}
	}
	//current year
	year = 1970 + numYearsPassed;
	int numMonth;
	// for loop to get the month number 
	for (int i = 0; i<12; i++) {
		if (numDaysLeft <= DAYS_IN_MONTH[i]) {
			numMonth = i;
			break;
		}
		else {
			numDaysLeft -= DAYS_IN_MONTH[i];
		}
	}
	//To get the c-string related to the month number obtained in the above loop
	strcpy_s(month, strlen(months[numMonth]) + 1, months[numMonth]);
	//To get the date day
	day = numDaysLeft + 1;
	//To get hour in the time
	hour = seconds / SECS_PER_HOUR;
	//to get seconds remaining after counting hours
	seconds -= hour*SECS_PER_HOUR;
	//To get minute in the time
	min = seconds / SECS_PER_MIN;
	//To get seconds after counting nimutes
	seconds -= min*SECS_PER_MIN;
	//To get final seconds and passing it to the reference variable
	sec = seconds;
}



/**
* Parameters of leapYear : year- every year since 1970 to current
*						   & leap- Returns true if it is leap to the reference address or returns false if it is not
*
* Purpose of leapYear: To check if the year is leap or not
*
* Algorithm to implement leapYear:
* START
* 1) IF year/400 gives remainder 0
*	1.1) leap<-true
* 2) ELSE IF year/100 gives remainder 0
*   2.1) leap<-false
* 3) ELSE IF year/4 gives remainder 0
*	3.1) leap<-true
* 4)ELSE
*	4.1) leap<-false
* END
*/

void leapYear(unsigned year, bool& leap) {
	if (year % 400 == 0)
		leap = true;
	else if (year % 100 == 0)
		leap = false;
	else if (year % 4 == 0)
		leap = true;
	else
		leap = false;
}


