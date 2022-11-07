#include "tickercompleter.h"

TickerModel *TickerCompleter::model() const
{
    return m_model;
}


TickerCompleter::TickerCompleter(QObject *parent)
    : QCompleter{parent}
{
    setCompletionMode(QCompleter::UnfilteredPopupCompletion);
    m_model = new TickerModel(this);
    setModel(m_model);
}

TickerCompleter::~TickerCompleter()
{
    delete m_model;
}

void TickerModel::resetItems(QStringList list)
{
    clear();
    QString word;
    foreach(word , list){
        appendRow(new QStandardItem(word));
    }
}
