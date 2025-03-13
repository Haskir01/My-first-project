#pragma once
#include"clsBankClient.h"
#include<iostream>
#include"clsInputValidate.h"
#include"clsScreen.h"
class clsDeleteClientScreen :protected clsScreen
{
private:


public:
	static void ShowDeleteClientScreen() {
		if (!CheckAccessRights(clsUser::pDeleteClient)) {
			return;
		}

		clsScreen::_DrawScreenHeader("\tDelete Client Screen");
		string accountnum = "";
		cout << "\nPlease Enter Account Number: ";
		accountnum = clsInputValidate::ReadString();
		while (!clsBankClient::IsClientExist(accountnum)) {
			cout << "\nAccount number is not found, choose another one: ";
			accountnum = clsInputValidate::ReadString();
		}
		clsBankClient Client = clsBankClient::Find(accountnum);
		Client.Print();
		cout << "\nAre you sure you want to delete this client y/n? ";

		char Answer = 'n';
		cin >> Answer;

		if (Answer == 'y' || Answer == 'Y') {
			if (Client.Delete(Client)) {
				cout << "\nClient Deleted Successfully :-)\n";
				Client.Print();
			}
			else {
				cout << "\nError Client Was not Deleted\n";
			}
		}
	}
};

