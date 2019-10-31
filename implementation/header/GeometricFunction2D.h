/**
 * \class GeometricFunction2D
 * \brief A class for set of geometric functions.
 *
 * \details Using this class, you can do the followings:
 *        1) finding intersection points between lines and circles;
 *        2) finding tangent lines between two circles. 
 */

 //* This is a source code for implementation of "QuickhullDisk: A Faster Convex Hull Algorithm for Disks."
 //* Code authors: Chanyoung Song, Joonghyun Ryu, and Deok-Soo Kim.
 //* Version:      1.0
 //* Date:         2019

#ifndef _GEOMETRIC_FUNCTION_2D_H_
#define _GEOMETRIC_FUNCTION_2D_H_

#include "ConstSet.h"
#include "Point2D.h"
#include "Line2D.h"
#include "Circle2D.h"

/*!
* \struct LineImplicitEquation
* \brief  This is for line implicit equation.
*         The line implicit equation are as follows.
*         coefficient[0] * x + coefficient[1] * y + coefficient[2] = 0
*/
struct LineImplicitEquation
{
    double coefficient[3] = {0.0, 0.0, 0.0};

    double evaluateImpEquation(const double& valueForX, const double& valueForY) const
    {
        return coefficient[0] * valueForX + coefficient[1] * valueForY + coefficient[2];
    }
};



class GeometricFunction2D
{
public:
    static Point2D compute_intersection_between_two_lines(const Point2D& startPointOfOrientedLineSegment1, const Point2D& endPointOfOrientedLineSegment1, const Point2D& startPointOfOrientedLineSegment2, const Point2D& endPointOfOrientedLineSegment2, bool& bTwoLinesAreParallel);
    
    static int     compute_intersection_between_circle_and_line(const Circle2D& circle, const Line2D& lineSegment, Point2D intersection[]);

    static int     compute_intersection_between_two_circles(const Circle2D & circle1, const Circle2D & circle2, Point2D* intersectionPt);


    static Line2D  compute_CCW_oriented_tangent_line_segment_from_circle_c1_to_c2(const Circle2D& circle1, const Circle2D& circle2);

    static Line2D  compute_CW_oriented_tangent_line_segment_from_circle_c1_to_c2(const Circle2D& circle1, const Circle2D& circle2);

    static void    compute_two_oriented_tangent_line_segments_from_circle_c1_to_c2(const Circle2D& circle1, const Circle2D& circle2, Line2D* twoTangentOrientedLineSegments);

private:
    static void    make_exterior_tangent_lines_of_two_circles(const Circle2D& circle1, const Circle2D& circle2, LineImplicitEquation& result1, LineImplicitEquation& result2);

    static Point2D compute_tangent_point_between_line_and_circle(const Circle2D& circle, const LineImplicitEquation& lineImplicitEq);
};


#endif //_GEOMETRIC_FUNCTION_H_


