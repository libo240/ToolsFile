#ifndef TIMER_H
#define TIMER_H

#include <sys/time.h>
#include <stdint.h>
#include <string>

class Timer
{
public:
    Timer();

    void UpdateToNow();

    uint64_t ElapsedMin();

    uint64_t ElapsedSec();

    uint64_t ElapsedMill();

    static uint64_t NowMinUnformat();

    static uint64_t NowSecUnformat();

    static uint64_t NowMillUnformat();

    static std::string NowWithFormat(const std::string& format);

private:
    struct timeval _start_time;
};
#endif // TIMER_H
