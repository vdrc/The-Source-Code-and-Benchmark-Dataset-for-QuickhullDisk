/**
 * \class Line2D
 * \brief A class for geometric line segment in 2-dimensional space.
 */

 //* This is a source code for implementation of "QuickhullDisk: A Faster Convex Hull Algorithm for Disks."
 //* Code authors: Chanyoung Song, Joonghyun Ryu, and Deok-Soo Kim.
 //* Version:      1.0
 //* Date:         2019


#ifndef _LINE2D_H_
#define _LINE2D_H_

#include "ConstSet.h"
#include "Point2D.h"
#include "RelativeOperator.h"
#include <cmath>

class Line2D
{
protected:
	Point2D m_StartPt;
	Point2D m_EndPt;

public: 
	Line2D();
	Line2D(const Point2D &sPt, const Point2D &ePt);
	Line2D(const Line2D &line);
	~Line2D();            
                                    
    inline Point2D get_start_point()        const { return m_StartPt; };
    inline Point2D get_end_point()          const { return m_EndPt; };
    inline Line2D  get_reversed_line2D() const { return Line2D(m_EndPt, m_StartPt); };

    inline void set_start_pt(const Point2D &pt) { m_StartPt = pt; };
    inline void set_end_pt(const Point2D &pt)   { m_EndPt   = pt; };
    inline void set_line2d(const Point2D &sPt, const Point2D &ePt) { m_StartPt = sPt; m_EndPt = ePt; };
    inline void set_line2d(const Line2D &line)  { m_StartPt = line.m_StartPt; m_EndPt = line.m_EndPt;};

    double   get_length()                          const;
    double   get_distance(const Point2D& point)    const;
    double   signed_distance(const Point2D& point) const;
    bool     does_contain(const Point2D& point)    const;

    Point2D  evaluate_vector()   const;
    Point2D  get_normal_vector() const;

    Point2D compute_intersection_with_line(const Line2D& lineSegment, bool& bTwoLinesAreParallel) const;
    Line2D  make_perpendicular_line(const Point2D& passingPoint);

    // Operator Overloading
    bool    operator==(const Line2D &line) const;
    Line2D& operator =(const Line2D& line);
};


#endif

