#ifndef STOCKXXLINECOMBOBOX_H
#define STOCKXXLINECOMBOBOX_H

#include "qcombobox.h"
#include <QWidget>

namespace Ui {
class StockxxLineComboBox;
}

class StockxxLineComboBox : public QWidget
{
    Q_OBJECT
private:
    Ui::StockxxLineComboBox *ui;
    QComboBox* penStyleComboBox;
    Qt::PenStyle m_penStyle;

public:
    explicit StockxxLineComboBox(QWidget *parent = nullptr);
    ~StockxxLineComboBox();
    Qt::PenStyle penStyle() const;
    void setPenStyle(Qt::PenStyle);

public slots:
    void onPenChanged();
signals:
    void penChanged();

};

#endif // STOCKXXLINECOMBOBOX_H
