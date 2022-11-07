#ifndef SYMBOLSERACHERAPI_H
#define SYMBOLSERACHERAPI_H

#include <QObject>
#include <QNetworkAccessManager>

class symbolseracherapi : public QObject
{
    Q_OBJECT
private:
    QString m_jsonString;
    QString m_keyWord;
    QNetworkAccessManager m_manager;
    QStringList m_lstResults;
    const QString m_apiKey {"CN0441U5HSJQDKPV"};
    const QString m_function {"SYMBOL_SEARCH"};
    const QString m_request {"https://www.alphavantage.co/query?function=" + m_function};
    const QString m_requestKeyWord {"&keywords="};
    const QString m_resquestApiKey {"&apikey=" + m_apiKey};    
public:
    symbolseracherapi();
    QStringList results();
    void setKeyWord(QString);
    void newRequest();
private slots:
    void finished(QNetworkReply*);
    void read();
signals:
    void dataReady();
};

#endif // SYMBOLSERACHERAPI_H
