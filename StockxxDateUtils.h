#ifndef STOCKXXDATEUTILS_H
#define STOCKXXDATEUTILS_H
#include "qdatetime.h"
namespace StockxxUtils {
inline long long DaysInBetween(QDateTime now, QDateTime then){
     return abs(now.daysTo(then));
}
namespace DateUtils = StockxxUtils;
}
#endif // STOCKXXDATEUTILS_H
