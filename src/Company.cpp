#include "Company.hpp"
#include <random>
#include <memory.h>

Company::Company()
{
	// Fills the data array with empty data
	memset(&m_companyData, 0, sizeof(m_companyData));
}

void Company::InitialiseCompany(CompanyType pType, string pName, uint32 pStartValue)
{
	m_type = pType;
	m_name = pName;
	m_companyData[0] = m_currentValue = pStartValue;
	m_ownedStocks = 0;
}

void Company::UpdateCompanyValue(float pMin, float pMax)
{
	// TODO: Fuck the line below me
	uint32 newValue = (uint32)(m_currentValue * ((pMax - pMin) * ((float)(rand() % 1000) / 1000) + pMin));
	if (m_currentValue + newValue > 0/* && m_currentValue + newValue < 1000*/)
	{
		m_currentValue += newValue;

		// Replaces each value in the array with the one before it to shift the whole array
		for (uint8 i = WIDTH - 2; i > 0; i--)
		{
			m_companyData[i] = m_companyData[i - 1];
		}

		m_companyData[0] = m_currentValue;
	}
}

char Company::GetDataFromArray(
	const uint32 inMaxValue,
	const uint8 inHorizontal,
	uint8 inVertical
) noexcept
{
	// The lines are drawn between the values
	// (Should be from 0 to DETAIL-1 but done this way to prevent clipping)
	// Inverts vertical from DETAIL-1 to 0 to 0 to DETAIL
	inVertical = DETAIL - inVertical;
	// 0 to m_maxValue value is scaled to 0 to DETAIL
	uint32 leftValue = (uint32)(GetCompanyData()[WIDTH - 2 - inHorizontal] / (float)(inMaxValue / DETAIL));
	uint32 rightValue = (uint32)(GetCompanyData()[WIDTH - 3 - inHorizontal] / (float)(inMaxValue / DETAIL));

	if (GetCompanyData()[WIDTH - 2 - inHorizontal] == 0)
		return ' ';
	else if (leftValue == inVertical && leftValue == rightValue)
		return '_';
	else if (leftValue == inVertical && leftValue < rightValue)
		return '/';
	else if (leftValue == inVertical + 1U && leftValue > rightValue)
		return '\\';
	else
		return ' ';
}

void Company::ModifyOwnedStocks(uint32 pDifference)
{ m_ownedStocks += pDifference; }

CompanyType Company::GetType() const
{ return m_type; }

string Company::GetName() const
{ return m_name; }

uint32 *Company::GetCompanyData()
{ return m_companyData; }

uint32 Company::GetCurrentValue() const
{ return m_currentValue; }

uint32 Company::GetOwnedStocks() const
{ return m_ownedStocks; }
