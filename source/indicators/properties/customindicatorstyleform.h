#ifndef CUSTOMINDICATORSTYLEFORM_H
#define CUSTOMINDICATORSTYLEFORM_H

#include "IndicatorDataTypes.h"
#include <QWidget>

namespace Ui {
class CustomIndicatorStyleForm;
}

class CustomIndicatorStyleForm : public QWidget
{
    Q_OBJECT
private:
    Ui::CustomIndicatorStyleForm *ui;
    QColor m_lineColor;
    void styleChanged();
    BasicIndicatorStyle m_style;
public:
    explicit CustomIndicatorStyleForm(QWidget *parent = nullptr);
    ~CustomIndicatorStyleForm();
    const BasicIndicatorStyle& getStyle();

private slots:
    void on_pushButton_clicked();
    void onPenChanged();
    void onWidthChanged();


};

#endif // CUSTOMINDICATORSTYLEFORM_H
