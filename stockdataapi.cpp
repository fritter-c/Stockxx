#include "stockdataapi.h"
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QJsonDocument>
#include <QJsonObject>
#include <QFile>


const QString &StockDataApi::getJsonString() const
{
    return m_jsonString;
}

StockDataApi::StockDataApi(QString ticker, QObject *parent)
    : QObject{parent}
{
    m_symbol = ticker;
    if (ticker == ""){
        QUrl url("https://www.alphavantage.co/query?function=TIME_SERIES_DAILY&symbol=IBM&outputsize=full&apikey=" + m_apiKey);
        m_manager = new QNetworkAccessManager(this);
        connect(m_manager, &QNetworkAccessManager::finished, this, &StockDataApi::finished);
        QNetworkReply* reply = m_manager->get(QNetworkRequest(url));
        connect(reply, &QNetworkReply::readyRead, this, &StockDataApi::read);
    }
    else{
        QUrl url(m_request + m_function + m_requestSymbol + ticker + m_output + m_requestKey);
        m_manager = new QNetworkAccessManager(this);
        connect(m_manager, &QNetworkAccessManager::finished, this, &StockDataApi::finished);
        QNetworkReply* reply = m_manager->get(QNetworkRequest(url));
        connect(reply, &QNetworkReply::readyRead, this, &StockDataApi::read);
    }

}

void StockDataApi::finished(QNetworkReply* reply)
{
    emit dataReady(m_symbol);
    reply->deleteLater();
}

void StockDataApi::read()
{
    QNetworkReply *reply = qobject_cast<QNetworkReply*>(sender());
    m_jsonString += reply->readAll();

}

