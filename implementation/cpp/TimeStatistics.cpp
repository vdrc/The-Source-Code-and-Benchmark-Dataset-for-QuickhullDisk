#include "TimeStatistics.h"

TimeStatistics::TimeStatistics()
{
}



TimeStatistics::TimeStatistics(const int& numTimes)
{
    m_ElapsedTimes.resize(numTimes, 0.0);
    m_StartClocks.resize(numTimes, 0.0);
}



TimeStatistics::TimeStatistics(const TimeStatistics& statistics)
    : m_ElapsedTimes(statistics.m_ElapsedTimes), m_StartClocks(statistics.m_StartClocks)
{
}



TimeStatistics::~TimeStatistics()
{
}



TimeStatistics& TimeStatistics::operator =(const TimeStatistics& statistics)
{
    if (this != &statistics) 
    {
        m_ElapsedTimes.clear();
        m_StartClocks.clear();

        m_ElapsedTimes      = statistics.m_ElapsedTimes;
        m_StartClocks = statistics.m_StartClocks;
    }

    return *this;
}

