#ifndef STOCKXXDATATYPES_H
#define STOCKXXDATATYPES_H
#include <QtCore>

const quint32 c_StreamStart = 0xA0B0C0D0;

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
struct QuoteIdentifier{
    QDateTime dtQuoteDate;
    uint64_t id;

public:
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

};
inline uint qHash(const QuoteIdentifier &key, uint seed)
{
    return qHash(key.dtQuoteDate, seed) ^ (key.id + 1);
}
inline uint qHash(const AssetId &key, uint seed)
{
    return qHash(key.name, seed);
}

struct DataSerieValue{
    double dOpen;
    double dClose;
    double dHigh;
    double dLow;
    double dVolume;
    double dTrades;
    QDateTime dtQuoteDate;
    QuoteIdentifier qiQuote;
};

enum StudieType {stNoStudie, stLine, stResistance, stFibonacci, stVertLine, stChannel, stFreeHand};

enum SerieInterval {siDaily = 0, siOneMin = 1, siFiveMin = 5, siFifteenMin = 15, siThirtyMin = 30, siSixtyMin = 60};

#endif

