#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node *position;  //make memory
typedef position list;     //change name

typedef struct
{
	int account_no;
	int balance;
}customer;          //making customer class

struct node
{
	customer element;         //creating a path to call customer class
	position next;				//creating a path to move next in the memory
};

list MakeEmpty(list L);
void DeleteList(list L);
void insert(list L, position P, int);
list search (list L, int);
void deposit(list L, int, int);
void withdraw(list L, int, int);
void transfer(list L, int, int, int);

list MakeEmpty(list L)										//since it is to return a node that is why we use list
{
	if (L != NULL)
	{
		DeleteList(L);
	}
	L = (list)malloc(sizeof(struct node));
	if (L == NULL)
	{
		printf("Out of space!!");
		exit(-1);
	}
	L->element.account_no = 0;
	L->element.balance = 0;
	//strcpy(L->element.balance, "");
	L->next = NULL;
	return L;
}


void DeleteList(list L)    //we use list as the parameter to assign the data on this function
{
	position P, Tmp;		//position is to assign us on the node

	P = L->next;       //to move our position to the next node on the list
	L->next = NULL;
	while (P != NULL)
	{
		Tmp = P->next;
		//free(P->element.account_no);
		//free(P->element.balance);
		free(P);
		P = Tmp;
	}
	free(L);
}

void insert(list L, position P, int i)          //The P here is same with list. Since list and position is the same thing, just to avoid confusion when we move with the data we use two variable.
{														//Without the list L is also ok
	position TmpCell;
	TmpCell = (position)malloc(sizeof(struct node));
	if (TmpCell == NULL)
	{
		printf("Out of space!!");
		exit(-1);
	}
	
	while (P->next != NULL)
	{
		P=P->next;
	}
	
	TmpCell->element.account_no = i;
	TmpCell->element.balance = 0;
	TmpCell->next = P->next;                          //To assign the the TmpCell->next value ==NULL
	P->next = TmpCell;									//To assign the P->next value with the TmpCell
    P = P->next;										//To let the position P now to the next node
	printf("Account for user %d registered\n",i);
	printf("Balance of user %d: 0\n",i);
    printf("Account for user %d registered\n",P->element.account_no);
    printf("Balance of user %d: %d\n",P->element.account_no, P->element.balance);
}

list search (list L ,int number)
{
	position P=L->next;									//To avoid confusion with the node and data that is why we use P and L. The data in here is the beginning of the data in the list
	while(P!= NULL)
	{
		if (P->element.account_no==number)
		{
			return P;
		}
		P=P->next;
	}
	return NULL;
}

void deposit(list L, int number, int amt)
{
	position P;
	int tmp;
	P= search(L, number);
	if (P==NULL)
	{
		printf("Account does not exist\n");
	}
	else
	{
		tmp = P->element.balance+amt;
		if(tmp<=1000000)
		{
			P->element.balance = tmp;
			//snprintf(P->element.balance, sizeof(8), "%d", tmp);
			printf("Success: Deposit to user %d %d\n",P->element.account_no, amt);
			printf("Balance of user %d: %d\n", P->element.account_no, P->element.balance);
		}
		else
		{
			printf("Failure: Deposit to user %d %d\n",P->element.account_no, amt);
			printf("Balance of user %d: %d\n", P->element.account_no, P->element.balance);
		}
	}
}

void withdraw(list L, int number, int amt)
{
	position P;
	int tmp;
	P = search(L, number);
	if (P==NULL)
	{
		printf("Account does not exist\n");
	}
	else
	{
		tmp = P->element.balance-amt;
		if(tmp>=0)
		{
			P->element.balance = tmp;
			//snprintf(P->element.balance, sizeof(8), "%d", tmp);
			printf("Success: Withdraw to user %d %d\n",P->element.account_no, amt);
			printf("Balance of user %d: %d\n", P->element.account_no, P->element.balance);
		}
		else
		{
			printf("Failure: Withdraw to user %d %d\n",P->element.account_no, amt);
			printf("Balance of user %d: %d\n", P->element.account_no, P->element.balance);
		}
	}
}

void transfer(list L, int number1, int number2, int amt)
{
    position P1,P2;
	int tmp1,tmp2;
	P1 = search(L, number1);
	P2 = search(L, number2);

    if (P1==NULL)
    {
            printf("Failure: Account %d does not exist\n", number1);
    }

	if (P2==NULL)
    {
            printf("Failure: Account %d does not exist\n", number2);
    }
    else
    {
        tmp1 = P1->element.balance-amt;
		tmp2 = P2->element.balance+amt;
        if(tmp1>=0 && tmp2<=1000000)
        {
            P1->element.balance = tmp1;
			P2->element.balance = tmp2;
            printf("Success: Transfer from user %d to %d %d\n",P1->element.account_no, P2->element.account_no, amt);

			if (P1->element.account_no<P2->element.account_no)
            {
				printf("Balance of user %d: %d\n", P1->element.account_no, P1->element.balance);
				printf("Balance of user %d: %d\n", P2->element.account_no, P2->element.balance);
			}

			else
			{
				printf("Balance of user %d: %d\n", P2->element.account_no, P2->element.balance);
				printf("Balance of user %d: %d\n", P1->element.account_no, P1->element.balance);
            }
		}
        else
        {
            printf("Failure: Transfer from user %d to %d %d\n",P1->element.account_no, P2->element.account_no, amt);

			if (P1->element.account_no<P2->element.account_no)
            {
				printf("Balance of user %d: %d\n", P1->element.account_no, P1->element.balance);
				printf("Balance of user %d: %d\n", P2->element.account_no, P2->element.balance);
			}
			else
			{
				printf("Balance of user %d: %d\n", P2->element.account_no, P2->element.balance);
				printf("Balance of user %d: %d\n", P1->element.account_no, P1->element.balance);
            }
        }
	}
}

int main()
{
	list List = NULL;
	//customer Cus;
	//position TmpNode;
	char op;
	int account_no, amount, index =0, gate=1, transferTO;
	List = MakeEmpty(List);
	//Cus.account_no = (char*)malloc(sizeof(char) * 100);
	while(gate==1)
	{	
		printf("\nJob:");
		while ((op = getchar()) != '\n' && op != EOF)
		{
			if (op == 'N')
			{
				if(index<=10)
				{
					insert(List,List, index);
					index+=1;
				}
				else
				{
					printf("Failure: No Extra Space\n");
				}
			}
			
			else if (op=='D')
			{
				scanf("%d %d", &account_no, &amount);
				fflush(stdin);
				deposit(List, account_no, amount);
			}

			else if (op=='W')
			{
				scanf("%d %d", &account_no, &amount);
				fflush(stdin);
				withdraw(List, account_no, amount);
			}

			else if (op=='T')
			{
				scanf("%d %d %d",&account_no,&transferTO, &amount);
				fflush(stdin);
				transfer(List, account_no,transferTO, amount);
			}

			else if (op=='Q')
			{
				gate=2;
			}

			else
			{
				printf("Failure: Wrong Command\n");
			}
		}	
	}
	DeleteList(List);
	return 0;
}
