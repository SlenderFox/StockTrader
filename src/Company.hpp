#pragma once
#include "GameDefines.hpp"
#include <string>

using std::string;

class Company
{
public:
	// The different types of companies avaliable
	enum class Type: uint8
	{
		UNDEFINED,
		Flat,
		Growth,
		UpNDown,
		FalseHope,
		TwinPeaks
	};

private:
	// The type of company, determining how the value changes over time
	Type m_type = Type::UNDEFINED;
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
	void InitialiseCompany(
		Type pType,
		string pName,
		uint32 pStartValue
	);
	// Updates the value of the company
	void UpdateCompanyValue(float pMin, float pMax);

	// Adds or removes owned stocks
	void ModifyOwnedStocks(uint32 pDifference);
	// Returns the type of company
	Type GetType() const;
	// Returns the name of the company
	string GetName() const;
	// Returns the company data array
	uint32 *GetCompanyData();
	// Returns the value of the company
	uint32 GetCurrentValue() const;
	// Returns the amount of stocks currently owned in the company
	uint32 GetOwnedStocks() const;
};
