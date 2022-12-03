#ifndef STUDIEPROPERTIES_H
#define STUDIEPROPERTIES_H

#include <QDialog>

namespace Ui {
class StudieProperties;
}

class StudieProperties : public QDialog
{
    Q_OBJECT

public:
    explicit StudieProperties(QWidget *parent = nullptr);
    ~StudieProperties();

private:
    Ui::StudieProperties *ui;
};

#endif // STUDIEPROPERTIES_H
