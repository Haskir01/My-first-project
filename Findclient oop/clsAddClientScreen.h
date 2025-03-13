#pragma once
#include<iostream>
#include"clsBankClient.h"
#include"clsScreen.h"
#include"clsInputValidate.h"

class clsAddClientScreen :protected clsScreen
{
private:
    static void _ReadClientInfo(clsBankClient& Client)
    {
        cout << "\nEnter FirstName: ";
        Client.FirstName = clsInputValidate::ReadString();

        cout << "\nEnter LastName: ";
        Client.LastName = clsInputValidate::ReadString();

        cout << "\nEnter Email: ";
        Client.Email = clsInputValidate::ReadString();

        cout << "\nEnter Phone: ";
        Client.Phone = clsInputValidate::ReadString();

        cout << "\nEnter PinCode: ";
        Client.PinCode = clsInputValidate::ReadString();

        cout << "\nEnter Account Balance: ";
        Client.AccountBalance = clsInputValidate::ReadFloatNumber();
    }
    static void _PrintClient(clsBankClient Client)
    {
        cout << "\nClient Card:";
        cout << "\n___________________";
        cout << "\nFirstName   : " << Client.FirstName;
        cout << "\nLastName    : " << Client.LastName;
        cout << "\nFull Name   : " << Client.GetFullName();
        cout << "\nEmail       : " << Client.Email;
        cout << "\nPhone       : " << Client.Phone;
        cout << "\nAcc. Number : " << Client.AccountNumber();
        cout << "\nPassword    : " << Client.PinCode;
        cout << "\nBalance     : " << Client.AccountBalance;
        cout << "\n___________________\n";

    }

public:
    static void ShowAddNewClientScreen() {
        if (!CheckAccessRights(clsUser::pAddNewClient)) {
            return;
        }

        clsScreen::_DrawScreenHeader("\tAdd Client Screen");
        string accountnum = "";
        cout << "\nPlease Enter Account Number: ";
        accountnum = clsInputValidate::ReadString();
        while (clsBankClient::IsClientExist(accountnum)) {
            cout << "\nAccount Number Is Already Used, Choose another one: ";
            accountnum = clsInputValidate::ReadString();
        }
        clsBankClient Client = clsBankClient::GetAddNewClientObject(accountnum);
        _ReadClientInfo(Client);
        clsBankClient::enSaveResult SaveResult;
        SaveResult = Client.Save(Client);
        switch (SaveResult) {
        case clsBankClient::enSaveResult::svFaildEmptyObject: {
            cout << "\nError account was not saved because it's Empty";
            break;
        }
        case clsBankClient::enSaveResult::svSucceeded: {
            cout << "\nAccount Addeded Successfully :-)\n";
            _PrintClient(Client);
            break;
        }
        case clsBankClient::enSaveResult::svFaildAccountNumberExists: {
            cout << "\nError account was not saved because account number is used!\n";
            break;

        }
        }
    }
};

