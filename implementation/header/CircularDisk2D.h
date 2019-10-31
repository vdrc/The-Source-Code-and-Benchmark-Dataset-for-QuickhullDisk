/**
 * \class CircularDisk2D
 * \brief A class for circular disk in 2-dimensional space based on Circle2D.
 *
 * \details Only 'id' member variable is added for representing a unique circle. 
 */

 //* This is a source code for implementation of "QuickhullDisk: A Faster Convex Hull Algorithm for Disks."
 //* Code authors: Chanyoung Song, Joonghyun Ryu, and Deok-Soo Kim.
 //* Version:      1.0
 //* Date:         2019

#ifndef _CIRCULAR_DISK_2D_ 
#define _CIRCULAR_DISK_2D_ 

#include "ConstSet.h"
#include "Circle2D.h"
#include "Point2D.h"
#include <list>
using namespace std;

class CircularDisk2D : public Circle2D
{
private:
    int m_ID;

public:
    CircularDisk2D();
    CircularDisk2D(const Point2D& center, const double& r, const int& id);
    CircularDisk2D(const double& pointX, const double& pointY, const double& r, const int& id);
    CircularDisk2D(const CircularDisk2D& circle, const int& id);
    CircularDisk2D(const CircularDisk2D& disk);
    ~CircularDisk2D();

    inline int  get_ID() const { return m_ID; } ;
    inline void set_ID(const int& id) { m_ID = id; };

    CircularDisk2D& operator=(const CircularDisk2D& disk);
    bool operator<(const CircularDisk2D& disk)  const;
    bool operator>(const CircularDisk2D& disk)  const;
    bool operator==(const CircularDisk2D& disk) const;
};

#endif //_CIRCULAR_DISK_2D_ 

