/*
	Assignment #2 Milestone #4
	Name   : Kyeongsoo Lee
	ID     : 128720208
	Email  : klee229@myseneca.ca
	Section: NCC
*/
#ifndef ACCOUNT_H_
#define ACCOUNT_H_
// Header file contents goes here...
#define MAXCOUNTRY 30
#define MAXDISPLAYNAME 30
#define MAXUSERLOGIN  10
#define MAXUSERPASSWORD 10
struct Demographic
{
	int birthYear;
	double householdIncome;
	char country[MAXCOUNTRY + 1];
};

struct UserLogin
{
	char displayName[MAXDISPLAYNAME+1];
	char userLogin[MAXUSERLOGIN+1];
	char userPassword[MAXUSERPASSWORD+1];
};

struct Account
{
	int accountNumber;
	char accountType;
	struct UserLogin userLoginData;
	struct Demographic UserDemographicData;
};

void getAccount(struct Account* accountData);  // get user Input : Account Number and Type
void getUserLogin(struct UserLogin* userLoginData);  // get user Input : Login ID, Display Name, and Login Password
void getDemographic(struct Demographic* demographicData);  // get user Input : Birth year, Income, and Country
void updateAccount(struct Account* updateAccount);  // Update user account : Account Number and Type
void updateUserLogin(struct UserLogin* updateUserLogin);  // Update user login : Display Name, and Login Password
void updateDemographic(struct Demographic* updateDemo);  // Update user demographic : Birth year, Income, and Country
int checkWhitespase(const char userLogin[]);  // Find Whitespase at the userLogin
int checkPassword(const char userPassword[]);  // userPassword Validation
int loadAccounts(struct Account accounts[], int arrSize); // Load account information from text file
int appendArcAccntData(const struct Account* accounts); // Append archived account data
int storeAccounts(struct Account accounts[], int arrSize); // Store removed account data
#endif // !ACCOUNT_H_