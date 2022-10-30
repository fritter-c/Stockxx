#ifndef DAILYPRICE_H
#define DAILYPRICE_H

#include "customprice.h"
#include "dailydataserie.h"

class DailyPrice : public CustomPrice
{
private:
    DailyDataSerie* m_dailyDataSerie;
public:
    explicit DailyPrice(DailyDataSerie* dataserie, QObject *parent = nullptr);
    virtual bool Next() override;
    virtual bool Prior() override;
    virtual bool PriorAll() override;
    virtual bool NextAll() override;
    virtual bool PriorN(size_t N) override;
    virtual bool NextN(size_t N) override;
    virtual size_t Size() override;
};

#endif // DAILYPRICE_H
