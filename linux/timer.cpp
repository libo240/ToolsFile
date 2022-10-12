#include "timer.h"

Timer::Timer()
{
    _start_time.tv_sec = 0;
    _start_time.tv_usec = 0;
}

void Timer::UpdateToNow()
{
    gettimeofday(&_start_time, nullptr);
}

uint64_t Timer::ElapsedMin()
{
    struct timeval _end_time;
    gettimeofday(&_end_time, nullptr);
    return ((_end_time.tv_sec - _start_time.tv_sec ) + (_end_time.tv_usec - _start_time.tv_usec) / 1000000)/60;
}

uint64_t Timer::ElapsedSec()
{
    struct timeval _end_time;
    gettimeofday(&_end_time, nullptr);
    return _end_time.tv_sec - _start_time.tv_sec  + (_end_time.tv_usec - _start_time.tv_usec) / 1000000;
}

uint64_t Timer::ElapsedMill()
{
    struct timeval _end_time;
    gettimeofday(&_end_time, nullptr);
    return 1000 * (_end_time.tv_sec - _start_time.tv_sec)  + (_end_time.tv_usec - _start_time.tv_usec) / 1000;
}

uint64_t Timer::NowMinUnformat()
{
    struct timeval now_time;
    gettimeofday(&now_time, nullptr);
    return (now_time.tv_sec + now_time.tv_usec / 1000000 ) / 60;
}

uint64_t Timer::NowSecUnformat()
{
    struct timeval now_time;
    gettimeofday(&now_time, nullptr);
    return now_time.tv_sec + now_time.tv_usec / 1000000;
}

uint64_t Timer::NowMillUnformat()
{
    struct timeval now_time;
    gettimeofday(&now_time, nullptr);
    return now_time.tv_sec * 1000 + now_time.tv_usec / 1000;
}

std::string Timer::NowWithFormat(const std::string &format)
{
    struct timeval now_time;
    gettimeofday(&now_time, nullptr);
    struct tm *now = localtime(&now_time.tv_sec);

    char out[100] = {0};
    strftime(out, 100, format.c_str(), now);
    return out;
}
