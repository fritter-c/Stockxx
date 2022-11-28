#ifndef STOCKXXDATEUTILS_H
#define STOCKXXDATEUTILS_H
#include "qdatetime.h"


inline long long
DaysInBetween(QDateTime now, QDateTime then){
         return abs(now.daysTo(then));
    }




#endif // STOCKXXDATEUTILS_H
