#pragma once

#if defined(WIN32) || defined(_WIN32)

	#define WIN32_LEAN_AND_MEAN
	#define UNICODE
	#define STRICT

	#ifdef NOMINMAX
		#include <Windows.h>
	#else
		#define NOMINMAX
		#include <Windows.h>
	#endif

	#undef WIN32_LEAN_AND_MEAN
	#undef UNICODE
	#undef STRICT
#endif
