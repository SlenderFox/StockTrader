/*---------------------------------------------------
	File Name: Companies.cpp
	Author: Dylan Glenister
	Modified: 20/12/19 (dd/mm/yy)
---------------------------------------------------*/

#include "Companies.h"
#include <random>

Companies::Companies() : m_type(CompanyType::UNDEFINED), m_currentValue(0), m_name("UNDEFINED")
{
	// Fills the data array with empty data
	for (byte i = 0; i < WIDTH - 1; i++)
	{
		m_companyData[i] = NULL;
	}
}

void Companies::InitializeCompany(CompanyType pType, string pName, unsigned short pStartValue)
{
	m_type = pType;
	m_name = pName;
	m_currentValue = pStartValue;

	// Resets the data array
	for (byte i = 0; i < WIDTH - 1; i++)
	{
		m_companyData[i] = NULL;
	}
}

void Companies::UpdateCompanyValue(byte pFloor, byte pRange)
{
	byte newValue = pFloor + rand() % pRange;
	if ((m_currentValue + newValue) < 1000 && (m_currentValue + newValue) > 0)
	{
		m_currentValue += newValue;

		// Shifts all the current data down the array 1 place
		for (byte i = WIDTH - 2; i > 0; i--)
		{
			m_companyData[i] = m_companyData[i - 1];
		}

		// Inserts the newest value at the beginning
		m_companyData[0] = m_currentValue;
	}
}
