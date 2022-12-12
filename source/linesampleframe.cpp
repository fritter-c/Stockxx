#include "linesampleframe.h"
#include "qpainter.h"

LineSampleFrame::LineSampleFrame(QWidget *parent) : QFrame{parent}
{
    m_style.penStyle = Qt::SolidLine;
    m_style.color = Qt::black;
    m_style.width = 1;
}

void LineSampleFrame::setlineStyle(BasicIndicatorStyle style)
{
    m_style = style;
    update();
}

BasicIndicatorStyle LineSampleFrame::style() const
{
    return m_style;
}

void LineSampleFrame::paintEvent(QPaintEvent *event)
{
    QFrame::paintEvent(event);
    QPainter painter(this);
    QPen pen;
    pen.setColor(m_style.color);
    pen.setWidth(m_style.width);
    pen.setStyle(m_style.penStyle);
    QPoint start{1, height()/2};
    QPoint end{width()-3, height()/2};
    painter.setPen(pen);
    painter.drawLine(start,end);
}
