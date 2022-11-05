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

StockDataApi::StockDataApi(QObject *parent)
    : QObject{parent}
{
    QUrl url("https://www.alphavantage.co/query?function=TIME_SERIES_DAILY&symbol=IBM&outputsize=full&apikey=" + m_apiKey);
    m_manager = new QNetworkAccessManager(this);
    connect(m_manager, &QNetworkAccessManager::finished, this, &StockDataApi::finished);
    m_reply = m_manager->get(QNetworkRequest(url));
    connect(m_reply, &QNetworkReply::readyRead, this, &StockDataApi::read);

}

void StockDataApi::finished(QNetworkReply* replay)
{
    emit dataReady();
}

void StockDataApi::read()
{
    QNetworkReply *reply = qobject_cast<QNetworkReply*>(sender());
    m_jsonString += reply->readAll();

}

