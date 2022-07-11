/*
	Assignment #2 Milestone #4
	Name   : Kyeongsoo Lee
	ID     : 128720208
	Email  : klee229@myseneca.ca
	Section: NCC
*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "commonHelpers.h"
#include <time.h>
#include <ctype.h>
// Uses the time.h library to obtain current year information 
// Get the current 4-digit year from the system 
int currentYear(void) 
{ 
	time_t currentTime = time(NULL);
	return localtime(&currentTime)->tm_year + 1900; 
}

// As demonstrated in the course notes: 
// Empty the standard input buffer 
void clearStandardInputBuffer(void)
{
	while (getchar() != '\n')
	{ 
		; // On purpose: do nothing 
	} 
}

int getInteger(void)  // get user Input : Interger value
{
	char newLine = 'x';
	int value, valid = 0;

	do
	{
		if (newLine == '\n')
			valid = 1;
		else
		{
			scanf("%d%c", &value, &newLine);
			if (newLine != '\n')
			{
				clearStandardInputBuffer();  // Empty the standard input buffer 
				printf("ERROR: Value must be an integer: ");
			}
		}
	} while (!valid);
	return value;
}

int getPositiveInteger(void)  // get user Input : Positivie interger value
{
	int value = 0, valid = 0;

	do
	{
		if (value > 0)
			valid = 1;
		else
		{
			value = getInteger();  // get user Input : Interger value
			if (value <= 0)
				printf("ERROR: Value must be a positive integer greater than zero: ");
		}
	} while (!valid);
	return value;
}

double getDouble(void)  // get user Input : Double value
{
	double value;
	char newLine = 'x';
	int valid = 0;

	do
	{
		if (newLine == '\n')
			valid = 1;
		else
		{
			scanf("%lf%c", &value, &newLine);
			if (newLine != '\n')
			{
				clearStandardInputBuffer();  // Empty the standard input buffer 
				printf("ERROR: Value must be a double floating-point number: ");
			}
		}
	} while (!valid);
	return value;
}

double getPositiveDouble(void)  // get user Input : Positive double value
{
	double value = 0;
	int valid = 0;
	do
	{
		if (value > 0.0)
			valid = 1;
		else
		{
			value = getDouble();  // get user Input : Double value			
			if (value <= 0.0)
				printf("ERROR: Value must be a positive double floating-point number: ");
		}
	} while (!valid);
	return value;
}

int getIntFromRange(int lowerBound, int upperBound)  // get user Input : Value should be within the range
{
	int value, valid = 0;

	do
	{
		value = getInteger();  // get user Input : Interger value
		if (value >= lowerBound && value <= upperBound)
			valid = 1;
		else
			printf("ERROR: Value must be between %d and %d inclusive: ", lowerBound, upperBound);
	} while (!valid);
	return value;
}

char getCharOption(const char str[])  // get user Input : Single character value
{
	char charInput, newLine;
	int i, flag, valid = 0;
	do
	{
		scanf("%c%c", &charInput, &newLine);
		if (newLine != '\n')
			clearStandardInputBuffer();  // Empty the standard input buffer 

		for (i = 0, flag = 0; !flag; i++)
		{
			if (charInput == str[i] && newLine == '\n')
			{
				flag = 1;
				valid = 1;
			}
			else if (str[i] == '\0')
			{
				printf("ERROR: Character must be one of [%s]: ", str);
				flag = 1;
			}
		}
	} while (!valid);
	return charInput;
}

void getCString(char* ptrStr, int minNumber,int maxNumber)  // get user Input : C string value
{
	char newLine, testchar[301];
	int valid, i;

	do
	{
		valid = 0;
		scanf("%300[^\n]%c", testchar, &newLine);

		if (newLine != '\n')
			clearStandardInputBuffer();  // Empty the standard input buffer 
		else
		{
			for (i = 0; testchar[i] != '\0'; i++){} // find '\0'

			if (i == minNumber && minNumber == maxNumber) // Characters is within the specified range (min == max)
				valid = 1;
			else if (i != minNumber && minNumber == maxNumber) // Error (min == max)
				printf("ERROR: String length must be exactly %d chars: ", maxNumber);
			
			if (i >= minNumber && i <= maxNumber && minNumber != maxNumber) // characters is within the specified range (min != max)
				valid = 1;
			else if (i < minNumber && minNumber != maxNumber) // It needs more characters
				printf("ERROR: String length must be between %d and %d chars: ", minNumber, maxNumber);
			else if (i > maxNumber && minNumber != maxNumber) // It needs less characters
				printf("ERROR: String length must be no more than %d chars: ", maxNumber);
		}
	} while (!valid);
	for(i = 0; ptrStr[i] != '\0'; i++ )
		ptrStr[i] = '\0';
	for (i = 0; testchar[i] != '\0'; i++)
		ptrStr[i] = testchar[i];
}

void changeUppercase(char* changeStr)//  Change all characters to Uppercase
{
	int i;
	for (i = 0; changeStr[i] != '\0'; i++)
		changeStr[i]=toupper(changeStr[i]);
}

int getPositiveIntegerOrZero(void)  // get user Input : Positivie interger value or zero
{
	int value = -1, valid = 0;

	do
	{
		if (value >= 0)
			valid = 1;
		else
		{
			value = getInteger();  // get user Input : Interger value
			if (value < 0)
				printf("ERROR: Value must be positive or zero: ");
		}
	} while (!valid);
	return value;
}