/*---------------------------------------------------
	Filename: Company.cpp
	Author: Dylan Glenister
	Modified: 25/02/21 (dd/mm/yy)
---------------------------------------------------*/

#include "Company.h"
#include <random>

Company::Company() : m_type(CompanyType::UNDEFINED), m_name("UNDEFINED"), m_currentValue(0), m_ownedStocks(0)
{
	// Fills the data array with empty data
	for (byte i = 0; i < WIDTH - 1; i++)
	{
		m_companyData[i] = NULL;
	}
}

void Company::InitialiseCompany(CompanyType pType, string pName, unsigned short pStartValue)
{
	m_type = pType;
	m_name = pName;
	m_companyData[0] = m_currentValue = pStartValue;
	m_ownedStocks = 0;
}

void Company::UpdateCompanyValue(float pMin, float pMax)
{
	int newValue = (int)(m_currentValue * ((pMax - pMin) * ((float)(rand() % 1000) / 1000) + pMin));
	if (m_currentValue + newValue > 0/* && m_currentValue + newValue < 1000*/)
	{
		m_currentValue += newValue;

		// Replaces each value in the array with the one before it to shift the whole array
		for (byte i = WIDTH - 2; i > 0; i--)
		{
			m_companyData[i] = m_companyData[i - 1];
		}

		m_companyData[0] = m_currentValue;
	}
}
