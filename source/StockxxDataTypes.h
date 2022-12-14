#ifndef STOCKXXDATATYPES_H
#define STOCKXXDATATYPES_H
#include "qcolor.h"
#include <QtCore>
#include <limits.h>
#include <string>

const quint32 c_StreamStart = 0xA0B0C0D0;


// assetID
struct AssetId{
    QString name;
public:
    inline bool operator==(const AssetId &a) const{
        if(a.name == name){
            return true;
        }
        return false;
    }
    inline bool operator !=(const AssetId &a) const {
        if (not (a == *this))
            return true;
        return false;
    }
};

inline uint qHash(const AssetId &key, uint seed)
{
    return (uint)qHash(key.name, seed);
}

// define a data invalida e o quoteid invalidos
inline QDateTime const ZERO_DATE = QDateTime(QDate(1900, 12, 31), QTime(23, 59, 59, 999));

inline constexpr int64_t INVALID_QUOTEID = -1;

// QuoteIdentifier
struct QuoteIdentifier{
    QDateTime dtQuoteDate;
    int64_t id;

public:
    QuoteIdentifier(){
       dtQuoteDate = ZERO_DATE;
       id = INVALID_QUOTEID;
    }
    inline bool operator==(const QuoteIdentifier &a) const{
        if((a.dtQuoteDate == this->dtQuoteDate) &&
           (a.id == this->id)){
            return true;
        }
        return false;
    }
    inline bool operator >(const QuoteIdentifier &a) const{
        if ((a.id > id) &&
            (a.dtQuoteDate <= dtQuoteDate)){
            return true;
        }
        return false;
    }
    inline bool operator <(const QuoteIdentifier &a) const{
        if ((a.id < id) &&
            (a.dtQuoteDate >= dtQuoteDate)){
            return true;
        }
        return false;
    }
    inline bool operator !=(const QuoteIdentifier &a) const{
        return (not (a == *this));
    }

    void invalidate(){
        dtQuoteDate = ZERO_DATE;
        id = INVALID_QUOTEID;
    }

};

// define a quote inválida
inline QuoteIdentifier const INVALID_QUOTE = QuoteIdentifier();


inline uint qHash(const QuoteIdentifier &key, uint seed)
{
    return (uint)qHash(key.dtQuoteDate, seed) ^ (key.id + 1);
}

const double INVALID_DOUBLE = std::numeric_limits<double>::lowest();

#pragma region DataSerieValues
struct DataSerieValue{
    double dOpen;
    double dClose;
    double dHigh;
    double dLow;
    double dVolume;
    double dTrades;
    QDateTime dtQuoteDate;
    QuoteIdentifier qiQuote;
public:
    DataSerieValue(){
        dOpen = INVALID_DOUBLE;
        dClose = INVALID_DOUBLE;
        dHigh = INVALID_DOUBLE;
        dLow = INVALID_DOUBLE;
        dVolume = INVALID_DOUBLE;
        dTrades = INVALID_DOUBLE;
        dtQuoteDate = ZERO_DATE;
        qiQuote = INVALID_QUOTE;
    }
};
inline bool operator !=(const DataSerieValue &a, const DataSerieValue &b){
    return (!(a.qiQuote == b.qiQuote));
}

inline bool operator ==(const DataSerieValue &a, const DataSerieValue &b){
    return ((a.qiQuote == b.qiQuote));
}

inline DataSerieValue const INVALID_DATA = DataSerieValue();
#pragma endregion DataSerieValues

#pragma region Studies
enum StudieType {stNoStudie, stLine, stResistance, stFibonacci, stVertLine, stChannel, stFreeHand};
struct BasicStudieStyle{
    Qt::PenStyle penStyle;
    int width;
    QColor color;
};
#pragma endregion Studies

#pragma region SerieInterval
enum SerieInterval {siDaily = 0, siOneMin = 1, siFiveMin = 5,
                    siFifteenMin = 15, siThirtyMin = 30, siSixtyMin = 60, siUnknown = -1};

inline const QString ToString(SerieInterval const & v)
{
    QString string;
    switch (v) {
    case (siDaily):
        string = "Daily";
        break;
    case (siOneMin):
        string = "1 Minute";
        break;
    case (siFiveMin):
        string = "5 Minute";
        break;
    case (siFifteenMin):
        string = "15 Minute";
        break;
    case (siThirtyMin):
        string = "30 Minute";
        break;
    case (siSixtyMin):
        string = "60 Minute";
        break;
    default:
        string = "Unknown";
        break;
    }
    return string;
}
#pragma endregion SerieInterval

#pragma region DataSerieIdentifier
struct DataSerieIdentifier{
    AssetId id;
    SerieInterval si;
};

inline const QString ToString(DataSerieIdentifier const & v){
    return v.id.name + " " + ToString(v.si);
}
inline bool operator==(const DataSerieIdentifier &a, const DataSerieIdentifier &b){
    return ((a.id == b.id) && (a.si == b.si));
}
inline uint qHash(const DataSerieIdentifier &key, uint seed)
{
    return (uint)qHash(key.id.name, seed) ^ (key.si + 1);
}
#pragma endregion DataSerieIdentifier

#endif
