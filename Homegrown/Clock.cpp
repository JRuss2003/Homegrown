#include "Clock.h"
#include <iostream>
void Clock::Tick()
{
	auto now = std::chrono::steady_clock::now();
	deltaTime = std::chrono::duration_cast<std::chrono::microseconds>(now - previousTime).count() / 100000.0f;
	previousTime = now;
}
