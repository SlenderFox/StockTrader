#pragma once
#include "GameDefines.hpp"
#include <string>

using std::string;

class Company
{
	// The type of company, determining how the value changes over time
	CompanyType m_type = CompanyType::UNDEFINED;
	// The name of the company
	string m_name = "UNDEFINED";
	// An array of previous values used to generate the graph (the width is correct)
	uint32 m_companyData[WIDTH - 1] = {};
	// The current value of the company
	uint32 m_currentValue = 0;
	// The amount of stocks owned in the current company
	uint32 m_ownedStocks = 0;

public:
	Company();
	~Company() {}

	// Starts up the company with default values
	void InitialiseCompany(CompanyType pType, string pName, uint32 pStartValue);
	// Updates the value of the company
	void UpdateCompanyValue(float pMin, float pMax);

	// Adds or removes owned stocks
	void ModifyOwnedStocks(uint32 pDifference) { m_ownedStocks += pDifference; }
	// Returns the type of company
	CompanyType GetType() const { return m_type; }
	// Returns the name of the company
	string GetName() const { return m_name; }
	// Returns the company data array
	uint32* GetCompanyData() { return m_companyData; }
	// Returns the value of the company
	uint32 GetCurrentValue() const { return m_currentValue; }
	// Returns the amount of stocks currently owned in the company
	uint32 GetOwnedStocks() const { return m_ownedStocks; }
};
