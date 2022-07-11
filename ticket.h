/*
	Assignment #2 Milestone #2
	Name   : Kyeongsoo Lee
	ID     : 128720208
	Email  : klee229@myseneca.ca
	Section: NCC
*/
#ifndef TICKET_H_
#define TICKET_H_
#define MAXDISPLAYNAME 30
#define MESSAGELIMIT 150
#define SUBJECTLINELIMIT 30
#define STOREMESSAGE 20

struct Message
{
	char msgAccountType;
	char msgDisplayName[MAXDISPLAYNAME+1];
	char msgDetail[MESSAGELIMIT+1];
};

struct Ticket
{
	int ticketNumber;
	int ticketCustomerAcctNum;
	int ticketStatus;
	char subjectLine[SUBJECTLINELIMIT+1];
	int msgCount;
	struct Message msgInfo[STOREMESSAGE];
};

void getTicket(struct Ticket* tickets, int accountNumber, const char accountType, const char displayName[]);  // get user Input : ticket SUBJECT and message details
void updateTicket(struct Ticket* tickets, int custTicketNum);  // update ticket menu
void addMsgDetail(struct Message msg[], int* msgCount); // Add message detail from customer
void manageTicket(struct Ticket* tickets, const char accountType, const char displayName[]); // Add message, close and re-open ticket
void addMsgAgent(struct Message msg[], int* msgCount, const char accountType, const char displayName[]); // Added message from agent
int loadTickets(struct Ticket tickets[], int arrSize); // Load tickets information from text file
int appendArcTicketsData(const struct Ticket* tickets, int* ticketCount, int* totalMsgCount); // Append archive ticket data
int storeTickets(struct Ticket tickets[], int arrSize); // Store ticket data
#endif // !TICKET_H_