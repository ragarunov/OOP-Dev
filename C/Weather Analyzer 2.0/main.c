//I declare that the attached assignment is wholly my
//own work in accordance with Seneca Academic Policy.  No part of this
//assignment has been copied manually or electronically from any
//other source (including web sites) or distributed to other students.
//
//Name   Ronen Agarunov   Student ID  029490158
//
//Ronen Agarunov
//Student I.D: #029490158
//Assignment #2
//
//Weather Analyzer 2.0
//This program reads in the weather data that is being provided by the user and prints a summary of the data entered.
//The code uses functions to decompose the solution into reusable modules. 

#include <stdio.h>
#include <string.h>

/*
This function prompts the user to enter an integer between the min and the max
If the input entered by the user is invalid, it displays an error and asks again.
It will continue asking the user until the integer the user enters falls between
min and max (inclusive).
This function returns an integer, ensured to be between min and max (inclusive)
and assumes that min <= max
*/
int getInteger(int min, int max){
	
	int numDays;
	int validation;
	
	printf("Enter an integer between %d and %d: ", min, max); 
	validation = scanf("%d", &numDays);
    
	while (numDays < min || numDays > max || validation != 1) {
		
		printf("ERROR! Try again!\n");
		printf("Enter an integer between %d and %d: ", min, max);
		while (getchar() != '\n');
		validation = scanf("%d", &numDays);
		
	}
	
	return numDays;
	
}

/*
This function prompts the user to enter a day's worth of data (high temperature,
low temperature, weather condition) separated by commas, validates the input such
that the user is forced to enter a floating point number for the high, a floating
point number for the low. It ensures that the low temperature is not higher than
the high temperature and that the condition is one of: 'c', 's', or 'p'.
If the user enters invalid input, this function displays an error and asks again.
float * high: a pointer holding the address of the float to which the function
will copy the day's high temperature before returning.
float * low: a pointer holding the address of a float to which the function will
copy the day's low temperature before returning.
char* condition: a pointer holding the address of the char to which the function
will copy the day's condition before returning.
*/
void getDailyData( float* high, float* low, char * condition){                           				    //NEED TO COMPLETE !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    
	int rc;

	printf("Enter today's high, low, and condition (c=cloudy, s=sunny, p=precipitation)\n separated by commas: ");
	rc = scanf("%f,%f, %c", high, low, condition);
	printf("%f, %f, %c\n", *high, *low, *condition);

	while (*high < *low || rc != 3 || (*condition != 'c' && *condition != 's' && *condition != 'p')) {

		printf("ERROR! Try again!\n");
		printf("Enter today's high, low, and condition (c=cloudy, s=sunny, p=precipitation)\n separated by commas: ");
		while (getchar() != '\n');
        	rc = scanf("%f,%f, %c", high, low, condition);
       		printf("%f, %f, %c\n", *high, *low, *condition);

	}
	
}


/*
This function draws a row of characters (such as @@@@@@@ ).
char c holds the character that will be repeated
int num holds the number of times that the character will be repeated
The number of characters is controlled by the value of "num".
*/
void draw( char c, int num ){
    
	int i;
	
	for (i = 0; i < num; i++) {
		
		printf("%c", c);
		
	}
	
	printf("\n");
	
}

/*
This function returns the average of the first and second floating point number.
*/
float average(float first, float second){
    
	float result;
	
	result = (first + second) / 2;
	
	return result;
	
}

/*
This function displays the average temperature for a period of days
(e.g. Your seven day average is: 14.3)
NOTE: it displays the int days as a word; for example, 3 as "three"
If the int days is greater than 9 (nine) it just prints the value;
for example Your 10 day average is: 12.2)
*/
void displayResult( int days, float allDaysAverage ){                           				    //NEED TO COMPLETE !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

	char numWord[9][6] = {"one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
	
	//scanf("%d", &days);
    
	printf("Your %s day average is: %f\n", numWord[days-1], allDaysAverage);
	
}

/*
This function returns the correct character (@, ~, *, ;) given the current
condition and the average temperature.
NOTE: Precipitation character (* or ;) will change depending on the average
temperature.
char condition represents the current conditions
float averageTemperature represents the average daily temperature
*/
char symbolToDraw(char condition, float averageTemperature){
    
	char correctChar;
	
	if (condition == 's') {
		
		correctChar = '@';
		
	}
	
	else if (condition == 'c') {
		
		correctChar = '~';
		
	}
	
	else if ((condition == 'p') && averageTemperature <= 0) {
		
		correctChar = '*';
		
	}
	
	else if ((condition == 'p') && averageTemperature > 0) {
		
		correctChar = ';';
		
	}

	return correctChar;
	
}


int main(void){
    int numDays;
    int i;
    float sum = 0;
    float dailyHigh;
    float dailyLow;
    char conditions;
    float dailyAvg = 0;
    //title
    printf("Weather Analyzer 2.0\n");
    printf("====================\n");
    //prompt the user for a number of days
    printf("How many days of data?\n");
    //get an integer between 1 and 14
    numDays = getInteger(1,14);
    for(i = 0; i < numDays; i++){
        //get input from the user
	getDailyData(&dailyHigh, &dailyLow, &conditions);
        dailyAvg = average(dailyHigh, dailyLow);
        printf("Today's average temperature is: %.2f\n", dailyAvg);
        sum += dailyAvg;
        draw(symbolToDraw(conditions, dailyAvg), 20);
    }
    //remember, arguments are separated by commas
    //there are two arguments here...
    displayResult(numDays, (sum/numDays));
    return 0;
}
