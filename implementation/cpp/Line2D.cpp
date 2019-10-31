#include "Line2D.h"
#include "RelativeOperator.h"
#include "GeometricFunction2D.h"

Line2D::Line2D()
{
}


Line2D::Line2D(const Point2D &sPt, const Point2D &ePt)
{
	m_StartPt = sPt;
	m_EndPt   = ePt;
}


Line2D::Line2D(const Line2D &line)
{
	m_StartPt = line.m_StartPt;
	m_EndPt = line.m_EndPt;
}


Line2D::~Line2D()
{
}


double Line2D::get_length() const
{
	Point2D length(m_EndPt - m_StartPt);
	return length.magnitude();
}


double Line2D::get_distance(const Point2D& point) const
{
    Point2D   spPtVector( point-m_StartPt );
    Point2D   epPtVector( point-m_EndPt );
    Point2D   lineVector( m_EndPt   -m_StartPt );

    double spPtLen = spPtVector.magnitude();
    double epPtLen = epPtVector.magnitude();
    double lineLen = lineVector.magnitude();

    if ( _GE( epPtLen*epPtLen, (spPtLen*spPtLen)+(lineLen*lineLen)) )
    {
        return spPtLen;
    }
    else if ( _GE( (spPtLen*spPtLen), (epPtLen*epPtLen)+(lineLen*lineLen)) )
    {
        return epPtLen;
    }
    else
    {
        double output= _ABS(lineVector*spPtVector)/lineLen;
        return output;
    }
}


double Line2D::signed_distance(const Point2D& point) const
{
    Point2D   spPtVector(point - m_StartPt);
    Point2D   lineVector(m_EndPt - m_StartPt);

    double output = lineVector*spPtVector / lineVector.magnitude();
    return output;
}


bool Line2D::does_contain(const Point2D& point) const
{
    return (_ZERO(signed_distance(point))) ? true : false;
}


Point2D Line2D::evaluate_vector() const
{
    Point2D output=m_EndPt-m_StartPt;
    return output;
}


Point2D Line2D::get_normal_vector() const
{
    Point2D dirVec = evaluate_vector();
    return Point2D(-dirVec.get_y(), dirVec.get_x());
}


Point2D Line2D::compute_intersection_with_line(const Line2D& lineSegment, bool& bTwoLinesAreParallel) const
{
    return GeometricFunction2D::compute_intersection_between_two_lines(m_StartPt, m_EndPt, lineSegment.m_StartPt, lineSegment.m_EndPt, bTwoLinesAreParallel);
}


Line2D Line2D::make_perpendicular_line(const Point2D& passingPoint)
{
    Point2D dirVec = get_normal_vector();
    return Line2D(passingPoint, passingPoint + dirVec);
}


////////////////////////////////////////////////////////////////////////
// Operator Overloading
bool Line2D::operator==(const Line2D &line) const
{
    if ( (m_StartPt == line.m_StartPt && m_EndPt == line.m_EndPt)
         || (m_StartPt == line.m_EndPt && m_EndPt == line.m_StartPt) )
    {
        return true;
    }
    else 
        return false;
}

Line2D& Line2D::operator =(const Line2D& line)
{
    if ( this == &line )
        return *this;

    m_StartPt = line.m_StartPt;
    m_EndPt = line.m_EndPt;

    return *this;
}


