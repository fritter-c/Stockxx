#ifndef STOCKXXDATEUTILS_H
#define STOCKXXDATEUTILS_H
#include "qdatetime.h"


inline long long
DaysInBetween(QDateTime now, QDateTime then){
         return abs(now.daysTo(then));
    }

const QDateTime ZERO_DATE = QDateTime(QDate(1900, 12, 31), QTime(23, 59, 59, 999));

#endif // STOCKXXDATEUTILS_H
