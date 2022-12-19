#pragma once
#include <QString>

inline double 
ifThen(double a, double b, bool condition) {
    if (condition) {
        return a;
    }
    return b;
}
inline QString
ifThen(QString a, QString b, bool condition) {
    if (condition) {
        return a;
    }
    return b;
}
inline void*
ifThen(void* a, void* b, bool condition) {
    if (condition) {
        return a;
    }
    return b;
}

