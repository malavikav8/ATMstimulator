

/* ATM UTILITIES */

#include <stdio.h>
#include <windows.h>

struct cardholderRec
{
    char custName[100];
    unsigned long long cardNo;
    int pin;
    long int accbal;
};

void pattern()
{
    printf("*************************************************************************************\n");
}
void pattern2()
{
    printf("^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n");
}
void pattern3()
{
    printf("_____________________________________________________________________________________\n");
}


void welcomefn()//header for the page
{
    pattern();
    printf("-----------------------------------> WELCOME TO ATM <--------------------------------\n");
    pattern();
}

int checkdigits(unsigned long long num)//checks if card number has 16 digits
{
    int c=0;//counter variable
    int isValid;

    while(num!=0)//counting number of characters in the card number
    {
        c++;
        num=num/10;
    }
    
    if(c==16)
        isValid=1;
    else
        isValid=0;
    
    return isValid;
}

void display()
{
    welcomefn();
    printf("\n");
}

int atm_menu()
{
    int n=0;
    pattern();
    
    printf("\n1.Withdraw\n");
    printf("2.Deposit\n");
    printf("3.Check balance\n");
    printf("4.Change pin\n");
    printf("5.Quick Money\n");
    printf("6.Exit\n ");
    printf("\nPlease select your transaction:");
    scanf("%d",&n);
    Beep(523,200);
    pattern3();
    return n;
}

void getData(char buff[], struct cardholderRec *cardHolder)
{
    // this function will load struct from one record
    char *token = strtok(buff,",");
    int counter=0;
 
    char* endPtr;
    strcpy(cardHolder[0].custName, token);
    token = strtok(NULL,",");
    cardHolder[0].cardNo = strtoull(token, &endPtr, 10);
    token = strtok(NULL,",");
    cardHolder[0].pin = atoi(token);
    token = strtok(NULL,",");
    cardHolder[0].accbal = atoi(token);
}

void readCSVfile(struct cardholderRec *cardHolderRecs, int* totalRecs)
{
    /* read .csv file */

    int count=0;
    char ch;
	FILE *fp = fopen("final_cpro2.csv", "r");
	
    do
	{
	    char buff[1024]={};
	    if (count==0)
            fgets(buff, 1024, fp);
        else
        {
            fgets(&buff[1], 1024, fp);
            buff[0]=ch;
        }

        if (buff != "")
        {
            getData(buff, &cardHolderRecs[count]);
            count++;
        }
        ch = fgetc(fp);
	} while(ch!=EOF);
    *totalRecs = count;
}

void writeCSVFile(struct cardholderRec *cardHolderRecs, int totalRecs)
{
    // will rewrite the CSV at the end
    int count=0;

	FILE *fp = fopen("final_cpro2.csv", "w+");
    do
	{        
	    fprintf(fp, "%s,%lld,%ld,%d\n",cardHolderRecs[count].custName, cardHolderRecs[count].cardNo, cardHolderRecs[count].pin, cardHolderRecs[count].accbal);
        count++;
	} while(count<totalRecs);
    
    fclose(fp);
}


/* void displayCardHolderData(struct cardholderRec *cardHolderRecs, int totalRecs)
{
    for (int i=0; i<totalRecs; i++)
    {
        printf("%s, %lld, %d, %d \n", cardHolderRecs[i].custName, cardHolderRecs[i].cardNo, cardHolderRecs[i].pin, cardHolderRecs[i].accbal);
    }
    
} */


int getIndexofCardNumber(struct cardholderRec *cardHolderRecs, unsigned long long card_num, int totalRecs)
{
    for (int i=0; i<totalRecs; i++)
    {
        if (cardHolderRecs[i].cardNo == card_num)
            return i;
    }
    return -1;
}

int checkpin (struct cardholderRec *cardHolderRecs, int pinNo, int index)
{
    /* check whether pin is valid for the card number */
    
    if (cardHolderRecs[index].pin == pinNo)
        return 1;
    else
        return 0;
}
