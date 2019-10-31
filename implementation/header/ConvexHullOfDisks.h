/**
 * \class ConvexHullOfDisks
 * \brief A class for convex hull problem of disks in 2-dimensional space.
 * 
 * \details Let D be a set of disks.
 *          Let x ¡ô ¡ÓConv(D) be a hull point. The disk d ¡ô D where x ¡ô ¡Ód is a hull disk.
 *          This algorithm finds hull disks. 
 */

 //* This is a source code for implementation of "QuickhullDisk: A Faster Convex Hull Algorithm for Disks."
 //* Code authors: Chanyoung Song, Joonghyun Ryu, and Deok-Soo Kim.
 //* Version:      1.0
 //* Date:         2019


#ifndef _CONVEX_HULL_OF_DISKS_ 
#define _CONVEX_HULL_OF_DISKS_ 

#include "ConstSet.h"
#include "Line2D.h"
#include "CircularDisk2D.h"
#include "CircularArc2D.h"
#include "TimeStatistics.h"
#include <list>
using namespace std;

class ConvexHullOfDisks
{
protected:
    list<CircularDisk2D>    m_InputDisks;
    list<CircularDisk2D*>   m_HullDisks;  /*< Pointers in the 'm_HullDisks' list points to the objects in 'm_InputDisks'. */
    TimeStatistics          m_TimeStatistics;

public:
    inline const list<CircularDisk2D>&  get_input_disks()     const { return m_InputDisks;     };
    inline const list<CircularDisk2D*>& get_hull_disks()      const { return m_HullDisks;      };
    inline const TimeStatistics&        get_time_statistics() const { return m_TimeStatistics; };

    void get_input_disks  (list<CircularDisk2D*>& inputDisks)   const;
    void get_hull_disks(list<CircularDisk2D*>& hullDisks) const;
    void get_hull_disks(list<CircularDisk2D>& hullDisks)  const;
    void get_pointers_of_disks(const list<CircularDisk2D>& disks, list<CircularDisk2D*>& diskPointers) const;
    void copy_disks_from_its_pointers(const list<CircularDisk2D*>& diskPointers, list<CircularDisk2D>& disks) const;
    
    /**
    * \brief Find extreme disks. Should be implemented in inherited class following the below parameter rules.
    *
    * \param[in]  inputDisks    The input disks of convex hull problem.
    * \param[out] hullDisks     The output hull disks stored in CCW direction starting from a disk having high left extreme point.
    *                           The same disk may occur many times but not consecutively; 
    *                            ex. Possible result:(d_1, d_2, d_1, d_3, d_4, d_1, ...), 
    *                                impossible result: (d_1, d_2, d_2, d_2, d_4, d_1, ...) because d_2 occurs consecutively.
    *                           The first disk must occurs at the last; ex. (d_1, ..., d_1).
    */
    virtual void find_hull_disks(const list<CircularDisk2D>& inputDisks, list<CircularDisk2D>& hullDisks) = 0;
    virtual void clear_convexhull();

    /**
    * \brief Extract convex hull boundary from the input hull disks.
    *
    * \details It assumes the input 'hullDisks' are hull disks. If not, you cannot get a correct solution.
    *          
    * \param[in]  hullDisks           The input hull disks of convex hull. ex. ( d_1, d_2, ..., d_k ).
    * \param[out] convexHullBoundary  The output convex hull boundary consist of pairs of arc(a_i) and line(t_i) so that the boundary is stored as ( (a_1, tl_1), (a_2, tl_2), ..., (a_k, tl_k) )
    *                                  where arc is on boundary of disk (d_i) and line is tangent to two consecutive hull disks (d_i, d_i+1).
    *                                 The start point of line 'tl_i' equals to the end point of arc 'a_i' and the end point of line 'tl_i' equals to the start point of arc 'a_i+1'.
    *                                 Notice that the end point of 'tl_k' is equals to the start point of 'a_1'.
    *                                 If the size of hullDisks is 1, it returns an circle arc and unmeaningful line having two end points as (x, y) = (DBL_MAX, DBL_MAX).
    * \param[return] length of convex hull boundary 
    */
    static double extract_convexhull_boundary(const list<CircularDisk2D>& hullDisks, list<pair<CircularArc2D, Line2D>>& boundaryArcNLines);
    static Line2D compute_a_CCW_oriented_tangent_line_from_disk_d1_to_d2(const CircularDisk2D& disk1, const CircularDisk2D& disk2);

    inline static bool disk1_is_smaller_than_disk2(CircularDisk2D*& disk1, CircularDisk2D*& disk2);
    inline static bool disk1_is_larger_than_disk2(CircularDisk2D*& disk1,  CircularDisk2D*& disk2);

protected:
    inline bool this_disk_is_a_member_of_expanded_non_positive_set_wrt_line(CircularDisk2D* candidateDisk, const Line2D& orientedLineSegment, const bool& includingOnPositive = false) const;
    inline bool this_disk_is_a_member_of_expanded_non_negative_set_wrt_line(CircularDisk2D* candidateDisk, const Line2D& orientedLineSegment, const bool& includingOnNegative = false) const;
    inline bool this_disk_is_a_member_of_expanded_non_positive_set_wrt_line_segment(CircularDisk2D* candidateDisk, const Line2D& orientedLineSegment, const bool& includingOnPositive = false) const;

    void sort_disks_by_their_radius_in_decreasing_order(const list<CircularDisk2D*>& inputDisks, list<CircularDisk2D*>& sortedDisks) const;
    void rearrange_hull_disks_for_output_format_by_begining_with_disk_having_high_left_extreme_point(list<CircularDisk2D*>& hullDisks) const;
    void find_high_left_extreme_point_N_its_disk(const list<CircularDisk2D*>& inputDisks, Point2D& highLeftExtremePt, CircularDisk2D*& diskHavingHighLeftExtremePt) const;
    void find_low_right_extreme_point_N_its_disk(const list<CircularDisk2D*>& inputDisks, Point2D& lowRightExtremePt, CircularDisk2D*& diskHavingLowRightExtremePt) const;

    inline void initialize_time_statistics(const unsigned int& size) { m_TimeStatistics.reset(size); };
    inline void ___start_clock_in(const unsigned int& step)          { m_TimeStatistics.start_clock(step); };
    inline void ___end_clock_in(const unsigned int& step)            { m_TimeStatistics.end_clock(step); };
};



inline bool ConvexHullOfDisks::this_disk_is_a_member_of_expanded_non_negative_set_wrt_line(CircularDisk2D* candidateDisk, const Line2D& orientedLineSegment, const bool& includingOnNegative) const
{
    if (includingOnNegative)
    {
        return (_GE(orientedLineSegment.signed_distance(candidateDisk->get_center_pt()), -candidateDisk->get_radius()));
    }
    else
    {
        return (_GT(orientedLineSegment.signed_distance(candidateDisk->get_center_pt()), -candidateDisk->get_radius()));
    }
}


inline bool ConvexHullOfDisks::this_disk_is_a_member_of_expanded_non_positive_set_wrt_line(CircularDisk2D* candidateDisk, const Line2D& orientedLineSegment, const bool& includingOnPositive) const
{
    if (includingOnPositive)
    {
        return (_LE(orientedLineSegment.signed_distance(candidateDisk->get_center_pt()), candidateDisk->get_radius()));
    }
    else
    {
        return (_LT(orientedLineSegment.signed_distance(candidateDisk->get_center_pt()), candidateDisk->get_radius()));
    }
}


inline bool ConvexHullOfDisks::this_disk_is_a_member_of_expanded_non_positive_set_wrt_line_segment(CircularDisk2D* candidateDisk, const Line2D& orientedLineSegment, const bool& includingOnPositive) const
{
    Line2D orientedLine              = orientedLineSegment;
    Line2D orthogonalLineAtStartPt   = orientedLine.make_perpendicular_line(orientedLineSegment.get_start_point());
    Line2D orthogonalLineAtEndPt     = orientedLine.make_perpendicular_line(orientedLineSegment.get_end_point());
  
    double signedDistanceFromOriendtedLineToDiskCenterPt = orientedLine.signed_distance(candidateDisk->get_center_pt());

    //negative or on-negative
    if ( _LE(signedDistanceFromOriendtedLineToDiskCenterPt, -candidateDisk->get_radius()) )
    {   // a candidate disk is fully contained between two lines 
        if (   _LT(orthogonalLineAtStartPt.signed_distance(candidateDisk->get_center_pt()), -candidateDisk->get_radius())
            && _GT(orthogonalLineAtEndPt.signed_distance(candidateDisk->get_center_pt()),    candidateDisk->get_radius()) )
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    //crossing 
    else if (   _GT(signedDistanceFromOriendtedLineToDiskCenterPt, -candidateDisk->get_radius()) 
             && _LT(signedDistanceFromOriendtedLineToDiskCenterPt,  candidateDisk->get_radius()) )
    {   // a center of disk is contained betweeen two lines
        if (   _LT(orthogonalLineAtStartPt.signed_distance(candidateDisk->get_center_pt()), 0.0)
            && _GT(orthogonalLineAtEndPt.signed_distance(candidateDisk->get_center_pt()),   0.0) )
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    //on-positive
    else if(includingOnPositive && _EQ(signedDistanceFromOriendtedLineToDiskCenterPt, candidateDisk->get_radius()))
    {   // a center of disk is contained betweeen two lines
        if (   _LT(orthogonalLineAtStartPt.signed_distance(candidateDisk->get_center_pt()), 0.0)
            && _GT(orthogonalLineAtEndPt.signed_distance(candidateDisk->get_center_pt()),   0.0) )
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    //positive
    else
    { 
        return false;
    }
}


inline bool ConvexHullOfDisks::disk1_is_smaller_than_disk2(CircularDisk2D*& disk1, CircularDisk2D*& disk2)
{
    return disk1->get_radius() < disk2->get_radius();
}


inline bool ConvexHullOfDisks::disk1_is_larger_than_disk2(CircularDisk2D*& disk1, CircularDisk2D*& disk2)
{
    return disk1->get_radius() > disk2->get_radius();
}


#endif //_CONVEX_HULL_OF_DISKS_ 

