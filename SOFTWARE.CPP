/*A CPP Program to demonstrate a copy trading management system*/
#include<stdio.h>
#include<iostream.h>
#include<conio.h>
#include<fstream.h>
#include<iomanip.h>
#include<ctype.h>
class acc
{
 int ano;
 char name[100];
 int dep;
 char type;
 char size;
public:
     void create_acc();
     void show_acc() const;
     void modify();
     void adep(int);
     void draw(int);
     void report() const;
     int retano() const;
     int retdep() const;
     char qtype() const;
};
 void acc::create_acc()
 {
  cout<<"\nENTER THE COPY NUMBER:";
  cin>>ano;
  cout<<"\n\nENTER NAME OF THE COPY:";
  cin.ignore();
  cin.getline(name,100);
  cout<<"\nENTER TYPE OF COPY(Ruled(r)/White(w)/Math(m)/English(e)/science(s)):";
  cin>>type;
  cout<<"\nENTER THE SIZE OF COPY(Very Long(v)/Long(l)/Medium(m)/Short(s))";
  cin>>size;
  cout<<"\nENTER THE INITIAL NUMBER OF COPIES:";
  cin>>dep;
  cout<<"\n\n\nCONGRATS ACCOUNT HAS BEEN CREATED:";
 }
 void acc::show_acc() const
 {
  cout<<"\nCOPY NUMBER:"<<ano;
  cout<<"\nCOPY COMPANY:";
  cout<<name;
  cout<<"\nTYPE OF COPY:"<<type;
  cout<<"\nSIZE OF COPY:"<<size;
  cout<<"\nNUMBER OF COPIES:"<<dep;
 }
  void acc::modify()
  {
   cout<<"\nCOPY NUMBER:"<<ano;
   cout<<"\nMODIFY COPY NAME:";
   cin.ignore();
   cin.getline(name,100);
   cout<<"\nMODIFY TYPE OF COPY:";
   cin>>type;
   cout<<"\nMODIFY SIZE OF COPY:";
   cin>>size;
   cout<<"\nMODIFY NUMBER OF COPIES:";
   cin>>dep;
  }
  void acc::adep(int x)
  {
   dep+=x;
  }
  void acc::draw(int x)
  {
   dep-=x;
  }
  void acc::report() const
  {
   cout<<"                   "<<ano<<setw(10)<<" "" "<<name<<setw(10)<<" "" "<<type<<setw(6)<<" "<<size<<setw(12)<<""<< dep<<endl;
  }
  int acc::retano() const
  {
   return ano;
  }
  int acc::retdep() const
  {
   return dep;
  }
  char acc::qtype() const
  {
   return type;
  }
  void write_acc();
  void display_sp(int);
  void modify_acc(int);
  void delete_acc(int);
  void display_all();
  void dep_withdraw(int,int);
  void intro();
  int main()
  {
   char ch;
   int num;
   clrscr();
   intro();
   do
   {
     clrscr();
     cout<<"\n\n\n\tACTION MENU";
     cout<<"\n\n\t01. NEW ACCOUNT";
     cout<<"\n\n\t02. ADD COPIES";
     cout<<"\n\n\t03. WITHDRAW";
     cout<<"\n\n\t04. ENQUIRY";
     cout<<"\n\n\t05. COMPLETE ENQUIRY";
     cout<<"\n\n\t06. CLOSE AN ACCOUNT";
     cout<<"\n\n\t07. MODIFY AN ACCOUNT";
     cout<<"\n\n\t08. EXIT";
     cout<<"\n\n\tSelect Your Option(1-8)";
     cin>>ch;
     clrscr();
     switch(ch)
     {
      case'1':
	    write_acc();
	    break;
      case'2':
	     cout<<"\n\n\tENTER THE COPY NUMBER:";cin>>num;
	     dep_withdraw(num,1);
	     break;
      case'3':
	     cout<<"\n\n\tENTER THE COPY NUMBER:";cin>>num;
	     dep_withdraw(num,2);
	     break;
      case'4':
	     cout<<"\n\n\tENTER THE COPY NUMBER:";cin>>num;
	     display_sp(num);
	     break;
      case'5':
	     display_all();
	     break;
      case'6':
	     cout<<"\n\n\tENTER THE COPY NUMBER:";cin>>num;
	     delete_acc(num);
	     break;
     case'7':
	    cout<<"\n\n\tENTER THE COPY NUMBER:";cin>>num;
	    modify_acc(num);
	    break;
     case'8':
	    cout<<"\n\n\tTHANKS FOR VISITING OUR SOFTWARE!";
	    break;
	    default: cout<<"\a";
    }
    cin.ignore();
    cin.get();
   }
   while(ch!='8');
   return 0;
 }
 void write_acc()
 {
  acc ac;
  ofstream x;
  x.open("info.dat",ios::binary|ios::app);
  ac.create_acc();
  x.write((char *) &ac, sizeof(acc));
  x.close();
 }
 void display_sp(int n)
 {
  acc ac;
  int flag=0;
  ifstream x;
  x.open("info.dat",ios::binary);
  if(!x)
  {

  cout<<"File Could Not Be Opened!! Press Any Key To Exist.......";
  return;
  }
  cout<<"\nBALANCE DETAILS\n";
  while(x.read((char *) (&ac), sizeof(acc)))
  {
   if (ac.retano()==n)
   {
    ac.show_acc();
    flag=1;
   }
  }
  x.close();
  if(flag==0)
  cout<<"\n\nAccount Number does not Exists";
 }
 void modify_acc(int n)
 {
  int found=0;
  acc ac;
  fstream x;
  x.open("info.dat",ios::binary|ios::in|ios::out);
  if(!x)
  {
   cout<<"File could not be open!! Press any key.......";
   return;
  }
   while(!x.eof()&&found==0)
   {
    x.read((char *)(&ac), sizeof(acc));
    if(ac.retano()==n)
    {
     ac.show_acc();
     cout<<"\n\nENTER THE NEW DETAILS OF THE ACCOUNT"<<endl;
     ac.modify();
     int pos=(-1)* sizeof(acc);
     x.seekp(pos,ios::cur);
     x.write((char *) &ac, sizeof(acc));
     cout<<"\n\n\tRECORD UPDATED";
     found=1;
    }
    x.close();
    if(found==0)
    cout<<"\n\nRECORD NOT FOUND";
   }
  }
   void delete_acc(int n)
   {
    acc ac;
    ifstream x;
    ofstream y;
    x.open("info.dat",ios::binary);
    if(!x)
    {
     cout<<"File could not be open!! Press any key.....";
    }
    y.open("temp.dat",ios::binary);
    x.seekg(0,ios::beg);
    while(x.read((char *)(&ac),sizeof(acc)))
    {
     if(ac.retano()!=n)
     {
      y.write((char *)(&ac),sizeof(acc));
     }
    }
    x.close();
    y.close();
    remove("info.dat");
    rename("temp.dat","info.dat");
    cout<<"\n\n\tRECORD DELETED.....";
   }
   void display_all()
   {
    acc ac;
    ifstream x;
    x.open("info.dat",ios::binary);
    if(!x)
    {
     cout<<"File could not be open!! Press any key.......";
     return;
   }
   cout<<"\n\n\t\t                     FULL ACCOUNT LIST\n\n";
   cout<<"             ==============================================================\n";
   cout<<"              COPY NO.         NAME           TYPE       SIZE       QUANTITY \n";
   cout<<"             ==============================================================\n";
   while(x.read((char *)(&ac),sizeof(acc)))
   {
    ac.report();
   }
  }
  void dep_withdraw(int n,int option)
  {
   int amt;
   int found=0;
   acc ac;
   fstream x;
   x.open("info.dat",ios::binary|ios::in|ios::out);
   if(!x)
   {
    cout<<"File could not be open!! Press any key.......";
    return;
   }
   while(!x. eof() &&found==0)
   {
    x.read((char *)(&ac),sizeof(acc));
    if(ac.retano()==n)
    {
     ac.show_acc();
     if(option==1)
     {
      cout<<"\n\n\tTo add Quantity";
      cout<<"\n\nEnter the Quantity to be added";
      cin>>amt;
      ac.adep(amt);
     }
     if(option==2)
     {
      cout<<"\n\n\tTo withdraw Quantity";
      cout<<"\n\nEnter The Quantity To Withdraw";
      cin>>amt;
      int bal=ac.retdep()-amt;
      if((bal<1&&ac.qtype()=='r') || (bal<1&&ac.qtype()=='w') || (bal<1&&ac.qtype()=='m') || (bal<1&&ac.qtype()=='e') || (bal<1&&ac.qtype()=='s'))
      cout<<"Insufficient Balance";
      else
       ac.draw(amt);
     }
      int pos=(-1)* (sizeof(ac));
      x.seekp(pos,ios::cur);
      x.write((char *) &ac,sizeof(acc));
      cout<<"\n\n\tRECORD UPDATED";
      found=1;
    }
  }
  x.close();
  if(found==0)
  cout<<"\n\nRecord not Found";
 }
 void intro()
 {
  textcolor(14);gotoxy(24,30);
  cout<<"\n\n\n\tWELCOME TO CHOWDHURY COPY MANAGEMENT SYSTEM";gotoxy(26,32);
  cout<<"\n\nA C++ CODE BY SUPRIYO CHOWDHURY";
  cout<<"\nPRESS ENTER TO CONTINUE........";
  cin.get();
 }
