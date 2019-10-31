#include <cmath>
#include "RelativeOperator.h"
#include "Point2D.h"

Point2D::Point2D()
{
	m_X  = 0.0;
	m_Y  = 0.0;
}


Point2D::Point2D( const Point2D& point )
{
	m_X  = point.m_X;
	m_Y  = point.m_Y;
}


Point2D::Point2D( const double &px, const double &py ) 
{
	m_X = px;
	m_Y = py;
}


Point2D::~Point2D()
{
}


double Point2D::magnitude() const
{
	return sqrt(m_X*m_X + m_Y*m_Y);
}


double Point2D::magnitude_square() const
{
	return (m_X*m_X + m_Y*m_Y);
}


Point2D Point2D::get_unit_vector() const
{
    return *this/magnitude();
}


double Point2D::distance(const Point2D &point) const
{
	return sqrt( (m_X-point.m_X)*(m_X-point.m_X) +
				 (m_Y-point.m_Y)*(m_Y-point.m_Y) );
}


Point2D& Point2D::operator =( const Point2D &point )
{
	m_X = point.m_X;
	m_Y = point.m_Y;

	return *this;
}


int Point2D::operator ==( const Point2D &point ) const 
{
	if ( _EQ(m_X, point.m_X) && _EQ(m_Y, point.m_Y))
		return true;

	else return false;
}


int Point2D::operator!=(const Point2D &point) const
{
    return !((*this) == point);
}


Point2D Point2D::operator +( const Point2D &point ) const
{
	return Point2D(m_X+point.m_X, m_Y+point.m_Y);
}


Point2D& Point2D::operator +=( const Point2D &point )
{
	m_X += point.m_X;
	m_Y += point.m_Y;

	return *this;
}


Point2D Point2D::operator -( const Point2D &point ) const
{
	return Point2D(m_X-point.m_X, m_Y-point.m_Y);
}


Point2D& Point2D::operator -=( const Point2D &point )
{
	m_X -= point.m_X;
	m_Y -= point.m_Y;

	return *this;
}


double Point2D::operator *( const Point2D &point ) const
{
	return m_X*point.m_Y - m_Y*point.m_X;
}


Point2D Point2D::operator *( const double &n ) const
{
	return Point2D(n*m_X, n*m_Y);
}


Point2D Point2D::operator /( const double &n ) const
{
	return Point2D(m_X/n, m_Y/n);
}


Point2D& Point2D::operator =( const double &n )
{
	m_X = n;
	m_Y = n;
	
	return *this;
}


double Point2D::operator %( const Point2D &point) const
{
    return ( m_X*point.get_x() + m_Y*point.get_y() );
}
 

Point2D operator *( const double n, const Point2D& point )
{
	return point * n;
}


Point2D operator -( const Point2D &point)
{
	return Point2D(-point.m_X, -point.m_Y);
}


double angle_from_vec1_to_vec2(const Point2D& vector1, const Point2D& vector2)
{
	Point2D vec1 = vector1.get_unit_vector();
	Point2D vec2 = vector2.get_unit_vector();
	Point2D pt2pt( vec1 - vec2 );
	double length = pt2pt.magnitude();

	double cosine = (2. - length*length)/(2.);

    if (cosine > 1.0)
    {
        cosine = 1.0;
    } 
    else if (cosine < -1.0)
    {
        cosine = -1.0;
    }

	if( vec1 * vec2 > 0.0 )  //less than PI (cross product)
	{
		return acos( cosine );
	}
	else
	{
		return 2.*_PI - acos( cosine );
	}
}


