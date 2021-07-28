//#############################################
//		HEADER FILES 
//#############################################
#include<iostream.h>
#include<conio.h>
#include<stdio.h>
#include<fstream.h>
#include<process.h>
#include<math.h>
#include<graphics.h>
//#############################################
//		GLOBAL VARIABLE
//#############################################
int ls;
//#############################################
//		CLASS
//#############################################
class metrod
{
	int stno;
	char sname[30];
	float dist;
	int time;
	public:
	   void insert(int ls)
	   {
		stno=ls;
		clrscr();
		cout<<"\n Your station no."<<stno;
		cout<<"\n Enter the station name:";
		gets(sname);
		cout<<" Enter the distance from previous station:";
		cin>>dist;
		cout<<" Enter the time from previous station:";
		cin>>time;
	   }
	   void insert()
	   {
		cout<<"\n Enter the station no.:";
		cin>>stno;
		cout<<" Enter the station name:";
		gets(sname);
		cout<<" Enter the distance from previous station:";
		cin>>dist;
		cout<<" Enter the time from previous station:";
		cin>>time;
	   }
	   void insert1(int no)
	   {
		stno=no;
		cout<<" Station number:"<<stno<<"\n";
		cout<<" Enter the station name:";
		gets(sname);
		cout<<" Enter the distance from previous station:";
		cin>>dist;
		cout<<" Enter the time from previous station:";
		cin>>time;
	   }

	   void display()
	   {
		cout<<" Station no.:"<<stno;
		cout<<"\n Station name:";
		puts(sname);
		cout<<" Distance from previous station:"<<dist<<" km";
		cout<<"\n Time from previous station:"<<time<<" min"<<endl;
	   }
	   void display2(int co)
	   {
		int j;
		j=co+1;
		gotoxy(2,j);
		cout<<stno<<".";
		gotoxy(10,j);
		cout<<sname;
		gotoxy(27,j);
		cout<<dist<<" km";
		gotoxy(43,j);
		cout<<time<<" min";

	   }
	   int getstno()
	   {
	       return stno;
	   }
	   void changestno(int s)
	   {   if(stno>s)
		  stno=stno-1;
	   }
	   void mname()
	   {
	      puts(sname);
	   }
	   char* tname()
	   {
	      return(sname);
	   }
	   float getdist()
	   {
	      return dist;
	   }
	   int gettime()
	   {
	      return time;
	   }
}m1;
//#############################################
//		INSERT FUNCTION
//#############################################
void insertfile()
{
	textcolor(BLACK);
	textbackground(YELLOW);
	fstream fil;
	int count =0;
	fil.open("distance.dat",ios::binary|ios::in|ios::out);
	while(fil)
	{
		fil.read((char*)&m1, sizeof(m1));
		if(fil.eof())
		break;
		count++;
	}
	ls=count+1;
	 m1.insert(ls);
	 fil.close();
	 fil.open("distance.dat",ios::app|ios::binary);

	 fil.write((char*)&m1,sizeof(m1));
	 fil.close();
}
//#############################################
//		SEARCH FUNCTION
//#############################################
void searchfile(int stnum)
{
	int flag=0;
	ifstream fin;
	fin.open("distance.dat",ios::in|ios::binary);
	while(fin)
	{
		fin.read((char*)&m1,sizeof(m1));
		if(fin.eof())
		   break;
		if(stnum==m1.getstno())
		{
		     m1.display();
		     flag=1;
		}
	}
	fin.close();
	if(flag==0)
	{
	      cout<<"\n Record not found!!!!!!";
	}
	getch();
}
//#############################################
//		DELETE FUNCTION
//#############################################
void deletefile(int s)
{
	char ch;
	ifstream fin;
	ofstream fout;
	fin.open("distance.dat",ios::in|ios::binary);
	fout.open("temp.dat",ios::out|ios::binary);
	while(fin)
	{
	      fin.read((char*)&m1,sizeof(m1));
	      if(fin.eof())
		 break;
	      if(s==m1.getstno())
	      {
		  m1.display();
		  continue;
	      }
	      m1.changestno(s);
	      fout.write((char*)&m1,sizeof(m1));

	}
	cout<<"\n Record successfully deleted.....";
	fin.close();
	fout.close();
	remove("distance.dat");
	rename("temp.dat","distance.dat");
	getch();
}
//#############################################
//		MODIFY FUNCTION
//#############################################
void modifyfile(int no)
{
	char choice;
	fstream fil;
	metrod m2;
	fil.open("distance.dat",ios::in|ios::out|ios::binary);
	while(fil)
	{
	     fil.read((char*)&m1,sizeof(m1));
	     if(fil.eof())
	     {
		cout<<"\n Reached end of file ....";
		getch();
		break;
	     }
	     if(no==m1.getstno())
	     {
		  clrscr();
		  cout<<"\n Record found...\n";
		  m1.display();
		  cout<<"\n Do you want to modify(y/n):";
		  cin>>choice;
		  if(choice=='y'||choice=='Y')
		  {
			 m2.insert1(no);
			 fil.seekp((fil.tellp()-sizeof(m1)),ios::beg);
			 fil.write((char*)&m2,sizeof(m2));
			 cout<<"\n Record successfully modified ....";
			 break;
		  }
		  else
		       break;
	     }
	}
	fil.close();
}
//#############################################
//		TRAVERSE FUNCTION
//#############################################
void transverse()
{
	clrscr();
	textcolor(BLACK);
	int count=0;
	cout<<" S No.\tNAME\t\t DISTANCE\t TIME";
	ifstream fin;
	fin.open("distance.dat",ios::in|ios::binary);
	while(fin)
	{
		fin.read((char*)&m1,sizeof(m1));
		if(fin.eof())
		    break;
		++count;
		m1.display2(count);
		getch();
	}
	if(count==0)
	{
	    clrscr();
	    cout<<"\n EMPTY FILE";
	}
	fin.close();
}
//#############################################
//		TICKET GENERATION
//#############################################
void ticket()
{
	int sp,dt,ns=0,amount=0,tim=0;
	float dis=0,c=0;
	Again:
	clrscr();
	cout<<"\n";
	ifstream inn;
	inn.open("distance.dat",ios::binary|ios::in);
	while(inn)
	{    inn.read((char*)&m1,sizeof(m1));
	     if(inn.eof())
	       break;
	     cout<<" "<<m1.getstno()<<"."<<m1.tname()<<"-->";
	     c++;
	}
	inn.close();
	cout<<"\n Enter the starting point:";
	cin>>sp;
	cout<<" Enter the destination:";
	cin>>dt;
	if(sp==dt||sp>c||dt>c)
	{
	    cout<<" Starting point is same";
	    cout<<" as the destination or ";
	    cout<<" starting point & destination are incorrect.Please enter again.....";
		goto Again;
	}
	clrscr();
	cout<<endl;
	cout<<"\tษออออออออออออออออออออออออออออออออออออออป"<<endl;
	cout<<"\tบ STARTING POINT:                      บ"<<endl;
	cout<<"\tฬออออออออออออออออออออออออออออออออออออออน"<<endl;
	cout<<"\tบ DESTINATION:                         บ"<<endl;
	cout<<"\tฬออออออออออออออออออหอออออออออออออออออออน"<<endl;
	cout<<"\tบ NO.OF STATIONS:  บ AMOUNT:Rs.        บ"<<endl;
	cout<<"\tฬออออออออออออออออออฮอออออออออออออออออออน"<<endl;
	cout<<"\tบ DISTANCE:      Kmบ TIME:      min    บ"<<endl;
	cout<<"\tฬออออออออออออออออออสอออออออออออออออออออน"<<endl;
	cout<<"\tบ    * *     *     *   * *     * *     บ"<<endl;
	cout<<"\tบ    *   *   * * * *   *  *   *        บ"<<endl;
	cout<<"\tบ    *   *   *  *  *   * *    *        บ"<<endl;
	cout<<"\tบ    *   *   *     *   * *    *        บ"<<endl;
	cout<<"\tบ    * *     *     *   *  *    * *     บ"<<endl;
	cout<<"\tศออออออออออออออออออออออออออออออออออออออผ"<<endl;
	ifstream fin;
	fin.open("distance.dat",ios::in|ios::binary);
	while(fin)
	{
		fin.read((char*)&m1,sizeof(m1));
		if(fin.eof())
		   break;
		if(sp==m1.getstno())
		{
		   gotoxy(26,3);
		   m1.mname();
		}

	}
	fin.close();
	fin .open("distance.dat",ios::binary|ios::in);
	while(fin)
	{
		 fin.read((char*)&m1,sizeof(m1));
		if(fin.eof())
		   break;
		if(dt==m1.getstno())
		{
		   gotoxy(23,5);
		   m1.mname();
		}
	}
	fin.close();
	ns=dt-sp;
	gotoxy(26,7);
	cout<<abs(ns);
	amount=8+(2*(abs(ns)-1));
	gotoxy(40,7);
	cout<<amount;
	// distance
	if(sp<dt)
	{
	  fin.open("distance.dat",ios::binary|ios::in);
	  while(fin)
	  {
		fin.read((char*)&m1,sizeof(m1));
		if(fin.eof())
		  break;
		if(sp==m1.getstno())
		{
		    while(fin)
		    {
			fin.read((char*)&m1,sizeof(m1));
			 dis=dis+m1.getdist();
			 tim=tim+m1.gettime();

			 if(dt==m1.getstno())
			      break;
		     }
		}
	  }
	  fin.close();
	}
	if(sp>dt)
	{
	   fin.open("distance.dat",ios::binary|ios::in);
	   while(fin)
	   {
		 fin.read((char*)&m1,sizeof(m1));
		 if(fin.eof())
		    break;
		 if(dt==m1.getstno())
		 {
		    while(fin)
		    {
		       fin.read((char*)&m1,sizeof(m1));
		       dis=dis+m1.getdist();
		       tim=tim+m1.gettime();
		       if((sp)==m1.getstno())
			 break;
		    }
		 }
	   }
	   fin.close();
	}
	gotoxy(20,9);
	cout<<dis;
	gotoxy(35,9);
	cout<<tim;
	getch();
}
//#############################################
//		MAIN FUNCTION
//#############################################
void main()
{
	textcolor(CYAN);
	textbackground(BLACK);
	int choice,ss,ds,ms;
	clrscr();
	for(int i=1;i<=27;i++)
		cout<<" * ";
	cout<<"\n\n\t\t\t DMRC ";
	cout<<"\n\t\t TICKET GENERATION\n\n";
	for(i=1;i<=27;i++)
		cout<<" * ";
	cout<<"\n\n\t MADE BY : KULDEEP SINGH";
	cout<<"\n\t SCHOOL : SRI GURU NANAK PUBLIC SCHOOL";
	getch();
	while(1)
	{
	     textcolor(YELLOW);
	     textbackground(BLUE);
	     clrscr();
	     cout<<"\t\t\t\t ษอออออออออออออป "<<endl;
	     cout<<"\t\t\t\t บ DELHI METRO บ "<<endl;
	     cout<<"\t\t\t\t ศอออออออออออออผ "<<endl;
	     cout<<"  ###### ENTRY/ EDIT MENU ######";
	     cout<<"\n 1.INSERT A STATION";
	     cout<<"\n 2.SEARHING A STATION";
	     cout<<"\n 3.DELETION OF STATION";
	     cout<<"\n 4.MODIFICATION OF STATION";
	     cout<<"\n 5.DISPLAYING ALL STATIONS";
	     cout<<"\n  ##############################\n";
	     cout<<"\n 6.TICKET GENERATION";
	     cout<<"\n 7.EXIT";
	     cout<<"\n ENTER YOUR CHOICE:";
	     cin>>choice;
	     switch(choice)
	     {
		  case 1:insertfile();
			 cout<<"\n Station inserted ....Press any key";
			 getch();
			 break;
		  case 2:clrscr();
			 cout<<"\n\n Enter the station no. for details:";
			 cin>>ss;
			 cout<<"\n";
			 searchfile(ss);
			 break;
		  case 3:clrscr();
			 cout<<"\n Enter the station no.for deletion:";
			 cin>>ds;
			 cout<<"\n";
			 deletefile(ds);
			 break;
		  case 4:clrscr();
			 cout<<"\n Enter the station no. for modification:";
			 cin>>ms;
			 cout<<"\n";
			 modifyfile(ms);
			 getch();
			 break;
		  case 5:transverse();
			 getch();
			 break;
		  case 6:ticket();
			 break;
		  case 7:exit(0);
			 break;
		  default:cout<<"\n INVALID CHOICE";
			  cout<<"\n press any key....:";
			  getch();
	     }
	}

}
//#############################################
//		END OF PROJECT
//#############################################


