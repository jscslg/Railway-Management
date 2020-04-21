#include<conio.h>
#include<iostream.h>
#include<fstream.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
struct passenger
{
	int age;
	char n[32];
};
void tr_details()
{
	char ch[32];
	int i=0;
	ifstream tl;
	clrscr();
	gotoxy(9,3);
	cout<<"Tr no        Tr name     Boarding    Destination    Date     Price";
	tl.open("trlist.txt");
	while(!(tl.eof()))
	{
		tl>>ch;
		gotoxy(10+(12*(i%6)),5+(i/6));
		puts(ch);
		i++;
	}
	tl.close();
	getch();
}
void status()
{
	clrscr();
	int pnr,d[100],a=0,b;
	char c,trn[10],ch1[32],ch2[32],ch3[32],ch4[32],dt[11];
	gotoxy(15,5);
	cout<<"Enter PNR number: ";
	gotoxy(33,5);
	cin>>pnr;
	ifstream tl("trlist.txt");
	ifstream ts2;
	for(int i=0;!(tl.eof());i++)
	{
		tl>>ch1;
		if(i%6==0)
		{
			strcpy(ch3,ch1);
			strcat(ch3,".txt");
			ts2.open(ch3);
			for(int j=0;!(ts2.eof());j++)
			{
				ts2>>ch2;
				if((atoi(ch2)==pnr))
				{
					strcpy(trn,ch1);
					a=j;
					goto br;
				}
			}
			ts2.close();
		}
	}
	br:
	strcpy(ch3,trn);
	strcat(ch3,".txt");
	ifstream out(ch3);
	for(int k=0;k<=(a+5);k++)
	{
		if(k<=a)
			out>>ch4;
		else if(k==(a+1))
		{
			out>>ch4;
			strcpy(dt,ch4);
		}
		else if(k==(a+2))
		{
			out>>ch4;
			b=atoi(ch4);
			gotoxy(15,6);
			cout<<"Date of Travel: ";
			gotoxy(31,6);
			puts(dt);
		}
		else if(k==(a+3))
		{
			for(int m=0;m<(2*b);m++)
			{
				out>>ch4;
				if(m%2==0)
				{
					gotoxy(15,7+(m));
					puts(ch4);
				}
				else if(m%2==1)
				{
					gotoxy(15,7+(m));
					cout<<"Age: ";
					gotoxy(20,7+(m));
					puts(ch4);
				}
			}
		}
		else if(k==(a+4))
		{
			out>>ch4;
			gotoxy(15,7+(2*b));
			cout<<"Price :";
			gotoxy(23,7+(2*b));
			puts(ch4);
		}
	}
	gotoxy(15,9+(2*b));
	cout<<"--------Your Reservation is confirmed--------";
	getch();
}
void addtr()
{
	clrscr();
	char trn[10],trname[32],bdr[32],des[32],dt[11],ch1[32];
	int pr;
	gotoxy(15,4);
	cout<<"Enter the Details as follows- ";
	gotoxy(16,7);
	cout<<"Train Number: ";
	gotoxy(20,8);
	cout<<"Tr no. should be a 3 digit number ";
	gotoxy(16,9);
	cout<<"Train Name: ";
	gotoxy(16,11);
	cout<<"Boarding Point: ";
	gotoxy(16,13);
	cout<<"Destination Point: ";
	gotoxy(16,15);
	cout<<"Date of Travel: ";
	gotoxy(20,16);
	cout<<"Date should be in DD-MM-YYYY format";
	gotoxy(16,17);
	cout<<"Ticket fare: ";
	gotoxy(30,7);
	gets(trn);
	gotoxy(28,9);
	gets(trname);
	gotoxy(32,11);
	gets(bdr);
	gotoxy(35,13);
	gets(des);
	gotoxy(32,15);
	gets(dt);
	gotoxy(29,17);
	cin>>pr;
	ofstream tl;
	tl.open("trlist.txt",ios::app);
	tl<<trn<<" "<<trname<<" "<<bdr<<" "<<des<<" "<<dt<<" "<<pr<<" ";
	tl.close();
	strcpy(ch1,trn);
	strcat(ch1,".txt");
	ofstream tr(ch1);
	tr.close();
	getch();
}
void remtr()
{
	clrscr();
	int a=0;
	char trn[10],ch,ch1[32],ch2[32];
	gotoxy(21,6);
	cout<<"Enter train no.: ";
	gotoxy(37,6);
	gets(trn);
	gotoxy(12,15);
	cout<<"Are you sure you want to remove train(y/n): ";
	gotoxy(57,15);
	cin>>ch;
	if(ch=='y')
	{
		strcpy(ch1,trn);
		strcat(ch1,".txt");
		remove(ch1);
		ifstream tl1("trlist.txt");
		ofstream temp("temp.txt");
		for(int i=0;!(tl1.eof());i++)
		{
			tl1>>ch2;
			if(atoi(ch2)==atoi(trn))
				a=i;
			if(!(i>=a&&i<=(a+5)))
				temp<<ch2<<" ";
		}
		tl1.close();
		temp.close();
		remove("trlist.txt");
		rename("temp.txt","trlist.txt");
	}
	else return;
	getch();
}
void psglist()
{
	char trn[10],ch1[15],ch2[32];
	int a=0,b=0;
	clrscr();
	gotoxy(15,2);
	cout<<"Enter Train Number: ";
	gotoxy(35,2);
	gets(trn);
	gotoxy(15,4);
	cout<<"Passenger name";
	gotoxy(40,4);
	cout<<"Age";
	strcpy(ch1,trn);
	strcat(ch1,".txt");
	ifstream psg(ch1);
	for(int i=0;!(psg.eof());i++)
	{
		if(i==(a+2))
		{
			psg>>ch2;
			b=atoi(ch2);
		}
		else if(i==(a+3))
		{
			for(int j=0;j<(2*b);j++)
			{
			psg>>ch2;
				if(j%2==0)
				{
					gotoxy(15,6+(j/2));
					puts(ch2);
				}
				else if(j%2==1)
				{
					gotoxy(40,6+(j/2));
					puts(ch2);
				}
			}
			a=a+(2*b)+4;
		}
		else
			psg>>ch2;
	}
	psg.close();
	getch();
}
void admin()
{
	char ch;
	int n;
	clrscr();
	gotoxy(16,4);
	cout<<"Are you sure you want to enter admin mode (y/n): ";
	gotoxy(69,4);
	cin>>ch;
	if(ch=='y')
	{
		do
		{
			clrscr();
			gotoxy(21,6);
			cout<<"Select any option: ";
			gotoxy(25,9);
			cout<<"1.Add Train";
			gotoxy(25,11);
			cout<<"2.Remove Train";
			gotoxy(25,13);
			cout<<"3.Passenger List";
			gotoxy(25,15);
			cout<<"4.Go Back";
			gotoxy(40,6);
			cin>>n;
			switch(n)
			{
				case 1:addtr();
				       break;
				case 2:remtr();
				       break;
				case 3:psglist();
				case 4:break;
				default:gotoxy(21,18);
					cout<<"Please select any valid option (1,2,3).\n";
					gotoxy(34,19);
					cout<<"Press any key to continue...";
					getch();
					clrscr();
					break;
			}
		}while(n!=4);
	}
	else return;
}
void reserve();
void cancel();
void enquiry();

void main()
{
	clrscr();
	int ch;
	gotoxy(15,8);
	cout<<"-----------------------------------------------------\n";
	gotoxy(15,10);
	cout<<"***** WELCOME TO THE RAILWAY RESERVATION SYSTEM *****\n";
	gotoxy(15,12);
	cout<<"-----------------------------------------------------\n";
	gotoxy(40,20);
	cout<<"Press any key to continue...";
	getch();
	do{
		clrscr();
		gotoxy(21,6);
		cout<<"Select any option:";
		gotoxy(25,9);
		cout<<"1.Reserve";
		gotoxy(25,11);
		cout<<"2.Cancel";
		gotoxy(25,13);
		cout<<"3.Enquiry";
		gotoxy(25,15);
		cout<<"4.Admin mode";
		gotoxy(25,17);
		cout<<"5.Exit";
		gotoxy(40,6);
		cin>>ch;
		gotoxy(42,6);
		switch(ch)
		{
			case 1:reserve();
			       break;
			case 2:cancel();
			       break;
			case 3:enquiry();
			       break;
			case 4:admin();
			       break;
			case 5:break;
			default:gotoxy(21,18);
				cout<<"Please select any valid option (1,2,3,4,5).\n";
				gotoxy(34,19);
				cout<<"Press any key to continue...";
				getch();
				clrscr();
				break;
		}
	}while(ch!=5);
	getch();
}
void reserve()
{
	passenger res[10];
	int n_seats,pr,tot;
	char trn[10],cl,ch,trname[32],brd[32],des[32],dt[11];
	clrscr();
	gotoxy(15,2);
	cout<<"Enter the Details as follows- ";
	gotoxy(16,5);
	cout<<"Train Number: ";
	gotoxy(16,6);
	cout<<"Train Name: ";
	gotoxy(16,7);
	cout<<"Boarding Point: ";
	gotoxy(16,8);
	cout<<"Destination Point: ";
	gotoxy(16,10);
	cout<<"Enter Class (first class-f,second class-s): ";
	gotoxy(20,9);
	cout<<"Note: 20% extra charge is applied for first-class tickets";
	gotoxy(16,12);
	cout<<"Date of Travel (DD-MM-YYYY): ";
	gotoxy(16,14);
	cout<<"Number of seats required: ";
	gotoxy(30,5);
	gets(trn);
	ifstream tl1;
	int i=0,n=0,a=0,b;
	char ch1[32],ch2[32],ch3[32];
	tl1.open("trlist.txt");
	for(i=0;!(tl1.eof());i++)
	{
		tl1>>ch1;
		if(i%6==0)
		{
			int d=0;
			for(int o=0;o<3;o++)
			{
				if(ch1[o]==trn[o])
					d++;
			}
		if(d==3)
			a=i;
		}
	}
	ifstream tl2;
	tl2.open("trlist.txt");
	for(n=0;!(tl2.eof());n++)
	{
		tl2>>ch2;
		if(n==(a+1))
			strcpy(trname,ch2);
		else if(n==(a+2))
			strcpy(brd,ch2);
		else if(n==(a+3))
			strcpy(des,ch2);
		else if(n==(a+4))
			strcpy(dt,ch2);
		else if(n==(a+5))
			pr=atoi(ch2);
	}
	tl1.close();
	tl2.close();

	gotoxy(28,6);
	puts(trname);
	gotoxy(32,7);
	puts(brd);
	gotoxy(35,8);
	puts(des);
	gotoxy(45,12);
	puts(dt);
	do
	{
		gotoxy(60,10);
		cin>>cl;
		if(cl!='f'&&cl!='s')
		{
			gotoxy(30,11);
			cout<<"Please enter a valid class ('f'or's')";
			gotoxy(60,10);
			cin>>cl;
		}
	}while(cl!='f'&&cl!='s');
	do
	{
		gotoxy(42,14);
		cin>>n_seats;
		if(n_seats>10)
		{
			gotoxy(30,15);
			cout<<"You Cannot reserve more than 10 seats at a time";
			gotoxy(42,14);
			cin>>n_seats;
		}
		else if(!(n_seats<=10&&n_seats>0))
		{
			gotoxy(30,15);
			cout<<"Enter a valid number";
			gotoxy(42,14);
			cin>>n_seats;
		}
	}while(!(n_seats<=10&&n_seats>0));
	for(int m=0;m<n_seats;m++)
	{
		gotoxy(18,16+(2*m));
		cout<<"Passenger name: ";
		gotoxy(18,17+(2*m));
		cout<<"Passenger age: ";
		gotoxy(34,16+(2*m));
		gets(res[m].n);
		gotoxy(33,17+(2*m));
		cin>>res[m].age;
	}
	gotoxy(15,17+(2*n_seats));
	cout<<"Confirm reservation (y/n): ";
	gotoxy(42,17+(2*n_seats));
	cin>>ch;
	if(ch=='y')
	{
		srand(time(0));
		if(cl=='f')
			pr=(pr*6)/5;
		int h=0,pnr;
		gotoxy(15,4);
		pnr=1000+(rand()%1000);
		char fn[15];
		strcpy(fn,trn);
		strcat(fn,".txt");
		ofstream psg(fn,ios::app);
		clrscr();
		psg<<pnr<<" "<<dt<<" "<<n_seats<<" ";
		for(int i=0;i<n_seats;i++)
		{
			psg<<res[i].n<<" "<<res[i].age<<" ";
			gotoxy(15,5+(i)); puts(res[i].n);
			if(res[i].age<=5)
			{
				gotoxy(45,5+(i));
				cout<<"- "<<pr*3/5<<" (Children)";
				h++;
			}
			else if(res[i].age>=60)
			{
				gotoxy(45,5+i);
				cout<<"- "<<pr*3/5<<" (Senior citizen)";
				h++;
			}
			else if(res[i].age<60&&res[i].age>5)
			{
				gotoxy(45,5+(i));
				cout<<"- "<<pr;
			}
		}
		tot = (n_seats*pr)-(h*2*pr/5);
		psg<<tot<<" \n";
		gotoxy(15,5+n_seats);
		cout<<"PNR no. : "<<pnr;
		gotoxy(15,6+n_seats);
		cout<<"Class: "<<cl;
		gotoxy(15,7+n_seats);
		cout<<"Date of Reservation: ";
		gotoxy(35,7+n_seats);
		puts(dt);
		gotoxy(15,9+n_seats);
		cout<<"Total Amount: Rs. "<<tot;
		gotoxy(15,11+n_seats);
		cout<<"--------Your seat(s) is/are reserved--------";
		getch();
		clrscr();
	}
	else
	{
		gotoxy(15,18+2*n_seats);
		cout<<"----------Reservation Cancelled----------";
		getch();
		clrscr();
		return;
	}
}
void cancel()
{
	char ch;
	int pnr,d[100],a=0,b,pr;
	char c,trn[10],ch1[32],ch2[32],ch3[32],ch4[32],dt[11];
	clrscr();
	gotoxy(15,5);
	cout<<"Enter PNR number: ";
	gotoxy(15,6);
	cout<<"Note: 60% of fare will be returned.";
	gotoxy(33,5);
	cin>>pnr;
	ifstream tl("trlist.txt");
	ifstream ts1,ts2;
	for(int i=0;!(tl.eof());i++)
	{
		tl>>ch1;
		if(i%6==0)
		{
			strcpy(ch3,ch1);
			strcat(ch3,".txt");
			ts2.open(ch3);
			for(int j=0;!(ts2.eof());j++)
			{
				ts2>>ch2;
				if((atoi(ch2)==pnr))
				{
					strcpy(trn,ch1);
					a=j;
					goto br;
				}
			}
			ts2.close();
		}
	}
	br:
	strcpy(ch3,trn);
	strcat(ch3,".txt");
	ifstream out(ch3);
	for(int k=0;k<=(a+5);k++)
	{
		if(k<=a)
			out>>ch4;
		else if(k==(a+1))
		{
			out>>ch4;
			strcpy(dt,ch4);
		}
		else if(k==(a+2))
		{
			out>>ch4;
			b=atoi(ch4);
			gotoxy(15,7);
			cout<<"Date of Travel: ";
			gotoxy(31,7);
			puts(dt);
		}
		else if(k==(a+3))
		{
			for(int m=0;m<(2*b);m++)
			{
				out>>ch4;
				if(m%2==0)
				{
					gotoxy(15,8+(m));
					puts(ch4);
				}
				else if(m%2==1)
				{
					gotoxy(15,8+(m));
					cout<<"Age: ";
					gotoxy(20,8+(m));
					puts(ch4);
				}
			}
		}
		else if(k==(a+4))
		{
			out>>ch4;
			gotoxy(15,8+(2*b));
			cout<<"Price :";
			gotoxy(23,8+(2*b));
			puts(ch4);
			pr=atoi(ch4);
		}
	}
	gotoxy(15,24);
	cout<<"Are you sure you want to cancel your reservation(y/n): ";
	gotoxy(70,24);
	cin>>ch;
	if(ch=='y')
	{
		 char ch5[32];
		 gotoxy(15,25);
		 cout<<"Price to be Refunded: ";
		 gotoxy(36,25);
		 cout<<(3*pr)/5;
		 gotoxy(15,26);
		 cout<<"----------Reservation Cancelled----------";
		 getch();
		 ifstream can(ch3);
		 ofstream temp("temp.txt",ios::app);
		 for(int s=0;!(can.eof());s++)
		 {
			can>>ch5;
			if(s<a||s>(a+4+(2*b)))
				temp<<ch5<<" ";
		 }
		 can.close();
		 temp.close();
		 remove(ch3);
		 rename("temp.txt",ch3);
	}
	else return;
}
void enquiry()
{
	int n;
	do
	{
		clrscr();
		gotoxy(21,6);
		cout<<"Select any option:";
		gotoxy(25,9);
		cout<<"1.Train Details";
		gotoxy(25,11);
		cout<<"2.PNR Status";
		gotoxy(25,13);
		cout<<"3.Back to main menu";
		gotoxy(42,6);
		cin>>n;
		switch(n)
		{
			case 1:tr_details();
			       break;
			case 2:status();
			       break;
			case 3:break;
			default:gotoxy(21,18);
				cout<<"Please select any valid option (1,2,3).\n";
				gotoxy(34,19);
				cout<<"Press any key to continue...";
				getch();
				clrscr();
				break;
		}
	}while(n!=3);
}