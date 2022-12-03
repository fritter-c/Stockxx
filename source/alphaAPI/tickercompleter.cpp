#include "tickercompleter.h"

TickerModel *TickerCompleter::model() const
{
    return m_model;
}

void TickerModel::resetItems(QStringList list)
{
    clear();
    QString word;
    foreach(word , list){
        appendRow(new QStandardItem(word));
    }
}
TickerCompleter::TickerCompleter(CompletionMode mode, QObject *parent)
    : QCompleter{parent}
{
    setCompletionMode(mode);
    m_model = new TickerModel(this);
    setCaseSensitivity(Qt::CaseInsensitive);
    setModel(m_model);
}

TickerCompleter::~TickerCompleter()
{
    delete m_model;
}


