#ifndef IMPORTVIEW_H
#define IMPORTVIEW_H

#include "application.h"
#include "utils/baseutils.h"
#include "utils/imageutils.h"
#include "controller/configsetter.h"
#include "controller/signalmanager.h"
#include "dbmanager/dbmanager.h"
#include "widgets/thumbnaillistview.h"


#include <QWidget>
#include <QVBoxLayout>
#include <DLabel>
#include <QPixmap>
#include <QStandardPaths>
#include <QImageReader>
#include <DPushButton>
#include <QDir>
#include <QFileDialog>
#include <QFileInfo>
#include <DStackedWidget>
#include <DSlider>

DWIDGET_USE_NAMESPACE

class ImportView : public DWidget
{
    Q_OBJECT

public:
    ImportView();

private:
    void initConnections();
    void initUI();

public:
    DPushButton* m_pImportBtn;
};

#endif // IMPORTVIEW_H
