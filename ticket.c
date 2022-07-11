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
#include "commonHelpers.h"
#include "ticket.h"

#define MAXSUBJECT 30
#define MINSUBJECT 1
#define MAXMSGDETALIS 150
#define MINMSGDETAILS 1

void getTicket(struct Ticket* tickets, int accountNumber, const char accountType, const char displayName[])  // get user Input : Ticket SUBJECT and message details
{
	const int statusType = 1; // Active

	printf("New Ticket (Ticket#:%06d)\n", tickets->ticketNumber);
	printf("----------------------------------------\n");
	printf("Enter the ticket SUBJECT (%d chars. maximum): ", MAXSUBJECT);
	getCString(tickets->subjectLine, MINSUBJECT, MAXSUBJECT); // get user Input : C string value
	putchar('\n');
	printf("Enter the ticket message details (%d chars. maximum). Press the ENTER key to submit:\n", MAXMSGDETALIS);
	getCString(tickets->msgInfo->msgDetail, MINMSGDETAILS, MAXMSGDETALIS); // get user Input : C string value
	tickets->ticketStatus = statusType;
	tickets->msgCount = 1;
	tickets->ticketCustomerAcctNum = accountNumber;
	tickets->msgInfo->msgAccountType = accountType;
	strcpy(tickets->msgInfo->msgDisplayName, displayName);

	printf("\n*** New ticket created! ***\n\n");
}

void updateTicket(struct Ticket* tickets, int custTicketNum) // update ticket menu
{
	const char openStatus[] = "ACTIVE", closedStatus[] = "CLOSED";
	const char yesNo[] = "YN";
	const int minNumMenu = 0, maxNumMenu = 3;
	const int maxStoreMsg = 20;
	int selection;

	do
	{
		printf("----------------------------------------\n");
		printf("Ticket %06d - Update Options\n", custTicketNum);
		printf("----------------------------------------\n");
		printf("Status  : %s\n", tickets->ticketStatus == 1 ? openStatus : closedStatus);
		printf("Subject : %s\n", tickets->subjectLine);
		printf("----------------------------------------\n");
		printf("1) Modify the subject\n");
		printf("2) Add a message\n");
		printf("3) Close ticket\n");
		printf("0) Done\n");
		printf("Selection: ");
		selection = getIntFromRange(minNumMenu, maxNumMenu);  // get user Input : Value should be within the range
		putchar('\n');
		switch (selection)
		{
		case 0:

			break;
		case 1:
			printf("Enter the revised ticket SUBJECT (%d chars. maximum): ", MAXSUBJECT);
			getCString(tickets->subjectLine, MINMSGDETAILS, MAXMSGDETALIS); // get user Input : C string value
			putchar('\n');
			break;
		case 2:

			if (tickets->msgCount < maxStoreMsg)
			{
				addMsgDetail(tickets->msgInfo, &tickets->msgCount); // Add message detail from customer
				putchar('\n');
			}
			else
			{
				printf("ERROR: Message limit has been reached, call ITS Support!\n");
				putchar('\n');
			}
			break;
		case 3:
			printf("Are you sure you CLOSE this ticket? ([Y]es|[N]o): ");
			if (getCharOption(yesNo) == 'Y') // get user Input : Single character value
			{
				putchar('\n');
				tickets->ticketStatus = 0;		// Change the type for CLOSED
				if (tickets->msgCount != 20)
				{
					printf("Do you want to leave a closing message? ([Y]es|[N]o): ");
					if (getCharOption(yesNo) == 'Y') // get user Input : Single character value
					{
						putchar('\n');
						addMsgDetail(tickets->msgInfo, &tickets->msgCount); // Add message detail from customer
					}
					putchar('\n');
				}
				printf("*** Ticket closed! ***\n");
				selection = 0;
				putchar('\n');
			}
			break;
		}
	} while (selection);
}

void addMsgDetail(struct Message msg[], int* msgCount) // Add message detail from customer
{
	char addMsg[MAXMSGDETALIS + 1] = { 0 };

	printf("Enter the ticket message details (%d chars. maximum). Press the ENTER key to submit:\n", MAXMSGDETALIS);
	getCString(addMsg, MINMSGDETAILS, MAXMSGDETALIS); // get user Input : C string value

	msg[*msgCount].msgAccountType = 'C';
	strcpy(msg[*msgCount].msgDetail, addMsg);
	strcpy(msg[*msgCount].msgDisplayName, msg->msgDisplayName);

	*msgCount += 1;
}

void addMsgAgent(struct Message msg[], int* msgCount, const char accountType, const char displayName[]) // Added message from agent
{
	char addMsg[MAXMSGDETALIS + 1] = { 0 };

	printf("Enter the ticket message details (%d chars. maximum). Press the ENTER key to submit:\n", MAXMSGDETALIS);
	getCString(addMsg, MINMSGDETAILS, MAXMSGDETALIS); // get user Input : C string value

	strcpy(msg[*msgCount].msgDetail, addMsg);
	strcpy(msg[*msgCount].msgDisplayName, displayName);
	msg[*msgCount].msgAccountType = accountType;
	*msgCount += 1;
}

void manageTicket(struct Ticket* tickets, const char accountType, const char displayName[]) // Add message, close and re-open ticket
{
	const char openStatus[] = "ACTIVE", closedStatus[] = "CLOSED";
	const char yesNo[] = "YN";
	const int minNumMenu = 0, maxNumMenu = 3;
	const int maxStoreMsg = 20;
	int selection;

	do
	{
		printf("----------------------------------------\n");
		printf("Ticket %06d - Update Options\n", tickets->ticketNumber);
		printf("----------------------------------------\n");
		printf("Status  : %s\n", tickets->ticketStatus == 1 ? openStatus : closedStatus);
		printf("Subject : %s\n", tickets->subjectLine);
		printf("Acct#   : %d\n", tickets->ticketCustomerAcctNum);
		printf("Customer: %s\n", tickets->msgInfo->msgDisplayName);
		printf("----------------------------------------\n");
		printf("1) Add a message\n");
		printf("2) Close ticket\n");
		printf("3) Re-open ticket\n");
		printf("0) Done\n");
		printf("Selection: ");
		selection = getIntFromRange(minNumMenu, maxNumMenu);  // get user Input : Value should be within the range
		putchar('\n');

		switch (selection)
		{
		case 0: break;
		case 1:
			if (tickets->ticketStatus == 0)
				printf("ERROR: Ticket is closed - new messages are not permitted.\n");
			else
			{
				if (tickets->msgCount < maxStoreMsg)
					addMsgAgent(tickets->msgInfo, &tickets->msgCount, accountType, displayName); // Added message from agent
				else
					printf("ERROR: Message limit has been reached, call ITS Support!\n");
			}
			putchar('\n');
			break;
		case 2: 
			if (tickets->ticketStatus == 0)
				printf("ERROR: Ticket is already closed!\n");
			else
			{
				printf("Are you sure you CLOSE this ticket? ([Y]es|[N]o): ");
				if (getCharOption(yesNo) == 'Y') // get user Input : Single character value
				{
					putchar('\n');
					tickets->ticketStatus = 0;		// Change the type for CLOSED
					if (tickets->msgCount != 20)
					{
						printf("Do you want to leave a closing message? ([Y]es|[N]o): ");
						if (getCharOption(yesNo) == 'Y') // get user Input : Single character value
						{
							putchar('\n');
							addMsgAgent(tickets->msgInfo, &tickets->msgCount, accountType, displayName); // Added message from agent
						}
						putchar('\n');
					}
					printf("*** Ticket closed! ***\n");
				}
			}
			putchar('\n');
			break;
		case 3: 
			if (tickets->ticketStatus == 1)
				printf("ERROR: Ticket is already active!\n");
			else
			{
				printf("Are you sure you RE-OPEN this closed ticket? ([Y]es|[N]o): ");
				if (getCharOption(yesNo) == 'Y') // get user Input : Single character value
				{
					putchar('\n');
					tickets->ticketStatus = 1;
					printf("*** Ticket re-opened! ***\n");
				}
			}
			putchar('\n');
			break;
		}
	} while (selection);
}

int loadTickets(struct Ticket tickets[], int arrSize) // Load tickets information from text file
{
	const char filename[] = "tickets.txt";
	int i = 0, j;

	FILE* fp = fopen(filename, "r");

	if (fp != NULL)
	{
		while (i < arrSize && fscanf(fp, "%d|%d|%d|%30[^|]|%d|",
			&tickets[i].ticketNumber, &tickets[i].ticketCustomerAcctNum, &tickets[i].ticketStatus, tickets[i].subjectLine,
			&tickets[i].msgCount) == 5)
		{
			j = 0;
			while (j < tickets[i].msgCount && fscanf(fp, "%c|%30[^|]|%150[^|]|", 
				&tickets[i].msgInfo[j].msgAccountType, tickets[i].msgInfo[j].msgDisplayName,
				tickets[i].msgInfo[j].msgDetail) == 3)
			{
				j++;
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

int appendArcTicketsData(const struct Ticket* tickets, int* ticketCount, int* totalMsgCount) // Append archive ticket data
{
	const char filename[] = "tickets_arc.txt";
	int i, closedTicketCount = 0;

	if (tickets->ticketStatus == 0 && tickets->ticketNumber != 0)
	{
		FILE* fp = fopen(filename, "a");

		if (fp != NULL)
		{
			fprintf(fp, "%d|%d|%d|%s|%d|", tickets->ticketNumber, tickets->ticketCustomerAcctNum, tickets->ticketStatus,
				tickets->subjectLine, tickets->msgCount);
			for (i = 0; i < tickets->msgCount; i++)
			{
				fprintf(fp, "%c|%s|%s|", tickets->msgInfo[i].msgAccountType, tickets->msgInfo[i].msgDisplayName,
					tickets->msgInfo[i].msgDetail);
				(*totalMsgCount)++;
			}
			fprintf(fp, "\n");
			fclose(fp);
			fp = NULL;
			(*ticketCount)++;
			closedTicketCount++;
		}
		else
			printf("ERROR: Unable to open file for appending.\n");
	}

	return closedTicketCount;
}

int storeTickets(struct Ticket tickets[], int arrSize) // Store ticket data
{
	const char filename[] = "tickets.txt";
	int i, j, saveTicketCount = 0;

	FILE* fp = fopen(filename, "w");

	if (fp != NULL)
	{
		for (i = 0; i < arrSize; i++)
		{
			if (tickets[i].ticketNumber != 0)
			{
				fprintf(fp, "%d|%d|%d|%s|%d|", tickets[i].ticketNumber, tickets[i].ticketCustomerAcctNum, tickets[i].ticketStatus,
					tickets[i].subjectLine, tickets[i].msgCount);
				for (j = 0; j < tickets[i].msgCount; j++)
				{
					fprintf(fp, "%c|%s|%s|", tickets[i].msgInfo[j].msgAccountType, tickets[i].msgInfo[j].msgDisplayName,
						tickets[i].msgInfo[j].msgDetail);
				}
				fprintf(fp, "\n");
				saveTicketCount++;
			}
		}
		fclose(fp);
		fp = NULL;
	}
	else
		printf("ERROR: Unable to open file for writing.\n");

	return saveTicketCount;
}