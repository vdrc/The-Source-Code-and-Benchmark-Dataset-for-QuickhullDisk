/**
 * \class Circle2D
 * \brief A class for geometric circle in 2-dimensional space.
 */

 //* This is a source code for implementation of "QuickhullDisk: A Faster Convex Hull Algorithm for Disks."
 //* Code authors: Chanyoung Song, Joonghyun Ryu, and Deok-Soo Kim.
 //* Version:      1.0
 //* Date:         2019

#ifndef _CIRCLE2D_H_
#define _CIRCLE2D_H_

#include "ConstSet.h"
#include "Point2D.h"
#include "Line2D.h"

class Circle2D
{
private:
	Point2D m_CenterPt;
	double	m_Radius;
	
public:
	Circle2D();
	Circle2D(const Point2D& center, const double& r);
	Circle2D(const double& pointX, const double& pointY, const double& r);
	Circle2D(const Circle2D& circle);
	~Circle2D();
	
    inline Point2D  get_center_pt() const { return m_CenterPt; };
    inline double   get_radius()    const { return m_Radius; };
    inline Circle2D get_circle()    const { return *this; };

    inline void set_center_pt(const Point2D& center) { m_CenterPt = center; };
    inline void set_radius(const double& r)          { m_Radius   = r; };
    inline void set_circle(const Circle2D& circle)   { m_CenterPt = circle.m_CenterPt; m_Radius = circle.m_Radius;};
    inline void set_circle(const Point2D& center, const double& r) { m_CenterPt = center; m_Radius = r; };

    inline double compute_area() const      { return _PI * m_Radius * m_Radius; }
    inline double compute_perimeter() const { return 2. * _PI * m_Radius; }

	Point2D*   get_intersection_point(const Circle2D& circle) const;	
	bool       is_intersected_with(const Circle2D& circle)    const;
    bool       is_this_circle_boundary_intersected_with_another_circle_boundary(const Circle2D& circle) const;
	bool       is_tangent_to(const Circle2D& circle)          const;
	bool       is_included_in(const Circle2D& circle)         const;

    bool       has_intersection_with(const Line2D& lineSegment)         const;
    bool       does_contain(const Point2D& point)                       const;
    bool       contain(const Circle2D& circle, const double& tolerance) const;

	Circle2D&  operator=(const Circle2D& circle);
    bool       operator==(const Circle2D& circle) const;

    double     distance(const Point2D& point)   const;
    double     distance(const Circle2D& circle) const;
};

inline  bool    Circle2D::has_intersection_with(const Line2D& lineSegment) const {
    return ( _LT(lineSegment.get_distance(m_CenterPt), m_Radius) == true ) ? true : false;
}

#endif


