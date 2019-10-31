#include <cmath>
#include "Circle2D.h"
#include "RelativeOperator.h"

Circle2D::Circle2D()
{
	m_CenterPt = 0.0;
	m_Radius   = 0.0;
}

Circle2D::Circle2D(const Point2D& center, const double& r)
{
	m_CenterPt = center;
	m_Radius   = r;
}

Circle2D::Circle2D(const double& pointX, const double& pointY, const double& r)
{
	m_CenterPt.set_point(pointX, pointY);
	m_Radius = r;
}

Circle2D::Circle2D(const Circle2D& circle)
{
	m_CenterPt = circle.get_center_pt();
	m_Radius = circle.get_radius();
}

	
Circle2D::~Circle2D()
{
}


bool Circle2D::is_intersected_with(const Circle2D& circle) const
{
	Point2D center2center( circle.m_CenterPt - m_CenterPt ); 
	double distance = center2center.magnitude();

	if( _LT(m_Radius + circle.m_Radius, distance) )	
	{
		return false;
	}

	return true;
}


bool Circle2D::is_this_circle_boundary_intersected_with_another_circle_boundary(const Circle2D& circle) const
{
    Point2D center2center(circle.m_CenterPt - m_CenterPt);
    double distance = center2center.magnitude();

    if (_GT(distance, _ABS(m_Radius - circle.m_Radius)) && _LT(distance, m_Radius + circle.m_Radius))
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool Circle2D::is_tangent_to(const Circle2D& circle) const
{
	Point2D center2center( circle.m_CenterPt - m_CenterPt ); 
	double distance = center2center.magnitude();

	if( _EQ(m_Radius + circle.m_Radius, distance) )
	{
		return true;
	}
	
	if( _EQ( _ABS(m_Radius - circle.m_Radius), distance) )
	{
		return true;
	}

	return false;
}



bool Circle2D::is_included_in(const Circle2D& circle) const
{
	Point2D center2center( circle.m_CenterPt - m_CenterPt ); 
	double distance = center2center.magnitude();

	if( _GT( (circle.m_Radius - m_Radius), distance) ) {
		return true;
	}
    else {
	    return false;
    }
}


bool Circle2D::does_contain(const Point2D& point) const
{
    double distance = m_CenterPt.distance(point);

    if ( _GT(m_Radius, distance ) ) {
        return true;
    }
    else {
        return false;
    }
}



bool Circle2D::contain(const Circle2D& circle, const double& tolerance) const
{
    Point2D center2center(circle.m_CenterPt - m_CenterPt);
    double distance = center2center.magnitude();

    if (m_Radius >= (circle.m_Radius + distance) - tolerance)
        return true;
    else
        return false;

}


Point2D* Circle2D::get_intersection_point(const Circle2D& circle) const
{
/*				 *	<-- intersect point
				/|\
			   / |  \
			  /	 |h   \
			 /_c_|______\
		center  foot   circle.center
*/	
	Point2D center2center( circle.m_CenterPt - m_CenterPt ); 
	double distance = center2center.magnitude();
	Point2D foot;
	
	if( _LT(m_Radius + circle.m_Radius, distance) )	
	{
		return _NULL;
	}
	
	if( _GT(_ABS( m_Radius - circle.m_Radius ), distance) )
	{
		return _NULL;
	}

	if( _EQ(m_Radius, circle.m_Radius) && _EQ(distance, 0.0) )
	{
		return _NULL;
	}

	double c=0, h=0;
	c = (distance*distance + m_Radius*m_Radius - 
		 circle.m_Radius*circle.m_Radius)/(2*distance);
	
	if(m_Radius*m_Radius - c*c > 0)
		h = sqrt(m_Radius*m_Radius - c*c);
	
	Point2D temp( -1*center2center.get_y(), center2center.get_x() );
	Point2D* intersectPt= new Point2D[2];  
		
	foot = m_CenterPt + c*( center2center.get_unit_vector() );
	intersectPt[0] = foot + temp.get_unit_vector()*h;
	intersectPt[1] = foot - temp.get_unit_vector()*h;
	
	return intersectPt;
}
	
Circle2D& Circle2D::operator=(const Circle2D& circle)
{
	if( this == &circle ) {
		return *this;
	}
	
	m_CenterPt = circle.m_CenterPt;
	m_Radius = circle.m_Radius;
	
	return *this;
}



bool Circle2D::operator==(const Circle2D& circle) const
{
    if (m_CenterPt == circle.m_CenterPt && m_Radius == circle.m_Radius) {
        return true;
    }
    else {
        return false;
    }
}


double Circle2D::distance(const Point2D& point) const
{
    return (m_CenterPt.distance(point) - m_Radius);
}



double Circle2D::distance(const Circle2D& circle) const
{	 
    double dist = 0;
	double distC2C = m_CenterPt.distance( circle.m_CenterPt );
    
    if ( _GT( distC2C, (m_Radius+circle.m_Radius) ) ) {
        dist = distC2C - (m_Radius+circle.m_Radius);
    }
    else {
        dist = (m_Radius+circle.m_Radius) - distC2C;
    }

    return dist;
}


