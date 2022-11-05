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
    QNetworkReply* m_reply;
    QString m_apiKey = "CN0441U5HSJQDKPV";
    QString m_jsonString;

public:
    explicit StockDataApi(QObject *parent = nullptr);


    const QString &getJsonString() const;

private slots:
    void finished(QNetworkReply*);
    void read();
signals:
    void dataReady();

};

#endif // STOCKDATAAPI_H
