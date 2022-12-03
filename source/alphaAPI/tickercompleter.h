#ifndef TICKERCOMPLETER_H
#define TICKERCOMPLETER_H

#include <QCompleter>
#include <QStandardItemModel>
class TickerModel : public QStandardItemModel
{
    Q_OBJECT
public:
    using QStandardItemModel::QStandardItemModel;
    void resetItems(QStringList);
};

class TickerCompleter : public QCompleter
{
private:
    TickerModel *m_model;
public:
    explicit TickerCompleter(QCompleter::CompletionMode ,QObject *parent = nullptr);
    ~TickerCompleter();
    TickerModel *model() const;

};



#endif // TICKERCOMPLETER_H
