/*
	Assignment #2 Milestone #4
	Name   : Kyeongsoo Lee
	ID     : 128720208
	Email  : klee229@myseneca.ca
	Section: NCC
*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "account.h"
#include "commonHelpers.h"
#include "accountTicketingUI.h"
#include "ticket.h"

#define MAXSECRETPASSWORD 9
#define PROMPT 1
#define DONT_PROMPT 0
#define MAXUSERLOGIN 10
#define MAXUSERPASSWORD 10
#define LIMITATTEMPTS 3
void displayAccountSummaryHeader(void)  // Display the summary of table header
{
	printf("Acct# Acct.Type Birth\n");
	printf("----- --------- -----\n");
}

void displayAccountDetailHeader(void)  // Display the Detail of table header
{
	printf("Acct# Acct.Type Birth Income      Country    Disp.Name       Login      Password\n");
	printf("----- --------- ----- ----------- ---------- --------------- ---------- --------\n");
}

void displayAccountSummaryRecord(const struct Account* accountDataSummary)  // Display the summary of user input data
{
	const char agent[] = "AGENT", customer[] = "CUSTOMER";
	
	printf("%05d %-9s %5d\n", accountDataSummary->accountNumber, accountDataSummary->accountType == 'A' ? agent : customer, accountDataSummary->UserDemographicData.birthYear);
}

void displayAccountDetailRecord(const struct Account* accountDataDetail)  // Display the detail of user input data
{
	const char agent[] = "AGENT", customer[] = "CUSTOMER";
	int i;
	char secrectPassWord[MAXSECRETPASSWORD] = { 0 };


	for (i = 0; accountDataDetail->userLoginData.userPassword[i] != '\0'; i++)
	{
		if (i % 2 == 1)
			secrectPassWord[i] = '*';
		else
			secrectPassWord[i] = accountDataDetail->userLoginData.userPassword[i];
	}
		printf("%05d %-9s %5d $%10.2lf %-10s %-15s %-10s %8s\n", accountDataDetail->accountNumber, accountDataDetail->accountType == 'A' ? agent : customer, accountDataDetail->UserDemographicData.birthYear, accountDataDetail->UserDemographicData.householdIncome, accountDataDetail->UserDemographicData.country, accountDataDetail->userLoginData.displayName, accountDataDetail->userLoginData.userLogin, secrectPassWord);
}

void applicationStartup(struct AccountTicketingData* data)  // Startup function
{
	int indexNum, valid;
	char exitInput;
	do
	{
		valid = 0;
		indexNum = menuLogin(data->accounts, data->ACCOUNT_MAX_SIZE);  // return value = index number of Account array/ or -1 to exit the application
		if (indexNum == -1)
		{
			putchar('\n');
			printf("Are you sure you want to exit? ([Y]es|[N]o): ");
			exitInput = getCharOption("yYnN");  // get user Input : Single character value
			putchar('\n');
			if (exitInput == 'y' || exitInput == 'Y' )
			valid = 1;
		}
		else if (data->accounts[indexNum].accountType == 'A')
		{
			putchar('\n');
			menuAgent(data, &data->accounts[indexNum]);  // Agent menu
		}
		else if (data->accounts[indexNum].accountType == 'C')
		{
			putchar('\n');
			menuCustomer(data->tickets, data->TICKET_MAX_SIZE, &data->accounts[indexNum]);  // Customer menu
		}

	} while (!valid);
	printf("==============================================\n");
	printf("Account Ticketing System - Terminated\n");
	printf("==============================================\n\n");
}

int menuLogin(const struct Account accountMenuLogin[], int arrSizeMenuLogin)   // Login menu
{
	const int minNumMenu = 0, maxNumMenu = 1;
	int selection, result, acctNumIndex, valid, loginValid, attempts, flag;

	do
	{
		attempts = LIMITATTEMPTS;
		valid = 0;
		printf("==============================================\n");
		printf("Account Ticketing System - Login\n");
		printf("==============================================\n");
		printf("1) Login to the system\n");
		printf("0) Exit application\n");
		printf("----------------------------------------------\n\n");
		printf("Selection: ");
		selection = getIntFromRange(minNumMenu, maxNumMenu);  // get user Input : Value should be within the range
		
		switch (selection)
		{
		case 0:
			valid = 1;
			result = -1;
			break;
		case 1:
			do
			{
				flag = 0;
				attempts--;
				putchar('\n');
				printf("Enter the account#: ");
				acctNumIndex = findAccountIndexByAcctNum(getPositiveInteger(), accountMenuLogin, arrSizeMenuLogin, DONT_PROMPT);  // Find the index of account number
				loginValid = userLoginCheck(accountMenuLogin, arrSizeMenuLogin, acctNumIndex, &attempts);  // UserLogin Validation
				if (loginValid == 1)
				{
					result = acctNumIndex;
					valid = 1;
					flag = 1;
				}
				if (loginValid == 0 && attempts == 0)
					flag = 1;

			} while (!flag);
		}
	} while (!valid);
	return result;
}

void menuAgent(struct AccountTicketingData data[], const struct Account* loggedInUserAccount)   // Agent menu
{
	const int minNumMenu = 0, maxNumMenu = 12;
	int selection, i, index = 0, copyLoggedInAccount = loggedInUserAccount->accountNumber, ticketValid, ticketNum;
	int arcAccnt = 0, removeArcTicketCount = 0, removeTotalArcMsgCount = 0;
	char agent[] = "AGENT", removeInput, copyUserDisplayName[31] = { 0 };
	const char yesNo[] = "YN";


	for (i = 0; loggedInUserAccount->userLoginData.displayName[i] != '\0'; i++)
		copyUserDisplayName[i] = loggedInUserAccount->userLoginData.displayName[i];
	do
	{
		printf("%s: %s (%d)\n", agent, copyUserDisplayName, copyLoggedInAccount);
		printf("==============================================\n");
		printf("Account Ticketing System - Agent Menu\n");
		printf("==============================================\n");
		printf(" 1) Add a new account\n");
		printf(" 2) Modify an existing account\n");
		printf(" 3) Remove an account\n");
		printf(" 4) List accounts: summary view\n");
		printf(" 5) List accounts: detailed view\n");
		printf("----------------------------------------------\n");
		printf(" 6) List new tickets\n");
		printf(" 7) List active tickets\n");
		printf(" 8) List closed tickets\n");
		printf(" 9) Manage a ticket\n");
		printf("10) Archive closed tickets\n");
		printf("----------------------------------------------\n");
		printf("11) View archived account statistics\n");
		printf("12) View archived tickets statistics\n");
		printf("----------------------------------------------\n");
		printf("0) Logout\n\n");
		printf("Selection: ");
		
		selection = getIntFromRange(minNumMenu, maxNumMenu);  // get user Input : Value should be within the range

		switch (selection)
		{
		case 0:
			putchar('\n');
			printf("Saving session modifications...\n");
			printf("   %d account saved.\n", storeAccounts(data->accounts, data->ACCOUNT_MAX_SIZE)); // Store removed account data
			printf("   %d tickets saved.\n", storeTickets(data->tickets, data->TICKET_MAX_SIZE)); // Store ticket data
			printf("### LOGGED OUT ###\n\n");
			break;
		case 1:
			for (i = 0, index = 0; i < data->ACCOUNT_MAX_SIZE && data->accounts[i].accountNumber != 0; i++)
				index++;

			if (index == data->ACCOUNT_MAX_SIZE)
			{
				putchar('\n');
				printf("ERROR: Account listing is FULL, call ITS Support!\n");
				putchar('\n');
			}
			else
			{
				data->accounts[i].accountNumber = findMaxAcctNum(data->accounts, data->ACCOUNT_MAX_SIZE) + 1;  // Find Maximum account number
				getAccount(&data->accounts[index]);  // get user Input : Account Number and Type
				getUserLogin(&data->accounts[index].userLoginData);  // get user Input : Login ID, Display Name, and Login Password
				getDemographic(&data->accounts[index].UserDemographicData);  // get user Input : Birth year, Income, and Country
			}
			pauseExecution();  // Pause execution until user enters the enter key
			break;
		case 2:
			putchar('\n');
			index = findAccountIndexByAcctNum(index, data->accounts, data->ACCOUNT_MAX_SIZE, PROMPT);  // Find the index of account number
			if (index != -1)
				updateAccount(&data->accounts[index]);  // Update user account : Account Number and Type
			else
				printf("\nERROR: Access Denied.\n");
			break;
		case 3:
			putchar('\n');
			index = findAccountIndexByAcctNum(index, data->accounts, data->ACCOUNT_MAX_SIZE, PROMPT);  // Find the index of account number
			if (data->accounts[index].accountNumber == loggedInUserAccount->accountNumber)
			{
				putchar('\n');
				printf("ERROR: You can't remove your own account!\n\n");
			}
			else if (index == -1)
			{
				putchar('\n');
				printf("ERROR: Access Denied.\n");
			}
			else
			{
				displayAccountDetailHeader();  // Display the Detail of table header
				displayAccountDetailRecord(&data->accounts[index]);  // Display the detail of user input data
				putchar('\n');
				printf("Are you sure you want to remove this record? ([Y]es|[N]o): ");
				removeInput = getCharOption("YN");  // get user Input : Single character value
				if (removeInput == 'N')
				{
					putchar('\n');
					printf("*** No changes made! ***\n");
				}
				else
				{
					arcAccnt += removeAccnt(data, index, &removeArcTicketCount, &removeTotalArcMsgCount);
					printf("*** Account Removed! ***\n");
				}
				putchar('\n');
			}
			pauseExecution();  // Pause execution until user enters the enter key
			break;
		case 4:
			displayAllAccountSummaryRecords(data->accounts, data->ACCOUNT_MAX_SIZE);  // Display summary records
			pauseExecution();  // Pause execution until user enters the enter key
			break;
		case 5:
			displayAllAccountDetailRecords(data->accounts, data->ACCOUNT_MAX_SIZE);  // Display Detail records
			pauseExecution();  // Pause execution until user enters the enter key
			break;
		case 6:
			putchar('\n');
			do
			{
				ticketValid = 0;
				ticketValid = displayNewTicket(data->tickets, data->TICKET_MAX_SIZE);  // Find new Ticket and call displayNewTicket function
			} while (!ticketValid);
			putchar('\n');
			break;
		case 7:
			putchar('\n');
			do
			{
				ticketValid = 0;
				displayTicketDetailFunction(data->tickets, data->TICKET_MAX_SIZE, 1);  // Display tickets list : 1) Active | 0) Closed
				ticketNum = getTicketNum();  // Get ticket number or zero
				index = findTicketNumIndex(ticketNum, data->tickets, data->TICKET_MAX_SIZE);  // Find the index of ticket number
				if (ticketNum == 0)
					ticketValid = 1;
				else if (index != -1)
				{
					displayTicketMsg(&data->tickets[index]);  // Display the messages of the ticket
					pauseExecution();  // Pause execution until user enters the enter key
				}
				else
				{
					putchar('\n');
					printf("ERROR: Invalid ticket number.\n\n");
					pauseExecution();  // Pause execution until user enters the enter key
				}
			} while (!ticketValid);
			putchar('\n');
			break;
		case 8:
			putchar('\n');
			do
			{
				ticketValid = 0;
				displayTicketDetailFunction(data->tickets, data->TICKET_MAX_SIZE, 0);  // Display tickets list : 1) Active | 0) Closed
				ticketNum = getTicketNum();  // Get ticket number or zero
				index = findTicketNumIndex(ticketNum, data->tickets, data->TICKET_MAX_SIZE);  // Find the index of ticket number
				if (ticketNum == 0)
					ticketValid = 1;
				else if (index != -1)
				{
					displayTicketMsg(&data->tickets[index]);  // Display the messages of the ticket
					pauseExecution();  // Pause execution until user enters the enter key
				}
				else
				{
					putchar('\n');
					printf("ERROR: Invalid ticket number.\n\n");
					pauseExecution();  // Pause execution until user enters the enter key
				}
			} while (!ticketValid);
			putchar('\n');
			break;
		case 9:
			putchar('\n');
			printf("Enter ticket number: ");
			ticketNum = getPositiveInteger(); // get user Input : Positivie interger value
			index = findTicketNumIndex(ticketNum, data->tickets, data->TICKET_MAX_SIZE);  // Find the index of ticket number
			if (ticketNum == -1)
			{
				putchar('\n');
				printf("ERROR: Invalid ticket number.\n\n");
				pauseExecution();  // Pause execution until user enters the enter key
			}
			else
			{
				putchar('\n');
				manageTicket(&data->tickets[index], loggedInUserAccount->accountType, loggedInUserAccount->userLoginData.displayName); // Add message, close and re-open ticket
			}		
			break;
		case 10:
			putchar('\n');
			printf("Are you sure? This action cannot be reversed. ([Y]es|[N]o): ");
			getCharOption(yesNo); // get user Input : Single character value
			putchar('\n');
			printf("*** %d tickets archived ***\n\n", findClosedTickets(data->tickets, data->TICKET_MAX_SIZE, &removeArcTicketCount, &removeTotalArcMsgCount)); // Find closed tickets
			pauseExecution();  // Pause execution until user enters the enter key
			break;
		case 11:
			putchar('\n');
			printf("There are %d account(s) currently archived.\n\n", arcAccnt);
			pauseExecution();  // Pause execution until user enters the enter key
			break;
		case 12:
			putchar('\n');
			printf("There are %d ticket(s) and a total of %d message(s) archived.\n\n", removeArcTicketCount, removeTotalArcMsgCount);
			pauseExecution();  // Pause execution until user enters the enter key
			break;
		}
	} while (selection);
}

void menuCustomer(struct Ticket tickets[], int arrSize, const struct Account* loggedInUserAccount) // Customer menu
{
	int i, selection, index, ticketNum, ticketValid;
	const int minNumMenu = 0, maxNumMenu = 4;
	char customer[] = "CUSTOMER";

	do
	{
		printf("%s: %s (%d)\n", customer, loggedInUserAccount->userLoginData.displayName, loggedInUserAccount->accountNumber);
		printf("==============================================\n");
		printf("Customer Main Menu\n");
		printf("==============================================\n");
		printf("1) View your account detail\n");
		printf("2) Create a new ticket\n");
		printf("3) Modify an active ticket\n");
		printf("4) List my tickets\n");
		printf("----------------------------------------------\n");
		printf("0) Logout\n\n");
		printf("Selection: ");

		selection = getIntFromRange(minNumMenu, maxNumMenu);  // get user Input : Value should be within the range
		putchar('\n');
		switch (selection)
		{
		case 0: 
			printf("Saving session modifications...\n");
			printf("   %d tickets saved.\n", storeTickets(tickets, arrSize)); // Store ticket data
			printf("### LOGGED OUT ###\n\n");
			break;
		case 1: 
			displayAccountDetailHeader();  // Display the Detail of table header
			displayAccountDetailRecord(loggedInUserAccount);  // Display the detail of user input data
			putchar('\n');
			pauseExecution();  // Pause execution until user enters the enter key
			break;
		case 2: 
			for (i = 0, index = 0; i < arrSize && tickets[i].ticketNumber != 0; i++, index++);  // Find the maximum index number of tickets

			if (index == arrSize)
				printf("ERROR: Ticket listing is FULL, call ITS Support!\n\n");
			else
			{
				tickets[index].ticketNumber = findMaxTicketNum(tickets) + 1;  // Find Maximum account number
				getTicket(&tickets[index], loggedInUserAccount->accountNumber, loggedInUserAccount->accountType , loggedInUserAccount->userLoginData.displayName);  // get user Input : Ticket SUBJECT and message details
			}
			pauseExecution();  // Pause execution until user enters the enter key
			break;
		case 3:
			ticketValid = 0;
			printf("Enter ticket number: ");
			ticketNum = getPositiveInteger(); // get user Input : Positivie interger value
			index = findTicketNumIndex(ticketNum, tickets, arrSize);  // Find the index of ticket number

			if (ticketNum == -1)
			{
				putchar('\n');
				printf("ERROR: Invalid ticket number.\n\n");
			}
			if (tickets[index].ticketStatus == 0)
			{
				putchar('\n');
				printf("ERROR: Ticket is closed - changes are not permitted.\n\n");
			}
			else
			{
				putchar('\n');
				if (!strcmp(tickets[index].msgInfo->msgDisplayName, loggedInUserAccount->userLoginData.displayName))
					updateTicket(&tickets[index], ticketNum); // update ticket menu
				else
					printf("ERROR: Invalid ticket number - you may only modify your own ticket.\n\n");
			}
			pauseExecution();  // Pause execution until user enters the enter key
			break;
		case 4: 
			do
			{
				ticketValid = 0;
				displayCustomerTicket(tickets, arrSize , loggedInUserAccount->accountNumber);  // Find customer tickets and call displaycustomer tickets
				ticketNum = getTicketNum();  // Get ticket number or zero
				if (ticketNum == 0)
				{
					putchar('\n');
					ticketValid = 1;
				}
				else
				{
					index = findTicketNumIndex(ticketNum, tickets, arrSize);  // Find the index of ticket number

					if (!strcmp(tickets[index].msgInfo->msgDisplayName, loggedInUserAccount->userLoginData.displayName))
					{
						displayTicketMsg(&tickets[index]);  // Display the messages of the ticket
						pauseExecution();  // Pause execution until user enters the enter key
					}
					else
					{
						putchar('\n');
						printf("ERROR: Invalid ticket number - you may only access your own tickets.\n\n");
						pauseExecution();  // Pause execution until user enters the enter key
					}
				}			
			} while (!ticketValid);
			break;
		}
	} while (selection);
}

int findAccountIndexByAcctNum(int accNum, const struct Account accounts[], int arrSize, int prompt)   // Find the index of account number
{
	int i, indexFound;
	
	if (prompt)
	{
		printf("Enter the account#: ");
		accNum = getPositiveInteger();  // get user Input : Positive double value
	}

	for (i = 0, indexFound = -1; indexFound < 0 && i < arrSize; i++)
	{
		if (accNum == accounts[i].accountNumber)
			indexFound = i;
	}
	return indexFound;
}

void displayAllAccountSummaryRecords(const struct Account displayAllSummaryAccounts[], int arrSize)   // Display summary records
{
	int i;
	putchar('\n');
	displayAccountSummaryHeader();	// Display the summary of table header
	for (i = 0; i < arrSize; i++)
	{
		if(displayAllSummaryAccounts[i].accountNumber != 0)
			displayAccountSummaryRecord(&displayAllSummaryAccounts[i]);  // Display the summary of user input data
	}
	putchar('\n');
}

void displayAllAccountDetailRecords(const struct Account displayAllDetailAccounts[],  int arrSize)   // Display Detail records
{
	int i;
	putchar('\n');
	displayAccountDetailHeader();  // Display the Detail of table header
	for (i = 0; i < arrSize; i++)
		if(displayAllDetailAccounts[i].accountNumber != 0)
			displayAccountDetailRecord(&displayAllDetailAccounts[i]);  // Display the detail of user input data
	putchar('\n');
}

// Pause execution until user enters the enter key
void pauseExecution(void)
{
	printf("<< ENTER key to Continue... >>");
	clearStandardInputBuffer();  // Empty the standard input buffer 
	putchar('\n');
}

int userLoginCheck(const struct Account accounts[], int arrSize, int acctIndex, int* attempts)			//  UserLogin Validation
{
	int loginValid = 0;
	char userLogin[MAXUSERLOGIN + 1] = { 0 }, userPassword[MAXUSERPASSWORD + 1] = { 0 };

	printf("User Login    : ");
	scanf("%10[^\n]", userLogin);
	clearStandardInputBuffer();  // Empty the standard input buffer 
	printf("Password      : ");
	scanf("%10[^\n]", userPassword);
	clearStandardInputBuffer();  // Empty the standard input buffer 

	if (strcmp(userLogin, accounts[acctIndex].userLoginData.userLogin) == 0 && strcmp(userPassword, accounts[acctIndex].userLoginData.userPassword) == 0)
	{
		*attempts = acctIndex;
		loginValid = 1;
	}		
	else
		printf("INVALID user login/password combination! [attempts remaining:%d]\n", *attempts);

	if (*attempts == 0 && loginValid == 0)
	{
		putchar('\n');
		printf("ERROR:  Login failed!\n\n");
		pauseExecution();  // Pause execution until user enters the enter key
	}

	return loginValid;
}

void displayTicketHeader(void)  // Display the table header of the ticket
{
	printf("------ ----- --------------- ------ ------------------------------ --------\n");
	printf("Ticket Acct# Display Name    Status Subject                        Messages\n");
	printf("------ ----- --------------- ------ ------------------------------ --------\n");
}

void displayTicketDetail(const struct Ticket* tickets)  // Display the detali of the tickets
{
	const char openStatus[] = "ACTIVE", closedStatus[] = "CLOSED";

	printf("%06d %05d %-15s %-6s %-30s %5d\n", tickets->ticketNumber, tickets->ticketCustomerAcctNum, tickets->msgInfo->msgDisplayName, tickets->ticketStatus == 1 ? openStatus : closedStatus, tickets->subjectLine, tickets->msgCount);
}

int displayNewTicket(const struct Ticket tickets[], int arrSize)  // Find new Ticket and call displayNewTicket function
{
	int i, ticketValid = 0, newTicketNum;

	displayTicketHeader();  // Display the table header of the ticket

	for (i = 0; i < arrSize; i++)
	{
		if (tickets[i].msgCount == 1)
			displayTicketDetail(&tickets[i]);  // Display the detali of the tickets
	}
	printf("------ ----- --------------- ------ ------------------------------ --------\n");
	putchar('\n');

	newTicketNum = getTicketNum();  // Get ticket number or zero

	if (newTicketNum == 0)
		ticketValid = 1;
	else 
	{
		for (i = 0; i < arrSize && newTicketNum != tickets[i].ticketNumber; i++);

		if (newTicketNum == tickets[i].ticketNumber && tickets[i].msgCount == 1)
		{
			displayTicketMsg(&tickets[i]);  // Display the messages of the ticket
			pauseExecution();  // Pause execution until user enters the enter key
		}
		else
		{
			putchar('\n');
			printf("ERROR: Invalid ticket number.\n\n");
			pauseExecution();  // Pause execution until user enters the enter key
		}
	}
	return ticketValid;
}

void displayTicketMsg(const struct Ticket* ticketMsg)  //  Display the messages of the ticket
{
	const char openStatus[] = "ACTIVE", closedStatus[] = "CLOSED";
	const char agent[] = "AGENT", customer[] = "CUSTOMER";
	int i;

	putchar('\n');
	printf("================================================================================\n");
	printf("%06d (%s) Re: %s\n", ticketMsg->ticketNumber, ticketMsg->ticketStatus == 1 ? openStatus : closedStatus, ticketMsg->subjectLine);
	printf("================================================================================\n");
	for (i = 0; i < ticketMsg->msgCount; i++)
	{
		printf("%s (%s):\n", ticketMsg->msgInfo[i].msgAccountType == 'A' ? agent : customer, ticketMsg->msgInfo[i].msgDisplayName);
		printf("   %s\n\n", ticketMsg->msgInfo[i].msgDetail);

		if (i % 5 == 4 && i != ticketMsg->msgCount-1)
			pauseExecution();  // Pause execution until user enters the enter key
	}
}


int getTicketNum(void)  // Get ticket number or zero
{
	int userInputTicketNum;

	printf("Enter the ticket number to view the messages or\n0 to return to previous menu: ");
	userInputTicketNum = getPositiveIntegerOrZero();  // get user Input : Positivie integer value or zero

	return userInputTicketNum;
}

int findTicketNumIndex(int ticketNum, const struct Ticket tickets[], int arrSize)   // Find the index of ticket number
{
	int i, indexFound;

	for (i = 0, indexFound = -1; indexFound < 0 && i < arrSize; i++)
	{
		if (ticketNum == tickets[i].ticketNumber)
			indexFound = i;
	}
	return indexFound;
}

void displayTicketDetailFunction(const struct Ticket tickets[], int arrSize, int status)   // Display tickets list : 1) Active | 0) Closed
{
	int i;

	displayTicketHeader();  // Display the table header of the ticket
	if (!status)
	{
		for (i = 0; i < arrSize; i++)
		{
			if (tickets[i].ticketStatus == 0 && tickets[i].ticketNumber != 0)
				displayTicketDetail(&tickets[i]);  // Display the detali of the tickets
		}
	}
	else
	{
		for (i = 0; i < arrSize; i++)
		{
			if (tickets[i].ticketStatus == 1 && tickets[i].ticketNumber != 0)
				displayTicketDetail(&tickets[i]);  // Display the detali of the tickets
		}
	}
	printf("------ ----- --------------- ------ ------------------------------ --------\n");
	putchar('\n');
}

void displayCustomerTicketHeader(void)  //  Display the table header of customer tickets
{
	printf("------ ------ ------------------------------ --------\n");
	printf("Ticket Status Subject                        Messages\n");
	printf("------ ------ ------------------------------ --------\n");
}

void displayCustomerTicketDetail(const struct Ticket* customerticket)  //  Display the detail of customer tickets
{
	const char openStatus[] = "ACTIVE", closedStatus[] = "CLOSED";

	printf("%06d %-6s %-30s %5d\n", customerticket->ticketNumber, customerticket->ticketStatus == 1 ? openStatus : closedStatus, customerticket->subjectLine, customerticket->msgCount);
}

void displayCustomerTicket(const struct Ticket tickets[], int arrSize , const int custAcct)  //  Find customer tickets and call displaycustomer tickets
{
	int i;

	displayCustomerTicketHeader();  // Display the table header of customer tickets
	for (i = 0; tickets[i].ticketNumber != 0 && i < arrSize; i++)
	{
		if (tickets[i].ticketCustomerAcctNum == custAcct)
		{
			displayCustomerTicketDetail(&tickets[i]);  // Display the detail of customer tickets
		}
	}
	printf("------ ------ ------------------------------ --------\n\n");
}

int findMaxAcctNum(const struct Account acct[], int arrSize)  // Find Maximum account number
{
	int i, maxAcctNum;
	for (i = 0, maxAcctNum = 0; i < arrSize; i++) 
	{
		if (acct[i].accountNumber > maxAcctNum)
			maxAcctNum = acct[i].accountNumber;
	}
	return maxAcctNum;
}

int findMaxTicketNum(const struct Ticket tickets[])  // Find Maximum ticket number
{
	int i, maxTicketNum;
	for (i = 0, maxTicketNum = 0; tickets[i].ticketNumber != 0; i++)
	{
		if (tickets[i].ticketNumber > maxTicketNum)
			maxTicketNum = tickets[i].ticketNumber;
	}

	return maxTicketNum;
}

int removeAccnt(struct AccountTicketingData data[], int indexNum, int* ticketCount, int* totalMsgCount) // remove account data
{
	struct Account accountTmp = { 0 };
	struct Ticket ticketTmp = { 0 };
	int i, ticketAccntNum, result;

	ticketAccntNum = data->accounts[indexNum].accountNumber;

	for (i = 0; i < data->TICKET_MAX_SIZE; i++)
	{
		if (ticketAccntNum == data->tickets[i].ticketCustomerAcctNum)
		{
			appendArcTicketsData(&data->tickets[i], ticketCount, totalMsgCount); // Append archive ticket data
			data->tickets[i] = ticketTmp;
		}
	}
	result = appendArcAccntData(&data->accounts[indexNum]); // Append archived account data
	data->accounts[indexNum] = accountTmp;
	putchar('\n');

	return result;
}

int findClosedTickets(struct Ticket tickets[], int arrSize, int* ticketCount, int* totalMsgCount) // Find closed tickets
{
	int i, ClosedTicketsCount = 0;
	struct Ticket ticketTmp = { 0 };

	for (i = 0; i < arrSize; i++)
	{
		if (tickets[i].ticketStatus == 0 && tickets[i].ticketNumber != 0)
		{
			ClosedTicketsCount += appendArcTicketsData(&tickets[i], ticketCount, totalMsgCount); // Append archive ticket data
			tickets[i] = ticketTmp;
		}
	}
	return ClosedTicketsCount;
}