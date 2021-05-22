/*     BANK MANAGEMENT SYSTEM
           AUTHORED BY
NAME 								ENROLL
ADITYA PRATAP SINGH CHAUHAN	        9920103027
VANSH PANWAR                        9920103003
ADITYA RAJ SINGH					9920103012
MADHUR GOEL	                        9920103022
BATCH F1*/

#include<iostream>
#include<fstream>
#include<conio.h>
#include<cctype>
#include<iomanip>
using namespace std;


class Account
{
    int acno; float deposit;
    char type, name[500];
    public:
        void CreateAccount()
        {
            system("CLS");
            cout<<"\nEnter the Account No. : ";
            cin>>acno;
            cout<<"\nEnter the Name of the Account holder : ";
            cin.ignore();
            cin.getline(name,50);
            cout<<"\nEnter Type of the Account (C/S) : ";
            cin>>type;
            type=toupper(type);
            cout<<"\nEnter The Initial amount : ";
            cin>>deposit;
            cout<<"\n\nAccount Created..";
        }
        void ShowAccount() const
        {
            cout<<"\nAccount No. : "<<acno;
            cout<<"\nAccount Holder Name : ";
            cout<<name;
            cout<<"\nType of Account : "<<type;
            cout<<"\nBalance amount : "<<deposit;
        }
        void ModifyAccount()
        {
            cout<<"\n\t\t\tAccount No. : "<<acno;
            cout<<"\n\t\t\tModify Account Holder Name : ";
            cin.ignore();
            cin.getline(name,50);
            cout<<"\n\t\t\tModify Type of Account : ";
            cin>>type;
            type=toupper(type);
            cout<<"\n\t\t\tModify Balance amount : ";
            cin>>deposit;
        }
        void Deposit(int);
        void Withdraw(int);
        void report() const;
        int retacno() const;
        int retdeposit() const;
        char rettype() const;
};

void Account::Deposit(int x)
{
    deposit+=x;
}
void Account::Withdraw(int x)
{
    deposit-=x;
}
void Account::report() const
{
	cout<<acno<<setw(10)<<" "<<name<<setw(10)<<" "<<type<<setw(6)<<deposit<<endl;
}

int Account::retacno() const
{
	return acno;
}

int Account::retdeposit() const
{
	return deposit;
}

char Account::rettype() const
{
	return type;
}



void WriteAccount();
void displaySpecificAC(int);
void modifyAccount(int);
void DeleteAccount(int);
void displayAllAC();
void DepositWithdraw(int, int);

int main()
{
    char ch;
	int num;
	do
	{
        system("CLS");
        cout<<"\n============================================";
        cout<<"\n============================================\n";
        cout<<"===========BANK MANAGEMENT SYSTEM===========";
        cout<<"\n============================================";
        cout<<"\n============================================\n";


		cout<<"\t  :::::::MAIN MENU:::::::\n";
		cout<<"1. NEW ACCOUNT";
		cout<<"\n2. DEPOSIT AMOUNT";
		cout<<"\n3. WITHDRAW AMOUNT";
		cout<<"\n4. BALANCE ENQUIRY";
		cout<<"\n5. ALL ACCOUNT HOLDER LIST";
		cout<<"\n6. CLOSE AN ACCOUNT";
		cout<<"\n7. MODIFY AN ACCOUNT";
		cout<<"\n8. EXIT";
		cout<<"\n\nSelect Your Option (1-8): ";
		cin>>ch;

        switch(ch)
		{
            case '1':
                WriteAccount();
            break;
            case '2':
                system("CLS");
                cout<<"\n\nEnter The account No. : "; cin>>num;
                DepositWithdraw(num, 1);
            break;
            case '3':
                system("CLS");
                cout<<"\n\nEnter The account No. : "; cin>>num;
                DepositWithdraw(num, 2);
            break;
            case '4':
                system("CLS");
                cout<<"\n\nEnter The account No. : "; cin>>num;
                displaySpecificAC(num);
            break;
            case '5':
                displayAllAC();
            break;
            case '6':
                system("CLS");
                cout<<"\n\nEnter The account No. : "; cin>>num;
                DeleteAccount(num);
            break;
            case '7':
                system("CLS");
                cout<<"\n\nEnter The account No. : "; cin>>num;
                modifyAccount(num);
            break;
            case '8':
                system("CLS");
                cout<<"\n\nThank You....";
            break;
            default :cout<<"\a";
		}
		cin.ignore();
		cin.get();
    }while(ch!='8');
    return 0;
    getch();
}

void WriteAccount()
{
	Account ac;
	ofstream outFile;
	outFile.open("account.dat",ios::binary|ios::app);
	ac.CreateAccount();
	outFile.write(reinterpret_cast<char *> (&ac), sizeof(Account));
	outFile.close();
}

void displaySpecificAC(int n)
{
	Account ac;
	bool flag=false;
	ifstream inFile;
	inFile.open("account.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	cout<<"\n\tBALANCE DETAILS\n";
    	while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(Account)))
	{
		if(ac.retacno()==n)
		{
			ac.ShowAccount();
			flag=true;
		}
	}
    inFile.close();
	if(flag==false)
		cout<<"\n\n\tAccount number does not exist";
}

void modifyAccount(int n)
{
	bool found=false;
	Account ac;
	fstream File;
    File.open("account.dat",ios::binary|ios::in|ios::out);
	if(!File)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	while(!File.eof() && found==false)
	{
		File.read(reinterpret_cast<char *> (&ac), sizeof(Account));
		if(ac.retacno()==n)
		{
			ac.ShowAccount();
			cout<<"\n\n\tEnter The New Details of account"<<endl;
			ac.ModifyAccount();
			int pos=(-1)*static_cast<int>(sizeof(Account));
			File.seekp(pos,ios::cur); //fncallat1353
		    File.write(reinterpret_cast<char *> (&ac), sizeof(Account));
		    cout<<"\n\n\t\tRecord Updated";
		    found=true;
		}
	}
	File.close();
	if(found==false)
		cout<<"\n\n\tRecord Not Found ";
}

void DeleteAccount(int n)
{
	Account ac;
	ifstream inFile;
	ofstream outFile;
	inFile.open("account.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	outFile.open("Temp.dat",ios::binary);
	inFile.seekg(0,ios::beg);
	while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(Account)))
	{
		if(ac.retacno()!=n)
		{
			outFile.write(reinterpret_cast<char *> (&ac), sizeof(Account));
		}
	}
    inFile.close();
	outFile.close();
	remove("account.dat");
	rename("Temp.dat","account.dat");
	cout<<"\n\nRecord Deleted ..";
}

void displayAllAC()
{
	system("CLS");
	Account ac;
	ifstream inFile;
	inFile.open("account.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	cout<<"\n\n\t\tACCOUNT HOLDER LIST\n\n";
	cout<<"====================================================\n";
	cout<<"A/c no.      NAME           Type  Balance\n";
	cout<<"====================================================\n";
	while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(Account)))
	{
		ac.report();
	}
	inFile.close();
}

void DepositWithdraw(int n, int option)
{
	int amt;
	bool found=false;
	Account ac;
	fstream File;
    File.open("account.dat", ios::binary|ios::in|ios::out);
	if(!File)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	while(!File.eof() && found==false)
	{
		File.read(reinterpret_cast<char *> (&ac), sizeof(Account));
		if(ac.retacno()==n)
		{
			ac.ShowAccount();
			if(option==1)
			{
				cout<<"\n\n\t\t\tTO DEPOSITSS AMOUNT";
				cout<<"\n\n\t\t\tEnter The amount to be deposited: ";
				cin>>amt;
				ac.Deposit(amt);
			}
		    if(option==2)
			{
				cout<<"\n\n\t\t\tTO WITHDRAW AMOUNT";
				cout<<"\n\n\t\t\tEnter The amount to be withdraw: ";
				cin>>amt;
				int bal=ac.retdeposit()-amt;
				if(bal<0)
					cout<<"Insufficience balance";
				else
					ac.Withdraw(amt);
		      }
			int pos=(-1)*static_cast<int>(sizeof(ac));
			File.seekp(pos,ios::cur);//fn1353
			File.write(reinterpret_cast<char *> (&ac), sizeof(Account));
			cout<<"\n\n\t\t\tRecord Updated";
			found=true;
	       }
         }
    File.close();
	if(found==false)
		cout<<"\n\n\t\t\tRecord Not Found ";
}


