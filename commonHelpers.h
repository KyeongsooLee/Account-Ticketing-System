/*
	Assignment #2 Milestone #2
	Name   : Kyeongsoo Lee
	ID     : 128720208
	Email  : klee229@myseneca.ca
	Section: NCC
*/
#ifndef COMMONHELPERS_H_
#define COMMONHELPERS_H_
// Header file contents goes here...

int currentYear(void);  // Get the current 4-digit year from the system 
void clearStandardInputBuffer(void);  // Empty the standard input buffer 
int getInteger(void);  // get user Input : Interger value
int getPositiveInteger(void);  // get user Input : Positivie interger value
double getDouble(void);  // get user Input : Double value
double getPositiveDouble(void);  // get user Input : Positive double value
int getIntFromRange(int lowerBound, int upperBound);  // get user Input : Value should be within the range
char getCharOption(const char str[]);  // get user Input : Single character value
void getCString(char* ptrStr, int minNumber,int maxNumber);  // get user Input : C string value
void changeUppercase(char* changeStr);  // Change all characters to Uppercase
int getPositiveIntegerOrZero(void);  // get user Input : Positivie integer value or zero
#endif // !COMMONHELPERS_H_