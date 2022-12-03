#ifndef SYMBOLSEARCHER_H
#define SYMBOLSEARCHER_H

#include <QDialog>
#include <QNetworkAccessManager>
#include "StockxxDataTypes.h"
#include "symbolseracherapi.h"
#include "tickercompleter.h"

namespace Ui {
class SymbolSearcher;
}

class SymbolSearcher : public QDialog
{
    Q_OBJECT
private:
    symbolseracherapi m_tickerSearcherApi;
     Ui::SymbolSearcher *ui;
    QString m_keyWord;
    QTimer* m_tmrSearch;
    QStringList m_lstResults;
    TickerCompleter *m_completer{nullptr};
    TickerModel *m_model;
    bool m_local;
public:
    explicit SymbolSearcher(QWidget *parent = nullptr, bool bLocal = false);
    ~SymbolSearcher();
    void NewRequest();
    void setKeyWord(const QString &newKeyWord);
    QString getTicker();
    SerieInterval getInterval();
    bool getFreeWindow();

private slots:
    void onSearchTimer();
    void onCompleterActivated(const QString&);
    void on_lineEdit_tickerKeyword_textChanged(const QString &arg1);

public slots:
    void onDataReady();
signals:
    void complete(QRect);
};

#endif // SYMBOLSEARCHER_H
