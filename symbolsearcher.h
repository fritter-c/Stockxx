#ifndef SYMBOLSEARCHER_H
#define SYMBOLSEARCHER_H

#include <QDialog>
#include <QNetworkAccessManager>
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
    QString m_keyWord;
    QTimer* m_tmrSearch;
    QStringList m_lstResults;
    TickerCompleter *m_completer{nullptr};
    TickerModel *m_model;
    bool m_local;
    const QString m_apiKey {"CN0441U5HSJQDKPV"};
    const QString m_function {"SYMBOL_SEARCH"};
    const QString m_request {"https://www.alphavantage.co/query?function=" + m_function};
    const QString m_requestKeyWord {"&keywords="};
    const QString m_resquestApiKey {"&apikey=" + m_apiKey};

public:
    explicit SymbolSearcher(QWidget *parent = nullptr, bool bLocal = false);
    ~SymbolSearcher();
    void NewRequest();
    void setKeyWord(const QString &newKeyWord);
    QString getTicker();
    bool getFreeWindow();

private:
    Ui::SymbolSearcher *ui;

private slots:
    void onSearchTimer();
    void onCompleterActivated(const QString&);
public slots:
    void onDataReady();
signals:
    void complete(QRect);
};

#endif // SYMBOLSEARCHER_H
