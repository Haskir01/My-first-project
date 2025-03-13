#pragma once
#include<iostream>
#include<string>
#include<fstream>
#include"clsPerson.h"
#include"clsString.h"
using namespace std;
using namespace std;
string FileName = "Clients.txt";
class clsBankClient :public clsPerson
{
private:
	enum enMode{EmptyMode=0,UpdateMode=1,AddMode=2};
	enMode _Mode;
	string _AccountNumber;
	string _PinCode;
	float _AccountBalance;
    bool _MarkForDelete = false;
    static clsBankClient _ConvertLinetoClientObject(string Line, string Seperator = "#//#") {
        vector<string>vClientData;
        vClientData = clsString::Split(Line, Seperator);
        return clsBankClient(enMode::UpdateMode, vClientData[0], vClientData[1], vClientData[2], vClientData[3], vClientData[4], vClientData[5], stod(vClientData[6]));
    }
    static clsBankClient _GetEmptyClientObject()
    {
        return clsBankClient(enMode::EmptyMode, "", "", "", "", "", "", 0);
    }
    static string _ConverClientObjectToLine(clsBankClient Client, string Seperator = "#//#")
    {

        string stClientRecord = "";
        stClientRecord += Client.FirstName + Seperator;
        stClientRecord += Client.LastName + Seperator;
        stClientRecord += Client.Email + Seperator;
        stClientRecord += Client.Phone + Seperator;
        stClientRecord += Client.AccountNumber() + Seperator;
        stClientRecord += Client.PinCode + Seperator;
        stClientRecord += to_string(Client.AccountBalance);

        return stClientRecord;

    }
    static vector<clsBankClient>_LoadDataFromFile() {
        vector<clsBankClient>AllClient;
        fstream MyFile;
        MyFile.open(FileName, ios::in);
        if (MyFile.is_open()) {
            string Line;
            while (getline(MyFile, Line)) {
                AllClient.push_back(_ConvertLinetoClientObject(Line, "#//#"));
            }MyFile.close();
        }return AllClient;
    }
    static void _LoadDataToFile(vector<clsBankClient>All) {
        fstream MyFile;
        MyFile.open(FileName, ios::out);
        if (MyFile.is_open()) {
            for (clsBankClient &t : All) {
                if (t.MarkForDelete() == false)
                MyFile << _ConverClientObjectToLine(t, "#//#")<<endl;
            }MyFile.close();
        }
    }
    static void _Update(clsBankClient Client) {
        vector<clsBankClient>all = _LoadDataFromFile();
        for (clsBankClient& t : all) {
            if (t.AccountNumber() == Client.AccountNumber()) {
                t = Client;break;
            }
        }_LoadDataToFile(all);
    }
    static void _AddNew(clsBankClient Client) {
        fstream MyFile;
        
        MyFile.open(FileName, ios::app);
        if (MyFile.is_open()) {
            MyFile << _ConverClientObjectToLine(Client, "#//#") << endl;
            MyFile.close();
        }

    }
    string _PrepareTransferLogRecord(float Amount, clsBankClient DestinationClient,
        string UserName, string Seperator = "#//#") {
        string TransferLogRecord = "";
        TransferLogRecord += clsDate::GetSystemDateTimeString() + Seperator;
        TransferLogRecord += AccountNumber() + Seperator;
        TransferLogRecord += DestinationClient.AccountNumber() + Seperator;
        TransferLogRecord += to_string(Amount) + Seperator;
        TransferLogRecord += to_string(AccountBalance) + Seperator;
        TransferLogRecord += to_string(DestinationClient.AccountBalance) + Seperator;
        TransferLogRecord += UserName;
        return TransferLogRecord;
    }
    void _RegisterTransferLog(float Amount, clsBankClient DestinationClient, string UserName) {
        string stDataLine = _PrepareTransferLogRecord(Amount, DestinationClient, UserName);
        fstream MyFile;
        MyFile.open("TransferLog", ios::out | ios::app);
        if (MyFile.is_open()) {
            MyFile << stDataLine << endl;
        }MyFile.close();
    }
 
    struct stTrnsferLogRecord;
    static stTrnsferLogRecord  _ConvertTransferLogLineToRecord(string Line, string Seperator = "#//#") {
        stTrnsferLogRecord TrnsferLogRecord;

        vector <string> vTrnsferLogRecordLine = clsString::Split(Line, Seperator);
        TrnsferLogRecord.DateTime = vTrnsferLogRecordLine[0];
        TrnsferLogRecord.SourceAccountNumber = vTrnsferLogRecordLine[1];
        TrnsferLogRecord.DestinationAccountNumber = vTrnsferLogRecordLine[2];
        TrnsferLogRecord.Amount = stod(vTrnsferLogRecordLine[3]);
        TrnsferLogRecord.srcBalanceAfter = stod(vTrnsferLogRecordLine[4]);
        TrnsferLogRecord.destBalanceAfter = stod(vTrnsferLogRecordLine[5]);
        TrnsferLogRecord.UserName = vTrnsferLogRecordLine[6];

        return TrnsferLogRecord;
    }
public:
    struct stTrnsferLogRecord
    {
        string DateTime;
        string SourceAccountNumber;
        string DestinationAccountNumber;
        float Amount;
        float srcBalanceAfter;
        float destBalanceAfter;
        string UserName;

    };


	clsBankClient(enMode mode, string first, string last, string email, string phone, string accountnumber, string pincode, float accountbalance)
		:clsPerson(first, last, email, phone) {
		_Mode = mode;
		_AccountNumber = accountnumber;
		_PinCode = pincode;
		_AccountBalance = accountbalance;
	}
    bool IsEmpty()
    {
        return (_Mode == enMode::EmptyMode);
    }


    string AccountNumber()
    {
        return _AccountNumber;
    }

    void SetPinCode(string PinCode)
    {
        _PinCode = PinCode;
    }

    string GetPinCode()
    {
        return _PinCode;
    }
    __declspec(property(get = GetPinCode, put = SetPinCode)) string PinCode;

    void SetAccountBalance(float AccountBalance)
    {
        _AccountBalance = AccountBalance;
    }

    float GetAccountBalance()
    {
        return _AccountBalance;
    }
    __declspec(property(get = GetAccountBalance, put = SetAccountBalance)) float AccountBalance;
    bool MarkForDelete() {
        return _MarkForDelete;
    }
    void Print()
    {
        cout << "\nClient Card:";
        cout << "\n___________________";
        cout << "\nFirstName   : " << FirstName;
        cout << "\nLastName    : " << LastName;
        cout << "\nFull Name   : " << GetFullName();
        cout << "\nEmail       : " << Email;
        cout << "\nPhone       : " << Phone;
        cout << "\nAcc. Number : " << _AccountNumber;
        cout << "\nPassword    : " << _PinCode;
        cout << "\nBalance     : " << _AccountBalance;
        cout << "\n___________________\n";

    }
    static clsBankClient Find(string AccountNumber) {
        fstream MyFile;
        MyFile.open(FileName, ios::in);
        if (MyFile.is_open()) {
            string line;
            while (getline(MyFile, line)) {
                clsBankClient Client = _ConvertLinetoClientObject(line, "#//#");
                if (Client.AccountNumber() == AccountNumber) {
                    MyFile.close();
                    return Client;
                }
            }
        }
        MyFile.close();
        return _GetEmptyClientObject();
    }
    static bool IsClientExist(string accountnum) {
        clsBankClient Client1 = clsBankClient::Find(accountnum);
        return (!Client1.IsEmpty());
    }
    enum enSaveResult{ svFaildEmptyObject = 0, svSucceeded = 1, svFaildAccountNumberExists =2 };
    enSaveResult Save(clsBankClient Client) {
        switch (_Mode) {
        case enMode::EmptyMode:return enSaveResult::svFaildEmptyObject;break;
        case enMode::UpdateMode:_Update(Client);return enSaveResult::svSucceeded;
        case enMode::AddMode:
        {
            //This will add new record to file or database
            if (clsBankClient::IsClientExist(_AccountNumber))
            {
                return enSaveResult::svFaildAccountNumberExists;
            }
            else
            {
                _AddNew(Client);

                //We need to set the mode to update after add new
                _Mode = enMode::UpdateMode;
                return enSaveResult::svSucceeded;
            }

            break;
        }
        }
    }
    static clsBankClient GetAddNewClientObject(string AccountNumber) {
        return clsBankClient(enMode::AddMode, "", "", "", "", AccountNumber, "", 0);
    }
     bool Delete(clsBankClient Client) {
        vector<clsBankClient>all = _LoadDataFromFile();
        for (clsBankClient& t : all) {
            if (t.AccountNumber() == Client.AccountNumber()) {
                t._MarkForDelete = true;break;
            }
        }_LoadDataToFile(all);
        *this = _GetEmptyClientObject();
        return true;
    }
     static vector<clsBankClient> GitClientList() {
         return _LoadDataFromFile();
     }
     static double GetTotalBalances() {
         vector<clsBankClient>vClient = GitClientList();
         double total = 0;
         for (clsBankClient& t : vClient) {
             total += t.AccountBalance;
         }return total;
     }
     void Deposit(double Amount,clsBankClient &Client) {
         _AccountBalance += Amount;
         Save(Client);
     }
     bool Withdraw(double Amount)
     {
         if (Amount > _AccountBalance)
         {
             return false;
         }
         else
         {
             _AccountBalance -= Amount;
             Save(*this);
             return true;
         }

     }
     bool Transfer(float Amount, clsBankClient& DestinationClient,string UserName)
     {
         if (Amount > AccountBalance)
         {
             return false;
         }

         Withdraw(Amount);
         DestinationClient.Deposit(Amount,DestinationClient);
         _RegisterTransferLog(Amount, DestinationClient,UserName );

         return true;
     }

     static  vector <stTrnsferLogRecord> GetTransfersLogList() {
         vector<stTrnsferLogRecord>vTransferLog;
         fstream MyFile;MyFile.open("TransferLog", ios::in);
         if (MyFile.is_open()) {
             string line;
             while (getline(MyFile, line)) {
                 vTransferLog.push_back(_ConvertTransferLogLineToRecord(line, "#//#"));
             }MyFile.close();
         }return vTransferLog;
     }
    
     
};

