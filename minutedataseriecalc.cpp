#include "minutedataseriecalc.h"


int MinuteDataSerieCalc::nOffset() const
{
    return m_nOffset;
}

void MinuteDataSerieCalc::loadSerieFromCSV(QString path, QChar delimiter)
{
    QFile file(m_strPath);
       if(!file.open(QIODevice::ReadOnly)) return;

       QDataStream in(&file);
       quint32 start;
       AssetId id;

       in >> start;

       if (start != c_StreamStart){
           file.close();
           return;
       }

       in >> id.name;

       if (m_assetId != id) return;

       if(in.version() != QDataStream::Qt_6_0){
           file.close();
           return;
       }
       ClearDataSerie();
       DataSerieValue dt;
       while(not in.atEnd())
       {

           in >> dt.dOpen;
           in >> dt.dHigh;
           in >> dt.dLow;
           in >> dt.dClose;
           in >> dt.dVolume;
           in >> dt.dTrades;
           in >> dt.dtQuoteDate;
           in >> dt.qiQuote.id;
           dt.qiQuote.dtQuoteDate = dt.dtQuoteDate;
           ar_values.append(new DataSerieValue(dt));

       }
       file.close();
}

void MinuteDataSerieCalc::loadSerieFromStream()
{
    QFile file(m_strPath);
    if(!file.open(QIODevice::ReadOnly)) return;

    QDataStream in(&file);
    quint32 start;
    AssetId id;

    in >> start;

    if (start != c_StreamStart){
        file.close();
        return;
    }

    in >> id.name;

    if (m_assetId != id) return;

    if(in.version() != QDataStream::Qt_6_0){
        file.close();
        return;
    }
    ClearDataSerie();
    DataSerieValue dt;
    while(not in.atEnd())
    {

        in >> dt.dOpen;
        in >> dt.dHigh;
        in >> dt.dLow;
        in >> dt.dClose;
        in >> dt.dVolume;
        in >> dt.dTrades;
        in >> dt.dtQuoteDate;
        in >> dt.qiQuote.id;
        dt.qiQuote.dtQuoteDate = dt.dtQuoteDate;
        ar_values.append(new DataSerieValue(dt));

    }
    file.close();
}

void MinuteDataSerieCalc::serieToStream()
{
    CustomDataSerieCalc::serieToStream();
}

void MinuteDataSerieCalc::createId()
{
    DataSerieIdentifier dsId;
    dsId.id = m_assetId;
    switch (m_nOffset) {
    case 1:
       dsId.si = siOneMin;
    break;
    case 5:
        dsId.si = siFiveMin;
    case 15:
        dsId.si = siFifteenMin;
    case 30:
        dsId.si = siThirtyMin;
    case 60:
        dsId.si = siSixtyMin;
    default:
        break;
    }
    m_ID = dsId;
}

void MinuteDataSerieCalc::loadSerieFromJsonAV(QString json)
{
    QJsonDocument json_doc = QJsonDocument::fromJson(json.toUtf8());
    QVariantMap vmap = qvariant_cast<QVariantMap>(json_doc["Time Series (" + QString::number(m_nOffset) + "min)"]);
    DataSerieValue quote;
    DataSerieValue* pquote;
    DataSerieValue* pquoteaux{nullptr};
    QList<QString> list = vmap.keys();
    for(long long i{list.count() - 1}; i >= 0; --i){
        QString key = list[i];
        quote.dtQuoteDate = QDateTime::fromString(key, "yyyy-MM-dd hh:mm:ss");
        quote.qiQuote.dtQuoteDate = quote.dtQuoteDate;
        if (pquoteaux)
            quote.qiQuote.id = pquoteaux->qiQuote.id + 1;
        else
          quote.qiQuote.id = 0;
        QJsonObject obj = vmap[key].toJsonObject();

        QJsonValue open = obj.value("1. open");
        QJsonValue high = obj.value("2. high");
        QJsonValue low = obj.value("3. low");
        QJsonValue close = obj.value("4. close");
        QJsonValue volume = obj.value("5. volume");

        quote.dOpen = (open.toString()).toDouble();
        quote.dHigh = (high.toString()).toDouble();
        quote.dLow =  (low.toString()).toDouble();
        quote.dClose = (close.toString()).toDouble();
        quote.dVolume = (volume.toString()).toDouble();


        pquote = new DataSerieValue(quote);
        ar_values.append(pquote);
        pquoteaux = pquote;
    }
    serieToStream();
}

MinuteDataSerieCalc::MinuteDataSerieCalc(AssetId assetId, int offset, bool bLoad) : CustomDataSerieCalc(assetId)
{
    m_nOffset = offset;
    m_strDat = strFolder + assetId.name + "_" + QString::number(m_nOffset) + strPathSufix;
    m_strPath += m_strDat;
    MinuteDataSerieCalc::createId();

    if (bLoad)
        MinuteDataSerieCalc::loadSerieFromStream();
}
