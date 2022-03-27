

/* main program */
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#include "final_atm_utilities.h"
int main()
{
    display();
    
    unsigned long long card_num;
    int cnt = 0, totalRecs = 0, indexOfCard=-1;

    struct cardholderRec cardHolderRecs[100];

    readCSVfile(cardHolderRecs, &totalRecs);
    int pincheck4;
     int pin; 

    // displayCardHolderData(cardHolderRecs, totalRecs);

    cnt = 1;
    
    while (cnt < 4)
    {
        printf("Please enter your card number: ");
        scanf("%lld", &card_num);

        if (checkdigits(card_num) == 1)
        {
            /* valid card number digits (16) */
            indexOfCard = getIndexofCardNumber(cardHolderRecs, card_num, totalRecs);
            if (indexOfCard != -1)
                break;
            else
            {   
                if(cnt == 3)
                {
                    printf("Wrong card no\n");
                    exit(0);
                }
                else
                    printf("wrong card no\n");
                cnt++; 
            }   
        } 
        else
        {
            if(cnt == 3)
            {
                printf("Wrong card no\n");
                exit(0);
            }
            else
            {
                printf("wrong card no\n");
            }
            
            cnt++;

        }
    }
   
    if (cnt < 3)
    {
       
        cnt = 1;
        while (cnt < 4)
        {
            printf("Please enter your PIN number: ");
            scanf("%d", &pin);

            if (checkpin(cardHolderRecs, pin, indexOfCard) == 1)
            {
                //Valid PIN for valid card number  
                printf ("Thanks for validating your PIN\n");
                printf("\n");
                pattern();
                printf("Welcome %s!!! \n", cardHolderRecs[indexOfCard].custName);
                break;
            } 
            else
            {
                // Invalid PIN number
                if(cnt != 3)  
                    printf ("Invalid PIN, Please try again !!!\n");
                else if(cnt == 3)
                {
                    printf ("Invalid PIN...Card blocked!!!\n");
                    exit(0);
                }
                cnt++;
            }
        }
    }
    
    
   
    // Display main menu
    int option = 0;

    do {
        option = atm_menu();
        switch (option)
        {   case 1:
            {
                long int n;char p;
                printf("Please enter your amount in the multiples of 100's or 500's: ");
                scanf("%ld",&n);

                while(n>10000)
                {
                    printf("Please re-enter your amount which should be less than 10000: ");
                    scanf("%ld",&n); 
                }

                while(n%100  !=0)
                {
                    printf("Please re-enter your amount in the multiples of 100's or 500's: ");
                    scanf("%ld",&n);
                }

               // conditions to check whether the withdrawal is feasible
                if (cardHolderRecs[indexOfCard].accbal>n)
                {       
                        
                       if(cardHolderRecs[indexOfCard].accbal-n < 1000)
                        {
                          printf("Minimum balance to be retained in your account is 1000.\nThus transaction cancelled\n");

                        }
                        else
                        {
                            cardHolderRecs[indexOfCard].accbal = cardHolderRecs[indexOfCard].accbal-n;
                            printf("Please collect your cash\n");
                            
                            printf("Do you want to print receipt of your transaction(y/n):");
                            scanf(" %c",&p);
                            if(p=='y' ||p=='Y')
                            { pattern3();
                               printf("\nHello %s !\n", cardHolderRecs[indexOfCard].custName);
                               printf("Your balance before transaction was:Rs.%ld\n",cardHolderRecs[indexOfCard].accbal+n);
                               printf("Amount withdrawn:Rs.%d\n", n);
                               printf("Your present balance is Rs.%ld\n",cardHolderRecs[indexOfCard].accbal);
                               pattern3();
                            }
                         
                             
                        }
                        
                 } 
                 
                //If the user doesnot have sufficient balance
                else if (cardHolderRecs[indexOfCard].accbal <=n)
                {
                printf("Insufficient balance\n");
                }
               
                
               
            }
            break;
                
            case 2:
            {
                long int x;//gets amount to deposit
                char p;
                printf("Enter amount to Deposit in multiples of 100's or 500's: ");
                scanf("%ld",&x);
                
                while(x %100 !=0 )
                {
                    printf("Please re-enter your amount in the multiples of 100's or 500's: ");
                    scanf("%d",&x);
                }

                if(x%100 == 0)
                {
                    cardHolderRecs[indexOfCard].accbal = cardHolderRecs[indexOfCard].accbal + x;
                    printf("\nRs.%ld has been successfully deposited\n", x);
                    printf("Do you want to print receipt of your transaction(y/n):");
                    scanf(" %c",&p);
                    if(p=='y' ||p=='Y')
                    {    pattern3();
                        printf("\nHello %s !\n", cardHolderRecs[indexOfCard].custName);
                        printf("Your balance before transaction was:Rs.%ld\n",cardHolderRecs[indexOfCard].accbal - x);
                        printf("Amount deposited:Rs.%ld\n",x);
                        printf("Your present balance is Rs.%ld\n", cardHolderRecs[indexOfCard].accbal);
                        pattern3();
                    }
                     
                }
                pattern3();
             writeCSVFile(cardHolderRecs, totalRecs);    
            }
            break;
            case 3:
            {   pattern();
                printf("\nYour current account balance is Rs.%d\n",cardHolderRecs[indexOfCard].accbal);
                
            }
            break;
            case 4:
            {
                int newpin;
                int newpincheck;
                printf("Please enter your existing pin number:");
                scanf("%d",&pincheck4);
                if(pincheck4==pin)
                {
                printf("Enter your new pin: ");
                scanf("%d", &newpin);
                printf("Confirm your pin: ");
                scanf("%d", &newpincheck);
                if(newpin != newpincheck)
                {
                    printf("Pins dont match.... Try again\n");
                    break;
                }
                
                else
                {
                    printf("Pin was successfully changed\n");
                    cardHolderRecs[indexOfCard].pin=newpin;
                }
                }
                else
                  printf("Sorry your existing pin was entered wrong\nYour request cannot be completed\n");
               
            }
            break; 
            case 5:
            {
              long int m;char p;
              printf("\nEnter the amount you would like to withdraw from below\n");
              printf("100\t200\t500\t2000\n");
              printf("Rs.");
              scanf("%d",&m);
              if (m==100 ||m==200 ||m ==500 || m==2000)
              {     
                    if(m+1000 <= cardHolderRecs[indexOfCard].accbal)
                    {
                        cardHolderRecs[indexOfCard].accbal = cardHolderRecs[indexOfCard].accbal - m;
                        printf("\nPlease collect your cash\n");
                        pattern3();
                        printf("Do you want to print receipt of your transaction(y/n):");
                        scanf(" %c",&p);
                        if(p=='y' ||p=='Y')
                        { 
                            pattern2();
                            printf("\nHello %s !\n", cardHolderRecs[indexOfCard].custName);
                            printf("Your balance before transaction was:Rs.%ld\n",cardHolderRecs[indexOfCard].accbal + m);
                            printf("Amount withdrawn:Rs.%d\n",m);
                            printf("Your present balance is Rs.%ld\n",cardHolderRecs[indexOfCard].accbal);
                            pattern2();
                        }
                    }
                    else if(cardHolderRecs[indexOfCard].accbal==1000)
                       printf("Minimum balance to be retained in your account is 1000.\nThus transaction cancelled\n");
                    else
                        printf("Insufficient balance\n");
            
              }
               
              else 
              {
                    printf("Valid amount not chosen\n");
              }
              
            }
            break;
             
            case 6:
            {   
                pattern2();
                printf("----------------------->Thank you for using our ATM services<------------------------\n");
                pattern2();
                break;
                exit(0);  // terminates the program
            }
            default:
            {
                printf("\nChoose valid option (1 to 6):\n");
            }
     
  
     }
     writeCSVFile(cardHolderRecs, totalRecs);
    } while (option != 6);
    return 0;
}  // end of main
