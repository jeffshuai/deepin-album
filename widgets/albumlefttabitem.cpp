#include "widgets/albumlefttabitem.h"
#include "dbmanager/dbmanager.h"
#include "utils/baseutils.h"
#include "application.h"
#include <QHBoxLayout>
#include "controller/signalmanager.h"
#include <DFontSizeManager>
#include <QPainter>
namespace
{
const int LAYOUT_SPACING = 10;
const int OPE_MODE_ADDNEWALBUM = 0;
const int OPE_MODE_RENAMEALBUM = 1;
const QString EXTERNAL_DEVICE_ALBUM = "External Devices";
}// namespace

using namespace utils::common;

AlbumLeftTabItem::AlbumLeftTabItem(QString str, QString strAlbumType)
{
    m_albumNameStr = str;
    m_opeMode = 0;
    m_albumTypeStr = strAlbumType;

    initUI();
    initConnections();
}

AlbumLeftTabItem::~AlbumLeftTabItem()
{

}

void AlbumLeftTabItem::initConnections()
{
    connect(m_pLineEdit, &DLineEdit::editingFinished, this, &AlbumLeftTabItem::onCheckNameValid);
}

void AlbumLeftTabItem::initUI()
{
    setFixedSize(160, 40);
    QHBoxLayout *pHBoxLayout = new QHBoxLayout();
    pHBoxLayout->setContentsMargins(0,0,0,0);
    pHBoxLayout->setSpacing(0);


    QLabel* pLabel = new QLabel();
    pLabel->setFixedSize(18, 18);


    if (COMMON_STR_RECENT_IMPORTED == m_albumNameStr)
    {
        QPixmap pixmap;
        pixmap = utils::base::renderSVG(":/resources/images/sidebar/normal/icon_import_normal.svg", QSize(18,18));
        pLabel->setPixmap(pixmap);
    }
    else if (COMMON_STR_TRASH == m_albumNameStr)
    {
        QPixmap pixmap;
        pixmap = utils::base::renderSVG(":/resources/images/sidebar/normal/icon_trash_normal.svg", QSize(18, 18));
        pLabel->setPixmap(pixmap);
    }
    else if (COMMON_STR_FAVORITES == m_albumNameStr)
    {
        QPixmap pixmap;
        pixmap = utils::base::renderSVG(":/resources/images/sidebar/normal/icon_collection_normal.svg", QSize(18, 18));
        pLabel->setPixmap(pixmap);
    }
    else if (EXTERNAL_DEVICE_ALBUM == m_albumTypeStr)
    {
        QPixmap pixmap;
        pixmap = utils::base::renderSVG(":/resources/images/sidebar/normal/icon_iphone_normal.svg", QSize(18, 18));
        pLabel->setPixmap(pixmap);
    }
    else
    {
        QPixmap pixmap;
        pixmap = utils::base::renderSVG(":/resources/images/sidebar/normal/icon_album_normal.svg", QSize(18, 18));
        pLabel->setPixmap(pixmap);
    }

    DWidget *pWidget = new DWidget();

    m_nameLabel = new QLabel(pWidget);
    m_nameLabel->setGeometry(QRect(16, 0, 118, 40));

//    QString streElide = geteElidedText(m_nameLabel->font(),m_albumNameStr,20);
//    m_nameLabel->setText(streElide);

    QFontMetrics elideFont(m_nameLabel->font());
    if (COMMON_STR_RECENT_IMPORTED == m_albumNameStr)
    {
        m_nameLabel->setText(elideFont.elidedText(tr(COMMON_STR_RECENT_IMPORTED), Qt::ElideRight, 85));
    }
    else if (COMMON_STR_TRASH == m_albumNameStr)
    {
        m_nameLabel->setText(elideFont.elidedText(tr(COMMON_STR_TRASH), Qt::ElideRight, 85));
    }
    else if (COMMON_STR_FAVORITES == m_albumNameStr)
    {
        m_nameLabel->setText(elideFont.elidedText(tr(COMMON_STR_FAVORITES), Qt::ElideRight, 85));
    }
    else
    {
        m_nameLabel->setText(elideFont.elidedText(m_albumNameStr, Qt::ElideRight, 85));
    }
    m_nameLabel->setAlignment(Qt::AlignVCenter);
    m_nameLabel->setFont(DFontSizeManager::instance()->get(DFontSizeManager::T6));

    m_pLineEdit = new DLineEdit(pWidget);
    m_pLineEdit->setGeometry(QRect(0, 0, 120, 40));
    if (COMMON_STR_RECENT_IMPORTED == m_albumNameStr)
    {
        m_pLineEdit->setText(tr(COMMON_STR_RECENT_IMPORTED));
    }
    else if (COMMON_STR_TRASH == m_albumNameStr)
    {
        m_pLineEdit->setText(tr(COMMON_STR_TRASH));
    }
    else if (COMMON_STR_FAVORITES == m_albumNameStr)
    {
        m_pLineEdit->setText(tr(COMMON_STR_FAVORITES));
    }
    else
    {
        m_pLineEdit->setText(m_albumNameStr);
    }

    m_pLineEdit->lineEdit()->setTextMargins(14,0,0,0);
    m_pLineEdit->lineEdit()->setAlignment(Qt::AlignVCenter| Qt::AlignLeft);
//    m_pLineEdit->setStyleSheet(QString::fromUtf8("selection-background-color: rgb(0,129,255);"));
//    m_pLineEdit->setStyleSheet("border-radius:8px;"
//                               "background: rgba(255,255,255,0.00);"
//                               "border: 2px solid #0081FF;"
//                               "box-shadow: 0 2px 4px 0 rgba(0,0,0,0.05);"
//                               );

    m_pLineEdit->setVisible(false);
    m_pLineEdit->lineEdit()->setMaxLength(64);
    m_pLineEdit->setClearButtonEnabled(false);


    pHBoxLayout->addWidget(pLabel, Qt::AlignVCenter);
    pHBoxLayout->addWidget(pWidget, Qt::AlignVCenter);



    this->setLayout(pHBoxLayout);
}

void AlbumLeftTabItem::editAlbumEdit()
{
    m_nameLabel->setVisible(false);
    m_pLineEdit->setVisible(true);
    m_pLineEdit->lineEdit()->selectAll();
    m_pLineEdit->lineEdit()->setFocus();
}

void AlbumLeftTabItem::onCheckNameValid()
{
    QString newNameStr = m_pLineEdit->text().trimmed();

    if (DBManager::instance()->getAllAlbumNames().contains(newNameStr)
        || COMMON_STR_RECENT_IMPORTED == newNameStr
        || COMMON_STR_TRASH == newNameStr
        || COMMON_STR_FAVORITES == newNameStr
        || newNameStr.isEmpty())
    {
        newNameStr = m_albumNameStr;
    }

    if (OPE_MODE_RENAMEALBUM == m_opeMode)
    {
        m_nameLabel->setText(newNameStr);
        QFontMetrics elideFont(m_nameLabel->font());
        m_nameLabel->setText(elideFont.elidedText(newNameStr, Qt::ElideRight, 85));
        QFont ft;
        ft.setPixelSize(14);

        m_pLineEdit->setText(newNameStr);

        m_nameLabel->setVisible(true);
        m_pLineEdit->setVisible(false);

        DBManager::instance()->renameAlbum(m_albumNameStr, newNameStr);

        m_albumNameStr = newNameStr;
        emit dApp->signalM->sigUpdataAlbumRightTitle(m_albumNameStr);
    }

    if (OPE_MODE_ADDNEWALBUM == m_opeMode)
    {
        m_nameLabel->setText(newNameStr);
        QFontMetrics elideFont(m_nameLabel->font());
        m_nameLabel->setText(elideFont.elidedText(newNameStr, Qt::ElideRight, 85));
        QFont ft;
        ft.setPixelSize(14);

        m_pLineEdit->setText(newNameStr);

        m_nameLabel->setVisible(true);
        m_pLineEdit->setVisible(false);

        DBManager::instance()->insertIntoAlbum(newNameStr, QStringList(" "));

        m_albumNameStr = newNameStr;
        emit dApp->signalM->sigUpdataAlbumRightTitle(m_albumNameStr);
    }
}
