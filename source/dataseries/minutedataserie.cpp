#include "minutedataserie.h"

int MinuteDataSerie::nOffset() const
{
    return m_nOffset;
}

void MinuteDataSerie::loadSerieFromCSV(QString path, QChar delimiter)
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
           ar_values.append(dt);
           if(dt.dHigh > m_dMax){
               m_dMax = dt.dHigh;
           }
           if (dt.dLow < m_dMin){
               m_dMin = dt.dLow;
           }

       }
       file.close();
       fixEmptySeries();
}

void MinuteDataSerie::loadSerieFromStream()
{
    QFile file(m_strPath);
    if(!file.open(QIODevice::ReadOnly)) return;

    QDataStream in(&file);
    quint32 start;
    AssetId id;
    QVector<DataSerieValue> temp_values;

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
        temp_values.append(dt);
        if(dt.dHigh > m_dMax){
            m_dMax = dt.dHigh;
        }
        if (dt.dLow < m_dMin){
            m_dMin = dt.dLow;
        }

    }
    ar_values.resize(temp_values.count());
    for(long long i{temp_values.count() -1}; i >= 0; --i){
        ar_values[i] = temp_values[temp_values.count() - 1 - i];
    }
    file.close();
    fixEmptySeries();
}

void MinuteDataSerie::serieToStream()
{
    CustomDataSerie::serieToStream();
}

void MinuteDataSerie::createId()
{
    DataSerieIdentifier dsId;
    dsId.id = m_assetId;
    dsId.si = (SerieInterval)m_nOffset;
    m_ID = dsId;
}

void MinuteDataSerie::loadSerieFromJsonAV(QString json)
{
    QJsonDocument json_doc = QJsonDocument::fromJson(json.toUtf8());
    QVariantMap vmap = qvariant_cast<QVariantMap>(json_doc["Time Series (" + QString::number(m_nOffset) + "min)"]);
    DataSerieValue quote;
    DataSerieValue quoteaux{};
    QList<QString> list = vmap.keys();
    QVector<DataSerieValue> temp_values;
    for(long long i{list.count() - 1}; i >= 0; --i){
        QString key = list[i];
        quote.dtQuoteDate = QDateTime::fromString(key, "yyyy-MM-dd hh:mm:ss");
        quote.qiQuote.dtQuoteDate = quote.dtQuoteDate;
        if (quoteaux != INVALID_DATA)
            quote.qiQuote.id = quoteaux.qiQuote.id + 1;
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

        temp_values.append(quote);
        quoteaux = quote;
        if(quote.dHigh > m_dMax){
            m_dMax = quote.dHigh;
        }
        if (quote.dLow < m_dMin){
            m_dMin = quote.dLow;
        }
    }
    ar_values.resize(temp_values.count());
    for(long long i{temp_values.count() -1}; i >= 0; --i){
        ar_values[i] = temp_values[temp_values.count() - 1 - i];
    }
    fixEmptySeries();
    serieToStream();
}

MinuteDataSerie::MinuteDataSerie(AssetId assetId, int offset, bool bLoad) : CustomDataSerie(assetId)
{
    m_nOffset = offset;
    m_strDat = m_strFolder + assetId.name + "_" + QString::number(m_nOffset) + m_strPathSufix;
    m_strPath += m_strDat;
    QDir dir{m_strBasePath + m_strFolder};
    if (!dir.exists()){
        dir.mkdir(m_strBasePath + m_strFolder);
    }
    MinuteDataSerie::createId();

    if (bLoad)
        MinuteDataSerie::loadSerieFromStream();
}
