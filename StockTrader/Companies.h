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
	~Companies() {}

	void InitializeCompany(CompanyType, string, unsigned short);	//Starts up the company with default values

	void UpdateCompanyValue(byte, byte);	//Updates the value of the company

	CompanyType GetType() const { return m_type; }				//Returns the type of company
	unsigned int* GetCompanyData() { return m_companyData; }	//Returns the company data array
	int GetCurrentValue() const { return m_currentValue; }		//Returns the value of the company
	string GetName() const { return m_name; }					//Returns the name of the company

	// Variables
private:
	CompanyType m_type;							//The type of company, determining how the value changes over time
	unsigned int m_companyData[WIDTH - 1];	//An array of previous values used to generate the graph (the width is correct)
	unsigned int m_currentValue;				//The current value of the company
	string m_name;								//The name of the company
};
