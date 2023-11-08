#ifndef TIMER
#define TIMER

#include <chrono>

class Timer {
    
protected:

    std::chrono::steady_clock::time_point start;  // начало счетчика времени; // начало счетчика времени

public:

    Timer();

    int getPassedTime();

};


#endif //TIMER