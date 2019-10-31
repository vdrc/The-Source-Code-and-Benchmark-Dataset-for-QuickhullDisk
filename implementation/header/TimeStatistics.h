/**
 * \class TimeStatistics
 * \brief A class for checking and storing many times(sec).
 *         
 * \details Its resolution is 1/1000 sec.
 */

 //* This is a source code for implementation of "QuickhullDisk: A Faster Convex Hull Algorithm for Disks."
 //* Code authors: Chanyoung Song, Joonghyun Ryu, and Deok-Soo Kim.
 //* Version:      1.0
 //* Date:         2019

#ifndef _TIME_STATISTICS_H_
#define _TIME_STATISTICS_H_

#include <float.h>
#include <time.h>
#include <vector>
using namespace std;


class TimeStatistics
{
private:
    vector<double> m_ElapsedTimes;
    vector<double> m_StartClocks;

public:
    TimeStatistics();
    TimeStatistics(const int& numTimes);
    TimeStatistics(const TimeStatistics& statistics);
    ~TimeStatistics();

    TimeStatistics& operator =(const TimeStatistics& statistics);

    inline int     size() const;
    
    /**
    * \brief Reset two vectors 'm_ElapsedTimes' and 'm_StartClocks' with the size 'numTimes'. 
    */
    inline void    reset(const int& numTimes = 0);

    /**
    * \brief Get value of 'm_ElapsedTimes' at the index 'it'.
    */
    inline double  time(const unsigned int& it) const;

    /**
    * \brief Set time at the index 'it' of 'm_ElapsedTimes'.
    */
    inline void    set_time(const unsigned int& it, const double& time);

    /**
    * \brief Set time at the last position of 'm_ElapsedTimes'.
    */
    inline void    set_time(const double& time);

    /**
    * \brief Mark the start clock at the index 'it' of 'm_StartClocks'.
    */
    inline void    start_clock(const unsigned int& it);

    /**
    * \brief Mark the end clock; 
             compute and store a elpased time between m_StartClocks[it] and end clock at the index 'it' of 'm_ElapsedTimes'.
    */
    inline void    end_clock(const unsigned int& it);

    /**
    * \brief Mark the start clock at the last position of 'm_StartClocks'.
    */
    inline void    start_clock();

    /**
    * \brief Mark the end clock;
             compute and store a elpased time between m_StartClocks[it] and end clock at the last position of 'm_ElapsedTimes'.
    */
    inline void    end_clock();
};

inline int TimeStatistics::size() const
{
    return m_ElapsedTimes.size();
}


inline double TimeStatistics::time(const unsigned int& it) const 
{
    if (it < m_ElapsedTimes.size())
    {
        return m_ElapsedTimes[it];
    }
    else
    {
        return DBL_MAX;
    }
}

inline void TimeStatistics::set_time(const unsigned int& it, const double& inputTime)
{
    if (it < m_ElapsedTimes.size()) 
    {
        m_ElapsedTimes[it] = inputTime;
    }
}


inline void TimeStatistics::set_time(const double& time)
{
    m_ElapsedTimes.push_back(time);
}


inline void TimeStatistics::reset(const int& numTimes) 
{
    m_ElapsedTimes.clear();
    m_StartClocks.clear();

    if (numTimes > 0) 
    {
        m_ElapsedTimes.resize(numTimes, 0.0);
        m_StartClocks.resize(numTimes, 0.0);
    }
}


inline void TimeStatistics::start_clock(const unsigned int& it)
{
    if (it < m_StartClocks.size())
    {
        m_StartClocks[it] = ((double)clock() / CLOCKS_PER_SEC);
    }
}


inline void TimeStatistics::end_clock(const unsigned int& it)
{
    if (it < m_StartClocks.size())
    {
        double startClock = m_StartClocks[it];
        double endClock   = ((double)clock() / CLOCKS_PER_SEC);

        double totalTime = time(it) + (endClock - startClock);
        
        set_time(it, totalTime);
    }
}


inline void TimeStatistics::start_clock()
{
    m_StartClocks.push_back(((double)clock() / CLOCKS_PER_SEC));
}



inline void TimeStatistics::end_clock()
{
    double startClock = m_StartClocks.back();
    double endClock = ((double)clock() / CLOCKS_PER_SEC);

    double totalTime = endClock - startClock;

    set_time(totalTime);
}




#endif

