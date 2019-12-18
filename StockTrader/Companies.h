/*---------------------------------------------------
	File Name: Companies.h
	Author: Dylan Glenister
	Modified: 17/12/19 (dd/mm/yy)

	The player buys stocks into companies and as the
		value of the company goes up and down the player
		can sell their stock or buy more to gain money.
---------------------------------------------------*/

#pragma once
#include "GameDefines.h"
#include <string>

using std::string;

//Structure for the graphs
struct Point2D
{
	short y;
	short x;
};

class Companies
{
	// Functions
public:
	Companies();
	~Companies();

	void InitializeCompany(int pType, string pName);	//Starts up the company with default values
	int GetType();													//Returns the type of company
	string GetName();												//Returns the name of the company
	int GetCurrentValue();										//Retruns the value of the company
	void UpdateValue();											//Updates the value of the company
	void UpdateCompGraph();									//Updates the graph of the company

	// Variables
public:
	char m_companyArray[20][78];		//The array used by each individual company

private:
	char m_type;					//The type of company (int between 1-5)
	int m_startValue;				//The starting value of the company when initialised
	int m_currentValue;			//The current value of the company
	int m_previousValue;			//Interger used to assist in the updating of the graph
	int m_arrHelper;				//Interger used to assist in the updating of the graph
	Point2D m_pos;				//The position in the graph
	string m_name;				//The name of the company
};
