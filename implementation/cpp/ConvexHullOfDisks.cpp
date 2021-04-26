#include "ConvexHullOfDisks.h"
#include "GeometricFunction2D.h"

void ConvexHullOfDisks::get_input_disks(list<CircularDisk2D*>& inputDisks) const
{
    get_pointers_of_disks(m_InputDisks, inputDisks);
}


void ConvexHullOfDisks::get_hull_disks(list<CircularDisk2D*>& hullDisks) const
{
    for (list<CircularDisk2D*>::const_iterator it_Disk = m_HullDisks.begin(); it_Disk != m_HullDisks.end(); ++it_Disk)
    {
        hullDisks.push_back(const_cast<CircularDisk2D*>(*it_Disk));
    }
}


void ConvexHullOfDisks::get_hull_disks(list<CircularDisk2D>& hullDisks) const
{
    copy_disks_from_its_pointers(m_HullDisks, hullDisks);
}


void ConvexHullOfDisks::clear_convexhull()
{
    m_InputDisks.clear();
    m_HullDisks.clear();
    initialize_time_statistics(0);
}


double ConvexHullOfDisks::extract_convexhull_boundary(const list<CircularDisk2D>& hullDisks, list<pair<CircularArc2D, Line2D>>& boundaryArcNLines)
{
    if (hullDisks.empty())
    {
        return 0.0;
    }
    else if (hullDisks.size() == 1)
    {
        CircularArc2D arc(CircularArc2D(hullDisks.front()));
        Line2D tangentLine(Point2D(DBL_MAX, DBL_MAX), Point2D(DBL_MAX, DBL_MAX));
        boundaryArcNLines.push_back(make_pair(arc, tangentLine));

        return 2.0 * _PI * arc.get_radius();
    }

    vector<Line2D>         tangentLineSegments;
    vector<CircularDisk2D> geometryOfHullDisks;

    const int numOfTangentLines = hullDisks.size() - 1;
    tangentLineSegments.resize(numOfTangentLines);
    geometryOfHullDisks.resize(numOfTangentLines);

    list<CircularDisk2D>::const_iterator it_Disk = hullDisks.begin();
    list<CircularDisk2D>::const_iterator it_LastDiskInExtremeDisks = --hullDisks.end();

    int idx = 0;
    while (it_Disk != it_LastDiskInExtremeDisks)
    {
        const CircularDisk2D& currDisk = *it_Disk;
        geometryOfHullDisks[idx] = currDisk;

        const CircularDisk2D& nextDisk = *(++it_Disk);
        Line2D orientedTangentLineSegment = ConvexHullOfDisks::compute_a_CCW_oriented_tangent_line_from_disk_d1_to_d2(currDisk, nextDisk);
        tangentLineSegments[idx++] = orientedTangentLineSegment;
    }


    //adjusting 
    for (int i = 0; i < numOfTangentLines; ++i)
    {
        Line2D& currLineSegment = tangentLineSegments[  i  %numOfTangentLines];
        Line2D& nextLineSegment = tangentLineSegments[(i+1)%numOfTangentLines];
       
        if (   _EQ(currLineSegment.get_end_point().get_x(), nextLineSegment.get_start_point().get_x(), _resNeg5)
            && _EQ(currLineSegment.get_end_point().get_y(), nextLineSegment.get_start_point().get_y(), _resNeg5))
        {
            nextLineSegment.set_start_pt(currLineSegment.get_end_point());
        }

        /*
        Point2D currLineVector = currLineSegment.evaluate_vector();
        Point2D nextLineVector = nextLineSegment.evaluate_vector();

        Point2D oldEndPointOfCurrLine = currLineSegment.get_end_point();
        if (currLineVector * nextLineVector < 0.0)
        {
            currLineSegment.set_end_pt(nextLineSegment.get_start_point());
            nextLineSegment.set_start_pt(oldEndPointOfCurrLine);
        }
        */  
    }


    for (int i = 0; i < numOfTangentLines; ++i)
    {
        Point2D startPtOfArc = tangentLineSegments[(i - 1 + numOfTangentLines) % numOfTangentLines].get_end_point();
        Point2D endPtOfArc = tangentLineSegments[i].get_start_point();

        CircularArc2D   currArc(geometryOfHullDisks[i], startPtOfArc, endPtOfArc);
        Line2D  tangentLineSegmentNextToCurrArc = tangentLineSegments[i];
        boundaryArcNLines.push_back(make_pair(currArc, tangentLineSegmentNextToCurrArc));
    }


    double lengthOfHullBoundary = 0.0;
    for (list<pair<CircularArc2D, Line2D>>::const_iterator it_ArcNLine = boundaryArcNLines.begin(); it_ArcNLine != boundaryArcNLines.end(); ++it_ArcNLine)
    {
        const pair<CircularArc2D, Line2D>& arcNLine = *it_ArcNLine;
        const CircularArc2D& arc                    = arcNLine.first;
        const Line2D& line                          = arcNLine.second;

        lengthOfHullBoundary += arc.caculate_arc_length();
        lengthOfHullBoundary += line.get_length();
    }

    return lengthOfHullBoundary;
}


Line2D ConvexHullOfDisks::compute_a_CCW_oriented_tangent_line_from_disk_d1_to_d2(const CircularDisk2D& disk1, const CircularDisk2D& disk2)
{
    return GeometricFunction2D::compute_CCW_oriented_tangent_line_segment_from_circle_c1_to_c2(disk1, disk2);
}


void ConvexHullOfDisks::find_out_unique_disks_using_binary_search_tree(const list<CircularDisk2D>& inputDisks, list<CircularDisk2D>& uniqueDisks)
{
    set<CircularDisk2D, compare_two_disk_for_unique_existence_in_set> setOfDisks;
    setOfDisks.insert(inputDisks.begin(), inputDisks.end());

    uniqueDisks.insert(uniqueDisks.end(), setOfDisks.begin(), setOfDisks.end());
    uniqueDisks.sort(disk1_id_is_smaller_than_disk2_id);
}


void ConvexHullOfDisks::sort_disks_by_their_radius_in_decreasing_order(const list<CircularDisk2D*>& inputDisks, list<CircularDisk2D*>& sortedDisks) const
{
    sortedDisks = inputDisks;
    sortedDisks.sort(ConvexHullOfDisks::disk1_is_larger_than_disk2);
}


void ConvexHullOfDisks::rearrange_hull_disks_for_output_format_by_begining_with_disk_having_high_left_extreme_point(list<CircularDisk2D*>& hullDisks) const
{
    CircularDisk2D* diskHavingHighLeftExtremePt = _NULL;
    Point2D highLeftExtremePt;
    find_high_left_extreme_point_N_its_disk(hullDisks, highLeftExtremePt, diskHavingHighLeftExtremePt);

    if (hullDisks.front() != diskHavingHighLeftExtremePt)
    {
        hullDisks.pop_back(); /*Because the first disk and the last is same for output format.*/

        do
        {
            CircularDisk2D* currDisk = hullDisks.front();
            hullDisks.pop_front();
            hullDisks.push_back(currDisk);
        } while (hullDisks.front() != diskHavingHighLeftExtremePt);

        hullDisks.push_back(hullDisks.front());  /*Because the first disk and the last is same for output format.*/
    }
}


void ConvexHullOfDisks::find_high_left_extreme_point_N_its_disk(const list<CircularDisk2D*>& inputDisks, Point2D& highLeftExtremePt, CircularDisk2D*& diskHavingHighLeftExtremePt) const
{
    diskHavingHighLeftExtremePt = *inputDisks.begin();
    double leftMostX            = diskHavingHighLeftExtremePt->get_center_pt().get_x() - diskHavingHighLeftExtremePt->get_radius();

    for (list<CircularDisk2D*>::const_iterator it_Disk = ++inputDisks.begin(); it_Disk != inputDisks.end(); ++it_Disk)
    {
        CircularDisk2D* currDisk = *it_Disk;
        double leftMostXOfCurrDisk = currDisk->get_center_pt().get_x() - currDisk->get_radius();

        if (leftMostXOfCurrDisk < leftMostX)
        {
            leftMostX                      = leftMostXOfCurrDisk;
            diskHavingHighLeftExtremePt    = currDisk;
        }
        else if (leftMostXOfCurrDisk == leftMostX)
        {
            if (currDisk->get_center_pt().get_y() > diskHavingHighLeftExtremePt->get_center_pt().get_y())
            {
                diskHavingHighLeftExtremePt = currDisk;
            }
            else if (currDisk->get_center_pt().get_y() == diskHavingHighLeftExtremePt->get_center_pt().get_y())
            {
                if (currDisk->get_radius() > diskHavingHighLeftExtremePt->get_radius())
                {
                    diskHavingHighLeftExtremePt = currDisk;
                }
            }
        }
    }

    highLeftExtremePt = Point2D(leftMostX, diskHavingHighLeftExtremePt->get_center_pt().get_y());
}


void ConvexHullOfDisks::find_low_right_extreme_point_N_its_disk(const list<CircularDisk2D*>& inputDisks, Point2D& lowRightExtremePt, CircularDisk2D*& diskHavingLowRightExtremePt) const
{
    diskHavingLowRightExtremePt = *inputDisks.begin();
    double rightMostX = diskHavingLowRightExtremePt->get_center_pt().get_x() + diskHavingLowRightExtremePt->get_radius();
    
    for (list<CircularDisk2D*>::const_iterator it_Disk = ++inputDisks.begin(); it_Disk != inputDisks.end(); ++it_Disk)
    {
        CircularDisk2D* currDisk = *it_Disk;
        double rightMostXOfCurrDisk = currDisk->get_center_pt().get_x() + currDisk->get_radius();

        if (rightMostXOfCurrDisk > rightMostX)
        {
            rightMostX                     = rightMostXOfCurrDisk;
            diskHavingLowRightExtremePt    = currDisk;
        }
        else if (rightMostXOfCurrDisk == rightMostX)
        {
            if (currDisk->get_center_pt().get_y() < diskHavingLowRightExtremePt->get_center_pt().get_y())
            {
                diskHavingLowRightExtremePt    = currDisk;
            }
            else if (currDisk->get_center_pt().get_y() == diskHavingLowRightExtremePt->get_center_pt().get_y())
            {
                if (currDisk->get_radius() > diskHavingLowRightExtremePt->get_radius())
                {
                    diskHavingLowRightExtremePt    = currDisk;
                }
            }
        }
    }

    lowRightExtremePt = Point2D(rightMostX, diskHavingLowRightExtremePt->get_center_pt().get_y());
}


void ConvexHullOfDisks::get_pointers_of_disks(const list<CircularDisk2D>& disks, list<CircularDisk2D*>& diskPointers) const
{
    for (list<CircularDisk2D>::const_iterator it_Disk = disks.begin(); it_Disk != disks.end(); ++it_Disk)
    {
        CircularDisk2D* currDisk = const_cast<CircularDisk2D*>(&(*it_Disk));
        diskPointers.push_back(currDisk);
    }
}


void ConvexHullOfDisks::copy_disks_from_its_pointers(const list<CircularDisk2D*>& diskPointers, list<CircularDisk2D>& disks) const
{
    for (list<CircularDisk2D*>::const_iterator it_Disk = diskPointers.begin(); it_Disk != diskPointers.end(); ++it_Disk)
    {
        CircularDisk2D* currDisk = *it_Disk;
        disks.push_back(*currDisk);
    }
}

