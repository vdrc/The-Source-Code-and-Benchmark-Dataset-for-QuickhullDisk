#include "GeometricFunction2D.h"
#include "RelativeOperator.h"
#include <cmath>


Point2D GeometricFunction2D::compute_intersection_between_two_lines(const Point2D& startPointOfOrientedLineSegment1, const Point2D& endPointOfOrientedLineSegment1, const Point2D& startPointOfOrientedLineSegment2, const Point2D& endPointOfOrientedLineSegment2, bool& bTwoLinesAreParallel)
{
    double parameterOfIntersectionForLineSeg1 = DBL_MAX;

    Point2D lineSeg1Vec = endPointOfOrientedLineSegment1 - startPointOfOrientedLineSegment1;
    Point2D lineSeg2Vec = endPointOfOrientedLineSegment2 - startPointOfOrientedLineSegment2;

    if (_ZERO(lineSeg1Vec.operator*(lineSeg2Vec)))
    {
        bTwoLinesAreParallel = true;
        return Point2D(DBL_MAX, DBL_MAX);
    }
    else
    {
        bTwoLinesAreParallel = false;

        double startX1 = startPointOfOrientedLineSegment1.get_x();
        double startY1 = startPointOfOrientedLineSegment1.get_y();
        double endX1   = endPointOfOrientedLineSegment1.get_x();
        double endY1   = endPointOfOrientedLineSegment1.get_y();

        double startX2 = startPointOfOrientedLineSegment2.get_x();
        double startY2 = startPointOfOrientedLineSegment2.get_y();
        double endX2   = endPointOfOrientedLineSegment2.get_x();
        double endY2   = endPointOfOrientedLineSegment2.get_y();

        parameterOfIntersectionForLineSeg1 = (endX2 * startY1 - endX2 * startY2 - endY2 * startX1 + endY2 * startX2 + startX1 * startY2 - startX2 * startY1) / (endX1 * endY2 - endX1 * startY2 - endX2 * endY1 + endX2 * startY1 + endY1 * startX2 - endY2 * startX1 + startX1 * startY2 - startX2 * startY1);

        return ((1. - parameterOfIntersectionForLineSeg1)*startPointOfOrientedLineSegment1 + parameterOfIntersectionForLineSeg1*endPointOfOrientedLineSegment1);
    }
}


int GeometricFunction2D::compute_intersection_between_two_circles( const Circle2D & circle1, const Circle2D & circle2, Point2D * intersectionPt )
{
    double radius1  = circle1.get_radius();
    double radius2  = circle2.get_radius();
    Point2D center1 = circle1.get_center_pt();
    Point2D center2 = circle2.get_center_pt();

    Point2D vecCenter12  = center2 - center1;
    Point2D vecOrthogonalToVecCenter12(vecCenter12.get_y(), -vecCenter12.get_x());

    double  radiu1_plus_radius2       = radius1 + radius2;
    double  radiu1_minus_radius2      = radius1 - radius2;
    double  normOfVecCenter12_squared = vecCenter12.magnitude_square();
    double  parameterOfVecCenter12    = (radiu1_plus_radius2 * radiu1_minus_radius2 / normOfVecCenter12_squared + 1.0) * 0.5;
    double  parameterOfVecOrthogonalToVecCenter12_squared = (-normOfVecCenter12_squared + radiu1_plus_radius2*radiu1_plus_radius2) * (normOfVecCenter12_squared - radiu1_minus_radius2*radiu1_minus_radius2) / (4.0 * normOfVecCenter12_squared * normOfVecCenter12_squared);

    if (parameterOfVecOrthogonalToVecCenter12_squared < 0.0)
    {
        return 0;
    }
    else
    {
        double  parameterOfVecOrthogonalToVecCenter12[2] = { sqrt(parameterOfVecOrthogonalToVecCenter12_squared), -sqrt(parameterOfVecOrthogonalToVecCenter12_squared) };

        intersectionPt[0] = center1 + parameterOfVecCenter12 * vecCenter12 + parameterOfVecOrthogonalToVecCenter12[0] * vecOrthogonalToVecCenter12;
        intersectionPt[1] = center1 + parameterOfVecCenter12 * vecCenter12 + parameterOfVecOrthogonalToVecCenter12[1] * vecOrthogonalToVecCenter12;

        return 2;
    }
}


//this function returns tangent lines 
void GeometricFunction2D::make_exterior_tangent_lines_of_two_circles(const Circle2D& circle1,
											                         const Circle2D& circle2,
											                         LineImplicitEquation& result1,
											                         LineImplicitEquation& result2)
{
	Circle2D w1, w2;

	//the radius of w2 is less than that of w1
	if( circle1.get_radius() < circle2.get_radius() )
	{
		w1 = circle2;
		w2 = circle1;
	}
	else
	{
		w1 = circle1;
		w2 = circle2;
	}

	Point2D c2cVector = w1.get_center_pt() - w2.get_center_pt();
	double r          = w1.get_radius() - w2.get_radius();
	double length     = c2cVector.magnitude();
	double sine       = r / length;
	double cosine     = sqrt( length*length - r*r ) / length;

	//rotate theta  /  -theta
	Point2D normal1( c2cVector.get_x() * cosine - c2cVector.get_y() * sine ,
					 c2cVector.get_x() * sine + c2cVector.get_y() * cosine );
	Point2D normal2( c2cVector.get_x() * cosine + c2cVector.get_y() * sine ,
					 c2cVector.get_y() * cosine - c2cVector.get_x() * sine );
	normal1 = normal1.get_unit_vector();
	normal2 = normal2.get_unit_vector();
	
	//rotate -PI/2  /  PI/2
	normal1.set_point( normal1.get_y() , -1 * normal1.get_x() );
	normal2.set_point( -1 * normal2.get_y() , normal2.get_x() );


    //set results
	result1.coefficient[0] = normal1.get_x();
    result1.coefficient[1] = normal1.get_y();
    result1.coefficient[2] = -1 * normal1.get_x() * w2.get_center_pt().get_x()
						   - normal1.get_y() * w2.get_center_pt().get_y() 
						   + w2.get_radius();

    result2.coefficient[0] = normal2.get_x();
    result2.coefficient[1] = normal2.get_y();
    result2.coefficient[2] = -1 * normal2.get_x() * w2.get_center_pt().get_x()
						   - normal2.get_y() * w2.get_center_pt().get_y() 
						   + w2.get_radius();
}


Point2D GeometricFunction2D::compute_tangent_point_between_line_and_circle(const Circle2D& circle, const LineImplicitEquation& lineImplicitEq) 
{
    Point2D tangentPt;

    double x = circle.get_center_pt().get_x();
    double y = circle.get_center_pt().get_y();
    double a = lineImplicitEq.coefficient[0];
    double b = lineImplicitEq.coefficient[1];
    //double c = lineImplicitEq.coefficient[2];
    double a2_b2 = pow(a, 2) + pow(b, 2);

    if (_EQ(a2_b2, 1.0))
    {
        tangentPt.set_x(-a * lineImplicitEq.evaluateImpEquation(x, y) + x);
        tangentPt.set_y(-b * lineImplicitEq.evaluateImpEquation(x, y) + y);
    }
    else
    {
        tangentPt.set_x(-a * lineImplicitEq.evaluateImpEquation(x, y) / a2_b2 + x);
        tangentPt.set_y(-b * lineImplicitEq.evaluateImpEquation(x, y) / a2_b2 + y);
    }

    return tangentPt;
}



void GeometricFunction2D::compute_two_oriented_tangent_line_segments_from_circle_c1_to_c2(const Circle2D& circle1, const Circle2D& circle2, Line2D* twoTangentOrientedLineSegments) 
{
    LineImplicitEquation implicitEqOfTangentLine1;
    LineImplicitEquation implicitEqOfTangentLine2;

    make_exterior_tangent_lines_of_two_circles(circle1, circle2, implicitEqOfTangentLine1, implicitEqOfTangentLine2);

    Point2D tangentPtOnDisk1[2];
    Point2D tangentPtOnDisk2[2];

    if (circle1.get_radius() != 0.0)
    {
        tangentPtOnDisk1[0] = compute_tangent_point_between_line_and_circle(circle1, implicitEqOfTangentLine1);
        tangentPtOnDisk1[1] = compute_tangent_point_between_line_and_circle(circle1, implicitEqOfTangentLine2);
    }
    else
    {
        tangentPtOnDisk1[0] = circle1.get_center_pt();
        tangentPtOnDisk1[1] = circle1.get_center_pt();
    }


    if (circle2.get_radius() != 0.0)
    {
        tangentPtOnDisk2[0] = compute_tangent_point_between_line_and_circle(circle2, implicitEqOfTangentLine1);
        tangentPtOnDisk2[1] = compute_tangent_point_between_line_and_circle(circle2, implicitEqOfTangentLine2);
    }
    else
    {
        tangentPtOnDisk2[0] = circle2.get_center_pt();
        tangentPtOnDisk2[1] = circle2.get_center_pt();
    }

    twoTangentOrientedLineSegments[0] = Line2D(tangentPtOnDisk1[0], tangentPtOnDisk2[0]);
    twoTangentOrientedLineSegments[1] = Line2D(tangentPtOnDisk1[1], tangentPtOnDisk2[1]);
}


Line2D GeometricFunction2D::compute_CCW_oriented_tangent_line_segment_from_circle_c1_to_c2(const Circle2D& circle1, const Circle2D& circle2) 
{
    if (circle1.get_radius() == 0.0 && circle2.get_radius() == 0.0)
    {
        return Line2D(circle1.get_center_pt(), circle2.get_center_pt());
    }
    else
    {
        Line2D twoTangentOrientedLineSegments[2];
        compute_two_oriented_tangent_line_segments_from_circle_c1_to_c2(circle1, circle2, twoTangentOrientedLineSegments);

        double sumOfSignedDistance = twoTangentOrientedLineSegments[0].signed_distance(circle1.get_center_pt())
                                   + twoTangentOrientedLineSegments[0].signed_distance(circle2.get_center_pt());

        if (sumOfSignedDistance > 0.0)
        {
            return twoTangentOrientedLineSegments[0];
        }
        else
        {
            return twoTangentOrientedLineSegments[1];
        }
    }
}

Line2D GeometricFunction2D::compute_CW_oriented_tangent_line_segment_from_circle_c1_to_c2(const Circle2D& circle1, const Circle2D& circle2) 
{
    if (circle1.get_radius() == 0.0 && circle2.get_radius() == 0.0)
    {
        return Line2D(circle1.get_center_pt(), circle2.get_center_pt());
    }
    else
    {
        Line2D twoTangentOrientedLineSegments[2];
        compute_two_oriented_tangent_line_segments_from_circle_c1_to_c2(circle1, circle2, twoTangentOrientedLineSegments);

        double sumOfSignedDistance = twoTangentOrientedLineSegments[0].signed_distance(circle1.get_center_pt())
                                   + twoTangentOrientedLineSegments[0].signed_distance(circle2.get_center_pt());

        if (sumOfSignedDistance < 0.0)
        {
            return twoTangentOrientedLineSegments[0];
        }
        else
        {
            return twoTangentOrientedLineSegments[1];
        }
    }
}



int GeometricFunction2D::compute_intersection_between_circle_and_line(const Circle2D& circle, const Line2D& lineSegment, Point2D intersection[]) 
{
    Point2D startPoint = lineSegment.get_start_point();
    Point2D endPoint   = lineSegment.get_end_point();
    Point2D center     = circle.get_center_pt();
    double radius      = circle.get_radius();

    double startX  = startPoint.get_x();
    double startY  = startPoint.get_y();
    double endX    = endPoint.get_x();
    double endY    = endPoint.get_y();
    double centerX = center.get_x();
    double centerY = center.get_y();

    double coefficient[3] = { 0.0, 0.0, 0.0 };
    coefficient[0] = pow(startX - centerX, 2.0) + pow(startY - centerY, 2.0) - radius * radius;;
    coefficient[1] = 2.0 * (startX - centerX) * (-startX + endX) + 2.0 * (startY - centerY) * (-startY + endY);
    coefficient[2] = pow(-startX + endX, 2.0) + pow(-startY + endY, 2.0);

    double realSolution[2] = {DBL_MAX, DBL_MAX};
    if(!_ZERO(coefficient[ 2 ]))
	{
		double p = coefficient[ 1 ] / (2.0 * coefficient[ 2 ]);
		double q = coefficient[ 0 ] / coefficient[ 2 ];
		
		double determinant =  p * p - q;

		// determinant >= 0
		if(_NNEG(determinant))
		{
			realSolution[ 0 ] = -p + sqrt(determinant);
			realSolution[ 1 ] = -p - sqrt(determinant);
		}
	}
	else // coefficient[ 2 ] == 0.0
	{
        realSolution[ 0 ] = - coefficient[ 0 ] / coefficient[ 1 ];
	}

    int numberOfIntersections = 0;

    for (int i = 0; i < 2; i++)
    {
        if (realSolution[i] != DBL_MAX)
        {
            double r = realSolution[i];
            intersection[numberOfIntersections] = (1. - r)*startPoint + r * endPoint;
            numberOfIntersections++;
        }
    }

    return numberOfIntersections;
}

