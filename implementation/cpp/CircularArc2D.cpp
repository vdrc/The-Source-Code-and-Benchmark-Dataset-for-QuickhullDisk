#include "CircularArc2D.h"
#include <math.h>

CircularArc2D::CircularArc2D()
    : CircularDisk2D(0.0,0.0,0.0,-1), m_StartPoint(DBL_MAX, DBL_MAX), m_EndPoint(DBL_MAX, DBL_MAX)
{
}


CircularArc2D::CircularArc2D(const CircularDisk2D& disk)
    : CircularDisk2D(disk), m_StartPoint(DBL_MAX, DBL_MAX), m_EndPoint(DBL_MAX, DBL_MAX)
{
}


CircularArc2D::CircularArc2D(const CircularDisk2D& disk, const Point2D& startPoint, const Point2D& endPoint)
    : CircularDisk2D(disk), m_StartPoint(startPoint), m_EndPoint(endPoint)
{
}


CircularArc2D::CircularArc2D(const CircularArc2D& arc)
: CircularDisk2D( arc )
{
    m_StartPoint = arc.m_StartPoint;
    m_EndPoint   = arc.m_EndPoint;
}


CircularArc2D::~CircularArc2D()
{
}


CircularArc2D& CircularArc2D::operator =(const CircularArc2D& arc)
{
    if ( this == &arc ) 
    {
        return *this;
    }

    CircularDisk2D::operator =(arc);
    m_StartPoint = arc.m_StartPoint;
    m_EndPoint   = arc.m_EndPoint;
        
    return *this;
}


    
bool CircularArc2D::operator==(const CircularArc2D& arc) const
{
    if ( CircularDisk2D::operator==(arc) && m_StartPoint == arc.m_StartPoint && m_EndPoint == arc.m_EndPoint ) {
        return true;
    }
    else {
        return false;
    }        
}

    
double CircularArc2D::angle_btw_start_and_end_pts() const
{
    if (m_StartPoint.get_x() == DBL_MAX || m_StartPoint.get_y() == DBL_MAX)
    {
        return 2.0 * _PI;
    }
    else if (m_StartPoint == m_EndPoint)
    {
        return 0.0;
    }
    else 
    {
        Point2D center           = get_center_pt();
        Point2D vecCenterToStart = m_StartPoint - center;
        Point2D vecCenterToEnd   = m_EndPoint - center;

        double angleStartToEnd   = angle_from_vec1_to_vec2(vecCenterToStart, vecCenterToEnd);

        return angleStartToEnd;
    }
}


void CircularArc2D::evaluate_points_on_arc_given_resolution(const int& circleResolution, list<Point2D>& pointsOnArc) const
{
    Point2D center = get_center_pt();
    double  radius = get_radius();

    if ( m_StartPoint == m_EndPoint ) 
    {
		for(int i = 0; i < circleResolution; i++) 
        {
			double angle = 2*_PI*(double)i/(double)circleResolution;
			Point2D point(center.get_x() + radius*cos(angle), center.get_y() + radius*sin(angle));  

            pointsOnArc.push_back( point );
		}		
        pointsOnArc.push_back( *(pointsOnArc.begin()) );
    }
    else 
    {
        Point2D startVec = m_StartPoint - center;
        Point2D endVec   = m_EndPoint - center;
	    Point2D uVector  = startVec.get_unit_vector();
        Point2D vVector(-uVector.get_y(), uVector.get_x());

        double    arcAngle = angle_from_vec1_to_vec2(startVec, endVec);
        double    angle    = 0.0;

        int i = 0;
        do {            
            Point2D point = center + radius*(cos(angle)*uVector + sin(angle)*vVector);
            pointsOnArc.push_back( point );

            i++;
			angle = 2*_PI*(double)i/(double)circleResolution;
        } while ( angle < arcAngle );

        pointsOnArc.push_back( m_EndPoint );
    }
}
