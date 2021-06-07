
#ifndef ESSENTIALQTSO_DATETIME_HPP
#define ESSENTIALQTSO_DATETIME_HPP

#include "crossPlatformMacros.hpp"

//converts a time amount to a datetime string,
//i.e., 200000000 milliseconds = 2d 7:33:20
//milliseconds are printed when not equal to 000
//the largest unit is "d" --> days
extern EXPIMP_ESSENTIALQTSO QString formatedTime_f(const int_fast64_t milliseconds_par_con);

#endif // ESSENTIALQTSO_DATETIME_HPP


