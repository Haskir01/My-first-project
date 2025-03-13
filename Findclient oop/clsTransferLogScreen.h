#pragma once
#include<iostream>
#include"clsBankClient.h"
#include "clsScreen.h"
#include <iomanip>
#include <fstream>
using namespace std;
class clsTransferLogScreen :public clsScreen
{
private:
	static void _PrintTransferLogRecordLine(clsBankClient::stTrnsferLogRecord TransferLogRecord) {
		cout << setw(8) << left << "| " << setw(23) << left << TransferLogRecord.DateTime << "| " << setw(8) << left
			<< TransferLogRecord.SourceAccountNumber << "| " << setw(8) << left << TransferLogRecord.DestinationAccountNumber <<
			"| "<<setw(8)<<left<<TransferLogRecord.Amount<<
			"| " << setw(10) << left << TransferLogRecord.srcBalanceAfter << "| " << setw(10) << left << TransferLogRecord.destBalanceAfter <<
			"| " << setw(8) << left << TransferLogRecord.UserName;
	}
public:
	static void ShowTransferLogScreen() {
		vector<clsBankClient::stTrnsferLogRecord>AllRecord = clsBankClient::GetTransfersLogList();
		string Title = "\tTransfer Log List Screen";
		string SubTitle = "\t    (" + to_string(AllRecord.size()) + ") Record(s).";

		_DrawScreenHeader(Title, SubTitle);
		cout << setw(8) << left << "" << "\n\t_______________________________________________________";
		cout << "_________________________________________\n" << endl;

		cout << setw(8) << left << "" << "| " << left << setw(23) << "Date/Time";
		cout << "| " << left << setw(8) << "s.Acct";
		cout << "| " << left << setw(8) << "d.Acct";
		cout << "| " << left << setw(8) << "Amount";
		cout << "| " << left << setw(10) << "s.Balance";
		cout << "| " << left << setw(10) << "d.Balance";
		cout << "| " << left << setw(8) << "User";

		cout << setw(8) << left << "" << "\n\t_______________________________________________________";
		cout << "_________________________________________\n" << endl;
		if (AllRecord.size() == 0)
			cout << "\t\t\t\tNo Transfers Available In the System!";
		else

			for (clsBankClient::stTrnsferLogRecord Record : AllRecord)
			{

				_PrintTransferLogRecordLine(Record);
				cout << endl;
			}

		cout << setw(8) << left << "" << "\n\t_______________________________________________________";
		cout << "_________________________________________\n" << endl;
	}
};

