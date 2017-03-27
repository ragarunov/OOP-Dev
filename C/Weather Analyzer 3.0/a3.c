/*
I declare that the attached assignment is wholly my
own work in accordance with Seneca Academic Policy.  No part of this
assignment has been copied manually or electronically from any
other source (including web sites) or distributed to other students.

Name   Ronen Agarunov   Student ID  029490158

Ronen Agarunov
Student I.D: #029490158
Assignment #3

Weather Analyzer 3.0
=====================
This program will process, read and store a large volume of weather data found in a file called historicaldata.csv. 
Each row of this data file will consist of weather for Toronto for a particular day.
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*V 1.1:
Changes:

1) declared i outside of loop, you don't need -std=c99 to compile anymore
2) added a check for existence of historicaldata.csv
*/

/*an instance of this struct holds the weather data for a single day*/
struct DailyData{
    int day;
    int month;
    int year;
    float high;
    float low;
    float precipitation;
    char condition;
};

/*an instance of this struct holds summary information for the weather
for a given month*/
struct MonthlyStatistic{
    float minTemperature;
    float maxTemperature;
    float averageTemperature;
    float totalPrecipitation;
};
int readDailyData(FILE* fp, struct DailyData allData[]);

int getRelevantRecords(int yearWanted, const struct DailyData allData[], int sz,  struct DailyData yearData[]);
void sortYearData(struct DailyData yearData[], int sz);
void getStats(int month, const struct DailyData yearData[],
                    int sz, struct MonthlyStatistic* monthStats);
void printMonthlyStatistic(int month, const struct MonthlyStatistic* monthly);
void graphLine(int month, const struct MonthlyStatistic* monthly);
void printVerbose(const struct DailyData yearData[],int sz);
char symbolToDraw(char condition, float avgTemp);
float average(float first, float second);
void draw( char c, int num );


int main(void){
    FILE* fp = fopen("historicaldata.csv","r");
    if(!fp){
        printf("you need to put historicaldata.csv into this directory\n");
        exit(0);
    }
    struct DailyData  allData[3000];
    struct DailyData yearData[366];
    int numTotalRecords;

    numTotalRecords = readDailyData(fp, allData);
    int year;
    int reportType;
    int i;
    struct MonthlyStatistic monthly[12];
    printf("Please enter the year for the report: ");
    scanf("%d",&year);
    printf("Please enter the type of report you wish to generate:\n");
    printf("1) summary\n");
    printf("2) detailed\n");
    scanf("%d",&reportType);
    int numDays = getRelevantRecords(year,allData,numTotalRecords,yearData);
    sortYearData(yearData,numDays);

    for(i=0;i<12;i++){
        getStats(i+1,yearData,numDays,&monthly[i]);
    }

    printf("Weather summary for %d\n",year);
    printf("|   Month   | High  |  Low  |  Avg  | Precip  |\n");
    printf("|-----------|-------|-------|-------|---------|\n");
    for(i=0;i<12;i++){
        printMonthlyStatistic(i+1,&monthly[i]);
    }
    printf("\n\n");
    printf("Precipitation Graph\n\n");
    for (i=0;i<12;i++){
        graphLine(i+1,&monthly[i]);
    }
    if(reportType == 2){
        printf("\n\n");
        printf("Detailed report:\n");
        printVerbose(yearData,numDays);
    }
    return 0;
}
int readDailyData(FILE* fp, struct DailyData allData[]){
    int i=0;
    while(fscanf(fp,"%d,%d,%d,%f,%f,%f,%c\n",
        &allData[i].year,&allData[i].month,&allData[i].day,
        &allData[i].high,&allData[i].low,&allData[i].precipitation,
        &allData[i].condition) == 7){
        i++;
    }
    return i;
}

/*
This function must copy over all records from allData to yearData that matches yearWanted. Function returns number of records copied. 
Note, do not assume there are 365 days in a year. Some years will have 366 days because they are leap years. 
*/
int getRelevantRecords(int yearWanted, const struct DailyData allData[], 
                                    int sz,  struct DailyData yearData[]){
										
	int i;
	int j = 0;
	
	for (i = 0; i < sz; i++) {
		
		if (yearWanted == allData[i].year) {
			
			yearData[j] = allData[i];
			
			j++;

		}
		
	}

	return j;
	
}

/*
This function sorts the records in the yearData array. 
The sorting is done so that the earliest date is the first record. 
Thus, if yearData had a record for every day of the year, this function would put the data for January 1 into yearData[0], January 2 into yearData[1] and so on. 
*/
void sortYearData(struct DailyData yearData[], int sz){
    
	int i;
	int j;
	struct DailyData tmp ;

	for (i=0; i < ( sz - 1 ); i++) {

		for (j=0; j <sz-1-i; j++) {

			if (yearData[j].month > yearData[j+1].month) {

				tmp = yearData[j];
				yearData[j] = yearData[j+1];
				yearData[j+1] = tmp;

			}

			else if (yearData[j].month == yearData[j+1].month) {
				
				if (yearData[j].day > yearData[j+1].day) {

					tmp = yearData[j];
					yearData[j] = yearData[j+1];
					yearData[j+1] = tmp;

				}
		
			}	

		}

	}

}

/*
This function must find minimum temperature, the maximum temperature, 
the average temperature and total precipitation for a given month using the data in the array with a matching month. 
The results are passed back to the calling function by storing them into the appropriate data members of monthStats
*/
void getStats(int month, const struct DailyData yearData[],
                    int sz,struct MonthlyStatistic* monthly){
    
	int i = 0;
	double average;
	double num = 0;
	monthly->maxTemperature = -999;
	monthly->minTemperature = 100;	

	for (i = 0; i < sz; i++) {

		if (yearData[i].month == month) {
			
			if (yearData[i].low < monthly->minTemperature) {

				monthly->minTemperature = yearData[i].low;

			}

			if (yearData[i].high > monthly->maxTemperature) {

				monthly->maxTemperature = yearData[i].high;

			}
			
			average += (monthly->maxTemperature + monthly->minTemperature) / 2;

			monthly->totalPrecipitation += yearData[i].precipitation;
			
			num++;
		}
		
	}	

	monthly->averageTemperature = average / num;

}

/*
This function will print out one single row of the summary table. 
Each row of the table consists of text and values separated by the vertical bar symbol ('|'). 
*/
void printMonthlyStatistic(int month,const struct MonthlyStatistic* monthly){
	
	char numWord[12][10] = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};
    
	printf ("| %9s | %5.1f | %5.1f | %5.1f | %7.1f |\n", numWord[month-1], monthly->maxTemperature, monthly->minTemperature, monthly->averageTemperature, monthly->totalPrecipitation);
	
}

/*
This function will print out one single row of the precipitation bar graph
*/
void graphLine(int month,const struct MonthlyStatistic* monthly){
    
	int i;
	int prec = monthly->totalPrecipitation;
	int num;

	char numWord[12][10] = {"January", "February", "March", "April", "May", "June", "July", "August", 
"September", "October", "November", "December"};
	
	prec = (prec / 10) + 1;
	
	printf("%12s|", numWord[month-1]);
	for (i=0; i<prec; i++) {
	
		printf("*");
	
	}	
	
	printf("\n");
}

/*
This function will print the details of the weather data for each of the records in yearData. 
The output of this function is sz lines, where each line shows the detailed weather information for a specific date. 
This information includes the date as well as the average temperature and 20 symbols based on the condition of the day. 
*/
void printVerbose(const struct DailyData yearData[],int sz){
    
	char c;
	char numWord[12][10] = {"January", "February", "March", "April", "May", "June", "July", "August", 
"September", "October", "November", "December"};
	int i;
	
	for (i=0; i<sz; i++) {
		c = symbolToDraw(yearData[i].condition, (yearData[i].high+yearData[i].low)/2);
		
		printf("%9s %3d %5d: %7.1f ", 
numWord[yearData[i].month-1], yearData[i].day, yearData[i].year, (yearData[i].high+yearData[i].low)/2, 
c);

		draw (c, 20);
		
	}
}

/*
This function returns the correct character ('@', '~', '*', ';') given the current condition and the average temperature. 
Function returns '@' for condition 's', '~' for condition 'c', '*' for condition 'p' if average temperature is below 0, ; for condition 'p' othewise.
*/
char symbolToDraw(char condition, float avgTemp){
    
	char correctChar;
	
	if (condition == 's') {
		
		correctChar = '@';
		
	}
	
	else if (condition == 'c') {
		
		correctChar = '~';
		
	}
	
	else if ((condition == 'p') && avgTemp <= 0) {
		
		correctChar = '*';
		
	}
	
	else if ((condition == 'p') && avgTemp > 0) {
		
		correctChar = ';';
		
	}

	return correctChar;
	
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
This function prints the symbol passed in num times.
*/
void draw( char c, int num ){

	int i;
	
	for (i = 0; i < num; i++) {
		
		printf("%c", c);
		
	}
	
	printf("\n");
	
}