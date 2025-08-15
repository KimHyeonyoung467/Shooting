#include "pch.h"
#include "Timer.h"

namespace Time
{
	GlobalTimer::GlobalTimer() : start(), last(), deltaTime(0.0f), totalTime(0.0f) {}

	GlobalTimer& GlobalTimer::GetInstance() {
		static GlobalTimer instance;
		return instance;
	}

	void GlobalTimer::Initiailize()
	{
		start = Clock::now();
		last = start;
	}
	void GlobalTimer::update()
	{
		TimePoint now = Clock::now();
		deltaTime = std::chrono::duration_cast<Duration>(now - last).count();
		totalTime = std::chrono::duration_cast<Duration>(now - start).count();
		last = now;
	}

	float GlobalTimer::getDeltaTime() const { return deltaTime; }
	float GlobalTimer::getTotalTime() const { return totalTime; }

	void InitTime() { GlobalTimer::GetInstance().Initiailize(); }
	void updateTime() { GlobalTimer::GetInstance().update(); }
	float getdeltaTime() { return GlobalTimer::GetInstance().getDeltaTime(); }
	float gettotalTime() { return GlobalTimer::GetInstance().getTotalTime(); }
}