/**
 * \class RelativeOperator
 * \brief A class for relative operators.
 */

 //* This is a source code for implementation of "QuickhullDisk: A Faster Convex Hull Algorithm for Disks."
 //* Code authors: Chanyoung Song, Joonghyun Ryu, and Deok-Soo Kim.
 //* Version:      1.0
 //* Date:         2019


#ifndef _RELATIVE_OPERATOR_
#define _RELATIVE_OPERATOR_

#include "ConstSet.h"

double _ABS(const double& x);
int    _EQ(const double& r1, const double& r2, const double& res = _MATH_RES);
int    _GT(const double& r1, const double& r2, const double& res = _MATH_RES);
int    _LT(const double& r1, const double& r2, const double& res = _MATH_RES);
int    _GE(const double& r1, const double& r2, const double& res = _MATH_RES);
int    _LE(const double& r1, const double& r2, const double& res = _MATH_RES);
int    _NE(const double& r1, const double& r2, const double& res = _MATH_RES);
int    _ZERO(const double& r, const double& res = _MATH_RES);
int    _POS(const double& r, const double& res = _MATH_RES);
int    _NEG(const double& r, const double& res = _MATH_RES);
int    _NZERO(const double& r, const double& res = _MATH_RES);
int    _NPOS(const double& r, const double& res = _MATH_RES);
int    _NNEG(const double& r, const double& res = _MATH_RES);
int    _BTOR(const double& left, const double& value, const double& right, const double& res = _MATH_RES);
int    _BTORexclusive(const double& left, const double& value, const double& right, const double& res = _MATH_RES);
int    _BTR(const double& r1, const double& r, const double& r2, const double& res = _MATH_RES);
int    _COMPARE(const double& v1, const double& v2, const double& res = _MATH_RES);

double _Max( double const& first, double const& second);
double _Min( double const& first, double const& second);

template<class T>
T _Min(const T& v1, const T& v2)
{
   return ((v1<v2) ? v1 : v2);
}

template<class T>
T _Max(const T& v1, const T& v2)
{
   return ((v1>v2) ? v1 : v2);
}


#endif


