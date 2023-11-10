#include "../h/timer.h"

Timer::Timer() {
    start = std::chrono::steady_clock::now(); 
}


int Timer::getPassedTime() {

    auto end = std::chrono::steady_clock::now();

    auto elapsedTime = std::chrono::duration_cast<std::chrono::seconds>(end - start);
    int timePassed = elapsedTime.count(); 
    
    return timePassed;
}