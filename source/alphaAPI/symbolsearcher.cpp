#include "symbolsearcher.h"
#include "qtimer.h"
#include "ui_symbolsearcher.h"
#include <QNetworkReply>
#include <QJsonObject>
#include <QCompleter>
#include "QPushButton"

void SymbolSearcher::setKeyWord(const QString &newKeyWord)
{
    if ((m_keyWord != newKeyWord) and (!m_local)){
        m_keyWord = newKeyWord;
        m_tickerSearcherApi.setKeyWord(m_keyWord);
        m_tickerSearcherApi.newRequest();
    }
}

QString SymbolSearcher::getTicker()
{
    return ui->lineEdit_tickerKeyword->text();
}

SerieInterval SymbolSearcher::getInterval()
{
    if (ui->radioButton_Daily->isChecked()){
        return siDaily;
    }
    else if(ui->radioButton_1->isChecked()){
        return siOneMin;
    }
    else if(ui->radioButton_5->isChecked()){
        return siFiveMin;
    }
    else if(ui->radioButton_15->isChecked()){
        return siFifteenMin;
    }
    else if(ui->radioButton_30->isChecked()){
        return siThirtyMin;
    }
    return siSixtyMin;

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

void SymbolSearcher::onCompleterActivated(const QString &ticker)
{
    m_tmrSearch->stop();
    ui->lineEdit_tickerKeyword->setText(ticker);
    ui->buttonBox->button(QDialogButtonBox::StandardButton::Ok)->click();

}

void SymbolSearcher::onDataReady()
{
    m_lstResults = m_tickerSearcherApi.results();
    m_completer->model()->resetItems(m_lstResults);
    emit complete(QRect());
}

SymbolSearcher::SymbolSearcher(QWidget *parent, bool bLocal) :
    QDialog(parent),
    ui(new Ui::SymbolSearcher)
{
    ui->setupUi(this);
    setFixedSize(400,300);
    m_local = bLocal;
    if (!bLocal){
        m_tmrSearch = new QTimer(this);
        m_tmrSearch->setInterval(2000);
        connect(m_tmrSearch, &QTimer::timeout, this, &SymbolSearcher::onSearchTimer);
        connect(&m_tickerSearcherApi, &symbolseracherapi::dataReady, this, &SymbolSearcher::onDataReady);        
        m_completer = new TickerCompleter(QCompleter::UnfilteredPopupCompletion, this);
        connect(this, &SymbolSearcher::complete,
                m_completer, &TickerCompleter::complete);
        connect(m_completer, QOverload<const QString &>::of(&QCompleter::activated),this,
                [this](const QString &index){this->onCompleterActivated(index);});
        ui->lineEdit_tickerKeyword->setCompleter(m_completer);
        ui->groupBox_timeFrame->setVisible(true);
    }
}

SymbolSearcher::~SymbolSearcher()
{
    delete ui;
    if (m_completer){
        delete m_completer;
    }
}

void SymbolSearcher::on_lineEdit_tickerKeyword_textChanged(const QString &arg1)
{
    if ((!m_local) && (m_tmrSearch))
        m_tmrSearch->start();
}

