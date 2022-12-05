#include "io.hpp"
#include <iostream>

using std::cout;

char *io::bufferA = nullptr;
char *io::bufferB = nullptr;
char *io::activeBuffer = nullptr;

void io::SwapBuffers() noexcept
{
	if (activeBuffer == bufferA) activeBuffer = bufferB;
	if (activeBuffer == bufferB) activeBuffer = bufferA;
}
