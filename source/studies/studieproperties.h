#ifndef STUDIEPROPERTIES_H
#define STUDIEPROPERTIES_H

#include "StockxxDataTypes.h"
#include <QDialog>

namespace Ui {
class StudieProperties;
}

class StudieProperties : public QDialog
{
    Q_OBJECT
private:
    Ui::StudieProperties *ui;
    QColor m_studieColor{Qt::yellow};
public:
    explicit StudieProperties(QWidget *parent = nullptr);
    ~StudieProperties();
    BasicStudieStyle getStyle() const;
    void setStyle(BasicStudieStyle style);
signals:
    void styleChanged();
private slots:
    void onPenChanged();
    void on_pushButton_ColorPicker_clicked();
    void on_spinBox_LineWidth_valueChanged(int arg1);
};

#endif // STUDIEPROPERTIES_H
