#include "symbolseracherapi.h"
#include "qjsonarray.h"
#include "qjsondocument.h"
#include "qjsonobject.h"
#include "qnetworkreply.h"

void symbolseracherapi::newRequest()
{
     QUrl url(m_request + m_requestKeyWord + m_keyWord + m_resquestApiKey);
     QNetworkReply* reply = m_manager.get(QNetworkRequest(url));
     QObject::connect(reply, &QNetworkReply::readyRead, this, &symbolseracherapi::read);
}

symbolseracherapi::symbolseracherapi()
{
    QObject::connect(&m_manager, &QNetworkAccessManager::finished, this, &symbolseracherapi::finished);
}

QStringList symbolseracherapi::results()
{
    return m_lstResults;
}

void symbolseracherapi::setKeyWord(QString word)
{
    m_keyWord = word;
}

void symbolseracherapi::finished(QNetworkReply *reply)
{
    const QString c_alphaAdavantageJsonObj = "bestMatches";
    const QString c_symbol = "1. symbol";
    QJsonDocument json_doc;
    json_doc = QJsonDocument::fromJson(m_jsonString.toUtf8());
    QJsonObject json_obj {json_doc.object()};
    QJsonArray json_array {json_obj.value(c_alphaAdavantageJsonObj)};
    m_lstResults.clear();
    for (int i{0}; i < json_array.first().toArray().count(); ++i){
        QJsonValue value = json_array.first().toArray()[i];
        m_lstResults.append(value[c_symbol].toString());
    }
    reply->deleteLater();
    emit dataReady();
}

void symbolseracherapi::read()
{
    m_jsonString.clear();
    QNetworkReply* reply = qobject_cast<QNetworkReply*>(sender());
    m_jsonString += reply->readAll();
}
