#include "statusbar.h"
#include <QGraphicsDropShadowEffect>

StatusBar::StatusBar()
{

    initUI();

}

void StatusBar::initUI()
{
    setFixedHeight(27);

    QString str = tr("%1张照片");
    m_allPicNum = DBManager::instance()->getImgsCount();

    m_pAllPicNumLabel = new DLabel(this);
    m_pAllPicNumLabel->setText(str.arg(QString::number(m_allPicNum)));
    m_pAllPicNumLabel->setFont(DFontSizeManager::instance()->get(DFontSizeManager::T8));
    m_pAllPicNumLabel->setAlignment(Qt::AlignCenter);
    m_pAllPicNumLabel->setFixedHeight(18);

    m_pSlider = new DSlider(Qt::Horizontal, this);
    m_pSlider->setFixedWidth(180);
    m_pSlider->setFixedHeight(27);
    m_pSlider->setMinimum(0);
    m_pSlider->setMaximum(4);
    m_pSlider->slider()->setSingleStep(1);
    m_pSlider->slider()->setTickInterval(1);
    m_pSlider->setValue(2);

    QGraphicsDropShadowEffect *effect = new QGraphicsDropShadowEffect();
    effect->setOffset(0,2);
    effect->setColor(QColor(44,167,248,127));
    effect->setBlurRadius(4);
    m_pSlider->setGraphicsEffect(effect);

    QHBoxLayout* pHBoxLayout = new QHBoxLayout();
    pHBoxLayout->setContentsMargins(0,0,0,3);
    pHBoxLayout->addWidget(m_pAllPicNumLabel,Qt::AlignCenter);
    this->setLayout(pHBoxLayout);

    initConnections();
}

void StatusBar::initConnections()
{
    connect(dApp->signalM, &SignalManager::imagesInserted, this, &StatusBar::onUpdateAllpicsNumLabel);
    connect(dApp->signalM, &SignalManager::imagesRemoved, this, &StatusBar::onUpdateAllpicsNumLabel);
}

void StatusBar::onUpdateAllpicsNumLabel()
{
    QString str = tr("%1张照片");

    m_allPicNum = DBManager::instance()->getImgsCount();
    m_pAllPicNumLabel->setText(str.arg(QString::number(m_allPicNum)));
}

void StatusBar::resizeEvent(QResizeEvent *e)
{
    m_pSlider->move(width()-214, -1);
}
