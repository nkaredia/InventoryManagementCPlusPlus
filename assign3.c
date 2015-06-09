/*
A signed declaration of honesty must be included in your the project.
I declare that the attached assignment is wholly my
own work in accordance with Seneca Academic Policy. No part of this
assignment has been copied manually or electronically from any
other source (including web sites) or distributed to other students.

Name : KAREDIA NOORSIL    
*/



/* NOTE: THIS PROGRAM WAS WRITTEN IN VISUAL STUDIO AND ALSO EDITED IN LINUX CLUSTER.....IF YOU SEE ANY INDENTING STYLE GOT MESSED UP THATS BECAUSE
	 OF THIS.*/
#include<stdio.h>
#include<time.h>
int findupc(int fupc[],int num,int upc);
void writeinvoice(int inquantity[],int Fupc[],int cashid,int num);
void writewarning(int num,int errquantity[],int Fupc[]);
void updateinventory(int FUPC[],char name[][100],int Fquantity[],double Fprice[],int num);

int main(void)
{
	int start,cashid,c=0,z=0,a=0;										//c , z , a , and y are counter variable
	double subtotal=0,tax=0,finaltotal=0;
	int inquantity[1000]={};										//quantity that should be printed in invoice
	int revalue;													// sets the value of SOME VARIABLES back to zero		 
	int FUPC[100],fupc;												//FUPC[] and fupc for storing values after reading from file 
	int Fupc[1000],upc;												//Fupc[] and upc is storing values from the user 
	char name[100][100];											//storing name (read file)
	int Fquantity[100],fquantity;									// storing quantity (read file) 
	double Fprice[100],fprice;										// storing price (read file)
	int searchupc;													// searching upc from FUPC[100]									
	char finalize;													
	int finupc;														//find upc if already exist when user type in the upc
	int errquantity[1000]={};						// this array will decide the ERROR and WARNING that should be printed in warnings.txt
	
	FILE *fp;
	fp = fopen("inventory.txt","r");
	if (fp == NULL)
	{
		printf("No Such File\n");
	}
	else
	{
		while(fscanf(fp,"%d|%[^|]|%d|%lf%*c",&fupc,name[c],&fquantity,&fprice)==4)
		{
			FUPC[c]=fupc;
			Fquantity[c]=fquantity;	
			Fprice[c]=fprice;
			c++;
		}
		fclose(fp);
	}
	printf("Welcome to the Memory Lane inventory system program\n\n");
	printf("Please enter your cashier ID: ");
	scanf("%d",&cashid);
	printf("\n");
	do
	{
		printf("1. Start a new invoice\n");
		printf("0. Quit\n\n");
		printf("Please select what you would like to do: ");
		scanf("%d",&start);
       		printf("\n");		
		if(start == 1)
		{
			do
			{
				do
				{
						printf("Enter UPC (0 to finish): ");
                	    			scanf("%d",&upc);
						if(upc==0)
							break;
						searchupc=findupc(FUPC,c,upc);
						while(searchupc<0)
						{
							printf("INVALID ENTRY\n");
						        printf("Enter UPC (0 to finish): ");
            	 			    		scanf("%d",&upc);
							if(upc==0)
								break;
							searchupc=findupc(FUPC,c,upc);
						}
						finupc=findupc(Fupc,z,upc);
						if(finupc<0)						//this part
						{							//is for storing
							errquantity[a]=Fquantity[searchupc];		//upc and quantity 
							errquantity[a]--;				//that will be
							Fupc[a]=upc;					//printed in INVOICE.TXT
							inquantity[a]++;				// and also
							a++;						//it store upc in errquntity
						}							//that will decide
						else							//to print
						{							//warning or error
							errquantity[finupc]--;				//in the warnings.txt
							inquantity[finupc]++;
						}							
						subtotal=subtotal+Fprice[searchupc];
						tax=subtotal*13/100;
						finaltotal=tax+subtotal;
				
						Fquantity[searchupc]--;
						if(Fquantity[searchupc] < 0)
						{
							Fquantity[searchupc]=0;
						}
						z++;
					}
                			while(upc!=0);
                    			printf("\nSub Total: $%.2lf\n",subtotal);
                    			printf("Tax (13%%): $%.2lf\n",tax );
                    			printf("Final Total: $%.2lf\n\n",finaltotal);
					printf("Finalize the transaction (y/n)? ");
					scanf(" %c", &finalize);
					printf("\n");
			}
			while(finalize == 'n');
			printf("Invoice complete, data updated.\n");
			writewarning(a,errquantity,Fupc);
			writeinvoice(inquantity,Fupc,cashid,a);
			updateinventory(FUPC,name,Fquantity,Fprice,c);
			for(revalue=0;revalue<1000;revalue++)
			{
				errquantity[revalue] = 0;
				inquantity[revalue] = 0;
				Fupc[revalue] = 0;
			}
			subtotal = 0;
			tax = 0;
			finaltotal = 0;
			a = 0;
			z = 0;
        	}
	}
    	while(start != 0 );

	
	printf("Good Bye\n");
	return 0;
}

int findupc(int fupc[],int num,int upc)
{
	int i,track=-1;
	for(i=0;i<=num;i++)
	{
		if(upc == fupc[i])
		{
			track = i;
			i = num;
		}
	}
	return track;
}

void writeinvoice(int inquantity[],int Fupc[],int cashid,int num)
{
	
	int i;
	FILE *fp;
	fp = fopen("invoice.txt","a");
	if (fp == NULL)
	{
		printf("No Such File\n");
	}
	else
	{
		time_t tim;
		struct tm * time1;
		char tym [80];

		time (&tim);
	    	time1 = localtime (&tim);
		fprintf(fp,"%00004d|",cashid);								// %0004d also prints number starting from 0
		strftime (tym,80,"%H:%M:%S|%m/%d/%Y\n",time1);
		fputs(tym,fp);
		for(i=0;i<num;i++)
		{
			fprintf(fp,"%00000008d|%d\n",Fupc[i],inquantity[i]);                          // %000000008d is for printing any integer that starts with 0
		}
		printf("\n");
	}
	fclose(fp);
}

void updateinventory(int Fupc[],char name[][100],int Fquantity[],double Fprice[],int num)
{
	int i;
	FILE *fp;
	fp = fopen("inventory.txt","w");
	if (fp == NULL)
	{
		printf("No Such File\n");
	}
	else
	{
		for(i=0;i<num;i++)
		{
			fprintf(fp,"%00000008d|%s|%d|%.2lf\n",Fupc[i],name[i],Fquantity[i],Fprice[i]);
		}
	}
	fclose(fp);
}

void writewarning(int num,int errquantity[],int Fupc[])
{
	int i;
	FILE *fp;
	fp=fopen("warnings.txt","a");
	if (fp==NULL)
	{
		printf("No Such File\n");
	}
	else
	{
		for(i=0;i<num;i++)
		{
			if(errquantity[i] == 0)
			{
				fprintf(fp,"Warning: %000000008d has run out of stock\n",Fupc[i]);
			}
			else if(errquantity[i] < 0)
			{
				fprintf(fp,"Error: %000000008d stock was in error, attempted to drop below zero\n",Fupc[i]);
			}
		}
	}					
	fclose(fp);
}


