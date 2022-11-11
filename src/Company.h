#pragma once
#include "GameDefines.h"
#include <string>

using std::string;

class Company
{
	// Functions
public:
	Company();
	~Company() {}

	// Starts up the company with default values
	void InitialiseCompany(CompanyType pType, string pName, unsigned short pStartValue);
	// Updates the value of the company
	void UpdateCompanyValue(float pMin, float pMax);

	// Adds or removes owned stocks
	void ModifyOwnedStocks(int pDifference) { m_ownedStocks += pDifference; }
	// Returns the type of company
	CompanyType GetType() const { return m_type; }
	// Returns the name of the company
	string GetName() const { return m_name; }
	// Returns the company data array
	unsigned int* GetCompanyData() { return m_companyData; }
	// Returns the value of the company
	unsigned int GetCurrentValue() const { return m_currentValue; }
	// Returns the amount of stocks currently owned in the company
	unsigned int GetOwnedStocks() { return m_ownedStocks; }

	// Variables
private:
	CompanyType m_type = CompanyType::UNDEFINED;	// The type of company, determining how the value changes over time
	string m_name = "UNDEFINED";					// The name of the company
	unsigned int m_companyData[WIDTH - 1] = {};		// An array of previous values used to generate the graph (the width is correct)
	unsigned int m_currentValue = 0;				// The current value of the company
	unsigned int m_ownedStocks = 0;					// The amount of stocks owned in the current company
};
