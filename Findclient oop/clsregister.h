#pragma once
#include<iostream>
#include"clsUser.h"
#include"clsDate.h"
#include<fstream>
#include"clsString.h"
#include<iomanip>
#include"clsUser.h"
using namespace std;
class clsregister : clsScreen
{
private:
	string _DateandTime = clsDate::GetSystemDateTimeString();
	string _UserName;
	string _Password;
	int _Permission;

	 string _ConvertRegisterToString(string seperator="#//#") {
		string LoginRecord = "";
		LoginRecord += clsDate::GetSystemDateTimeString() + seperator;
		LoginRecord += _UserName + seperator;
		LoginRecord += clsUser::Encryption(_Password,2)+ seperator;
		LoginRecord += to_string(_Permission);
		return LoginRecord;
	}
	 static clsregister _ConvertLoginRegisterLineToRecord(string Line, string Seperator = "#//#")
	 {
		 clsregister LoginRegisterRecord;


		 vector <string> LoginRegisterDataLine = clsString::Split(Line, Seperator);
		 LoginRegisterRecord.DateandTime = LoginRegisterDataLine[0];
		 LoginRegisterRecord._UserName = LoginRegisterDataLine[1];
		 LoginRegisterRecord.Password = clsUser::Decryption(LoginRegisterDataLine[2],2);
		 LoginRegisterRecord._Permission = stoi(LoginRegisterDataLine[3]);

		 return LoginRegisterRecord;

	 }
	static vector<clsregister>_LoadRegisterDataFromFile() {
		vector<clsregister>allRegister;
		fstream MyFile;
		MyFile.open("LoginRegister.txt", ios::in);
		if (MyFile.is_open()) {
			string line;
			while (getline(MyFile, line)) {
				allRegister.push_back(_ConvertLoginRegisterLineToRecord(line,"#//#"));
			}MyFile.close();
		}return allRegister;
	}
	static void _printRecord(clsregister reg) {
		cout << setw(8) << left << "|" << setw(35) << left << reg._DateandTime;
		cout << "|" << setw(20) << left << reg._UserName;
		cout << "|" << setw(20) << left << reg._Password;
		cout << "|" << setw(15) << left << reg._Permission;
	}

public:

	static vector<clsregister>GetRegisterUserList() {
		return _LoadRegisterDataFromFile();
	}
	void SetDate(string date) {
		_DateandTime = date;
	}
	string GetDateandTime() {
		return _DateandTime;
	}
	__declspec(property(get = GetDateandTime, put = SetDate)) string DateandTime;
	void SetPassWord(string Password)
	{
		_Password = Password;
	}
	string GetPassword()
	{
		return _Password;
	}
	__declspec(property(get = GetPassWord, put = SetPassWord)) string Password;
	void SetPermission(short Permission)
	{
		_Permission = Permission;
	}
	short GetPermission()
	{
		return _Permission;
	}
	void setUserName(string UserName)
	{
		_UserName = UserName;
	}
	string GetUserName()
	{
		return _UserName;
	}
	__declspec(property(get = GetUserName, put = SetUserName)) string UserName;
	static void ShowRegisterScreen() {
		if (!CheckAccessRights(clsUser::pLoginRegister)) {
			return;
		}

		vector<clsregister>vUsers = GetRegisterUserList();
		string Title = "\t  Login Register List Screen";
		string SubTitle = "\t    (" + to_string(vUsers.size()) + ") Record(s).";

		_DrawScreenHeader(Title, SubTitle);
		cout << setw(8) << left << "" << "\n\t_______________________________________________________";
		cout << "______________________________________________\n" << endl;
		cout << setw(8) << left << "" << "| " << left << setw(35) << "Date/Time";
		cout << "| " << left << setw(20) << "UserName";
		cout << "| " << left << setw(20) << "PassWord";
		cout << "| " << left << setw(15) << "Permission";
		cout << setw(8) << left << "" << "\n\t_______________________________________________________";
		cout << "______________________________________________\n" << endl;

		if (vUsers.size() == 0)
			cout << "\t\t\t\tNo Register Record In the System!";
		else

			for (clsregister& U : vUsers)
			{

				_printRecord(U);
				cout << endl;
			}

		cout << setw(8) << left << "" << "\n\t_______________________________________________________";
		cout << "______________________________________________\n" << endl;
	}
	
};

