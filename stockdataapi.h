#ifndef STOCKDATAAPI_H
#define STOCKDATAAPI_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
class StockDataApi : public QObject
{
    Q_OBJECT
private:
    QNetworkAccessManager* m_manager;
    const QString m_apiKey {"CN0441U5HSJQDKPV"};
    const QString m_functionDaily {"TIME_SERIES_DAILY_ADJUSTED"};
    const QString m_functionMin {"TIME_SERIES_INTRADAY"};
    const QString m_request{"https://www.alphavantage.co/query?function="};
    const QString m_requestSymbol{"&symbol="};
    const QString m_interval{"&interval="};
    const QString m_output{"&outputsize=full"};
    const QString m_requestKey{"&apikey=" + m_apiKey};
    QString m_jsonString;
    QString m_fullJson;
    QString m_lastTicker;

public:
    explicit StockDataApi(QObject *parent = nullptr);
    const QString getJsonString();
    void requestDailySerie(const QString ticker);
    void requestMinuteSerie(const QString ticker, int offset);

private slots:
    void finished(QNetworkReply*);
    void read();
signals:
    void dataReady(QString);

};

#endif // STOCKDATAAPI_H
