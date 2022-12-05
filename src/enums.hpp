#pragma once
#include "typeDefines.hpp"

/** Singular state machine controls the flow of the game */
enum class gameState: uint8
{
	clear,
	gameOver,
	invalid,
	info,
	help,
	endDay,
	gotoDay,
	select,
	buy,
	sell
};

/** The different types of companies avaliable */
enum class companyType: uint8
{
	undefined,
	flat,
	growth,
	upAndDown,
	falseHope,
	twinPeaks
};
