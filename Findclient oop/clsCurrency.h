#pragma once
#include<iostream>
#include<vector>
#include"clsString.h"
#include<string>
#include<fstream>
using namespace std;
class clsCurrency
{
private:
	enum enMode { EmptyMode = 0, UpdateMode = 1 };
	enMode _Mode;

	string _Country;
	string _CurrencyCode;
	string _CurrencyName;
	float _Rate;

	static string _ConverCurrencyObjectToLine(clsCurrency Currency, string Seperator = "#//#") {
		string CurrencyString = "";
		CurrencyString += Currency.Country() + Seperator;
		CurrencyString += Currency.CurrencyCode() + Seperator;
		CurrencyString += Currency.CurrencyName() + Seperator;
		CurrencyString += to_string(Currency.Rate());
		return CurrencyString;


	}
	static clsCurrency _ConvertLinetoCurrencyObject(string Line, string Seperator = "#//#") {
		vector<string>vLine = clsString::Split(Line,Seperator);
		return clsCurrency(enMode::UpdateMode, vLine[0], vLine[1], vLine[2], stod(vLine[3]));
	}
	static  vector <clsCurrency> _LoadCurrencysDataFromFile() {
		vector <clsCurrency> vCurrencys;
		fstream MyFile;
		MyFile.open("Currencies.txt", ios::in);
		if (MyFile.is_open()) {
			string line;
			while (getline(MyFile, line)) {
				vCurrencys.push_back(_ConvertLinetoCurrencyObject(line, "#//#"));
			}MyFile.close();
		}return vCurrencys;
	}
	static void _SaveCurrencyDataToFile(vector <clsCurrency> vCurrencys) {
		fstream MyFile;
		MyFile.open("Currencies.txt", ios::out);
		if (MyFile.is_open()) {
			for (clsCurrency& C : vCurrencys) {
				MyFile << _ConverCurrencyObjectToLine(C, "#//#") << endl;
			}MyFile.close();
		}
	}
	void _Update()
	{
		vector <clsCurrency> _vCurrencys;
		_vCurrencys = _LoadCurrencysDataFromFile();

		for (clsCurrency& C : _vCurrencys)
		{
			if (C.CurrencyCode() == CurrencyCode())
			{
				C = *this;
				break;
			}

		}

		_SaveCurrencyDataToFile(_vCurrencys);

	}

	static clsCurrency _GetEmptyCurrencyObject()
	{
		return clsCurrency(enMode::EmptyMode, "", "", "", 0);
	}
public:
	clsCurrency(enMode Mode, string Country, string CurrencyCode, string CurrencyName, float Rate) {
		_Mode = Mode;
		_Country = Country;
		_CurrencyCode = CurrencyCode;
		_CurrencyName = CurrencyName;
		_Rate = Rate;
	}
	string Country()
	{
		return _Country;
	}

	string CurrencyCode()
	{
		return _CurrencyCode;
	}

	string CurrencyName()
	{
		return _CurrencyName;
	}

	float Rate() {
		return _Rate;
	}
	void UpdateRate(float NewRate)
	{
		_Rate = NewRate;
		_Update();
	}
	static vector <clsCurrency> GetAllUSDRates()
	{

		return _LoadCurrencysDataFromFile();

	}

	bool IsEmpty()
	{
		return (_Mode == enMode::EmptyMode);
	}

	static   clsCurrency FindByCode(string CurrencyCode) {
		CurrencyCode = clsString::UpperAllString(CurrencyCode);
		fstream MyFile;
		MyFile.open("Currencies.txt", ios::in);
		if (MyFile.is_open()) {
			string line;
			while (getline(MyFile, line)) {
				clsCurrency C = _ConvertLinetoCurrencyObject(line, "#//#");
				if (C.CurrencyCode() == CurrencyCode) {
					MyFile.close();
					return C;
				}
					
			}
		}return _GetEmptyCurrencyObject();
	}
	static   clsCurrency FindByCountry(string Country) {
		Country = clsString::UpperAllString(Country);
		fstream MyFile;
		MyFile.open("Currencies.txt", ios::in);
		if (MyFile.is_open()) {
			string line;
			while (getline(MyFile, line)) {
				clsCurrency C = _ConvertLinetoCurrencyObject(line, "#//#");
				if (C.Country() == Country) {
					MyFile.close();
					return C;
				}
			}
		}return _GetEmptyCurrencyObject();
	}
	static bool IsCurrencyExist(string CurrencyCode)
	{
		clsCurrency C1 = clsCurrency::FindByCode(CurrencyCode);
		return (!C1.IsEmpty());

	}

	static vector <clsCurrency> GetCurrenciesList()
	{
		return _LoadCurrencysDataFromFile();
	}
	float ConvertToUSD(float Amount)
	{
		return (float)(Amount / Rate());
	}

	float ConvertToOtherCurrency(float Amount, clsCurrency Currency2)
	{
		float AmountInUSD = ConvertToUSD(Amount);

		if (Currency2.CurrencyCode() == "USD")
		{
			return AmountInUSD;
		}

		return (float)(AmountInUSD * Currency2.Rate());

	}
};

