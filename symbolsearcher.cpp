#include "symbolsearcher.h"
#include "qtimer.h"
#include "ui_symbolsearcher.h"
#include <QNetworkReply>
#include <QJsonObject>
#include <QCompleter>
#include "dataseriemanager.h"

void SymbolSearcher::setKeyWord(const QString &newKeyWord)
{
    if (m_keyWord != newKeyWord){
        m_keyWord = newKeyWord;
        m_tickerSearcherApi.setKeyWord(m_keyWord);
        m_tickerSearcherApi.newRequest();
    }
}

QString SymbolSearcher::getTicker()
{
    return ui->lineEdit_tickerKeyword->text();
}

bool SymbolSearcher::getFreeWindow()
{
    return ui->checkBox_FreeWindow->isChecked();
}

void SymbolSearcher::onSearchTimer()
{
    m_tmrSearch->stop();
    setKeyWord(ui->lineEdit_tickerKeyword->text());
    m_tmrSearch->start();
}

void SymbolSearcher::onDataReady()
{
    m_lstResults = m_tickerSearcherApi.results();
    m_completer->model()->resetItems(m_lstResults);
}

SymbolSearcher::SymbolSearcher(QWidget *parent, bool bLocal) :
    QDialog(parent),
    ui(new Ui::SymbolSearcher)
{
    ui->setupUi(this);
    setFixedSize(400,300);
    if (!bLocal){
        m_tmrSearch = new QTimer(this);
        m_tmrSearch->setInterval(500);

        connect(m_tmrSearch, &QTimer::timeout, this, &SymbolSearcher::onSearchTimer);
        connect(&m_tickerSearcherApi, &symbolseracherapi::dataReady, this, &SymbolSearcher::onDataReady);
        m_tmrSearch->start();
        m_completer = new TickerCompleter(this);
        ui->lineEdit_tickerKeyword->setCompleter(m_completer);
    }
    else{
        m_completer = new TickerCompleter(this);
        ui->lineEdit_tickerKeyword->setCompleter(m_completer);
        m_completer->model()->resetItems(DataSerieManager::Instance().avaiableDataSeries);
    }

}

SymbolSearcher::~SymbolSearcher()
{
    delete ui;
    if (m_completer){
        delete m_completer;
    }
}
