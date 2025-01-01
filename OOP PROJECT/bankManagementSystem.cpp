#include<fstream>
#include<iostream>
#include<vector>
#include<string>
using namespace std;
class Bank{ 								//defining a class Bank with attribute bankName
	protected:
		string bankName;
};
class Branch:protected Bank{				//defining a class Branch derived from Bank in protected mode with attribute branchCode
	protected:
		int branchCode;
};
int acc=100000000;
class Account:protected Branch{				//defining a class Account derived from Branch in protected mode
	private:
		string nameOfUser;
		string accNo;
		int password;
		float balance;
	public:
		void createAccount(vector<string> &data){	   //function to create a new account
			cout<<"Please enter the Bank name: ";
			cin>>bankName;
			cout<<"Please enter the Bank Branch Code(3 digit number): ";
			cin>>this->branchCode;
			cout<<"Please enter the name of user: ";
			cin>>this->nameOfUser;
			cout<<"Please set a 4 digit Password: ";
			cin>>this->password;
			this->balance=0;
			this->accNo = acc;
			string accdata = to_string(acc) + to_string(password) + to_string(branchCode) + "!" + bankName + "!" + "(" + to_string(balance) + ")" + "|" + nameOfUser + "|";
			cout<<"\nAccount created successfully!"<<endl;
			cout<<"Your Bank account number is: "<<acc<<"\n"<<endl;
			acc++;
			data[data.size()-1] = accdata;
			data.push_back(to_string(acc));
		}
		Account* createAccount(string accDetails){		//function creates a Account object from the string passed as argument
			this->accNo = accDetails.substr(0,9);
			this->password = stoi(accDetails.substr(9,4));
			this->branchCode = stoi(accDetails.substr(13,3));
			int i=17;
			string s="";
			while(accDetails[i]!='!'){
				s = s + accDetails[i];
				i++;
			}
			this->bankName = s;
			s="";
			i+=2;
			while(accDetails[i]!=')'){
				s = s + accDetails[i];
				i++;
			}
			this->balance = stoi(s);
			i+=2;
			s="";
			while(accDetails[i]!='|'){
				s = s + accDetails[i];
				i++;
			}
			this->nameOfUser = s;
			return this;
		}
		bool checkPassword(int userIp){		//function returns true if user input password matches the origiinal password and false otherwise
			if(this->password == userIp) return true;
			return false;
		}
		void getBalance(){					//function returns the balance in the account
			cout<<"Your balance is: "<<this->balance<<"\n"<<endl;
			return;
		}
		void deposit(){						//function to deposit money in the account
			int ipamount;
			char cash;
			cout<<"How much cash would you like to deposit: "<<endl;
			cin>>ipamount;
			cout<<"Press Y to deposit "<<ipamount<<" cash"<<endl;
			cin>>cash;
			if(cash=='Y'){
				balance += ipamount;
				cout<<ipamount<<"Rs cash deposited."<<endl;
				cout<<"Your Account Balance is : "<<balance<<"\n"<<endl;
			}
			else{
				cout<<"Deposit cancelled!.\n"<<endl;
			}
		}
		void withdraw(){					//function to withdraw money from the account
			int ipamount;
			char cash;
			cout<<"How much cash would you like to withdraw: "<<endl;
			cin>>ipamount;
			if(ipamount > balance) {
				cout<<"Insufficient balance..\n"<<endl;
				return;
			}
			cout<<"Press Y to withdraw "<<ipamount<<" cash"<<endl;
			cin>>cash;
			if(cash=='Y'){
				balance -= ipamount;
				cout<<ipamount<<"Rs cash withdrawn."<<endl;
				cout<<"Your Account Balance is : "<<balance<<"\n"<<endl;
				cout<<endl;
			}
			else{
				cout<<"Withdraw cancelled!.\n"<<endl;
			}
		}
		void transfer(Account &temp){	       	//transfers money from senders account to recievers account
			char choice;
			int amount;
			cout<<"The Reciever is "<<temp.nameOfUser<<". Press Y to continue: ";
			cin>>choice;
			if(choice=='Y'){
				cout<<"Enter the amount to be transferred: ";
				cin>>amount;
				if(amount>balance){
					cout<<"Insufficient balance!! Could not transfer money!\n"<<endl;
					return;
				}
				balance = balance - amount;
				temp.balance = temp.balance + amount;
				cout<<"Rs"<<amount<<" were transferred successfully.\n"<<endl;
			}
		}
		string createString(){			//function will return a string that converts details of a account object into a string
			string accdata = this->accNo + to_string(password) + to_string(branchCode) + "!" + bankName + "!" + "(" + to_string(balance) + ")" + "|" + nameOfUser + "|";
			return accdata;	
		}
};
int findAcc(vector<string> data,string inputAcc){	//function checking the data to find a account with given account number
	int i=0;									//return index if account found
	Account temp;
	while(i<data.size()-1)
	{
		if(inputAcc == data[i].substr(0,9)){
			return i;
		}
		i++;
	}
	return -1;
}
vector<string> readFile(){							//function reading the data from the file into a string vector
	ifstream my_file("bankData.txt");
	vector<string> temp;
	if(!my_file){
		cout<<"Unable to open"<<endl;
	}
	else{
		string line;
		while(!my_file.eof())
		{
			getline(my_file,line);
			if(line!="") temp.push_back(line);
		}
		acc = stoi(temp[temp.size()-1]);
		return temp;
	}
	my_file.close();
}
void writeFile(vector<string> &data){				//function rewriting the data in the same file
	ofstream fileOut("bankData.txt");
	if(!fileOut){
		cout<<"Unable to open"<<endl;
		return;
	}
	else{
		for(int i=0;i<data.size();i++){
			fileOut<<data[i]<<endl;
		}
		data.clear();
	}
	fileOut.close();	
	return;
}
int main()
{
	cout<<"..Welcome to the bank management system.."<<endl;
	int choice=0;
	vector<string> data = readFile();
	Account currAcc;
    Account newtemp;
    string ipaccno;
    int inputPassword;
    int ans,ans2;
    
	while(choice!=6){
		cout<<"..........How can we help you:..........."<<endl;
		cout<<".     Enter 1 to Create a Account       ."<<endl;
		cout<<".     Enter 2 to Check your balance     ."<<endl;
		cout<<".     Enter 3 to Deposit money          ."<<endl;
		cout<<".     Enter 4 to Withdraw money         ."<<endl;
		cout<<".     Enter 5 to Transfer money         ."<<endl;
		cout<<".     Enter 6 to Quit                   ."<<endl;
		cout<<"........................................."<<endl;
		cout<<"            Your choice:";
		cin>>choice;
		switch(choice){
			case 1:
				currAcc.createAccount(data);
				break;
			case 2:
				cout<<"\nEnter your Account number: ";
				cin>>ipaccno;
				ans = findAcc(data,ipaccno);
				if(ans!= -1){
					newtemp.createAccount(data[ans]);
					cout<<"Please enter the password: ";
					cin>>inputPassword;
					if(newtemp.checkPassword(inputPassword)){
						newtemp.getBalance();
					}
					else{
						cout<<"Incorrect Password.. Access Denied..\n"<<endl;
					}
				}
				else{
					cout<<"Account not found..Please create new account..\n"<<endl;
				}
				break;
			case 3:
				cout<<"\nEnter your account number: ";
				cin>>ipaccno;
				ans = findAcc(data,ipaccno);
				if(ans!=-1){
					newtemp.createAccount(data[ans]);
					cout<<"Please enter the password: ";
					cin>>inputPassword;
					if(newtemp.checkPassword(inputPassword)){
						newtemp.deposit();
						data[ans] = newtemp.createString();
					}
					else{
						cout<<"Incorrect Password.. Access Denied..\n"<<endl;
					}
				}
				else{
					cout<<"Account not found..Please create new account..\n"<<endl;
				}
				break;
			case 4:
				cout<<"\nEnter your account number: ";
				cin>>ipaccno;
				ans = findAcc(data,ipaccno);
				if(ans!=-1){
					newtemp.createAccount(data[ans]);
					cout<<"Please enter the password: ";
					cin>>inputPassword;
					if(newtemp.checkPassword(inputPassword)){
						newtemp.withdraw();
						data[ans] = newtemp.createString();
					}
					else{
						cout<<"Incorrect Password.. Access Denied..\n"<<endl;
					}
				}
				else{
					cout<<"Account not found..Please create new account..\n"<<endl;
				}
				break;
			case 5:
				cout<<"\nEnter the Sender's account number: ";
				cin>>ipaccno;
				ans = findAcc(data,ipaccno);
				if(ans!=-1){
					currAcc.createAccount(data[ans]);
					cout<<"Please enter the password: ";
					cin>>inputPassword;
					if(currAcc.checkPassword(inputPassword)){
						cout<<"Enter the Reciever's account number: ";
						cin>>ipaccno;
						ans2 = findAcc(data,ipaccno);
						if(ans2!=-1){
							newtemp.createAccount(data[ans2]);
							currAcc.transfer(newtemp);
							data[ans] = currAcc.createString();
							data[ans2] = newtemp.createString();
						}
						else{
							cout<<"Reciever's account doesnt exist..\n"<<endl;
						}
					}
					else{
						cout<<"Incorrect Password.. Access Denied..\n"<<endl;
					}
				}
				else{
					cout<<"Sender's Account not found..Please create new account.."<<endl;
				}
				break;
			case 6:
				writeFile(data);
				break;
			default:
				cout<<"Please enter a valid choice";
		}
	}
	return 0;
}
