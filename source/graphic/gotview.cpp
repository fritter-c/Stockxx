#include "gotview.h"
#include <QResizeEvent>
#include <QOpenGLWidget>
GoTView::GoTView(QWidget* parent) : QGraphicsView(parent)
{
    setMouseTracking(true);
    setHorizontalScrollBarPolicy (Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy (Qt::ScrollBarAlwaysOff);
    setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    setFocusPolicy(Qt::StrongFocus);
    setBackgroundBrush(QBrush(QColor::fromRgb(2,42,68)));
}

GoTView::~GoTView()
{
    delete scene();
    deleteLater();
}

void GoTView::resizeEvent(QResizeEvent *event)
{
    emit Resize(event);
    event->accept();
}

void GoTView::wheelEvent(QWheelEvent *event)
{
    QGraphicsView::wheelEvent(event);
}

void GoTView::mousePressEvent(QMouseEvent *event)
{
    QGraphicsView::mousePressEvent(event);
    emit MouseClick(event);

}

void GoTView::mouseReleaseEvent(QMouseEvent *event)
{
    QGraphicsView::mouseReleaseEvent(event);
    emit MouseRelease(event);
}

void GoTView::mouseMoveEvent(QMouseEvent *event)
{
    QGraphicsView::mouseMoveEvent(event);
    emit MouseMove(event);
}

void GoTView::keyPressEvent(QKeyEvent *event)
{
    QGraphicsView::keyPressEvent(event);
    //emit KeyPress(event);
    //event->accept();
}
