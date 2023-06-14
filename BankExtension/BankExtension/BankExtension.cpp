#include<iostream>
#include <string>
#include <vector>
#include <fstream>
#include <iomanip>
using namespace std;

string ClientName = "Clients.txt";

struct sClient {
	string AccountNubmer, PinCode, Name, Phone;
	double AccountBalance;
	bool ClientDelete = false;
};

void ShowMainSreen();
void ShowTransactionsScreen();

vector <string> SpiltString(string s1, string delim) {
	vector <string> vstring;
	string sWord;
	short Pos = 0;
	while ((Pos = s1.find(delim)) != std::string::npos) {
		sWord = s1.substr(0, Pos);
		if (sWord != " ") {
			vstring.push_back(sWord);
		}
		s1.erase(0, Pos + delim.length());
	}
	if (s1 != " ") {
		vstring.push_back(s1);

	}
	return vstring;
}

sClient ConvertLineToRecord(string line, string delim = "#//#") {
	vector <string> vstring = SpiltString(line, delim);
	sClient Client;

	Client.AccountNubmer = vstring[0];
	Client.PinCode = vstring[1];
	Client.Name = vstring[2];
	Client.Phone = vstring[3];
	Client.AccountBalance = stod(vstring[4]);

	return Client;

}

string ConverRecordToLine(sClient Client, string delim = "#//#") {
	string Line = "";

	Line = Client.AccountNubmer + delim;
	Line += Client.PinCode + delim;
	Line += Client.Name + delim;
	Line += Client.Phone + delim;
	Line += to_string(Client.AccountBalance);

	return Line;
}

vector <sClient> LoadDataFromFileToVector(string FileName) {
	vector <sClient> vClient;
	fstream MyFile;

	MyFile.open(FileName, ios::in);
	string line;
	sClient Client;

	if (MyFile.is_open()) {
		while (getline(MyFile, line)) {
			Client = ConvertLineToRecord(line);
			vClient.push_back(Client);
		}
		MyFile.close();
	}
	return vClient;
}

bool IsExisitingCleintByAccountNumber(string AccountNumber, string FileName) {
	fstream MyFile;

	MyFile.open(FileName, ios::in);
	string line;
	sClient Client;

	if (MyFile.is_open()) {
		while (getline(MyFile, line)) {
			Client = ConvertLineToRecord(line);
			if (Client.AccountNubmer == AccountNumber) {
				MyFile.close();
				return true;
			}
		}
		MyFile.close();
	}
	return false;
}

sClient ReadNewClient() {
	sClient Client;

	cout << "Enter Account Number?";
	getline(cin >> ws, Client.AccountNubmer);

	while (IsExisitingCleintByAccountNumber(Client.AccountNubmer, ClientName)) {
		cout << "Cleint [" << Client.AccountNubmer << "] is not fount, Enter Another Client? ";
		getline(cin >> ws, Client.AccountNubmer);
	}

	cout << "Enter PinCode?";
	getline(cin, Client.PinCode);

	cout << "Enter Client Name?";
	getline(cin, Client.Name);

	cout << "Enter Phone?";
	getline(cin, Client.Phone);

	cout << "Enter Acocunt Balance?";
	cin >> Client.AccountBalance;

	return Client;

}

sClient ChangeClient(string AccountNumber) {
	sClient Client;

	Client.AccountNubmer = AccountNumber;

	cout << "Enter PinCode?";
	getline(cin >> ws, Client.PinCode);

	cout << "Enter Client Name?";
	getline(cin, Client.Name);

	cout << "Enter Phone?";
	getline(cin, Client.Phone);

	cout << "Enter Acocunt Balance?";
	cin >> Client.AccountBalance;

	return Client;
}

void AddNewCleintToFile(string FileName, string line) {
	fstream MyFile;

	MyFile.open(FileName, ios::out | ios::app);

	if (MyFile.is_open()) {
		MyFile << line << endl;

		MyFile.close();
	}
}

void AddNewCleint() {
	sClient Client;
	Client = ReadNewClient();
	AddNewCleintToFile(ClientName, ConverRecordToLine(Client));
}

void AddCleint() {
	char Answer = 'n';
	do {
		cout << "\nAdd New Cleint\n";
		AddNewCleint();

		cout << "\nCleint Added Successfully, do you want to Add more? ";
		cin >> Answer;
	} while (toupper(Answer) == 'Y');
}

void ShowAddClient() {
	cout << "===================================\n";
	cout << "\t Add Client\n";
	cout << "===================================\n";
	AddCleint();
}

void printClientReocrd(sClient Cleint) {

	cout << "| " << left << setw(16) << Cleint.AccountNubmer;
	cout << "| " << left << setw(10) << Cleint.PinCode;
	cout << "| " << left << setw(25) << Cleint.Name;
	cout << "| " << left << setw(12) << Cleint.Phone;
	cout << "| " << left << setw(15) << Cleint.AccountBalance;
}

void ShowClientList() {
	vector <sClient> vClient = LoadDataFromFileToVector(ClientName);

	cout << "\n\t\t\tClient [" << vClient.size() << "] Client(s).\n";
	cout << "--------------------------------------------------------------------------------------------\n";
	cout << "| " << setw(16) << left << "Account Number";
	cout << "| " << setw(10) << left << "PinCode";
	cout << "| " << setw(25) << left << "Client Name";
	cout << "| " << setw(12) << left << "Phone";
	cout << "| " << setw(15) << left << "Account Balance";
	cout << "\n--------------------------------------------------------------------------------------------\n";

	if (vClient.size() == 0) {
		cout << "No Cleint in the system\n";
	}
	else {
		for (sClient Cleint : vClient) {
			printClientReocrd(Cleint);
			cout << endl;
		}
	}

}

string ReadAccountNumber() {
	string AccountNumber;
	cout << "Enter Account Number? ";
	cin >> AccountNumber;
	return AccountNumber;
}

void PrintClientCard(sClient Client) {
	cout << "\nThe following are the Client details\n";
	cout << "---------------------------------------------";
	cout << "\nAccount Number  = " << Client.AccountNubmer;
	cout << "\nPinCode         = " << Client.PinCode;
	cout << "\nAccount Name    = " << Client.Name;
	cout << "\nPhone Number    = " << Client.Phone;
	cout << "\nAccount balance = " << Client.AccountBalance;
	cout << "\n---------------------------------------------\n";

}

bool FindClientByAccountNumber(string AccountNumber, vector <sClient> vClient, sClient& Client) {

	for (sClient c : vClient) {
		if (c.AccountNubmer == AccountNumber) {
			Client = c;
			return true;
		}
	}
	return false;
}

bool MarkClientByAccountNumber(string AccountNumber, vector <sClient>& vClient) {

	for (sClient& c : vClient) {
		if (c.AccountNubmer == AccountNumber) {
			c.ClientDelete = true;
			return true;
		}
	}
	return false;
}

vector <sClient> SaveClientByAccountNumber(vector <sClient> vClient, string FileName) {
	fstream MyFile;

	MyFile.open(FileName, ios::out);

	string line;

	if (MyFile.is_open()) {

		for (sClient c : vClient) {
			if (c.ClientDelete == false) {
				line = ConverRecordToLine(c);
				MyFile << line << endl;
			}
		}
		MyFile.close();
	}
	return vClient;
}

bool DeleteClientByAccountNumber(string AccountNumber, vector <sClient>& vClient) {
	char Answe = 'n';
	sClient Client;
	if (FindClientByAccountNumber(AccountNumber, vClient, Client)) {
		PrintClientCard(Client);

		cout << "\n\nAre you sure you want to delete this Cleint? ";
		cin >> Answe;

		if (toupper(Answe) == 'Y') {

			MarkClientByAccountNumber(AccountNumber, vClient);

			SaveClientByAccountNumber(vClient, ClientName);

			vClient = LoadDataFromFileToVector(ClientName);

			cout << "\nClietn Deleted Successfully\n";
			return true;
		}

	}
	else {
		cout << "\nClient [" << AccountNumber << "] is not found!\n";
		return false;
	}
}

bool UpdateClientByAccountNumber(string AccountNumber, vector <sClient>& vClient) {
	char Answe = 'n';
	sClient Client;
	if (FindClientByAccountNumber(AccountNumber, vClient, Client)) {
		PrintClientCard(Client);

		cout << "\n\nAre you sure you want to delete this Cleint? ";
		cin >> Answe;

		if (toupper(Answe) == 'Y') {

			for (sClient& c : vClient) {
				if (c.AccountNubmer == AccountNumber) {
					c = ChangeClient(AccountNumber);
				}
			}

			SaveClientByAccountNumber(vClient, ClientName);

			cout << "\nClietn Deleted Successfully\n";
			return true;
		}

	}
	else {
		cout << "\nClient [" << AccountNumber << "] is not found!\n";
		return false;
	}
}

void ShowDeleteClient() {
	cout << "===================================\n";
	cout << "\t Delete Client\n";
	cout << "===================================\n";
	vector <sClient> vClient = LoadDataFromFileToVector(ClientName);
	string AccountNumber = ReadAccountNumber();
	DeleteClientByAccountNumber(AccountNumber, vClient);
}

void ShowUpdateClient() {
	cout << "===================================\n";
	cout << "\t Delete Client\n";
	cout << "===================================\n";
	vector <sClient> vClient = LoadDataFromFileToVector(ClientName);
	string AccountNumber = ReadAccountNumber();
	UpdateClientByAccountNumber(AccountNumber, vClient);
}

void ShowFindClient() {
	cout << "===================================\n";
	cout << "\t Find Client\n";
	cout << "===================================\n";
	vector <sClient> vClient = LoadDataFromFileToVector(ClientName);
	sClient Client;
	string AccountNumber = ReadAccountNumber();
	if (FindClientByAccountNumber(AccountNumber, vClient, Client)) {
		PrintClientCard(Client);
	}
	else {
		cout << "\nClinet is no found\n";
	}
}

void ShowEndProgramm() {
	cout << "===================================\n";
	cout << "\t End Program :-( \n";
	cout << "===================================\n";
}


bool DepositToAccountBalance(string AccountNumber, vector <sClient>& vClient, double Amount) {
	char Answe = 'n';

	cout << "\nAre you sure you want to perform this transactions?Y/N ";
	cin >> Answe;
	if (toupper(Answe) == 'Y')
	{

		for (sClient& c : vClient)
		{
			if (c.AccountNubmer == AccountNumber)
			{
				c.AccountBalance += Amount;
				SaveClientByAccountNumber(vClient, ClientName);
				cout << "\nDone successfully, new balance is [" << c.AccountBalance << "].\n";
				return true;
			}
		}
	}
	return false;
}
void PrintTotlaBalance(sClient Cleint) {

	cout << "| " << left << setw(16) << Cleint.AccountNubmer;
	cout << "| " << left << setw(25) << Cleint.Name;
	cout << "| " << left << setw(15) << Cleint.AccountBalance;
}

void ShowDepositScreen() {
	cout << "\n----------------------------------------\n";
	cout << "\tDeposit Screen";
	cout << "\n----------------------------------------\n\n";
	vector <sClient> vClient = LoadDataFromFileToVector(ClientName);
	sClient Client;
	string AccountNumber = ReadAccountNumber();

	while (!FindClientByAccountNumber(AccountNumber, vClient, Client)) {
		cout << "\nClinet With [" << AccountNumber << "] does not exisit\n\n";
		AccountNumber = ReadAccountNumber();
	}
	PrintClientCard(Client);

	double Amount;
	cout << "\nPlease enter deposit amount? ";
	cin >> Amount;

	DepositToAccountBalance(AccountNumber, vClient, Amount);
}
void ShowWithdrawScreen() {
	cout << "\n----------------------------------------\n";
	cout << "\tWithdraw Screen";
	cout << "\n----------------------------------------\n\n";
	vector <sClient> vClient = LoadDataFromFileToVector(ClientName);
	sClient Client;
	string AccountNumber = ReadAccountNumber();

	while (!FindClientByAccountNumber(AccountNumber, vClient, Client)) {
		cout << "\nClinet With [" << AccountNumber << "] does not exisit\n\n";
		AccountNumber = ReadAccountNumber();
	}
	PrintClientCard(Client);

	double Amount;
	cout << "\nPlease enter Withdraw amount? ";
	cin >> Amount;

	while (Amount > Client.AccountBalance)
	{
		cout << "\nAmount Exceeds the balance, you can withdraw up to : " << Client.AccountBalance;
		cout << "\nPlease enter Withdraw amount? ";
		cin >> Amount;

	}
	DepositToAccountBalance(AccountNumber, vClient, Amount * -1);
}
void ShowTotalBalance() {
	vector <sClient> vClient = LoadDataFromFileToVector(ClientName);

	cout << "\n\t\t\tClient [" << vClient.size() << "] Client(s).\n";
	cout << "--------------------------------------------------------------------------------------------\n";
	cout << "| " << setw(16) << left << "Account Number";
	cout << "| " << setw(25) << left << "Client Name";
	cout << "| " << setw(15) << left << "Account Balance";
	cout << "\n--------------------------------------------------------------------------------------------\n";

	int TotalBalance = 0;

	if (vClient.size() == 0) {
		cout << "No Cleint in the system\n";
	}
	else {
		for (sClient Cleint : vClient) {
			PrintTotlaBalance(Cleint);
			TotalBalance += Cleint.AccountBalance;

			cout << endl;
		}
	}
	cout << "--------------------------------------------------------------------------------------------\n";
	cout << "\n\t\t\t\t\t\tTotal Balances = " << TotalBalance;
}

short ReadMainMenueOption() {
	short Choose;
	cout << "Choose Main Menue Option [1 to 6]? ";
	cin >> Choose;
	return Choose;
}
short ReadTransactionsMenueOption() {
	short Choose;
	cout << "Choose Main Menue Option [1 to 4]? ";
	cin >> Choose;
	return Choose;
}
enum enMainMenueOption {
	eClientList = 1,
	eAddClient = 2,
	eDeleteClient = 3,
	eUpdateClient = 4,
	eFindClient = 5,
	eTransactions = 6,
	eExit = 7
};
enum enTransactionsMenueOption {
	eDeposit = 1,
	eWithdraw = 2,
	eTotalBalance = 3,
	eMainMenue = 4
};
void GoBacktoMainMenue() {
	cout << "\n\nPress any Key to go back to main menue....";
	system("pause >0");
	ShowMainSreen();
}
void GoBacktoTransactionsMainMenue() {
	cout << "\n\nPress any Key to go back to Transactions menue....";
	system("pause >0");
	ShowTransactionsScreen();
}

void TransactionsMianMenueOptine(enTransactionsMenueOption TransactionsMenueOption) {

	switch (TransactionsMenueOption) {
	case enTransactionsMenueOption::eDeposit:
		system("cls");
		ShowDepositScreen();
		GoBacktoTransactionsMainMenue();

	case enTransactionsMenueOption::eWithdraw:
		system("cls");
		ShowWithdrawScreen();
		GoBacktoTransactionsMainMenue();

	case enTransactionsMenueOption::eTotalBalance:
		system("cls");
		ShowTotalBalance();
		GoBacktoTransactionsMainMenue();

	case enTransactionsMenueOption::eMainMenue:
		system("cls");
		ShowMainSreen();
	}
}
void ShowTransactionsScreen() {
	system("cls");
	cout << "=================================================\n";
	cout << "\t\tTransactions Menue Screen\n";
	cout << "=================================================\n";
	cout << "\t[1] Deposit." << endl;
	cout << "\t[2] Withdraw." << endl;
	cout << "\t[3] Total Balance." << endl;
	cout << "\t[4] Main Menue" << endl;
	cout << "=================================================\n";
	TransactionsMianMenueOptine((enTransactionsMenueOption)ReadTransactionsMenueOption());
}

void PerformMianMenueOptine(enMainMenueOption MainMenueOption) {

	switch (MainMenueOption) {

	case enMainMenueOption::eClientList:
		system("cls");
		ShowClientList();
		GoBacktoMainMenue();

	case enMainMenueOption::eAddClient:
		system("cls");
		ShowAddClient();
		GoBacktoMainMenue();

	case enMainMenueOption::eDeleteClient:
		system("cls");
		ShowDeleteClient();
		GoBacktoMainMenue();

	case enMainMenueOption::eUpdateClient:
		system("cls");
		ShowUpdateClient();
		GoBacktoMainMenue();

	case enMainMenueOption::eFindClient:
		system("cls");
		ShowFindClient();
		GoBacktoMainMenue();

	case enMainMenueOption::eTransactions:
		system("cls");
		ShowTransactionsScreen();
		GoBacktoMainMenue();

	case enMainMenueOption::eExit:
		system("cls");
		ShowEndProgramm();
	}
}
void ShowMainSreen() {

	system("cls");
	cout << "=================================================\n";
	cout << "\t\tMain Menue Screen\n";
	cout << "=================================================\n";
	cout << "\t[1] Show Client List." << endl;
	cout << "\t[2] Add New Client." << endl;
	cout << "\t[3] Delete Client." << endl;
	cout << "\t[4] Update CLient" << endl;
	cout << "\t[5] Find Client" << endl;
	cout << "\t[6] Transactions" << endl;
	cout << "\t[7] Exit" << endl;
	cout << "=================================================\n";
	PerformMianMenueOptine((enMainMenueOption)ReadMainMenueOption());

}

int main() {

	ShowMainSreen();

	system("pause > 0");
	return 0;
}
