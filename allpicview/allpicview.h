#ifndef ALLPICVIEW_H
#define ALLPICVIEW_H

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

class AllPicView : public ThumbnailListView
{
    Q_OBJECT

public:
    AllPicView();

signals:

private:
    void initConnections();
    void initThumbnailListView();

    void updatePicsIntoThumbnailView();



    void removeDBAllInfos();
private:

};

#endif // ALLPICVIEW_H
