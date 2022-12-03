#ifndef STOCKXXDATATYPES_H
#define STOCKXXDATATYPES_H
#include <QtCore>
#include <limits.h>

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
    return qHash(key.name, seed);
}

// assetID


// define a data invalida e o quoteid invalidos
inline QDateTime const ZERO_DATE = QDateTime(QDate(1900, 12, 31), QTime(23, 59, 59, 999));
constexpr int64_t INVALID_QUOTEID = -1;

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
    return qHash(key.dtQuoteDate, seed) ^ (key.id + 1);
}

// QuoteIdentifier


constexpr double INVALID_DOUBLE = std::numeric_limits<double>::lowest();

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

enum StudieType {stNoStudie, stLine, stResistance, stFibonacci, stVertLine, stChannel, stFreeHand};
enum SerieInterval {siDaily = 0, siOneMin = 1, siFiveMin = 5, siFifteenMin = 15, siThirtyMin = 30, siSixtyMin = 60};

struct DataSerieIdentifier{
    AssetId id;
    SerieInterval si;
};
inline bool operator==(const DataSerieIdentifier &a, const DataSerieIdentifier &b){
    return ((a.id == b.id) && (a.si == b.si));
}
inline uint qHash(const DataSerieIdentifier &key, uint seed)
{
    return qHash(key.id.name, seed) ^ (key.si + 1);
}

inline DataSerieValue const INVALID_DATA = DataSerieValue();

enum IndicatorType {itPrice = 0, itMovingAverage = 1};

struct IndicatorIdentifier{
    IndicatorType type;
    int id;
public:
    inline bool operator==(const  IndicatorIdentifier &a) const{
        if((a.type == this->type) &&
           (a.id == this->id)){
            return true;
        }
        return false;
    }
};
inline uint qHash(const IndicatorIdentifier &key, uint seed)
{
    return qHash(key.type, seed) ^ (key.id + 1);
}

#endif
