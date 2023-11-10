#ifndef TIMER
#define TIMER

#include <chrono>

class Timer {
    
protected:

    std::chrono::steady_clock::time_point start;

public:

    Timer();

    int getPassedTime();

};


#endif //TIMER