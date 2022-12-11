#ifndef CUSTOMINDICATOR_H
#define CUSTOMINDICATOR_H

#include "IndicatorDataTypes.h"
#include "icustomserienotifiable.h"
#include <customserie.h>
#include <qgraphicsitem.h>

class CustomIndicator : public CustomSerie
{
    Q_OBJECT
private:
    IndicatorIdentifier m_ID;
protected:
    CustomSerie* m_baseIndicator;
    QGraphicsItem* m_visualParent{ nullptr };
    QVector<ICustomSerieNotifiable*> m_subscribers;
public:
    CustomIndicator(CustomSerie *base);
    ~CustomIndicator();
    IndicatorIdentifier ID() const;
    void setID(IndicatorIdentifier newNID);
    void setVisualParent(QGraphicsItem*);
    QGraphicsItem *visualParent() const;
    void addSubscriber(ICustomSerieNotifiable*);
    void removeSubscriber(ICustomSerieNotifiable*);
private slots:
    virtual void NotifyNewData(size_t);
signals:
    void NewData(size_t);
};

#endif // CUSTOMINDICATOR_H
