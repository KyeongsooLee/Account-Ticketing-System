/*
	Assignment #2 Milestone #4
	Name   : Kyeongsoo Lee
	ID     : 128720208
	Email  : klee229@myseneca.ca
	Section: NCC
*/

#ifndef ACCOUNTTICKETINGUI_H_
#define ACCOUNTTICKETINGUI_H_
// Header file contents goes here...
#include "account.h"
#include "ticket.h"

struct AccountTicketingData
{
	struct Account* accounts; // array of accounts 
	const int ACCOUNT_MAX_SIZE; // maximum elements for account array 
	struct Ticket* tickets; // array of tickets 
	const int TICKET_MAX_SIZE; // maximum elements for ticket array 
};

void displayAccountSummaryHeader(void);  // Display the summary of table header
void displayAccountDetailHeader(void);  // Display the Detail of table header
void displayAccountSummaryRecord(const struct Account* accountDataSummary);  // Display the summary of user input data
void displayAccountDetailRecord(const struct Account* accountDataDetail);  // Display the detail of user input data
void applicationStartup(struct AccountTicketingData* data);  // Startup function
int menuLogin(const struct Account accountMenuLogin[], int arrSizeMenuLogin);  // Login menu
void menuAgent(struct AccountTicketingData data[], const struct Account* loggedInUserAccount);  // Agent menu
void menuCustomer(struct Ticket tickets[], int arrSize, const struct Account* loggedInUserAccount);  // Customer menu
int findAccountIndexByAcctNum(int accNum, const struct Account accounts[], int arrSize, int prompt);  // Find the index of account number
void displayAllAccountSummaryRecords(const struct Account accounts[], int arrSize);  // Display summary records
void displayAllAccountDetailRecords(const struct Account accounts[], int arrSize);  // Display Detail records
void pauseExecution(void);  // Pause execution until user enters the enter key
int userLoginCheck(const struct Account accounts[], int arrSize, int acctIndex, int* attempts); //  UserLogin Validation
void displayTicketHeader(void);  // Display the table header of the ticket
void displayTicketDetail(const struct Ticket* tickets);  // Display the detali of the tickets
int displayNewTicket(const struct Ticket tickets[], int arrSize);  // Find new Ticket and call displayNewTicket function
void displayTicketMsg(const struct Ticket* ticketMsg);  // Display the messages of the ticket
int getTicketNum(void);  // Get ticket number or zero
int findTicketNumIndex(int ticketNum, const struct Ticket tickets[], int arrSize);  // Find the index of ticket number
void displayTicketDetailFunction(const struct Ticket tickets[], int arrSize, int status);  // Display tickets list : 1) Active | 0) Closed
void displayCustomerTicketHeader(void);  // Display the table header of customer tickets
void displayCustomerTicketDetail(const struct Ticket* customerticket);  // Display the detail of customer tickets
void displayCustomerTicket(const struct Ticket tickets[], int arrSize, const int custAcct);  // Find customer tickets and call displaycustomer tickets
int findMaxAcctNum(const struct Account acct[], int arrSize);  // Find Maximum account number
int findMaxTicketNum(const struct Ticket tickets[]);  // Find Maximum ticket number
int removeAccnt(struct AccountTicketingData data[], int indexNum, int* ticketCount, int* totalMsgCount); // remove account data
int findClosedTickets(struct Ticket tickets[], int arrSize, int* ticketCount, int* totalMsgCount); // Find closed tickets

#endif // !ACCOUNTTICKETINGUI_H_