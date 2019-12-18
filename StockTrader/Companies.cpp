/*---------------------------------------------------
	File Name: Companies.cpp
	Author: Dylan Glenister
	Modified: 17/12/19 (dd/mm/yy)
---------------------------------------------------*/

#include "Companies.h"
#include <random>

Companies::Companies() : m_type(0), m_startValue(0), m_currentValue(0), 
	m_previousValue(0), m_arrHelper(0), m_pos({ 0, 0 }), m_name("")
{
	for (int x = 0; x < 20; x++)
	{
		for (int y = 0; y < 78; y++)
		{
			m_companyArray[x][y] = ' ';
		}
	}
}

Companies::~Companies()
{
}

void Companies::InitializeCompany(int pType, string pName)
{
	m_currentValue = m_startValue;
	m_previousValue = 19;
	m_type = pType;
	m_name = pName;

	for (int x = 0; x < 20; x++)
	{
		for (int y = 0; y < 78; y++)
		{
			m_companyArray[x][y] = ' ';
		}
	}
}

int Companies::GetType() { return m_type; }

string Companies::GetName() {return m_name; }

int Companies::GetCurrentValue() { return m_currentValue; }

void Companies::UpdateValue()
{
	int newValue;
	int oldTemp = m_currentValue;
	newValue = -25 + rand() % 75;
	if ((oldTemp += newValue) < 1000 && (oldTemp += newValue) > 0)
	{
		m_currentValue += newValue;
	}
}

void Companies::UpdateCompGraph()
{
	// Converts the 0-1000 value into 0-20 for ease of use in graph updating
	int tempValue = m_currentValue;
	tempValue = 19 - (tempValue / 50); //Fix this

	// Every position except the furthest right colomn of the graph
	if (m_arrHelper < 78)
	{
		m_pos.y = (tempValue);
		m_pos.x = m_arrHelper;
		m_arrHelper++;
	}
	// If the function is updating the furthest right colomn of the graph
	else
	{
		m_pos.x = 77;
		m_pos.y = (tempValue);

		for (int x = 0; x < 78; x++)
		{
			for (int y = 0; y < 20; y++)
			{
				if (x < 77)
				{
					// Moves every character on the array left one position
					m_companyArray[y][x] = m_companyArray[y][x + 1];
				}
				else
				{
					// Clears the furthest right colomn
					m_companyArray[y][x] = ' ';
				}
			}
		}
	}

	// Enters the correct character into the array to show the price change
	if (tempValue == m_previousValue)
	{
		m_companyArray[m_pos.y][m_pos.x] = '_';
	}
	else if (tempValue < m_previousValue)
	{
		m_companyArray[m_pos.y + 1][m_pos.x] = '/';
	}
	else if (tempValue > m_previousValue)
	{
		m_companyArray[m_pos.y][m_pos.x] = '\\';
	}
	m_previousValue = tempValue;
}
