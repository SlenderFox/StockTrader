/*---------------------------------------------------
	File Name: Companies.h
	Author: Dylan Glenister
	Modified: 20/12/19 (dd/mm/yy)

	A company has stocks of varying value that the
		player can buy and sell in an attempt to turn a
		profit
---------------------------------------------------*/

#pragma once
#include "GameDefines.h"
#include <string>

using std::string;

class Companies
{
	// Functions
public:
	Companies();
	~Companies();

	void InitializeCompany(byte, string, unsigned short);	//Starts up the company with default values

	void UpdateValue();				//Updates the value of the company
	void UpdateCompanyData();	//Updates the company data array

	byte GetType() const { return m_type; }						//Returns the type of company
	byte* GetCompanyData() { return m_companyData; }	//Returns the company data array
	int GetCurrentValue() const { return m_currentValue; }	//Returns the value of the company
	string GetName() const { return m_name; }					//Returns the name of the company

	// Variables
private:
	byte m_type;									//The type of company (int between 0-5)
	byte m_companyData[WIDTH - 2];		//The array used by each individual company
	unsigned short m_currentValue;			//The current value of the company
	string m_name;								//The name of the company
};
