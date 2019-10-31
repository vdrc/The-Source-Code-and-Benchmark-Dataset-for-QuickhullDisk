#include <cmath>
#include "ConstSet.h"

double _ABS(const double& x)
{
   return (x>0 ? x : -x);
}

// relative operators
int _EQ(const double& r1, const double& r2, const double& res)
        { return (_ABS(r1 - r2) <= res); }
int _GT(const double& r1, const double& r2, const double& res)
        { return (r1 > r2 + res); }
int _LT(const double& r1, const double& r2, const double& res)
        { return (r1 < r2 - res); }
int _GE(const double& r1, const double& r2, const double& res)
        { return (! _LT(r1, r2, res)); }
int _LE(const double& r1, const double& r2, const double& res)
        { return (! _GT(r1, r2, res)); }
int _NE(const double& r1, const double& r2, const double& res)
        { return (! _EQ(r1, r2, res)); }

//      Compare to rg_ZERO        
int _ZERO(const double& r, const double& res) 
		{ return (_ABS(r) <= res); }
int _POS(const double& r, const double& res) 
		{ return (r > res); }
int _NEG(const double& r, const double& res) 
		{ return (r < -res); }
int _NZERO(const double& r, const double& res) 
		{ return (! _ZERO(r, res)); }
int _NPOS(const double& r, const double& res) 
		{ return (! _POS(r, res)); }
int _NNEG(const double& r, const double& res) 
		{ return (! _NEG(r, res)); }

//      Between Two Ordered Reals: (the real vaues are ordered, i.e., left <= right)    
int _BTOR(const double& left, const double& value, const double& right, const double& res)
		{ return (_LE(left, value, res) && _LE(value, right, res)); }
int _BTORexclusive(const double& left, const double& value, const double& right, const double& res)
		{ return (_LT(left, value, res) && _LT(value, right, res)); }

//      Between Two Reals: (the real values are not ordered.)    
int _BTR(const double& r1, const double& r, const double& r2, const double& res)
		{ return ((_LE(r1, r, res) && _LE(r, r2, res)) || (_LE(r2, r, res) && _LE(r, r1, res))); }
 
//----- if r1 > r2 then 1 is returned  
//----- if r1 = r2 then 0 is returned
//----- if r1 < r2 then -1is  returned 
int _COMPARE(const double& r1, const double& r2, const double& res)
{
   if ( _ABS(r1 - r2) < res ) 
      return 0;
   else if ( r1 > r2 )      
      return 1;
   else 
      return -1;
}


double   _Max( double const& first, double const& second)
{ if( first > second ) return first;
	else return second;
}
double   _Min( double const& first, double const& second)
{ if( first < second ) return first;
	else return second;
}


