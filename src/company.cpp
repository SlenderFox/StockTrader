#include "company.hpp"
#include <random>
#include <memory.h>

company::company()
{
	// Fills the data array with empty data
	memset(&m_companyData, 0, sizeof(m_companyData));
}

void company::initialiseCompany(
	companyType inType,
	std::string inName,
	uint32 inStartValue
)
{
	m_type = inType;
	m_name = inName;
	m_companyData[0] = m_currentValue = inStartValue;
	m_ownedStocks = 0;
}

void company::updateCompanyValue(float inMin, float inMax)
{
	// TODO: Fuck the line below me
	uint32 newValue = (uint32)(m_currentValue * ((inMax - inMin) * ((float)(rand() % 1000) / 1000) + inMin));
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

char company::getDataFromArray(
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
	uint32 leftValue = (uint32)(getCompanyData()[WIDTH - 2 - inHorizontal] / (float)(inMaxValue / DETAIL));
	uint32 rightValue = (uint32)(getCompanyData()[WIDTH - 3 - inHorizontal] / (float)(inMaxValue / DETAIL));

	if (getCompanyData()[WIDTH - 2 - inHorizontal] == 0)
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

void company::modifyOwnedStocks(uint32 inDifference)
{ m_ownedStocks += inDifference; }

companyType company::getType() const
{ return m_type; }

std::string company::getName() const
{ return m_name; }

uint32 *company::getCompanyData()
{ return m_companyData; }

uint32 company::getCurrentValue() const
{ return m_currentValue; }

uint32 company::getOwnedStocks() const
{ return m_ownedStocks; }
