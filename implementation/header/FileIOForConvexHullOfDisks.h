/**
 * \class FileIOForConvexHullOfDisks
 * \brief A class for reading and writing files for convex hull of disks.
 */

 //* This is a source code for implementation of "QuickhullDisk: A Faster Convex Hull Algorithm for Disks."
 //* Code authors: Chanyoung Song, Joonghyun Ryu, and Deok-Soo Kim.
 //* Version:      1.0
 //* Date:         2019


#ifndef _FILE_IO_FOR_CONVEXHULL_OF_DISKS_ 
#define _FILE_IO_FOR_CONVEXHULL_OF_DISKS_ 
#define  _CRT_SECURE_NO_WARNINGS //for using strtok() cmd with complier version c++11 in Window O.S.. 

#include "ConstSet.h"
#include "CircularDisk2D.h"

#include <iostream>
#include <cstring>
#include <fstream>
#include <list>
using namespace std;


class FileIOForConvexHullOfDisks
{
public:
    static void read_disks_from_file_with_single_precision(const string& inputFileNameWithPath, list<CircularDisk2D>& inputDisks);
    static void read_disks_from_file_with_double_precision(const string& inputFileNameWithPath, list<CircularDisk2D>& inputDisks);
    static void write_disks_to_file(const string& outputFileNameWithPath, const list<CircularDisk2D>& outputDisks, const int& precision = 6);
};

#endif //_FILE_IO_FOR_CONVEXHULL_OF_DISKS_

