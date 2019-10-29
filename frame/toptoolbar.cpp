/*
 * Copyright (C) 2016 ~ 2018 Deepin Technology Co., Ltd.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "toptoolbar.h"
#include "application.h"
#include "controller/configsetter.h"
#include "controller/importer.h"
#include "controller/signalmanager.h"
#include "controller/viewerthememanager.h"
#include "settings/settingswindow.h"
#include "widgets/dialogs/aboutdialog.h"
#include "utils/baseutils.h"
#include "utils/shortcut.h"

#include <dthememanager.h>
#include <dwindowminbutton.h>
#include <dwindowmaxbutton.h>
#include <dwindowclosebutton.h>
#include <dwindowoptionbutton.h>
#include <dtitlebar.h>

#include <QDebug>
#include <QHBoxLayout>
#include <QPainter>
#include <QProcess>
#include <QResizeEvent>
#include <QShortcut>
#include <QMenu>
#include <QStyleFactory>
#include <QImageReader>
#include <QLabel>
DWIDGET_USE_NAMESPACE

namespace {

const int TOP_TOOLBAR_HEIGHT = 39;
const int ICON_MARGIN = 6;

//const QColor DARK_COVERCOLOR = QColor(0, 0, 0, 217);
//const QColor LIGHT_COVERCOLOR = QColor(255, 255, 255, 230);

const QColor DARK_TOP_BORDERCOLOR = QColor(255, 255, 255, 0);
const QColor LIGHT_TOP_BORDERCOLOR = QColor(255, 255, 255, 0);

const QColor DARK_BOTTOM_BORDERCOLOR = QColor(0, 0, 0, 51);
const QColor LIGHT_BOTTOM_BORDERCOLOR = QColor(0, 0, 0, 26);
}  // namespace

TopToolbar::TopToolbar(bool manager, QWidget *parent)
    :DBlurEffectWidget(parent)
{
    m_manager = manager;
//    onThemeChanged(dApp->viewerTheme->getCurrentTheme());

#ifndef LITE_DIV
    m_settingsWindow = new SettingsWindow();
    m_settingsWindow->hide();
#endif
    QPalette palette;
    palette.setColor(QPalette::Background, QColor(0,0,0,0)); // 最后一项为透明度
    setPalette(palette);

    initMenu();
    initWidgets();

}

void TopToolbar::setLeftContent(QWidget *content)
{
    QLayoutItem *child;
    while ((child = m_lLayout->takeAt(0)) != 0) {
        if (child->widget())
            child->widget()->deleteLater();
        delete child;
    }

    m_lLayout->addWidget(content);
}

void TopToolbar::setMiddleContent(QString path)
{
//    QLayoutItem *child;
//    while ((child = m_mLayout->takeAt(0)) != 0) {
//        if (child->widget())
//            child->widget()->deleteLater();
//        delete child;
//    }

//    m_mLayout->addWidget(content);
//    QString filename="";
//    if(!path.isNull() && !path.isNull()){
//        filename = QFileInfo(path).fileName();
//    }
//    m_titlebar->setTitle(path);
    m_titletxt->setText(path);
}

void TopToolbar::mouseDoubleClickEvent(QMouseEvent *e)
{
    if (e->button() == Qt::LeftButton) {
        if (window()->isMaximized())
            window()->showNormal();
        else if (! window()->isFullScreen())  // It would be normal state
            window()->showMaximized();
    }

    DBlurEffectWidget::mouseDoubleClickEvent(e);
}
void TopToolbar::onThemeChanged(ViewerThemeManager::AppTheme curTheme) {
    QLinearGradient lightLinearGrad;
    lightLinearGrad.setColorAt(0, QColor(0, 0, 0, 0));
    lightLinearGrad.setColorAt(1, QColor(0, 0, 0, 0));
    lightLinearGrad.setStart(x(), y());
    lightLinearGrad.setFinalStop(x(), y() + height());


    if (curTheme == ViewerThemeManager::Dark) {
//        setCoverBrush(QBrush(QColor(0, 0, 0, 0)));
        m_topBorderColor = DARK_TOP_BORDERCOLOR;
        m_bottomBorderColor = DARK_BOTTOM_BORDERCOLOR;

//        Dtk::Widget::DThemeManager::instance()->setTheme("dark");
    } else {
//        setCoverBrush(QBrush(lightLinearGrad));
        m_topBorderColor = LIGHT_TOP_BORDERCOLOR;
        m_bottomBorderColor = LIGHT_BOTTOM_BORDERCOLOR;

//        Dtk::Widget::DThemeManager::instance()->setTheme("light");
    }


//    connect(dApp->viewerTheme, &ViewerThemeManager::viewerThemeChanged, this,
//            &TopToolbar::onThemeChanged);
}

const QString TopToolbar::newAlbumShortcut() const
{
    return dApp->setter->value("SHORTCUTALBUM", "New album", "Ctrl+Shift+N").toString();
}

void TopToolbar::paintEvent(QPaintEvent *e)
{
//    BlurFrame::paintEvent(e);

    QPainter p(this);
//    p.setRenderHint(QPainter::Antialiasing);

    // Draw inside top border
//    const QColor tc(m_topBorderColor);
//    int borderHeight = 1;
//    QPainterPath tPath;
//    tPath.moveTo(QPointF(x(), y() + borderHeight - 0.5));
//    tPath.lineTo(QPointF(x() + width(), y() + borderHeight - 0.5));
//    p.setPen(QPen(tc));
//    p.drawPath(tPath);
//    QPen tPen(tc);
//    QLinearGradient linearGrad;
//    linearGrad.setStart(x(), y());
//    linearGrad.setFinalStop(x() + width(), y());
//    linearGrad.setColorAt(0, Qt::transparent);
//    linearGrad.setColorAt(0.005, tc);
//    linearGrad.setColorAt(0.995, tc);
//    linearGrad.setColorAt(1, Qt::transparent);
//    tPen.setBrush(QBrush(linearGrad));
//    p.setPen(tPen);
//    p.drawPath(tPath);

    // Draw inside bottom border
//    QPainterPath bPath;
//    borderHeight = 0;
//    bPath.moveTo(x(), y() + height() - borderHeight - 0.5);
//    bPath.lineTo(x() + width(), y() + height() - borderHeight - 0.5);
//    QPen bPen(m_bottomBorderColor, borderHeight);
//    p.setPen(bPen);
//    p.drawPath(bPath);
    QPixmap pixmap(":/resources/common/titlebar.png");
    const QPalette pal = QGuiApplication::palette();//this->palette();
    QBrush bgColor = QBrush(pixmap.scaled(size().width(),50));
    QRectF bgRect;
    bgRect.setSize(size());
    QPainterPath pp;
    pp.addRoundedRect(QRectF(bgRect.x(),bgRect.y(),bgRect.width(),50), 0, 0);
    p.fillPath(pp, bgColor);
}

void TopToolbar::initLeftContent()
{
    QWidget *w = new QWidget;
    m_lLayout = new QHBoxLayout(w);
    m_lLayout->setContentsMargins(0, 0, 0, 0);
    m_lLayout->setSpacing(0);
#ifdef LITE_DIV
//    QLabel *logo = new QLabel(this);
//    QImageReader ir(":/images/logo/resources/images/logo/deepin-image-viewer.svg");

//    ir.setScaledSize(QSize(22, 22) * devicePixelRatioF());

//    QPixmap logo_pix = QPixmap::fromImage(ir.read());

//    logo_pix.setDevicePixelRatio(this->devicePixelRatioF());
//    logo->setPixmap(logo_pix);
//    logo->setAlignment(Qt::AlignCenter);
//    m_layout->addSpacing(12);
//    m_layout->addWidget(logo, 1, Qt::AlignLeft);
#endif
    m_layout->addWidget(w, 1, Qt::AlignLeft);
}

void TopToolbar::initMiddleContent()
{
    QWidget *w = new QWidget;
    w->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    m_mLayout = new QHBoxLayout(w);
    m_mLayout->setContentsMargins(0, 0, 0, 0);
    m_mLayout->setSpacing(0);

    m_layout->addWidget(w, 0, Qt::AlignCenter);
}

void TopToolbar::initRightContent()
{
    QWidget *w = new QWidget;
    m_rLayout = new QHBoxLayout(w);
    m_rLayout->setContentsMargins(0, 0, 0, 0);
    m_rLayout->setSpacing(0);

    m_layout->addWidget(w, 1, Qt::AlignRight);
    DTitlebar* m_titlebar = new DTitlebar(this);
    m_titlebar->setWindowFlags(Qt::WindowMinMaxButtonsHint |
                               Qt::WindowSystemMenuHint | Qt::WindowCloseButtonHint);
    m_titlebar->setMenu(m_menu);
    m_titlebar->setBackgroundTransparent(true);

    QWidget *customWidget = new QWidget();
    customWidget->setFixedWidth(0);
    m_titlebar->setCustomWidget(customWidget, false);
    m_rLayout->addWidget(m_titlebar);
}

void TopToolbar::initWidgets()
{
    m_layout = new QHBoxLayout(this);
    m_layout->setContentsMargins(0, 0, 0, 0);
    m_layout->setSpacing(0);

//    initLeftContent();
//    initMiddleContent();
//    initRightContent();
    m_titlebar = new DTitlebar(this);
    m_titlebar->setWindowFlags(Qt::WindowMinMaxButtonsHint |
                               Qt::WindowSystemMenuHint | Qt::WindowCloseButtonHint);
    m_titlebar->setMenu(m_menu);
    m_titlebar->setBackgroundTransparent(true);
//    m_titlebar->setIcon(QIcon(":/resources/images/other/deepin-album.svg"));
    m_titlebar->setIcon(QIcon::fromTheme("deepin-album"));
    QPalette pa;
    pa.setColor(QPalette::WindowText,QColor(255,255,255,255));
//    pa.setColor(QPalette::WindowText,Qt::red);
    m_titlebar->setPalette(pa);
    m_titlebar->setTitle("");
    m_titletxt=new DLabel;
    m_titletxt->setText("");
    QGraphicsDropShadowEffect* shadowEffect = new QGraphicsDropShadowEffect(m_titletxt);
    shadowEffect->setOffset(0, 1);
    shadowEffect->setColor(QColor(255,255,255,127));
    shadowEffect->setBlurRadius(1);
    m_titletxt->setGraphicsEffect(shadowEffect);
    m_titlebar->addWidget(m_titletxt,Qt::AlignCenter);

//    QWidget *customWidget = new QWidget();
//    customWidget->setFixedWidth(0);
//    m_titlebar->setCustomWidget(customWidget, false);
    m_layout->addWidget(m_titlebar);
    connect(dApp->signalM, &SignalManager::updateFileName,
            this, [ = ](const QString & filename){
//        QString filename="";
//        if(!vinfo.path.isNull() && !vinfo.path.isNull()){
//            filename = QFileInfo(vinfo.path).fileName();
//        }
//        m_titlebar->setTitle(filename);
        m_titletxt->setText(filename);
    });
}

void TopToolbar::initMenu()
{
    m_menu = new QMenu(this);
//    m_menu->setStyle(QStyleFactory::create("dlight"));

#ifndef LITE_DIV
    if (m_manager)
    {
        QAction *acNA = m_menu->addAction(tr("New album"));
        connect(acNA, &QAction::triggered, this, &TopToolbar::onNewAlbum);
    }
#endif
//    QAction *acDT = m_menu->addAction(tr("Dark theme"));

//    bool checkSelected =
//            dApp->viewerTheme->getCurrentTheme() == ViewerThemeManager::Dark;
//    acDT->setCheckable(checkSelected);
//    acDT->setChecked(checkSelected);

#ifndef LITE_DIV
    if (m_manager)
    {
        QAction *acS = m_menu->addAction(tr("Settings"));
        connect(acS, &QAction::triggered, this, &TopToolbar::onSetting);
    }
#endif

    m_menu->addSeparator();

//    if (utils::base::isCommandExist("dman")) {
//        QAction *acH = m_menu->addAction(tr("Help"));
//        connect(acH, &QAction::triggered, this, &TopToolbar::onHelp);
//        QShortcut *scH = new QShortcut(QKeySequence("F1"), this);
//        connect(scH, SIGNAL(activated()), this, SLOT(onHelp()));
//    }
//    QAction *acA = m_menu->addAction(tr("About"));
//    QAction *acE = m_menu->addAction(tr("Exit"));

//    connect(acDT, &QAction::triggered, this, &TopToolbar::onDeepColorMode);

//    connect(acA, &QAction::triggered, this, &TopToolbar::onAbout);
//    connect(acE, &QAction::triggered, dApp, &Application::quit);

#ifndef LITE_DIV
    QShortcut *scNA = new QShortcut(QKeySequence(newAlbumShortcut()), this);
#endif

    QShortcut *scE = new QShortcut(QKeySequence("Ctrl+Q"), this);
    QShortcut *scViewShortcut = new QShortcut(QKeySequence("Ctrl+Shift+/"), this);
#ifndef LITE_DIV
    connect(scNA, SIGNAL(activated()), this, SLOT(onNewAlbum()));
#endif
    connect(scE, SIGNAL(activated()), dApp, SLOT(quit()));
    connect(scViewShortcut, SIGNAL(activated()), this, SLOT(onViewShortcut()));

//    connect(dApp->viewerTheme, &ViewerThemeManager::viewerThemeChanged, this,
//            [=](ViewerThemeManager::AppTheme dark){
//        if (dark == ViewerThemeManager::Dark) {
//            acDT->setCheckable(true);
//            acDT->setChecked(true);
//        } else {
//            acDT->setCheckable(false);
//            acDT->setChecked(false);
//        }
//    });

#ifndef LITE_DIV
    connect(dApp->setter, &ConfigSetter::valueChanged, this, [=] (const QString &group) {
        if (group == "SHORTCUTALBUM") {
            scNA->setKey(QKeySequence(newAlbumShortcut()));
        }
    });
#endif
}

void TopToolbar::onViewShortcut() {
    QRect rect = window()->geometry();
    QPoint pos(rect.x() + rect.width()/2 , rect.y() + rect.height()/2);
    Shortcut sc;
    QStringList shortcutString;
    QString param1 = "-j="+sc.toStr();
    QString param2 = "-p=" + QString::number(pos.x()) + "," + QString::number(pos.y());
    shortcutString << param1 << param2;

    QProcess::startDetached("deepin-shortcut-viewer", shortcutString);
}

//void TopToolbar::onAbout()
//{
//    AboutDialog *ad = new AboutDialog;
//    ad->show();
//    QWidget *w = window();
//    QPoint gp = w->mapToGlobal(QPoint(0, 0));
//    ad->move((w->width() - ad->width()) / 2 + gp.x(),
//               (w->height() - ad->sizeHint().height()) / 2 + gp.y());
//}

void TopToolbar::onHelp()
{
    if (m_manualPro.isNull()) {
        const QString pro = "dman";
        const QStringList args("deepin-image-viewer");
        m_manualPro = new QProcess(this);
        connect(m_manualPro.data(), SIGNAL(finished(int)),
                m_manualPro.data(), SLOT(deleteLater()));
        m_manualPro->start(pro, args);
    }
}

#ifndef LITE_DIV
void TopToolbar::onNewAlbum()
{
    emit dApp->signalM->createAlbum();
}

void TopToolbar::onSetting()
{
    m_settingsWindow->move((width() - m_settingsWindow->width()) / 2 +
                           mapToGlobal(QPoint(0, 0)).x(),
                           (window()->height() - m_settingsWindow->height()) / 2 +
                           mapToGlobal(QPoint(0, 0)).y());
    m_settingsWindow->show();
}
#endif

void TopToolbar::onDeepColorMode() {
    if (dApp->viewerTheme->getCurrentTheme() == ViewerThemeManager::Dark) {
        dApp->viewerTheme->setCurrentTheme(
                    ViewerThemeManager::Light);
    } else {
        dApp->viewerTheme->setCurrentTheme(
                    ViewerThemeManager::Dark);
    }
}
