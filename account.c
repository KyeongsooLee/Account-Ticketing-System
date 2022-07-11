/*
	Assignment #2 Milestone #4
	Name   : Kyeongsoo Lee
	ID     : 128720208
	Email  : klee229@myseneca.ca
	Section: NCC
*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <ctype.h>
#include "commonHelpers.h"
#include "account.h"

void getAccount(struct Account* accountData)   // get user Input : Account Number and Type
{
	const char accountType[] = "AC";

	putchar('\n');
	printf("New Account Data (Account#:%d)\n", accountData->accountNumber);
	printf("----------------------------------------\n");
	printf("Enter the account type (%c=Agent | %c=Customer): ", accountType[0], accountType[1]);
	accountData->accountType = getCharOption(accountType);  // get user Input : Single character value
	putchar('\n');
}

void getUserLogin(struct UserLogin* UserLoginData)   // get user Input : Login ID, Display Name, and Login Password
{
	const int minUserLogin = 1;
	const int maxUserLogin = 10;
	const int minDisplayName = 1;
	const int maxDisplayName = 30;
	const int numPassword = 8;
	int valid;

	printf("User Login Data Input\n");
	printf("----------------------------------------\n");
	do
	{
		valid = 1;
		printf("Enter user login (%d chars max): ", maxUserLogin);
		getCString(UserLoginData->userLogin, minUserLogin, maxUserLogin);  // get user Input : C string value
		valid = checkWhitespase(UserLoginData->userLogin);					//   Find Whitespase at the userLogin		
	} while (!valid);
	printf("Enter the display name (%d chars max): ", maxDisplayName);
	getCString(UserLoginData->displayName, minDisplayName, maxDisplayName);  // get user Input : C string value
	do
	{
		valid = 1;
		printf("Enter the password (must be %d chars in length): ", numPassword);
		getCString(UserLoginData->userPassword, numPassword, numPassword);  // get user Input : C string value
		valid = checkPassword(UserLoginData->userPassword);
	} while (!valid);
	putchar('\n');
}

void getDemographic(struct Demographic* demographicData)   // get user Input : Birth year, Income, and Country
{
	const int minCurrentAge = 18;
	const int maxCurrentAge = 110;
	const int minCountry = 1;
	const int maxCountry = 30;

	printf("Demographic Data Input\n");
	printf("----------------------------------------\n");
	printf("Enter birth year (current age must be between %d and %d): ", minCurrentAge, maxCurrentAge);
	demographicData->birthYear = getIntFromRange(currentYear() - maxCurrentAge, currentYear() - minCurrentAge);  // get user Input : Value should be within the range
	printf("Enter the household Income: $");
	demographicData->householdIncome = getPositiveDouble();  // get user Input : Positive double value
	printf("Enter the country (30 chars max.): ");
	getCString(demographicData->country, minCountry, maxCountry);  // get user Input : C string value
	changeUppercase(demographicData->country);  // Change all characters to Uppercase
	putchar('\n');
	printf("*** New account added! ***\n\n");
}

void updateAccount(struct Account* updateAccount)   // Update user account : Account Number and Type
{
	int selection;
	const int minNumMenu = 0, maxNumMenu = 3;
	const char accountType[] = "AC";
	putchar('\n');
	do
	{
		printf("Account: %d - Update Options\n", updateAccount->accountNumber);
		printf("----------------------------------------\n");

		printf("1) Update account type (current value: %c)\n", updateAccount->accountType);
		printf("2) Login\n");
		printf("3) Demographics\n");
		printf("0) Done\n");
		printf("Selection: ");
		selection = getIntFromRange(minNumMenu, maxNumMenu);  // get user Input : Value should be within the range
		switch (selection)
		{
		case 0:
			putchar('\n');
			break;
		case 1:
			putchar('\n');
			printf("Enter the account type (%c=Agent | %c=Customer): ", accountType[0], accountType[1]);
			updateAccount->accountType = getCharOption(accountType);  // get user Input : Single character value
			break;
		case 2:
			updateUserLogin(&updateAccount->userLoginData);  // Update user login : Display Name, and Login Password
			break;
		case 3:
			updateDemographic(&updateAccount->UserDemographicData);  // Update user demographic : Birth year, Income, and Country
			break;

		}
	} while (selection);
}
void updateUserLogin(struct UserLogin* updateUserLogin)   // Update user login : Display Name, and Login Password
{
	int selection, valid;
	const int minNumMenu = 0, maxNumMenu = 2;
	const int minDisplayName = 1, maxDisplayName = 30;
	const int numPassword = 8;
	putchar('\n');
	do
	{
		printf("User Login: %s - Update Options\n", updateUserLogin->userLogin);
		printf("----------------------------------------\n");
		printf("1) Display name (current value: %s)\n", updateUserLogin->displayName);
		printf("2) Password\n");
		printf("0) Done\n");
		printf("Selection: ");
		selection = getIntFromRange(minNumMenu, maxNumMenu);  // get user Input : Value should be within the range
		putchar('\n');
		switch (selection)
		{
		case 0:
			break;
		case 1:
			printf("Enter the display name (%d chars max): ", maxDisplayName);
			getCString(updateUserLogin->displayName, minDisplayName, maxDisplayName);  // get user Input : C string value
			putchar('\n');
			break;
		case 2:
			do
			{
				valid = 1;
				printf("Enter the password (must be %d chars in length): ", numPassword);
				getCString(updateUserLogin->userPassword, numPassword, numPassword);  // get user Input : C string value
				valid = checkPassword(updateUserLogin->userPassword);
			} while (!valid);
			putchar('\n');
			break;
		}
	} while (selection);
}
void updateDemographic(struct Demographic* updateDemo) // Update user demographic : Birth year, Income, and Country
{
	int selection, valid;
	const int minNumMenu = 0, maxNumMenu = 2;
	const int minCountry = 1, maxCountry = 30;
	putchar('\n');
	do
	{
		printf("Demographic Update Options\n");
		printf("----------------------------------------\n");
		printf("1) Household Income (current value: $%.2lf)\n", updateDemo->householdIncome);
		printf("2) Country (current value: %s)\n", updateDemo->country);
		printf("0) Done\n");
		printf("Selection: ");
		selection = getIntFromRange(minNumMenu, maxNumMenu);  // get user Input : Value should be within the range
		putchar('\n');
		switch (selection)
		{
		case 0: 
			break;
		case 1:
			printf("Enter the household Income: $");
			updateDemo->householdIncome = getPositiveDouble();  // get user Input : Positive double value
			putchar('\n');
			break;
		case 2:
			do
			{
				valid = 1;
				printf("Enter the country (30 chars max.): ");
				getCString(updateDemo->country, minCountry, maxCountry);  // get user Input : C string value
				changeUppercase(updateDemo->country);  // Change all characters to Uppercase
			} while (!valid);
			putchar('\n');
			break;
		}
	} while (selection);
}

int checkWhitespase(const char userLogin[]) //   Find Whitespase at the userLogin

{
	int i, valid = 1, result;
	for (i = 0; valid != 0 && userLogin[i] != '\0'; i++)    // Find Whitespace
	{
		if (isspace(userLogin[i]))
		{
			printf("ERROR:  The user login must NOT contain whitespace characters.\n");
			valid = 0;
		}
	}
	result = valid;

	return result;
}

int checkPassword(const char userPassword[])   //   userPassword Validation
{
	int i, j, valid = 1, digitCount, uppercaseCount, lowercaseCount, symbolCount, result;
	const char pwSymbol[] = "!@#$%^&*";
	const int eachNumber = 2;

	digitCount = uppercaseCount = lowercaseCount = symbolCount = 0;
	for (i = 0; userPassword[i] != '\0'; i++)
	{
		if (isdigit(userPassword[i]))
			digitCount++;
		else if (isupper(userPassword[i]))
			uppercaseCount++;
		else if (islower(userPassword[i]))
			lowercaseCount++;
		else
		{
			for (j = 0; pwSymbol[j] != '\0'; j++)
				if (pwSymbol[j] == userPassword[i])
					symbolCount++;
		}
	}
	if (digitCount == uppercaseCount && lowercaseCount == symbolCount)
		valid = 1;
	else
	{
		printf("SECURITY: Password must contain %d of each:\n", eachNumber);
		printf("          Digit: 0-9\n");
		printf("          UPPERCASE character\n");
		printf("          lowercase character\n");
		printf("          symbol character: %s\n", pwSymbol);
		valid = 0;
	}
	result = valid;

	return result;
}

int loadAccounts(struct Account accounts[], int arrSize) // Load account information from text file
{
	const char filename[] = "accounts.txt";
	int i = 0;
	char ch;

	FILE* fp = fopen(filename, "r");

	if (fp != NULL)
	{
		while (i < arrSize && fscanf(fp, "%d~%c~%30[^~]~%10[^~]~%10[^~]~%d~%lf~%30[^\n]%c",
			&accounts[i].accountNumber, &accounts[i].accountType, accounts[i].userLoginData.displayName, accounts[i].userLoginData.userLogin,
			accounts[i].userLoginData.userPassword, &accounts[i].UserDemographicData.birthYear, &accounts[i].UserDemographicData.householdIncome,
			accounts[i].UserDemographicData.country, &ch) == 9)
		{
			if (ch != '\n')
			{
				while (fgetc(fp) != '\n');
			}
			i++;
		}
		fclose(fp);
		fp = NULL;
	}
	else
		printf("ERROR: Unable to open file for reading.\n");

	return i;
}

int appendArcAccntData(const struct Account* accounts) // Append archived account data
{
	const char filename[] = "accounts_arc.txt";
	int result = 0;

	FILE* fp = fopen(filename, "a");

	if (fp != NULL)
	{
		fprintf(fp, "%d~%c~%s~%s~%s~%d~%.2lf~%s\n", accounts->accountNumber, accounts->accountType, accounts->userLoginData.displayName, 
			accounts->userLoginData.userLogin, accounts->userLoginData.userPassword, accounts->UserDemographicData.birthYear,
			accounts->UserDemographicData.householdIncome, accounts->UserDemographicData.country);

		fclose(fp);
		fp = NULL;
		result = 1;
	}
	else
		printf("ERROR: Unable to open file for appending.\n");
	
	return result;
}

int storeAccounts(struct Account accounts[], int arrSize) // Store removed account data
{
	const char filename[] = "accounts.txt";
	int i, saveAccountCount = 0;

	FILE* fp = fopen(filename, "w");

	if (fp != NULL)
	{
		for (i = 0; i < arrSize; i++)
		{
			if (accounts[i].accountNumber != 0)
			{
				fprintf(fp, "%d~%c~%s~%s~%s~%d~%.2lf~%s\n", accounts[i].accountNumber, accounts[i].accountType, accounts[i].userLoginData.displayName,
					accounts[i].userLoginData.userLogin, accounts[i].userLoginData.userPassword, accounts[i].UserDemographicData.birthYear,
					accounts[i].UserDemographicData.householdIncome, accounts[i].UserDemographicData.country);
				saveAccountCount++;
			}
		}
		fclose(fp);
		fp = NULL;
	}
	else
		printf("ERROR: Unable to open file for writing.\n");

	return saveAccountCount;
}