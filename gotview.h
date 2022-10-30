#ifndef GOTVIEW_H
#define GOTVIEW_H

#include <QGraphicsView>
#include <QObject>

class GoTView : public QGraphicsView
{
    Q_OBJECT
public:
    GoTView(QWidget* parent = nullptr);

    // QWidget interface
protected:
    virtual void resizeEvent(QResizeEvent *event) override;
    virtual void wheelEvent(QWheelEvent *event) override;
    virtual void mousePressEvent(QMouseEvent *event) override;
    virtual void mouseReleaseEvent(QMouseEvent *event) override;
    virtual void mouseMoveEvent(QMouseEvent *event) override;
    virtual void keyPressEvent(QKeyEvent *event) override;
signals:
    void Resize(QResizeEvent *event);
    void MouseClick(QMouseEvent *event);
    void MouseRelease(QMouseEvent *event);
    void MouseMove(QMouseEvent *event);
    void KeyPress(QKeyEvent *);





};

#endif // GOTVIEW_H
