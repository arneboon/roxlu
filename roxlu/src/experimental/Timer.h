#ifndef ROXLU_TIMERH
#define ROXLU_TIMERH

// NO! POCO!!

#include "sys/time.h"
//#include "Poco/Timer.h"
//#include "Poco/Thread.h"

//using Poco::TimerCallback;

namespace roxlu {

//template<typename T>
class Timer {	
public: 
	Timer()
//		:timer(NULL)
	{
	}
	
	~Timer() {
//		stop();
//		if(timer != NULL) {
//			delete timer;	
//		}
	}
	
	// returns millis since first call.
	static uint64_t millis() {
		static uint64_t t = Timer::now();
		return Timer::now() - t;
	}	
				
	// now in millis
	static uint64_t now() {
		timeval time;
		gettimeofday(&time, NULL);
		uint64_t n = time.tv_usec;
		n /= 1000; // convert seconds to millis
		n += (time.tv_sec * 1000); // convert micros to millis
		return n;
	}
	
	void stop() {
//		if(timer != NULL) {
//			timer->stop();
//		}
	}
	
//	void onTimer(Poco::Timer& t) {
//		callback->onTimer();	
//	}
	
//	void start(T& callbackObject, long startDelay, long interval) {
//		callback = &callbackObject;
//		timer = new Poco::Timer(startDelay, interval);
//		timer->start(TimerCallback<roxlu::Timer<T> >(*this, &roxlu::Timer<T>::onTimer));
//	}
	
//	Poco::Timer* timer;
//	T* callback;
}; // class Timer
}; // roxlu


#endif