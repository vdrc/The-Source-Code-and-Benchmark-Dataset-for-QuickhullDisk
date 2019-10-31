/* \section Examples
*
* The following program shows an example of the use of QuickhullDisk.
* A: Include header files for QuickhullDisk.
* B: Load input disks from file.
*     The FileIOForConvexHullOfDisks::read_disks_from_file(...) command loads a input disk file, and stores the disks in a list of CircularDisk2D objects.
* C: Find hull disks, 
*     counts the number of the hull disks, get the computation time for finding the hull disks, and write the hull disks to file.
* D. Extract and use convex hull boundary (application).
*   D-1: Extract convex hull boundary consisting of arcs and lines from hull disks, its length, 
*       and get the first acr and line in the list of convex hull boundary.
*   D-2: Count the number of hull boundary's line segments whose length is less than 1.0.
*/

//A. Include the header files for using following main function.
#include "QuickhullDisk.h"   
#include "CircularDisk2D.h"
#include "CircularArc2D.h"
#include "Line2D.h"
#include "FileIOForConvexHullOfDisks.h" 
#include <iostream>
#include <string>
#include <list>
using namespace std;

int main(int argc, char* argv[])
{
    string inputFileNameWithFullPath;
    string outputFileNameWithFullPath;

    if (argc != 5)
    {
        cout << "Usage: " << argv[0]
             << " -i [INPUT FILE NAME WITH FULL PATH]"
             << " -o [OUTPUT FILE NAME WITH FULL PATH]" << endl;
        
        return 1;
    }
    else
    {
        inputFileNameWithFullPath  = argv[2];
        outputFileNameWithFullPath = argv[4];

        /*Initialize cout style*/
        cout.setf(std::ios::fixed, std::ios::floatfield);
        cout.precision(3);

        cout << "1. Input arguments" << endl;
        cout << " Input file: "      << inputFileNameWithFullPath << endl;
        cout << " Output file: "     << outputFileNameWithFullPath << endl << endl;
    }


    //B. Load input disks from file. (We have two options to read disks with single or double precision)
    list<CircularDisk2D> inputDisks;
    FileIOForConvexHullOfDisks::read_disks_from_file_with_double_precision(inputFileNameWithFullPath, inputDisks);
    //FileIOForConvexHullOfDisks::read_disks_from_file_with_single_precision(inputFileNameWithFullPath, inputDisks);

    cout << "2. Input disks" << endl;
    cout << " #Input disks: " << inputDisks.size() << endl << endl;


    //C. Find hull disks. 
    list<CircularDisk2D> outputHullDisks;
    QuickhullDisk QuickHullDiskAlgorithm;
    QuickHullDiskAlgorithm.find_hull_disks(inputDisks, outputHullDisks);

    cout << "3. Output hull disks" << endl;
    cout << " #Hull disks: "          << outputHullDisks.size() << endl;
    cout << " QuickhullDisk comp. time: " << QuickHullDiskAlgorithm.get_time_statistics().time(QH_TIME_QUICKHULLDISK)  << " sec" << endl << endl;
    
    FileIOForConvexHullOfDisks::write_disks_to_file(outputFileNameWithFullPath, outputHullDisks);


    //D. Application to extract and use convex hull boundary.
    //D-1. Extract convex hull boundary consisting of arcs and lines from hull disks and its length.
    list<pair<CircularArc2D, Line2D>> boundaryArcNLines;
    double lengthOfHullBoundary = QuickHullDiskAlgorithm.extract_convexhull_boundary(outputHullDisks, boundaryArcNLines);

    CircularArc2D firstArc  = boundaryArcNLines.front().first;
    Line2D        firstLine = boundaryArcNLines.front().second;

    cout << "4-1. Output hull boundary arcs and edges" << endl;
    cout << " The length of hull boundary: "  << lengthOfHullBoundary  << endl;

    cout << " The first arc's start point: (" << firstArc.get_start_point().get_x() <<", " << firstArc.get_start_point().get_y() << "), "
         <<                   " end point: (" << firstArc.get_end_point().get_x()   <<", " << firstArc.get_end_point().get_y()   << "), "
         <<                " hull disk id: "  << firstArc.get_ID() << endl;

    cout << " The first line's start point: (" << firstLine.get_start_point().get_x() <<", " << firstLine.get_start_point().get_y() << "), "
         <<                    " end point: (" << firstLine.get_end_point().get_x()   <<", " << firstLine.get_end_point().get_y()   << ")" << endl << endl;


    //D-2. Count the number of hull boundary's line segments whose length is less than 100.0
    int numOfLineSegmentsWhoseLengthIsLessThan = 0;
    for(list<pair<CircularArc2D, Line2D>>::const_iterator it_ArcNLine = boundaryArcNLines.begin();
        it_ArcNLine != boundaryArcNLines.end();
        ++it_ArcNLine)
    {
        const pair<CircularArc2D, Line2D>& currArcNLine = *it_ArcNLine;
        const Line2D& currLine = currArcNLine.second;

        if (currLine.get_length() < 100.0)
        {
            ++numOfLineSegmentsWhoseLengthIsLessThan;
        }
    }

    cout << "4-2. Number of line segments in hull boundary" << endl;
    cout << " # of total line segments: " << boundaryArcNLines.size() << endl;
    cout << " # of line segments whose length is less than 100.0: " << numOfLineSegmentsWhoseLengthIsLessThan << endl;

    return 0;
}

