/**
 * \class Point2D
 * \brief A class for geometric point in 2-dimensional space.
 */

 //* This is a source code for implementation of "QuickhullDisk: A Faster Convex Hull Algorithm for Disks."
 //* Code authors: Chanyoung Song, Joonghyun Ryu, and Deok-Soo Kim.
 //* Version:      1.0
 //* Date:         2019

#ifndef	_POINT2D_H_
#define _POINT2D_H_

#include "ConstSet.h"

class Point2D 
{
private:
	double m_X;
	double m_Y;

public:
    Point2D();
	Point2D(const Point2D& point);
	Point2D(const double& px, const double& py);
	~Point2D();

    inline double   get_x() const { return m_X; };
    inline double   get_y() const { return m_Y; };

    inline void     set_x(const double& px) { m_X = px; };
    inline void     set_y(const double& py) { m_Y = py; };
    inline void     set_point(const Point2D &point) { m_X = point.m_X; m_Y = point.m_Y; };
	inline void     set_point(const double& px, const double& py) { m_X = px; m_Y = py; };

	double     magnitude() const;
	double     magnitude_square() const;
	Point2D    get_unit_vector() const;
	double	   distance(const Point2D &point) const;

	Point2D&  operator  =( const Point2D &point );
	int       operator ==( const Point2D &point ) const;
    int       operator !=( const Point2D &point ) const;
	Point2D   operator  +( const Point2D &point ) const;
	Point2D&  operator +=( const Point2D &point );
	Point2D   operator  -( const Point2D &point ) const;
	Point2D&  operator -=( const Point2D &point );
	Point2D   operator  *( const double&      n ) const;
	double    operator  *( const Point2D &point ) const;	// cross product
	Point2D   operator  /( const double&      n ) const;
	Point2D&  operator  =( const double&      n );
    double    operator  %( const Point2D  &point) const;	// dot product
	
	friend Point2D operator *( const double n, const Point2D& point );
	friend Point2D operator -( const Point2D &point );
    friend double  angle_from_vec1_to_vec2(const Point2D& vector1, const Point2D& vector2);
};


#endif  //Point2D class


