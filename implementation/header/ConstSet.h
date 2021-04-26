/**
 * \class ConstSet
 * \brief A class for set of contants.
 */

 //* This is a source code for implementation of "QuickhullDisk: A Faster Convex Hull Algorithm for Disks."
 //* Code authors: Chanyoung Song, Joonghyun Ryu, and Deok-Soo Kim.
 //* Version:      1.0
 //* Date:         2019

#ifndef _CONST_SET_H_
#define _CONST_SET_H_

#include <limits.h>
#include <float.h>

#define _NULL 0

const double _PI          = 3.14159265358979323846;
const double _RadToDegree = 57.2957795130823; // By Joonghyun on April 18, 2019 rename from _DegreeToRad 

////////////////////////////////////////////////////////////
///		TOLERANCES
////////////////////////////////////////////////////////////
const double _resNeg20= 1.0e-20 ;
const double _resNeg19= 1.0e-19 ;
const double _resNeg18= 1.0e-18 ;
const double _resNeg17= 1.0e-17 ;
const double _resNeg16= 1.0e-16 ;
const double _resNeg15= 1.0e-15 ;
const double _resNeg14= 1.0e-14 ;
const double _resNeg13= 1.0e-13 ;
const double _resNeg12= 1.0e-12 ;
const double _resNeg11= 1.0e-11 ;
const double _resNeg10= 1.0e-10 ;
const double _resNeg9= 1.0e-9 ;
const double _resNeg8= 1.0e-8 ;
const double _resNeg7= 1.0e-7 ;
const double _resNeg6= 1.0e-6 ;
const double _resNeg5= 1.0e-5 ;
const double _resNeg4= 1.0e-4 ;
const double _resNeg3= 1.0e-3 ;
const double _resNeg2= 1.0e-2 ;
const double _resNeg1= 1.0e-1 ;

const double _SYSTEM_RES = 1.0e-15;  //system resolution 
const double _MATH_RES   = 1.0e-6;   //mathematical resolution 
const double _MAX_REAL   = 1.0e38;   //the largest possible real value 

#endif


