#pragma once
#include <chrono> 

namespace Time
{
	using Clock = std::chrono::high_resolution_clock; 
	using TimePoint = std::chrono::time_point<Clock>; 
	using Duration = std::chrono::duration<float>; 

	class GlobalTimer
	{
	public: 
		static GlobalTimer& GetInstance(); 

		void Initiailize(); 
		void update(); 

		float getDeltaTime() const; 
		float getTotalTime() const; 

	private: 
		GlobalTimer(); 

		TimePoint start; 
		TimePoint last; 
		float deltaTime; 
		float totalTime; 
	};

	void InitTime(); 
	void updateTime(); 
	float getdeltaTime(); 
	float gettotalTime(); 

	template<typename Tag = void>
	class Timer
	{
	public: 
		Timer() { Reset(); }

		void Reset() { start = Clock::now(); }

		float Elapssed() const { return std::chrono::duration_cast<Duration>(Clock::now() - start).count(); }

		bool isElapssed(float seconds) const 
		{
			return Elapssed() >= seconds;
		}

	private: 
		TimePoint start; 
	};

}

