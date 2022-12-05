#pragma once
#include "company.hpp"

class io
{
	static char *bufferA;
	static char *bufferB;
	static char *activeBuffer;

public:
	static void SwapBuffers() noexcept;
};
