/*---------------------------------------------------
	File Name: Companies.cpp
	Author: Dylan Glenister
	Modified: 20/12/19 (dd/mm/yy)
---------------------------------------------------*/

#include "Companies.h"
#include <random>

Companies::Companies() : m_type(UNDEFINED), m_currentValue(0), m_name("UNDEFINED")
{
	for (byte i = 0; i < WIDTH - 2; i++)
	{
		m_companyData[i] = 0;
	}
}

Companies::~Companies()
{
}

void Companies::InitializeCompany(byte pType, string pName, unsigned short pStartValue)
{
	m_type = pType;
	m_name = pName;
	m_currentValue = pStartValue;

	// Resets the data graph
	for (byte i = 0; i < WIDTH - 2; i++)
	{
		m_companyData[i] = 0;
	}
}

void Companies::UpdateValue()
{
	byte newValue = -25 + rand() % 50;
	if ((m_currentValue + newValue) < 1000 && (m_currentValue + newValue) > 0)
	{
		m_currentValue += newValue;
	}
}

void Companies::UpdateCompanyData()
{
	// Shifts all the current data down the array 1 place
	for (byte i = 0; i < WIDTH - 3; i++)
	{
		m_companyData[i + 1] = m_companyData[i];
	}

	// Inserts the newest value at the beginning
	m_companyData[0] = m_currentValue;
}

//void Companies::UpdateCompanyData()
//{
//	// Converts the 0-1000 value into 0-20 for ease of use in graph updating
//	int tempValue = m_currentValue;
//	tempValue = 20 - (tempValue / 50); //Fix this
//
//	// Every position except the furthest right colomn of the graph
//	if (m_arrHelper < 78)
//	{
//		m_pos.y = (tempValue);
//		m_pos.x = m_arrHelper;
//		m_arrHelper++;
//	}
//	// If the function is updating the furthest right colomn of the graph
//	else
//	{
//		m_pos.x = 77;
//		m_pos.y = (tempValue);
//
//		for (int x = 0; x < 78; x++)
//		{
//			for (int y = 0; y < 20; y++)
//			{
//				if (x < 77)
//				{
//					// Moves every character on the array left one position
//					m_companyData[y][x] = m_companyData[y][x + 1];
//				}
//				else
//				{
//					// Clears the furthest right colomn
//					m_companyData[y][x] = ' ';
//				}
//			}
//		}
//	}
//
//	// Enters the correct character into the array to show the price change
//	if (tempValue == m_previousValue)
//	{
//		m_companyData[m_pos.y][m_pos.x] = '_';
//	}
//	else if (tempValue < m_previousValue)
//	{
//		m_companyData[m_pos.y + 1][m_pos.x] = '/';
//	}
//	else if (tempValue > m_previousValue)
//	{
//		m_companyData[m_pos.y][m_pos.x] = '\\';
//	}
//	m_previousValue = tempValue;
//}
