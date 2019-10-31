#include "QuickhullDisk.h"
#include "GeometricFunction2D.h"
#include <cstdlib>
using namespace std;

void QuickhullDisk::find_hull_disks(const list<CircularDisk2D>& inputDisks, list<CircularDisk2D>& hullDisks, 
                                const CotangentDisksDividingOption& cotangentDisksDividingOption)
{
    //*. Erase input disks, output extreme disks, and time statistics used before.
    clear_convexhull();

    //*. Set memory of the computation times of each step(#steps: QH_TIME_SIZE) 
    initialize_time_statistics(QH_TIME_SIZE);

    //*. Mark the clock of this line which is the begining of QH_TIME_TOTAL. 
    ___start_clock_in(QH_TIME_TOTAL);

    //* Set cotangent disks' dividing option between RANDOM_DIVIDE and BISECTION_DIVIDE.
    m_CotangentDisksDividingOption = cotangentDisksDividingOption;

    //*. For random selection of disks tangent to a common line, we initialize the seed number.
    if (m_CotangentDisksDividingOption == RANDOM_DIVIDE)
    {
        srand(time(_NULL));
    }

    //*. Set the input disks.
    m_InputDisks = inputDisks;

    //*. Extract pointers of input disks, which is a input format for 'find_hull_disks_by_QHULLDISK'.
    list<CircularDisk2D*> inputDisksForQHullDisk;
    get_pointers_of_disks(m_InputDisks, inputDisksForQHullDisk);

    //*. Run QuickhullDisk [core function].
    find_hull_disks_by_QHULLDISK(inputDisksForQHullDisk, m_HullDisks);
  
    //*. Rearrange for output format
    rearrange_hull_disks_for_output_format_by_begining_with_disk_having_high_left_extreme_point(m_HullDisks);

    //*. Copy extreme disks from disk pointers, which is a output format for 'find_hull_disks'.
    copy_disks_from_its_pointers(m_HullDisks, hullDisks);

    //*. Mark the clock of this line which is the end of QH_TIME_TOTAL. 
    //*. The total computation time of this function is a difference of start and end of QH_TIME_TOTAL, which is automatically stored in time statistics. 
    ___end_clock_in(QH_TIME_TOTAL);
}


void QuickhullDisk::find_hull_disks(const list<CircularDisk2D>& inputDisks, list<CircularDisk2D>& hullDisks)
{
    find_hull_disks(inputDisks, hullDisks, RANDOM_DIVIDE);
}


void QuickhullDisk::find_hull_disks_by_QHULLDISK(const list<CircularDisk2D*>& inputDisks_D, list<CircularDisk2D*>& hullDisks)
{
    ___start_clock_in(QH_TIME_QUICKHULLDISK);

    switch (inputDisks_D.size())
    {
        case 0:
        {
    	    break;
        }

        case 1:
        {
            hullDisks.push_back(inputDisks_D.front());
            break;
        }

        default: /* inputDisks_D.size() >= 2 */
        {

            //*. Initial step
            Point2D highLeftExtremePoint_p, lowRightExtremePoint_q;
            CircularDisk2D* diskHavingHighLeftPoint_p, *diskHavingLowRightPoint_q;
            find_high_left_N_low_right_extreme_points_and_their_disks_to_divide_disk_set(
                inputDisks_D, highLeftExtremePoint_p, lowRightExtremePoint_q, diskHavingHighLeftPoint_p, diskHavingLowRightPoint_q);

            list<CircularDisk2D*> initialExpandedNonPositiveDisks_D_right, initialExpandedNonNegativeDisks_D_left;
            Line2D orientedLineSegment_BaseLine_pq(highLeftExtremePoint_p, lowRightExtremePoint_q);
            divide_input_disks_into_two_initial_subsets(
                inputDisks_D, orientedLineSegment_BaseLine_pq, initialExpandedNonPositiveDisks_D_right, initialExpandedNonNegativeDisks_D_left);

            stack<InputForFindHull> stackForFindingHull;
            prepare_and_insert_input_data_for_finding_hull_to_stack(
                initialExpandedNonNegativeDisks_D_left, diskHavingLowRightPoint_q, diskHavingHighLeftPoint_p,
                lowRightExtremePoint_q, highLeftExtremePoint_p, stackForFindingHull);
            prepare_and_insert_input_data_for_finding_hull_to_stack(
                initialExpandedNonPositiveDisks_D_right, diskHavingHighLeftPoint_p, diskHavingLowRightPoint_q,
                highLeftExtremePoint_p, lowRightExtremePoint_q, stackForFindingHull);

            //*. Main step
            find_hull_disks_by_iteration(stackForFindingHull, hullDisks);
            break;
        }
    }

    ___end_clock_in(QH_TIME_QUICKHULLDISK);
}




void QuickhullDisk::find_high_left_N_low_right_extreme_points_and_their_disks_to_divide_disk_set(const list<CircularDisk2D*>& inputDisks_D, Point2D& highLeftExtremePoint_p, Point2D& lowRightExtremePoint_q, CircularDisk2D*& diskHavingHighLeftExtremePoint_p, CircularDisk2D*& diskHavingLowRightExtremePoint_q) const
{
    find_high_left_extreme_point_N_its_disk(inputDisks_D, highLeftExtremePoint_p, diskHavingHighLeftExtremePoint_p);
    find_low_right_extreme_point_N_its_disk(inputDisks_D, lowRightExtremePoint_q, diskHavingLowRightExtremePoint_q);
}


void QuickhullDisk::divide_input_disks_into_two_initial_subsets(const list<CircularDisk2D*>& inputDisks_D, const Line2D& orientedLineSegment_pq, list<CircularDisk2D*>& initialDisks_D_right, list<CircularDisk2D*>& initialDisks_D_left) const
{
    for (list<CircularDisk2D*>::const_iterator it_Disk = inputDisks_D.begin(); it_Disk != inputDisks_D.end(); ++it_Disk)
    {
        CircularDisk2D* currDisk = *it_Disk;

        if (this_disk_is_a_member_of_expanded_non_positive_set_wrt_line(currDisk, orientedLineSegment_pq))
        {
            initialDisks_D_right.push_back(currDisk);
        }

        if (this_disk_is_a_member_of_expanded_non_negative_set_wrt_line(currDisk, orientedLineSegment_pq))
        {
            initialDisks_D_left.push_back(currDisk);
        }
    }
}


void QuickhullDisk::find_expanded_non_positive_disks_wrt_oriented_line_segment(
    const list<CircularDisk2D*>& disks, const Line2D& orientedLineSegmentOfTwoPtsOn_d1_N_d2,
    CircularDisk2D* disk_d1, CircularDisk2D* disk_d2, list<CircularDisk2D*>& outputDisks, 
    const bool& includingOnPositive /*= false*/) const
{
    if (orientedLineSegmentOfTwoPtsOn_d1_N_d2.get_start_point() != orientedLineSegmentOfTwoPtsOn_d1_N_d2.get_end_point())
    {
        for (list<CircularDisk2D*>::const_iterator it_Disk = disks.begin(); it_Disk != disks.end(); ++it_Disk)
        {
            CircularDisk2D* currDisk = *it_Disk;

            if (currDisk == disk_d1 || currDisk == disk_d2)
            { // do not want numerical decision for d1 and d2, so pass those and insert to list at the end of this function.
                continue;
            }
            else
            {
                if (this_disk_is_a_member_of_expanded_non_positive_set_wrt_line_segment(currDisk, orientedLineSegmentOfTwoPtsOn_d1_N_d2, includingOnPositive))
                {
                    outputDisks.push_back(currDisk);
                }
            }
        }
    }

    if (disk_d1 == disk_d2)
    {
        outputDisks.push_back(disk_d1);
    }
    else
    {
        outputDisks.push_back(disk_d1);
        outputDisks.push_back(disk_d2);
    }
}


void QuickhullDisk::find_hull_disks_by_iteration(stack<InputForFindHull>& stackForFindingHull, list<CircularDisk2D*>& hullDisks) const
{
    while (!stackForFindingHull.empty())
    {
        InputForFindHull    inputOfCurrentStep = stackForFindingHull.top();
        stackForFindingHull.pop();

        list<CircularDisk2D*>& disks_D         = inputOfCurrentStep.disks;
        CircularDisk2D* const  preApexDisk_dp  = inputOfCurrentStep.preApexDisk;
        CircularDisk2D* const  postApexDisk_dq = inputOfCurrentStep.postApexDisk;
        const Point2D&         hullPoint_p     = inputOfCurrentStep.hullPointOfPreApexDisk;
        const Point2D&         hullPoint_q     = inputOfCurrentStep.hullPointOfPostApexDisk;

        const unsigned int numOfDisksInD = disks_D.size();
        if (numOfDisksInD == 1)
        {
            hullDisks.push_back(preApexDisk_dp);  /*Output*/
        }
        else if (numOfDisksInD == 2 && (preApexDisk_dp != postApexDisk_dq))
        {
            hullDisks.push_back(preApexDisk_dp);  /*Output*/
            hullDisks.push_back(postApexDisk_dq); /*Output*/
        }
        else
        {
            //*. Make two sets for next interation.
            list<CircularDisk2D*> disks_D_FrontEdge, disks_D_BackEdge;

            Point2D         triangleApex_x;
            CircularDisk2D* apexDisk_dx = _NULL;

            Line2D orientedLineSegment_BaseEdge_pq(hullPoint_p, hullPoint_q);
            list<pair<Point2D, CircularDisk2D*>> candidateApexNDiskPairs;
            find_the_highest_triangle_apex_and_the_apex_disk_wrt_this_oriented_line_segment(disks_D, orientedLineSegment_BaseEdge_pq, candidateApexNDiskPairs);
            
            if (candidateApexNDiskPairs.size() == 1)
            {
                triangleApex_x = candidateApexNDiskPairs.front().first;
                apexDisk_dx    = candidateApexNDiskPairs.front().second;
            }
            else //(apexPointNItsDisks.size() > 1)
            {
                pick_one_as_triangle_apex_and_apex_disk_among_disks_with_identical_height_and_remove_disks_contained_in_others_from_input_disks_if_exist(
                    candidateApexNDiskPairs, triangleApex_x, apexDisk_dx, disks_D, m_CotangentDisksDividingOption);
            }

            Line2D orientedLineSegment_FrontEdge_px(hullPoint_p, triangleApex_x);
            Line2D orientedLineSegment_BackEdge_xq(triangleApex_x, hullPoint_q);
            find_expanded_non_positive_disks_wrt_oriented_line_segment(
                disks_D, orientedLineSegment_FrontEdge_px, preApexDisk_dp, apexDisk_dx, disks_D_FrontEdge, true);
            find_expanded_non_positive_disks_wrt_oriented_line_segment(
                disks_D, orientedLineSegment_BackEdge_xq, apexDisk_dx, postApexDisk_dq, disks_D_BackEdge, true);

            //* Intriguing case 
            if (triangle_filter_is_sliver(disks_D.size(), disks_D_FrontEdge.size(), disks_D_BackEdge.size(), preApexDisk_dp, postApexDisk_dq))
            {
                disks_D_FrontEdge.clear();
                disks_D_BackEdge.clear();

                regularize_sliver_triangle_and_repivot_disks(
                    inputOfCurrentStep, disks_D_FrontEdge, disks_D_BackEdge, apexDisk_dx, triangleApex_x);
            }

            prepare_and_insert_input_data_for_finding_hull_to_stack(
                disks_D_BackEdge, apexDisk_dx, postApexDisk_dq, triangleApex_x, hullPoint_q, stackForFindingHull);
            prepare_and_insert_input_data_for_finding_hull_to_stack(
                disks_D_FrontEdge, preApexDisk_dp, apexDisk_dx, hullPoint_p, triangleApex_x, stackForFindingHull);
        }
    }

    //*. Current 'hullDisks' has same disks consecutively, so delete the repeated disks and make one.
    hullDisks.unique();
}



void QuickhullDisk::regularize_sliver_triangle_and_repivot_disks(
    InputForFindHull& inputForFindHull, list<CircularDisk2D*>& disks_D_FrontEdge, list<CircularDisk2D*>& disks_D_BackEdge, 
    CircularDisk2D*& pivotDisk_dx, Point2D& pivotPoint_x) const
{
    list<CircularDisk2D*>&       disks_D         = inputForFindHull.disks;
    CircularDisk2D* const        preApexDisk_dp  = inputForFindHull.preApexDisk;
    CircularDisk2D* const        postApexDisk_dq = inputForFindHull.postApexDisk;
    const Point2D&               hullPoint_p     = inputForFindHull.hullPointOfPreApexDisk;
    const Point2D&               hullPoint_q     = inputForFindHull.hullPointOfPostApexDisk;

    Line2D nonNegativeSupportingTangentLineSegmentFrom_dp_to_dq 
        = ConvexHullOfDisks::compute_a_CCW_oriented_tangent_line_from_disk_d1_to_d2(*preApexDisk_dp, *postApexDisk_dq);

    list<pair<Point2D, CircularDisk2D*>> triangleApexNDiskPairsOfExpandedNonPositive;
    list<pair<Point2D, CircularDisk2D*>> triangleApexNDiskPairsOfOnPositiveExcept_dp_N_dq;

    SliverConfiguration sliverConfiguration = find_sliver_triangle_configuration_and_apex_disks(
        disks_D, nonNegativeSupportingTangentLineSegmentFrom_dp_to_dq, preApexDisk_dp, postApexDisk_dq, 
        triangleApexNDiskPairsOfExpandedNonPositive, triangleApexNDiskPairsOfOnPositiveExcept_dp_N_dq);

    switch (sliverConfiguration)
    {
        case SLIVER_CASE_A:
        {
            list<pair<Point2D, CircularDisk2D*>> triangleApexNDiskPairsOf_dp_N_dq;
            triangleApexNDiskPairsOf_dp_N_dq.push_back(
                make_pair(nonNegativeSupportingTangentLineSegmentFrom_dp_to_dq.get_start_point(), preApexDisk_dp));
            triangleApexNDiskPairsOf_dp_N_dq.push_back(
                make_pair(nonNegativeSupportingTangentLineSegmentFrom_dp_to_dq.get_end_point() , postApexDisk_dq));

            pick_one_as_triangle_apex_and_apex_disk(
                triangleApexNDiskPairsOf_dp_N_dq, pivotPoint_x, pivotDisk_dx, m_CotangentDisksDividingOption);
            break;
        }
        case SLIVER_CASE_B:
        {
            if (triangleApexNDiskPairsOfOnPositiveExcept_dp_N_dq.size() == 1)
            {
                pivotPoint_x = triangleApexNDiskPairsOfOnPositiveExcept_dp_N_dq.front().first;
                pivotDisk_dx = triangleApexNDiskPairsOfOnPositiveExcept_dp_N_dq.front().second;
            }
            else // (triangleApexNDiskPairsOfOnPositiveExcept_dp_N_dq.size() >= 2)
            {
                pick_one_as_triangle_apex_and_apex_disk_among_disks_with_identical_height_and_remove_disks_contained_in_others_from_input_disks_if_exist(
                    triangleApexNDiskPairsOfOnPositiveExcept_dp_N_dq, pivotPoint_x, pivotDisk_dx, disks_D, m_CotangentDisksDividingOption);
            }

            break;
        }
        case SLIVER_CASE_C1:
        {
            pivotPoint_x = triangleApexNDiskPairsOfExpandedNonPositive.front().first;
            pivotDisk_dx = triangleApexNDiskPairsOfExpandedNonPositive.front().second;
            break;
        }
        case SLIVER_CASE_C2:
        {
            pick_one_as_triangle_apex_and_apex_disk_among_disks_with_identical_height_and_remove_disks_contained_in_others_from_input_disks_if_exist(
                triangleApexNDiskPairsOfExpandedNonPositive, pivotPoint_x, pivotDisk_dx, disks_D, m_CotangentDisksDividingOption);

            break;
        }
    }

    Line2D orientedLineSegment_FrontEdge_px(hullPoint_p, pivotPoint_x);
    find_expanded_non_positive_disks_wrt_oriented_line_segment(
        disks_D, orientedLineSegment_FrontEdge_px, preApexDisk_dp, pivotDisk_dx, disks_D_FrontEdge, true);

    Line2D orientedLineSegment_BackEdge_xq(pivotPoint_x, hullPoint_q);
    find_expanded_non_positive_disks_wrt_oriented_line_segment(
        disks_D, orientedLineSegment_BackEdge_xq, pivotDisk_dx, postApexDisk_dq, disks_D_BackEdge, true);
}



SliverConfiguration QuickhullDisk::find_sliver_triangle_configuration_and_apex_disks(
    list<CircularDisk2D*>& disks_D, const Line2D& nonNegativeSupportingTangentLineSegmentFrom_dp_to_dq, CircularDisk2D* preApexDisk_dp, CircularDisk2D* postApexDisk_dq,
    list<pair<Point2D, CircularDisk2D*>>& triangleApexNDiskPairsOfExpandedNonPositive, list<pair<Point2D, CircularDisk2D*>>& triangleApexNDiskPairsOfOnPositiveExcept_dp_N_dq) const
{
    SliverConfiguration sliverConfiguration;

    list<pair<Point2D, CircularDisk2D*>> triangleApexNDiskPairs;
    find_the_highest_triangle_apex_and_the_apex_disk_wrt_this_oriented_line_segment(
        disks_D, nonNegativeSupportingTangentLineSegmentFrom_dp_to_dq, triangleApexNDiskPairs, true, preApexDisk_dp, postApexDisk_dq);
  
    CircularDisk2D* candidateApexDisk = triangleApexNDiskPairs.front().second;
    double heightOfTriangleApex       = candidateApexDisk->get_radius() - nonNegativeSupportingTangentLineSegmentFrom_dp_to_dq.signed_distance(candidateApexDisk->get_center_pt());

    if (_ZERO(heightOfTriangleApex))
    {
        list<CircularDisk2D*> containedDisksInPreOrPostApexDisk;
        remove_pre_and_post_apex_disks_and_contained_disks_in_one_of_the_two_from_candidate_apex_disks_if_exist(
            preApexDisk_dp, postApexDisk_dq, triangleApexNDiskPairs, containedDisksInPreOrPostApexDisk);

        if (!containedDisksInPreOrPostApexDisk.empty())
        {
            remove_contained_disks_from_input_disks(containedDisksInPreOrPostApexDisk, disks_D);
        }

        if (triangleApexNDiskPairs.size() == 0)
        {
            sliverConfiguration = SLIVER_CASE_A;
        }
        else //(triangleApexNDiskPairs.size() >= 1)
        {
            sliverConfiguration = SLIVER_CASE_B;
            triangleApexNDiskPairsOfOnPositiveExcept_dp_N_dq = triangleApexNDiskPairs;
        }
    }
    else
    {
        if (triangleApexNDiskPairs.size() == 1)
        {
            sliverConfiguration = SLIVER_CASE_C1;
            triangleApexNDiskPairsOfExpandedNonPositive.push_back(triangleApexNDiskPairs.front());
        }
        else // (triangleApexNDiskPairs.size() >= 2)
        {
            sliverConfiguration = SLIVER_CASE_C2;
            triangleApexNDiskPairsOfExpandedNonPositive = triangleApexNDiskPairs;
        }
    }

    return sliverConfiguration;
}


void QuickhullDisk::remove_pre_and_post_apex_disks_and_contained_disks_in_one_of_the_two_from_candidate_apex_disks_if_exist(
    CircularDisk2D* preApexDisk_dp, CircularDisk2D* postApexDisk_dq, 
    list<pair<Point2D, CircularDisk2D*>>& candidateTriangleApexNDiskPairs, list<CircularDisk2D*>& containedDisksInPreOrPostApexDisk) const
{
    list<pair<Point2D, CircularDisk2D*>>::const_iterator it_TriangleApexNDisk = candidateTriangleApexNDiskPairs.begin();
   
    while (it_TriangleApexNDisk != candidateTriangleApexNDiskPairs.end())
    {
        CircularDisk2D* candidateApexDisk = (*it_TriangleApexNDisk).second;

        if (candidateApexDisk == preApexDisk_dp || candidateApexDisk == postApexDisk_dq)
        {
            it_TriangleApexNDisk = candidateTriangleApexNDiskPairs.erase(it_TriangleApexNDisk);
            continue;
        }

        if (preApexDisk_dp->contain(*candidateApexDisk, _resNeg6) || postApexDisk_dq->contain(*candidateApexDisk, _resNeg6))
        {
            containedDisksInPreOrPostApexDisk.push_back(candidateApexDisk);
            it_TriangleApexNDisk = candidateTriangleApexNDiskPairs.erase(it_TriangleApexNDisk);
        }
        else
        {
            ++it_TriangleApexNDisk;
        }
    }
}


void QuickhullDisk::find_the_highest_triangle_apex_and_the_apex_disk_wrt_this_oriented_line_segment(
    const list<CircularDisk2D*>& disks_D, const Line2D& orientedLineSegment_pq, 
    list<pair<Point2D, CircularDisk2D*>>& apexNDiskPairs, const bool& orientedLineIsNonNegativeSupportOf_dp_N_dq /*= false*/,
    CircularDisk2D* preApexDisk_dp /*= _NULL*/, CircularDisk2D* postApexDisk_dq /*= _NULL*/) const
{
    double largestMaxPerpendicularDistanceFromLineToBoundaryOfDiskAmongDisks = 0.0;

    for (list<CircularDisk2D*>::const_iterator it_Disk = disks_D.begin(); it_Disk != disks_D.end(); ++it_Disk)
    {
        CircularDisk2D* currDisk = *it_Disk;

        if (orientedLineIsNonNegativeSupportOf_dp_N_dq && (currDisk == preApexDisk_dp || currDisk == postApexDisk_dq))
        {  // avoid numerical decision for preApexDisk_dp and preApexDisk_dp
            continue;
        }

        double maxPerpendicularDistanceFromLineToBoundaryOfCurrDisk = currDisk->get_radius() - orientedLineSegment_pq.signed_distance(currDisk->get_center_pt());

        if (_GT(maxPerpendicularDistanceFromLineToBoundaryOfCurrDisk, largestMaxPerpendicularDistanceFromLineToBoundaryOfDiskAmongDisks))
        {
            largestMaxPerpendicularDistanceFromLineToBoundaryOfDiskAmongDisks = maxPerpendicularDistanceFromLineToBoundaryOfCurrDisk;
            
            apexNDiskPairs.clear();
            Point2D farthestPointOnCurrDiskTouchingTangentLine = find_the_fartest_point_of_disk_from_this_line(*currDisk, orientedLineSegment_pq);
            apexNDiskPairs.push_back(make_pair(farthestPointOnCurrDiskTouchingTangentLine, currDisk));
        }
        else if (_EQ(maxPerpendicularDistanceFromLineToBoundaryOfCurrDisk, largestMaxPerpendicularDistanceFromLineToBoundaryOfDiskAmongDisks))
        {
            Point2D farthestPointOnCurrDiskTouchingTangentLine = find_the_fartest_point_of_disk_from_this_line(*currDisk, orientedLineSegment_pq);
            apexNDiskPairs.push_back(make_pair(farthestPointOnCurrDiskTouchingTangentLine, currDisk));
        }
    }

    if (orientedLineIsNonNegativeSupportOf_dp_N_dq && _ZERO(largestMaxPerpendicularDistanceFromLineToBoundaryOfDiskAmongDisks))
    {
        if (preApexDisk_dp != _NULL)
        {
            apexNDiskPairs.push_back(make_pair(orientedLineSegment_pq.get_start_point(), preApexDisk_dp));
        }

        if (postApexDisk_dq != _NULL)
        {
            apexNDiskPairs.push_back(make_pair(orientedLineSegment_pq.get_end_point(), postApexDisk_dq));
        }
    }
}



void QuickhullDisk::pick_one_as_triangle_apex_and_apex_disk_among_disks_with_identical_height_and_remove_disks_contained_in_others_from_input_disks_if_exist(
    const list<pair<Point2D, CircularDisk2D*>>& apexNDiskPairs, Point2D& triangleApex_x, CircularDisk2D*& apexDisk_dx, list<CircularDisk2D*>& disks_D, 
    const CotangentDisksDividingOption& cotangentDisksDividingOption) const
{
    Point2D         candidateOfTriangleApex;
    CircularDisk2D* candidateOfApexDisk = _NULL;

    pick_one_as_triangle_apex_and_apex_disk(
        apexNDiskPairs, candidateOfTriangleApex, candidateOfApexDisk, cotangentDisksDividingOption);

    list<CircularDisk2D*> containdDisksInOthers;
    triangleApex_x = candidateOfTriangleApex;
    apexDisk_dx    = find_largest_apex_disk_containing_this_apex_disk_selected_from_candidates(apexNDiskPairs, candidateOfApexDisk, containdDisksInOthers);

    if (!containdDisksInOthers.empty())
    {
        remove_contained_disks_from_input_disks(containdDisksInOthers, disks_D);
    }
}



void QuickhullDisk::pick_one_as_triangle_apex_and_apex_disk(
    const list<pair<Point2D, CircularDisk2D*>>& apexNDiskPairs, Point2D& triangleApex_x, CircularDisk2D*& apexDisk_dx, const CotangentDisksDividingOption& cotangentDisksDividingOption) const
{
    if (apexNDiskPairs.size() >= 2)
    {
        int generatedNumber = 0;
        switch (cotangentDisksDividingOption)
        {
            case RANDOM_DIVIDE:
            {
                generatedNumber = rand() % apexNDiskPairs.size();
                break;
            }

            case BISECTION_DIVIDE:
            {
                generatedNumber = apexNDiskPairs.size()  / 2;
                break;
            }
        }

        list<pair<Point2D, CircularDisk2D*>>::const_iterator it_ApexNItsDisk = apexNDiskPairs.begin();
        for (int i = 0; i < generatedNumber; ++i)
        {
            ++it_ApexNItsDisk;
        }

        triangleApex_x = (*it_ApexNItsDisk).first;
        apexDisk_dx    = (*it_ApexNItsDisk).second;
    }
    else // (apexNDiskPairs.size() == 1)
    {
        triangleApex_x = apexNDiskPairs.front().first;
        apexDisk_dx    = apexNDiskPairs.front().second;
    }
}



CircularDisk2D* QuickhullDisk::find_largest_apex_disk_containing_this_apex_disk_selected_from_candidates(const list<pair<Point2D, CircularDisk2D*>>& candidateTriangleApexNDiskPairs, CircularDisk2D* selectedApexDisk, list<CircularDisk2D*>& containdDisksInOthers) const
{
    CircularDisk2D* largestApexDiskContainingCandidateApexDisk = selectedApexDisk;

    for (list<pair<Point2D, CircularDisk2D*>>::const_iterator it_ApexNItsDisk = candidateTriangleApexNDiskPairs.begin(); 
         it_ApexNItsDisk != candidateTriangleApexNDiskPairs.end(); 
         ++it_ApexNItsDisk)
    {
        Point2D      currTriangleApex = (*it_ApexNItsDisk).first;
        CircularDisk2D* currApexDisk  = (*it_ApexNItsDisk).second;

        if (currApexDisk == largestApexDiskContainingCandidateApexDisk)
        {
            continue;
        }

        if (currApexDisk->contain(*largestApexDiskContainingCandidateApexDisk, _resNeg6))
        {
            containdDisksInOthers.push_back(largestApexDiskContainingCandidateApexDisk);
            largestApexDiskContainingCandidateApexDisk = currApexDisk;
        }
        else if (largestApexDiskContainingCandidateApexDisk->contain(*currApexDisk, _resNeg6))
        {
            containdDisksInOthers.push_back(currApexDisk);
        }
    }

    return largestApexDiskContainingCandidateApexDisk;
}


void QuickhullDisk::remove_contained_disks_from_input_disks(const list<CircularDisk2D*>& containdDisksInOthers, list<CircularDisk2D*>& disks_D) const
{
    for (list<CircularDisk2D*>::const_iterator it_ContainedDisk = containdDisksInOthers.begin();
        it_ContainedDisk != containdDisksInOthers.end();
        ++it_ContainedDisk)
    {
        disks_D.remove(*it_ContainedDisk);
    }
}

