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
    const QString m_function {"TIME_SERIES_DAILY_ADJUSTED"};
    const QString m_request{"https://www.alphavantage.co/query?function="};
    const QString m_requestSymbol{"&symbol="};
    const QString m_output{"&outputsize=full"};
    const QString m_requestKey{"&apikey=" + m_apiKey};
    QString m_symbol;
    QString m_jsonString;

public:
    explicit StockDataApi(QString ticker = "", QObject *parent = nullptr);


    const QString &getJsonString() const;

private slots:
    void finished(QNetworkReply*);
    void read();
signals:
    void dataReady(QString);

};

#endif // STOCKDATAAPI_H
