#ifndef STOCKXXDATATYPES_H
#define STOCKXXDATATYPES_H
#include <QtCore>

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

enum StudieType {stNoStudie, stLine, stResistance, stFibonacci, stVertLine};

#endif

