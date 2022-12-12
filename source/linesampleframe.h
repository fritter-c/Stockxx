#ifndef LINESAMPLEFRAME_H
#define LINESAMPLEFRAME_H

#include "IndicatorDataTypes.h"
#include <QFrame>

class LineSampleFrame : public QFrame
{
private:
    BasicIndicatorStyle m_style;
protected:
    virtual void paintEvent(QPaintEvent *event) override;
public:
    LineSampleFrame(QWidget* parent = nullptr);
    void setlineStyle(BasicIndicatorStyle);  
    BasicIndicatorStyle style() const;
};



#endif // LINESAMPLEFRAME_H
