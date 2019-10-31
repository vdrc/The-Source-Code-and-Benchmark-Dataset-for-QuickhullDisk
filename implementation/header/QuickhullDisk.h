 /**
  * \class QuickhullDisk
  * \brief A class for QuickhullDisk algorithm, which inherits from ConvexHullOfDisks.
  *
  * \details  It can find hull(extreme) disks even if inclusion and intersection between disks exists. 
  *           It removes the contained smaller disk on-the-fly during the convexhull computation.
  *           Although this algorithm is decribed by the concept of recursion in our paper,   
  *            it is implemented with iteration, not with recursion. 
  */

  //* This is a source code for implementation of "QuickhullDisk: A Faster Convex Hull Algorithm for Disks."
  //* Code authors: Chanyoung Song, Joonghyun Ryu, and Deok-Soo Kim.
  //* Version:      1.0
  //* Date:         2019

#ifndef _QHULLDISK_H_ 
#define _QHULLDISK_H_ 

#include "ConstSet.h"
#include "ConvexHullOfDisks.h"
#include <stack>
using namespace std;

/*!
* \enum  CotangentDisksDividingOption
* \brief This is dividing option when disks are cotangent to one common line.
*/
enum CotangentDisksDividingOption
{
    RANDOM_DIVIDE,
    BISECTION_DIVIDE
};

/*!
* \enum  SliverConfiguration
* \brief This is configuration type of sliver triangle filter.
*/
enum SliverConfiguration
{
    SLIVER_CASE_A,
    SLIVER_CASE_B,
    SLIVER_CASE_C1,
    SLIVER_CASE_C2
};


/*!
* \enum  QHullDiskAlgorithmStep
* \brief This is for checking computation time of each step. 
         Each computation time is stored in 'ConvexHullOfDisks::m_TimeStatistics' which is a vector of size 'QH_TIME_SIZE'.
*/
enum QHullDiskAlgorithmStep
{
    QH_TIME_QUICKHULLDISK,
    QH_TIME_TOTAL,
    QH_TIME_SIZE
};


/*! 
* \struct InputForFindHull 
* \brief  This is a representation for input of FindHull at each iteration.  
*/
struct InputForFindHull
{
    list<CircularDisk2D*> disks;
    CircularDisk2D*       preApexDisk;
    CircularDisk2D*       postApexDisk;
    Point2D               hullPointOfPreApexDisk;
    Point2D               hullPointOfPostApexDisk;
};

class QuickhullDisk: public ConvexHullOfDisks
{
private: 
    CotangentDisksDividingOption m_CotangentDisksDividingOption;

public:
    /**
    * \brief Find hull disks by QuickhullDisk; This function calls core function 'find_hull_disks_by_QHULLDISK'.
    *
    * \param[in]  inputDisks                     The input disks of convex hull problem.
    * \param[in]  cotangentDisksDividingOption   The dividing option for cotangent disks.
    *
    * \param[out] hullDisks     The output hull disks stored in CCW direction starting from a disk having high left extreme point.
    *                           The same disk may occur many times but not consecutively;
    *                            ex. Possible result:(d_1, d_2, d_1, d_3, d_4, d_1, ...),
    *                                impossible result: (d_1, d_2, d_2, d_2, d_4, d_1, ...) because d_2 occurs consecutively.
    *                           The first disk must occurs at the last; ex. (d_1, ..., d_1).
    */
    void find_hull_disks(const list<CircularDisk2D>& inputDisks, list<CircularDisk2D>& hullDisks, 
                         const CotangentDisksDividingOption& cotangentDisksDividingOption);

    void find_hull_disks(const list<CircularDisk2D>& inputDisks, list<CircularDisk2D>& hullDisks);

private:
    void find_hull_disks_by_QHULLDISK(const list<CircularDisk2D*>& inputDisks_D, list<CircularDisk2D*>& hullDisks);

    void find_high_left_N_low_right_extreme_points_and_their_disks_to_divide_disk_set(
                                                              const list<CircularDisk2D*>& inputDisks_D, 
                                                              Point2D& highLeftExtremePoint_p, 
                                                              Point2D& lowRightExtremePoint_q, 
                                                              CircularDisk2D*& diskHavingHighLeftExtremePoint_p, 
                                                              CircularDisk2D*& diskHavingLowRightExtremePoint_q) const;
    
    void find_expanded_non_positive_disks_wrt_oriented_line_segment(
                                                              const list<CircularDisk2D*>& disks, 
                                                              const Line2D& orientedLineSegmentOfTwoPtsOn_d1_N_d2, 
                                                              CircularDisk2D* disk_d1, 
                                                              CircularDisk2D* disk_d2,
                                                              list<CircularDisk2D*>& outputDisks,
                                                              const bool& includingOnPositive = false) const;

    void divide_input_disks_into_two_initial_subsets(const list<CircularDisk2D*>& inputDisks_D, 
                                                     const Line2D& orientedLineSegment_pq, 
                                                     list<CircularDisk2D*>& initialDisks_D_right, 
                                                     list<CircularDisk2D*>& initialDisks_D_left) const;
    
    inline void prepare_and_insert_input_data_for_finding_hull_to_stack(const list<CircularDisk2D*>& disks,
                                                        CircularDisk2D*       preApexDisk,
                                                        CircularDisk2D*       postApexDisk,
                                                        const Point2D&        hullPointOfPreApexDisk,
                                                        const Point2D&        hullPointOfPostApexDisk,
                                                        stack<InputForFindHull>& stackForFindingHull) const;

    void find_hull_disks_by_iteration(stack<InputForFindHull>& stackForFindingHull, list<CircularDisk2D*>& hullDisks) const;

    void find_the_highest_triangle_apex_and_the_apex_disk_wrt_this_oriented_line_segment(const list<CircularDisk2D*>& disks_D, 
                                                                                 const Line2D& orientedLineSegment_pq, 
                                                                                 list<pair<Point2D, CircularDisk2D*>>& apexNDiskPairs,
                                                                                 const bool& orientedLineIsNonNegativeSupportOf_dp_N_dq = false, 
                                                                                 CircularDisk2D* preApexDisk_dp = _NULL,
                                                                                 CircularDisk2D* postApexDisk_dq = _NULL) const;

    void pick_one_as_triangle_apex_and_apex_disk_among_disks_with_identical_height_and_remove_disks_contained_in_others_from_input_disks_if_exist(
                                                                 const list<pair<Point2D, CircularDisk2D*>>& apexNDiskPairs, 
                                                                 Point2D& triangleApex_x, 
                                                                 CircularDisk2D*& apexDisk_dx, 
                                                                 list<CircularDisk2D*>& disks_D, 
                                                                 const CotangentDisksDividingOption& cotangentDisksDividingOption) const;
  
    void pick_one_as_triangle_apex_and_apex_disk(const list<pair<Point2D, CircularDisk2D*>>& apexNDiskPairs, 
                                                 Point2D& triangleApex_x, 
                                                 CircularDisk2D*& apexDisk_dx, 
                                                 const CotangentDisksDividingOption& cotangentDisksDividingOption) const;

    CircularDisk2D* find_largest_apex_disk_containing_this_apex_disk_selected_from_candidates(const list<pair<Point2D, CircularDisk2D*>>& candidateTriangleApexNDiskPairs, CircularDisk2D* selectedApexDisk, list<CircularDisk2D*>& containdDisksInOthers) const;

    void remove_contained_disks_from_input_disks(const list<CircularDisk2D*>& containdDisksInOthers, list<CircularDisk2D*>& disks_D) const;

    inline bool triangle_filter_is_sliver(const int& numOfInputDisks, 
                                          const int& numOfDisksOnFrontEdge,
                                          const int& numOfDisksOnBackEdge,
                                          CircularDisk2D* preApexDisk_dp,
                                          CircularDisk2D* postApexDisk_dq) const;

    void regularize_sliver_triangle_and_repivot_disks( InputForFindHull& inputForFindHull,
                                                                                       list<CircularDisk2D*>& disks_D_FrontEdge,
                                                                                       list<CircularDisk2D*>& disks_D_BackEdge,
                                                                                       CircularDisk2D*& pivotDisk_dx,
                                                                                       Point2D& pivotPoint_x) const;

    SliverConfiguration find_sliver_triangle_configuration_and_apex_disks(list<CircularDisk2D*>& disks_D,
                                                                          const Line2D& nonNegativeSupportingTangentLineSegmentFrom_dp_to_dq, 
                                                                          CircularDisk2D* preApexDisk_dp, 
                                                                          CircularDisk2D* postApexDisk_dq, 
                                                                          list<pair<Point2D, CircularDisk2D*>>& triangleApexNDiskPairsOfExpandedNonPositive, 
                                                                          list<pair<Point2D, CircularDisk2D*>>& triangleApexNDiskPairsOfOnPositiveExcept_dp_N_dq) const;

    void remove_pre_and_post_apex_disks_and_contained_disks_in_one_of_the_two_from_candidate_apex_disks_if_exist(
                                                         CircularDisk2D* preApexDisk_dp,
                                                         CircularDisk2D* postApexDisk_dq,
                                                         list<pair<Point2D, CircularDisk2D*>>& candidateTriangleApexNDiskPairs,
                                                         list<CircularDisk2D*>& containedDisksInPreOrPostApexDisk) const;

    inline Point2D find_the_fartest_point_of_disk_from_this_line(const Circle2D& disk, const Line2D& orientedLine) const;

};


inline Point2D QuickhullDisk::find_the_fartest_point_of_disk_from_this_line(const Circle2D& disk, const Line2D& orientedLine) const
{
    Point2D negativeDirection = -orientedLine.get_normal_vector();
    Point2D farthestPoint     = negativeDirection.get_unit_vector() * disk.get_radius() + disk.get_center_pt();

    return farthestPoint;
}


inline void QuickhullDisk::prepare_and_insert_input_data_for_finding_hull_to_stack(const list<CircularDisk2D*>& disks, 
                                                               CircularDisk2D* preApexDisk, 
                                                               CircularDisk2D* postApexDisk, 
                                                               const Point2D& hullPointOfPreApexDisk, 
                                                               const Point2D& hullPointOfPostApexDisk, 
                                                               stack<InputForFindHull>& stackForFindingHull) const
{
    InputForFindHull inputForFindHull{ disks, preApexDisk, postApexDisk, hullPointOfPreApexDisk, hullPointOfPostApexDisk };
    stackForFindingHull.push(inputForFindHull);
}


inline bool QuickhullDisk::triangle_filter_is_sliver(const int& numOfInputDisks, 
                                                 const int& numOfDisksOnFrontEdge, 
                                                 const int& numOfDisksOnBackEdge, 
                                                 CircularDisk2D* preApexDisk_dp, 
                                                 CircularDisk2D* postApexDisk_dq) const
{
    return ((preApexDisk_dp != postApexDisk_dq) &&
            ((numOfDisksOnFrontEdge == numOfInputDisks && numOfDisksOnBackEdge == 1) || (numOfDisksOnFrontEdge == 1 && numOfDisksOnBackEdge == numOfInputDisks))
            );
}

#endif //_QHULLDISKS_