/**
 * \class CircularArc2D
 * \brief A class for geometric arc in 2-dimensional space.
 */

 //* This is a source code for implementation of "QuickhullDisk: A Faster Convex Hull Algorithm for Disks."
 //* Code authors: Chanyoung Song, Joonghyun Ryu, and Deok-Soo Kim.
 //* Version:      1.0
 //* Date:         2019

#ifndef _CIRCULAR_ARC2D_H_
#define _CIRCULAR_ARC2D_H_

#include "ConstSet.h"
#include "CircularDisk2D.h"
#include <list>
using namespace std;

class CircularArc2D : public CircularDisk2D
{
private:
    Point2D  m_StartPoint;
    Point2D  m_EndPoint;

public:
    CircularArc2D();
    CircularArc2D(const CircularDisk2D& disk);
    CircularArc2D(const CircularDisk2D& disk, const Point2D& startPoint, const Point2D& endPoint);
    CircularArc2D(const CircularArc2D& arc);
    ~CircularArc2D();

    inline Point2D get_start_point() const { return m_StartPoint; };
    inline Point2D get_end_point()   const { return m_EndPoint; };

    inline void set_start_point(const Point2D& startPoint) { m_StartPoint = startPoint; };
    inline void set_end_point(const Point2D& endPoint)     { m_EndPoint = endPoint; };

    CircularArc2D& operator= (const CircularArc2D& arc);
    bool   operator==(const CircularArc2D& arc) const;

    double angle_btw_start_and_end_pts() const;

    void   evaluate_points_on_arc_given_resolution(const int& resolution, list<Point2D>& pointsOnArc) const;
};

#endif

