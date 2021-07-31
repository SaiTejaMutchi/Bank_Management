#include<iostream>
#include<fstream>
#include<bits/stdc++.h>
using namespace std;

class bank_account {
	int ac_num;
	char name[50];
	int deposit;
	char type;
	public:
		void show_account() const;	//function to show data on screen
	void modify();	//function to add new data
	void dep(int);	//function to accept amount and add to balance amount
	void draw(int);	//function to accept amount and subtract from balance amount
	void report() const;	//function to show data in tabular format
	int retacno() const;	//function to return account number
	int retdeposit() const;	//function to return balance amount
	char rettype() const;	//function to return type of account
		void create_account(){
	
	cout<<"\nEnter The account No. : ";
	cin>>ac_num;
	cout<<"\n\nEnter The Name of The account Holder : ";
	cin.ignore();
	cin.getline(name,50);
	cout<<"\nEnter Type of The account (C/S) : ";
	cin>>type;
	type=toupper(type);
	cout<<"\nEnter The Initial amount : ";
	cin>>deposit;
	cout<<"\n\n\nAccount Created..";
	
			
		}
		
};

void bank_account::show_account() const
{
	cout<<"\nAccount No. : "<<ac_num;
	cout<<"\nAccount Holder Name : ";
	cout<<name;
	cout<<"\nType of Account : "<<type;
	cout<<"\nBalance amount : "<<deposit;
}


void bank_account::modify()
{
	cout<<"\nAccount No. : "<<ac_num;
	cout<<"\nModify Account Holder Name : ";
	cin.ignore();
	cin.getline(name,50);
	cout<<"\nModify Type of Account : ";
	cin>>type;
	type=toupper(type);
	cout<<"\nModify Balance amount : ";
	cin>>deposit;
}


void bank_account::dep(int x)
{
	deposit+=x;
}

void bank_account::draw(int x)
{
	deposit-=x;
}

void bank_account::report() const
{
	cout<<ac_num<<setw(10)<<" "<<name<<setw(10)<<" "<<type<<setw(6)<<deposit<<endl;
}

int bank_account::retacno() const
{
	return ac_num;
}

int bank_account::retdeposit() const
{
	return deposit;
}

char bank_account::rettype() const
{
	return type;
}

//case1 
void create_account(){
	bank_account ac;
	ofstream out;
	out.open("account.dat",ios::binary|ios::app);
	ac.create_account();
	out.write(reinterpret_cast<char *> (&ac), sizeof(bank_account));
	out.close();
}
//case 2 and 3
void deposit(int n, int option){
	int amt;
	bool found = false;
	bank_account ac;
	fstream File;
	File.open("account.dat", ios::binary|ios::in|ios::out);
	
	// No bank accounts file found. 
	if(!File)
	{
		cout<<"Data File could not be open !! Press any Key...";
		return;
	}
	//file found and running through the file
	while(!File.eof() && found==false)
	{
		File.read(reinterpret_cast<char *> (&ac), sizeof(bank_account));
		if(ac.retacno()==n)
		{
			ac.show_account();
			if(option==1)
			{
				cout<<"\n\n\tTO DEPOSITE AMOUNT ";
				cout<<"\n\nEnter The amount to be deposited";
				cin>>amt;
				ac.dep(amt);
			}
		    if(option==2)
			{
				cout<<"\n\n\tTO WITHDRAW AMOUNT ";
				cout<<"\n\nEnter The amount to be withdraw";
				cin>>amt;
				int bal=ac.retdeposit()-amt;
				if((bal<500 && ac.rettype()=='S') || (bal<1000 && ac.rettype()=='C'))
					cout<<"Insufficience balance";
				else
					ac.draw(amt);
		      }
			int pos=(-1)*static_cast<int>(sizeof(ac));
			File.seekp(pos,ios::cur);
			File.write(reinterpret_cast<char *> (&ac), sizeof(bank_account));
			cout<<"\n\n\t Record Updated";
			found=true;
	       }
         }
    File.close();
	if(found==false)
		cout<<"\n\n Record Not Found ";
}

// case 4
void display(int n)
{
	bank_account ac;
	bool flag=false;
	ifstream inFile;
	inFile.open("account.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	cout<<"\nBALANCE DETAILS\n";
    	while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(bank_account)))
	{
		if(ac.retacno()==n)
		{
			ac.show_account();
			flag=true;
		}
	}
    inFile.close();
	if(flag==false)
		cout<<"\n\nAccount number does not exist";
}


//Main Function
int main(){
	
	int ch, num;
	
	// Options
	cout<<"\n\n\n\tMAIN MENU";
	cout<<"\n\n\t01. NEW ACCOUNT";
	cout<<"\n\n\t02. DEPOSIT AMOUNT";
	cout<<"\n\n\t03. WITHDRAW AMOUNT";
	cout<<"\n\n\t04. BALANCE ENQUIRY";
	cout<<"\n\n\t06. EXIT";
	
	cout<<"\n\n\tSelect an  option (1-5) ";
	
	cin>>ch;
	system("cls"); // is used to make the screen/terminal clear
	
	switch(ch){
		case 1 :
			create_account();
			break;
		case 2:
			cout<<"\n\n\tEnter The account No. : "; cin>>num;
			deposit(num, 1);
			break;
		case 3 :
			cout<<"\n\n\tEnter The account No. : "; cin>>num;
			deposit(num, 2);
			break;
		case 4:
			cout<<"\n\n\tEnter The account No. : "; cin>>num;
			display(num);
		case 5:
			cout<<"\n\n\tThanks for using bank managemnt system";
			break;
		default:
			cout<<"Select an  option (1-5)";
			main();


	}
	
}
