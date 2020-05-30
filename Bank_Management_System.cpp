//                   BANK MANAGEMENT SYSTEM
//                   BY: ANKAN NATH

#include<iostream.h>      //For cout cin.
#include<conio.h>         //For getch().
#include<fstream.h>       //For file handling.
#include<string.h>        //For string functions.
#include<iomanip.h>       //For setw().
#include<process.h>       //For exit().
#include<stdio.h>

//using namespace std;  (Optional)


//*******************************************************
//*             CLASS USED IN PROGRAM
//*******************************************************


class Account
{ int accno;
  char name[30];
  char DOB[12];
  long int Phone;
  int amt;

public:

    void create_Account()
    {
	cout<<"\n\t\tNEW ACCOUNT ENTRY";
	cout<<"\nENTER THE NAME: ";
	gets(name);
	cout<<"\nENTER THE DOB(dd.mm.yyyy): ";
	gets(DOB);
	cout<<"\nENTER THE PHONE NUMBER: ";
	cin>>Phone;
	cout<<"\nENTER THE BALANCE: ";
	cin>>amt;
	cout<<"\nPROVIDE AN ACCOUNT NUMBER FOR THE CUSTOMER: ";
	cin>>accno;
	cout<<"\n Account successfully created...";
    }

    void Modify_Account()
    {
	cout<<"\n\nACCOUNT NUMBER: "<<accno;
	cout<<"\nENTER THE NEW NAME: ";
	gets(name);
	cout<<"\nENTER THE NEW DOB(dd.mm.yyyy): ";
	gets(DOB);
	cout<<"\nENTER THE NEW PHONE NUMBER: ";
	cin>>Phone;
    }

    void View_Account()
    {
	cout<<"\nAccount number: "<<accno;
	cout<<"\nName: ";
	puts(name);
	cout<<"\nDOB: ";
	puts(DOB);
	cout<<"\nPhone Number: "<<Phone;
	cout<<"\nAccount Balance: "<<amt;
    }

    int getaccno()
    {
	return accno;
    }

    void creamt(int n)
    {
	 amt+=n;
    }

    void debamt(int n)
    {
	amt-=n;
    }

    int getamt()
    {
	return amt;
    }

    void report()
    {
	cout<<"  "<<accno<<"\t      "<<name<<"    "<<DOB<<"\t   "<<Phone<<"\t\t"<<amt<<"\n";
    }


};      // Class ends here.

class Transaction
{  char operation[50];
   int debitcredit;
   int stepamt;
   int dupaccno;

public:

    void stepamtis(int k)
    {
	stepamt=k;
    }

    void cr()
    {
	strcpy(operation,"CREDIT");
    }

    void dr()
    {
	strcpy(operation,"DEBIT");
    }

    int getdebitcredit()
    {
	cin>>debitcredit;
	return debitcredit;
    }

    int getdebitcredit1()
    {
	return debitcredit;
    }

    void stepcredit(int n)
    {
	stepamt+=n;
    }

    void stepdebit(int n)
    {
	stepamt-=n;
    }

    void reAccount(int m)
    {
	dupaccno=m;
    }

    int gettaccno()
    {
	return dupaccno;
    }

    void report()
    {
	cout<<"  "<<dupaccno<<"\t\t "<<operation<<"\t\t  "<<debitcredit<<"\t\t "<<stepamt<<"\n";
    }
};      // Class ends here.



//*******************************************************************
//                     GLOBAL VARIABLE DECLARATION
//********************************************************************

Account ac;
Transaction ts;
fstream f,fp;

//*******************************************
//        Function to add details
//*******************************************

void add_DETAILS()
{
    char ch;
    clrscr();
     f.open("Account.dat",ios::out|ios::app);
    do
    {
	clrscr();
	ac.create_Account();
	f.write((char*)&ac,sizeof(Account));
	cout<<"\nDo you want to continue (y/n)?: ";
	cin>>ch;
    }while(ch=='y' || ch=='Y');
    f.close();
}

//************************************************
//       Function for viewing all details
//************************************************

void view_all()
{
    clrscr();
    f.open("Account.dat",ios::in);
	if(!f)
	{
		cout<<"ERROR!!! File could not be found... ";
		getch();
		return;
	}

	cout<<"\n\n\t\t\tCUSTOMER DETAILS\n\n";
	cout<<"===============================================================\n";
	cout<<" Account No.     Name          DOB       Phone No.     Amount"<<"\n";
	cout<<"===============================================================\n";

	while(f.read((char*)&ac,sizeof(Account)))
	{
		ac.report();
	}

	f.close();
	getch();

}

//*************************************************
//     Function for showing specific details
//*************************************************

void show_customer(int n)
{
    clrscr();
    int flag=0;
    f.open("Account.dat",ios::in);
    if(!f)
    {
	    cout<<"ERROR!!! File could not be open... ";
		getch();
		return;
    }
    while(f.read((char*)&ac,sizeof(Account)))
    {
	     if(n==ac.getaccno())
	        {
	            ac.View_Account();
	            flag=1;
            }
    }
    if(flag==0)
    {
	     cout<<"\nAccount does not exits...";

    }
    f.close();
    getch();
}


//*****************************************
//      Function to modify details
//*****************************************

void modify_DETAILS()
{
   char ch;
   int acno, found=0,pos;
   clrscr();
   cout<<"\n\t\tMODIFY ACCOUNT DETAILS";
   cout<<"\n\nENTER THE ACCOUNT NUMBER: ";
   cin>>acno;
   f.open("Account.dat",ios::in|ios::out);
   while(f.read((char*)&ac,sizeof(Account)) && found==0)
    {
		if(ac.getaccno()==acno)
		{
		    clrscr();
			cout<<"\n\t\tENTER THE NEW DETAILS OF THE CUSTOMER"<<endl;
			ac.Modify_Account();
			 pos=(-1)*sizeof(Account);
			f.seekp(pos,ios::cur);
			f.write((char*)&ac,sizeof(Account));
			cout<<"\n Details Updated...";
			found=1;
		}
	}

	if(found==0)
		{cout<<"\n Details Not Found... ";}
	f.close();
	getch();
}


//**************************************************
//       Function for deletion of Details
//**************************************************

void delete_trans(int n)
{
	fp.open("trans.dat",ios::in|ios::out);
	fstream fp3;
	fp3.open("Temp1.dat",ios::out);
	fp.seekg(0,ios::beg);
	while(fp.read((char*)&ts,sizeof(Transaction)))
	{
		if(ts.gettaccno()!=n)
			{fp3.write((char*)&ts,sizeof(Transaction));}
	}

	fp3.close();
    fp.close();
    remove("trans.dat");
    rename("Temp1.dat","trans.dat");

}

void delete_DETAILS()
{
	int n;
	int flag=0;
	clrscr();
	cout<<"\nDELETE DETAILS";
	cout<<"\n\nEnter the Account number you want to delete: ";
	cin>>n;
	f.open("Account.dat",ios::in|ios::out);
	fstream fp2;
	fp2.open("Temp.dat",ios::out);
	f.seekg(0,ios::beg);
	while(f.read((char*)&ac,sizeof(Account)))
	{
		if(ac.getaccno()!=n)
			{fp2.write((char*)&ac,sizeof(Account));}
		else
			{flag=1;}
	}

	fp2.close();
	f.close();
	remove("Account.dat");
	rename("Temp.dat","Account.dat");
	delete_trans(n);
	if(flag==1)
		cout<<"\nDetails Deleted...";
	else
		cout<<"\nDetails not found...";
	getch();
}

//*********************************************
//       Function for credit of amount
//*********************************************

void credit_amt(int n)
{
    clrscr();
    int pos;
    f.open("Account.dat",ios::in|ios::out);
    fp.open("trans.dat",ios::out|ios::app);
    f.seekg(0,ios::beg);
    while(f.read((char*)&ac,sizeof(Account)))
    {
	    if(ac.getaccno()==n)
	         {

	                  ts.reAccount(n);
	                  ts.stepamtis(ac.getamt());
	                  cout<<"\nEnter the amount to be credited: ";
	                  ac.creamt(ts.getdebitcredit());
	                  ts.stepcredit(ts.getdebitcredit1());
	                  ts.cr();
	                  fp.write((char*)&ts,sizeof(Transaction));
                      pos=-1*sizeof(Account);
	                  f.seekp(pos,ios::cur);
	                  f.write((char*)&ac,sizeof(Account));
	                  cout<<"\nTransaction successful...";
            }
    }
    f.close();
    fp.close();
    getch();
}

//************************************************
//         Function for debit of amount
//************************************************
void debit_amt(int n)
{
    clrscr();
    int pos;
    f.open("Account.dat",ios::in|ios::out);
    fp.open("trans.dat",ios::out|ios::app);
    f.seekg(0,ios::beg);
    while(f.read((char*)&ac,sizeof(Account)))
    {
	      if(ac.getaccno()==n)
	        {
	            if(ac.getamt()<1000)
	             {
                       cout<<"\nInsufficient balance...";
	             }
	            else
                    {

	                      ts.reAccount(n);
	                      ts.stepamtis(ac.getamt());
	                      cout<<"\nEnter the amount to be debited: ";
	                      ac.debamt(ts.getdebitcredit());
	                      ts.stepdebit(ts.getdebitcredit1());
	                      ts.dr();
	                      fp.write((char*)&ts,sizeof(Transaction));
	                      pos=-1*sizeof(Account);
                          f.seekp(pos,ios::cur);
	                      f.write((char*)&ac,sizeof(Account));
	                      cout<<"\nTransaction successful...";
                    }
            }
    }
    f.close();
    fp.close();
    getch();
}

//****************************************************
//         Function for viewing transaction
//****************************************************

void view_transall()
{
    clrscr();
    fp.open("trans.dat",ios::in);
    fp.seekg(0,ios::beg);
    if(!fp)
    {
	     cout<<"\nFile not found...";
    }
    cout<<"\n\n\t\tTRANSACTION DETAILS\n\n";
	cout<<"=======================================================\n";
	cout<<" Account No.\tOperation\tCR/DR Amt\tAmount"<<"\n";
	cout<<"=======================================================\n";
	while(fp.read((char*)&ts,sizeof(Transaction)))
    {
         ts.report();
    }
    fp.close();
    getch();
}

//****************************************************************
//         Function for viewing a specific transaction
//****************************************************************

void view_specifictrans(int n)
{
    clrscr();
    fp.open("trans.dat",ios::in);
    fp.seekg(0,ios::beg);
    if(!fp)
    {
	    cout<<"\nFile not found...";
    }
    cout<<"\n\n\t\tTRANSACTION DETAILS\n\n";
	cout<<"=======================================================\n";
	cout<<" Account No.\tOperation\tCR/DR Amt\tAmount"<<"\n";
	cout<<"=======================================================\n";
	while(fp.read((char*)&ts,sizeof(Transaction)))
    {
	    if(n==ts.gettaccno())
	         {ts.report();}
    }
    fp.close();
    getch();
}

//*************************************************
//        Function for Administrator menu
//*************************************************

void adminmenu()
{
    clrscr();
    int num;
	int ch2;
	while(1){
    clrscr();
	cout<<"\n\n\n\t\t\tADMINISTRATOR MENU";
	cout<<"\n\n\t1.CREATE NEW ACCOUNT";
	cout<<"\n\n\t2.DISPLAY ALL ACCOUNTS DETAILS";
	cout<<"\n\n\t3.DISPLAY SPECIFIC ACCOUNT DETAILS ";
	cout<<"\n\n\t4.MODIFY ACCOUNT DETAILS";
	cout<<"\n\n\t5.DELETE ACCOUNT";
	cout<<"\n\n\t6.VIEW ALL TRANSACTIONS";
	cout<<"\n\n\t7.VIEW SPECIFIC TRANSACTIONS";
	cout<<"\n\n\t8.BACK TO MAIN MENU";
	cout<<"\n\n\tPlease Enter Your Choice (1-8): ";
	ch2=getche();
	switch(ch2)
	{
		case '1':clrscr();add_DETAILS();break;
		case '2':clrscr();view_all();break;
		case '3':clrscr();
			     cout<<"\n\n\tPlease Enter The Account No.: ";
			     cin>>num;
			     show_customer(num);
			     break;
		case '4':clrscr(); modify_DETAILS();break;
		case '5':clrscr();delete_DETAILS();break;
	    case '6':clrscr();view_transall();break;
	    case '7':clrscr();
			     cout<<"\n\n\tEnter The Account No.: ";
			     cin>>num;
			     view_specifictrans(num);
			     break;
        case '8':return;
        default:cout<<"\nWrong choice...";
			    break;
	}
}

}

//*****************************************
//      Function for Customer menu
//*****************************************

void customermenu(int n)
{
    clrscr();
    char ch;
    while(1){
	    clrscr();
		cout<<"\n\n\n\t\t\tCUSTOMER MENU";
		cout<<"\n\n\t01. VIEW ACCOUNT DETAILS";
		cout<<"\n\n\t02. CREDIT";
		cout<<"\n\n\t03. DEBIT";
		cout<<"\n\n\t04. VIEW TRANSACTION DETAILS";
		cout<<"\n\n\t05. RETURN TO MAIN MENU";
		cout<<"\n\n\tPlease Select Your Option (1-5): ";
		ch=getche();
		switch(ch)
		{
		    case '1':clrscr();show_customer(n);break;
		    case '2':clrscr();credit_amt(n);break;
		    case '3':clrscr();debit_amt(n);break;
		    case '4':clrscr();view_specifictrans(n);break;
		    case '5':return;
		    default:cout<<"\nWrong choice";break;
		}
    }
}

//**************************************
//     	INTRODUCTION FUNCTION
//**************************************

void intro()
{
	clrscr();
	gotoxy(25,10);
	cout<<"BANK  MANAGEMENT SYSTEM";
	gotoxy(35,14);
	cout<<"\n\nMADE BY : ANKAN NATH";
	cout<<"\n\nCOLLEGE : TECHNO MAIN SALT LAKE";
	cout<<"\n\nDEPARTMENT : ELECTRONICS AND COMMUNICATION ENGINEERING";
	getch();
}


//********************************************
//      Function for Main menu
//********************************************

void mainmenu()
{
    char ch;
    int num,flag=0;
	while(1)
	{
		clrscr();
		cout<<"\n\n\n\t\t\tMAIN MENU";
		cout<<"\n\n\t01. ADMIN MENU";
		cout<<"\n\n\t02. CUSTOMER MENU";
		cout<<"\n\n\t03. EXIT";
		cout<<"\n\n\tPlease Select Your Option (1-3): ";
		ch=getche();
		switch(ch)
		{
			case '1':clrscr();adminmenu();break;
			case '2':clrscr();
			         cout<<"\nEnter your Account no.: ";
			         cin>>num;
			         f.open("Account.dat",ios::in);
			         f.seekg(0,ios::beg);
			         while(f.read((char*)&ac,sizeof(Account)))
	                      {
		                      if(num==ac.getaccno())
		                           {
		                                flag=1;
		                                break;
                                   }
	                      }
	                 if(flag==0)
	                      {
		                       f.close();
		                       cout<<"\nAccount doesn't exit...";
		                       getch();
	                      }
	                 else
                          {
                               f.close();
                               customermenu(num);
                          }
	                 break;
			case '3':exit(0);break;
			default :cout<<"\a";
		}
	}
}


//**********************************************
//       Main function of the program
//**********************************************

 void main()
 {
    intro();
    mainmenu();
    getch();
 }

//                            **************************************
//                                        END OF PROJECT
//                            **************************************
