#pragma once
#include "GameDefines.hpp"

// Singular state machine controls the flow of the game
enum class GameState: uint8
{
	Clear,
	GameOver,
	Invalid,
	Info,
	Help,
	EndDay,
	Goto,
	Select,
	Buy,
	Sell
};

// The different types of companies avaliable
enum class CompanyType: uint8
{
	UNDEFINED,
	Flat,
	Growth,
	UpNDown,
	FalseHope,
	TwinPeaks
};
