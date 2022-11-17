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

void StockDataApi::requestDailySerie(const QString ticker)
{
    m_lastTicker = ticker;
    QUrl url(m_request + m_functionDaily + m_requestSymbol + ticker + m_output + m_requestKey);
    connect(m_manager, &QNetworkAccessManager::finished, this, &StockDataApi::finished);
    QNetworkReply* reply = m_manager->get(QNetworkRequest(url));
    connect(reply, &QNetworkReply::readyRead, this, &StockDataApi::read);
}

void StockDataApi::requestMinuteSerie(const QString ticker, int offset)
{
    const QString min{"min"};
    m_lastTicker = ticker;
    QString strUrl{m_request + m_functionMin + m_requestSymbol +
                ticker + m_interval + QString::number(offset) + min + m_output + m_requestKey};
    QUrl url(strUrl);
    connect(m_manager, &QNetworkAccessManager::finished, this, &StockDataApi::finished);
    QNetworkReply* reply = m_manager->get(QNetworkRequest(url));
    connect(reply, &QNetworkReply::readyRead, this, &StockDataApi::read);
}

StockDataApi::StockDataApi(QObject *parent)
    : QObject{parent}
{
    m_manager = new QNetworkAccessManager(this);
}

void StockDataApi::finished(QNetworkReply* reply)
{
    emit dataReady(m_lastTicker);
    disconnect(m_manager, &QNetworkAccessManager::finished, this, &StockDataApi::finished);
    disconnect(reply, &QNetworkReply::readyRead, this, &StockDataApi::read);
    reply->deleteLater();
}

void StockDataApi::read()
{
    QNetworkReply *reply = qobject_cast<QNetworkReply*>(sender());
    m_jsonString += reply->readAll();

}

