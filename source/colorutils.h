#ifndef COLORUTILS_H
#define COLORUTILS_H

#include "qcolor.h"

inline bool
isDarkColor(QColor color){
    QRgb rgb{color.rgb()};
    int r = ((rgb >> 16) & 0xff);
    int g = ((rgb >> 8) & 0xff);
    int b = (rgb & 0xff);
    return ((0.2126 * r + 0.7152 * g + 0.0722 * b) < 40);
}
inline bool
isLightColor(QColor color){
    return (!isDarkColor(color));
}
#endif // COLORUTILS_H
