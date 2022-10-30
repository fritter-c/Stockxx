#include "dailydataserie.h"
#include <QFile>

void DailyDataSerie::LoadSerieFromCSV(QString path, QChar delimiter)
{
    QFile f("D:\\Projects\\ChartOnGraphicsView\\DJI.csv");
    delimiter = ';';
    QStringList list;
    DataSerieValue* pquote;
    DataSerieValue* pquoteaux{nullptr};
    DataSerieValue quote;
    ClearDataSerie();
    assetID.name = "PETR4";
    try{
        if (f.open(QIODevice::ReadOnly))
        {
            QString data;
            f.readLine();
            while(!f.atEnd())
            {
                data = f.readLine();
                list = data.split(delimiter);
                quote.dtQuoteDate = QDateTime(QDateTime::fromString(list[0], "dd/MM/yyyy"));
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
        DailyDataSerie::SerieToStream();
    }

    catch(...){

    }

}

DailyDataSerie::DailyDataSerie(AssetId assetId) : CustomDataSerie(assetId)
{
    DailyDataSerie::LoadSerieFromStream();
}

void DailyDataSerie::LoadSerieFromStream()
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

    if (assetID != id) return;

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

void DailyDataSerie::SerieToStream()
{
    QFile file(m_strPath);
    if (!file.open(QIODevice::WriteOnly)) return;
    QDataStream out(&file);
    out << c_StreamStart;
    out << assetID.name;
    out.setVersion(QDataStream::Qt_6_0);
    DataSerieValue dt;
    for(size_t i{0}; i < ar_values.count(); i++)
    {
        dt = *ar_values[i];
        out << dt.dOpen;
        out << dt.dHigh;
        out << dt.dLow;
        out << dt.dClose;
        out << dt.dVolume;
        out << dt.dTrades;
        out << dt.dtQuoteDate;
        out << dt.qiQuote.id;
    }
    file.close();
}
