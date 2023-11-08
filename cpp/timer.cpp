#include "../h/timer.h"

Timer::Timer() {
    start = std::chrono::steady_clock::now(); 
}


int Timer::getPassedTime() {

    auto end = std::chrono::steady_clock::now(); // каждый раз обновляем время

    auto elapsedTime = std::chrono::duration_cast<std::chrono::seconds>(end - start);
    int timePassed = elapsedTime.count(); // приводит тип к инту
    
    return timePassed;
}