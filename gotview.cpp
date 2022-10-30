#include "gotview.h"
#include <QResizeEvent>
#include <QOpenGLWidget>
GoTView::GoTView(QWidget* parent) : QGraphicsView(parent)
{
    setMouseTracking(true);
    setRenderHints(QPainter::Antialiasing);
    setHorizontalScrollBarPolicy (Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy (Qt::ScrollBarAlwaysOff);
    setFocusPolicy(Qt::StrongFocus);
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
    emit KeyPress(event);
    event->accept();
}
