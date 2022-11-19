#include "dailydataserie.h"
#include <QFile>

void DailyDataSerie::loadSerieFromCSV(QString path, QChar delimiter)
{
    QFile f("D:\\Projects\\ChartOnGraphicsView\\DJI.csv");
    delimiter = ';';
    QStringList list;
    DataSerieValue* pquote;
    DataSerieValue* pquoteaux{nullptr};
    DataSerieValue quote;
    ClearDataSerie();
    m_assetId.name = "DJI";
    try{
        if (f.open(QIODevice::ReadOnly))
        {
            QString data;
            f.readLine();
            while(!f.atEnd())
            {
                data = f.readLine();
                list = data.split(delimiter);
                quote.dtQuoteDate = QDateTime::fromString(list[0], "dd/MM/yyyy");
                quote.dOpen = list[1].toDouble();
                quote.dHigh = list[2].toDouble();
                quote.dLow  = list[3].toDouble();
                quote.dClose = list[4].toDouble();
                quote.dTrades = list[5].toDouble();
                quote.dVolume = list[6].toDouble();
                quote.qiQuote.dtQuoteDate = quote.dtQuoteDate;
                if (pquoteaux)
                    quote.qiQuote.id = pquoteaux->qiQuote.id + 1;
                else
                  quote.qiQuote.id = 0;
                pquote = new DataSerieValue(quote);
                ar_values.append(pquote);
                pquoteaux = pquote;
            }
        }
        DailyDataSerie::serieToStream();
    }

    catch(...){

    }

}

void DailyDataSerie::createId()
{
    DataSerieIdentifier id;
    id.id = m_assetId;
    id.si = siDaily;
    m_ID = id;
}

void DailyDataSerie::loadSerieFromJsonAV(QString json)
{
    QJsonDocument json_doc = QJsonDocument::fromJson(json.toUtf8());
    QVariantMap vmap = qvariant_cast<QVariantMap>(json_doc["Time Series (Daily)"]);
    DataSerieValue quote;
    DataSerieValue* pquote;
    DataSerieValue* pquoteaux{nullptr};
    QList<QString> list = vmap.keys();
    for(long long i{list.count() - 1}; i >= 0; --i){
        QString key = list[i];
        quote.dtQuoteDate = QDateTime::fromString(key, "yyyy-MM-dd");
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

DailyDataSerie::DailyDataSerie(AssetId assetId, bool bLoad) : CustomDataSerie(assetId)
{
    m_strDat = strFolder + assetId.name + strPathSufix;
    m_strPath += m_strDat;
    DailyDataSerie::createId();
    if (bLoad)
        DailyDataSerie::loadSerieFromStream();
}

DailyDataSerie::~DailyDataSerie()
{

}

void DailyDataSerie::loadSerieFromStream()
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

void DailyDataSerie::serieToStream()
{
    CustomDataSerie::serieToStream();
}
