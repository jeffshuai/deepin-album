/*
 * Copyright (C) 2020 ~ 2021 Uniontech Software Technology Co., Ltd.
 *
 * Author:     ZhangYong <zhangyong@uniontech.com>
 *
 * Maintainer: ZhangYong <ZhangYong@uniontech.com>
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
#ifndef THUMBNAILLISTVIEW_H
#define THUMBNAILLISTVIEW_H

#include "thumbnaildelegate.h"
#include "controller/configsetter.h"
#include "dbmanager/dbmanager.h"
#include "widgets/printhelper.h"
#include "imageengine/imageengineobject.h"
#include "albumgloabl.h"

#include <QListWidget>
#include <QListWidgetItem>
#include <QListView>
#include <QList>
#include <QWidgetAction>
#include <QPixmap>
#include <QIcon>
#include <QFileInfo>
#include <QSize>
#include <QStandardItemModel>
#include <QBuffer>
#include <QMouseEvent>
#include <QPointer>
#include <QPropertyAnimation>

#include <DPushButton>
#include <DImageButton>
#include <DIconButton>
#include <DListView>
#include <DLabel>
#include <DMenu>
#include <DApplicationHelper>


DWIDGET_USE_NAMESPACE

class ThumbnailListView : public DListView
{
    Q_OBJECT

public:
    enum ListViewUseFor {
        Normal,//
        Mount,//phone
    };
    enum MenuItemId {
        IdView,
        IdFullScreen,
        IdPrint,
        IdStartSlideShow,
        IdAddToAlbum,
        IdExport,
        IdCopy,
        IdCopyToClipboard,
        IdMoveToTrash,
        IdRemoveFromAlbum,
        IdEdit,
        IdAddToFavorites,
        IdRemoveFromFavorites,
        IdRotateClockwise,
        IdRotateCounterclockwise,
        IdLabel,
        IdSetAsWallpaper,
        IdDisplayInFileManager,
        IdImageInfo,
        IdSubMenu,
        IdSeparator,
        IdTrashRecovery,
        IdDrawingBoard//lmh0407画板
    };

    explicit ThumbnailListView(ThumbnailDelegate::DelegateType type = ThumbnailDelegate::NullType, const QString &imgtype = "All Photos", QWidget *parent = nullptr);
    ~ThumbnailListView() override;

    void insertThumbnail(const ItemInfo &iteminfo);//1050
    //为true则清除模型中的数据
    void stopLoadAndClear(bool bClearModel = false);
    //根据列表显示不同，返回不同数据
    QStringList getFileList(int row = -1);
    //获取所有文件信息
    QList<ItemInfo> getAllFileInfo(int row = -1);
    //根据路径返回所在行号
    int getRow(const QString &path);
    //筛选出所有选中缩略图
    QStringList selectedPaths();
    //获取拖拽的item
    QStringList getDagItemPath();
    //右键菜单
    void menuItemDeal(QStringList paths, QAction *action);
    int getListViewHeight();
    int getRow(QPoint point);
    void setListViewUseFor(ListViewUseFor usefor);
    //选中重复照片
    void selectDuplicatePhotos(QStringList paths);
    void updateModelRoleData(QString albumName, int actionType);
    void selectFirstPhoto();
    bool isFirstPhotoSelected();
    bool isNoPhotosSelected();
    void clearAll();

    /********* 插入一个空白项，ItemTypeBlank         *********/
    /********* 插入时间线标题，ItemTypeTimeLineTitle *********/
    /********* 插入已导入时间线标题，ItemTypeImportTimeLineTitle*********/
    void insertBlankOrTitleItem(ItemInfoType type, const QString &date = "", const QString &num = "", int height = 0);//1050
    //更新空白栏高度
    void resetBlankItemHeight(int height);//1050
    //根据DBImgInfoList插入listview
    void insertThumbnailByImgInfos(DBImgInfoList infoList);//1050

    //判断是否全部选中
    bool isAllSelected();//1050
    //判断选中图片是否都可旋转
    bool isAllSelectedSupportRotate();//1050
    //删除选中项到相册已删除
    void removeSelectToTrash(QStringList paths);//1050
    //更新时间线界面内各个按钮的text状态，单选/框选
    void updatetimeLimeBtnText();//1050
    //过滤显示选中类型
    void showSelectedTypeItem(ItemInfoType type);//1050
signals:
    //打开图片，该项在当前列表行数，以及该项所含信息路径
    void openImage(int row, QString path, bool bFullScreen);
    //幻灯片播放
    void sigSlideShow(QString path);
    void exportImage(QString, QStringList);
    void showExtensionPanel();
    void trashRecovery();

    void sigMouseRelease();
    void sigSelectAll();
    void sigMouseMove();
    //数据库图片加载完毕
    bool sigDBImageLoaded();

    //加载完成后刷新状态栏数量
    void sigUpdatePicNum();
    //时间线需要用到显示后的宽度
    void sigShowEvent();
    //最上方时间与图片数量
    void sigTimeLineDataAndNum(QString data, QString num, QString text);

    void sigMoveToTrash();

    //筛选显示图片或者视频，无结果时
    void sigNoPicOrNoVideo(bool isNoResult);//1050
protected:
    void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseMoveEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void keyPressEvent(QKeyEvent *event) Q_DECL_OVERRIDE;
    void dragEnterEvent(QDragEnterEvent *event) Q_DECL_OVERRIDE;
    void dragMoveEvent(QDragMoveEvent *event) Q_DECL_OVERRIDE;
    void dragLeaveEvent(QDragLeaveEvent *event) Q_DECL_OVERRIDE;
    void dropEvent(QDropEvent *event) Q_DECL_OVERRIDE;
    void startDrag(Qt::DropActions supportedActions) Q_DECL_OVERRIDE;
    void showEvent(QShowEvent *event) Q_DECL_OVERRIDE;
    void wheelEvent(QWheelEvent *event) Q_DECL_OVERRIDE;

private slots:
    void onMenuItemClicked(QAction *action);
    void onShowMenu(const QPoint &pos);
    void onPixMapScale(int value);
    void onCancelFavorite(const QModelIndex &index);
    void resizeEventF();
    void sltChangeDamagedPixOnThemeChanged();
    //删除图片之后更新listview中数据
    void updateThumbnailViewAfterDelete(const DBImgInfoList &infos);
    //时间线界面，选择当前时间内照片
    void slotSelectCurrentDatePic(bool isSelect, QStandardItem *item);
public slots:
    //所有照片界面
    void slotLoad80ThumbnailsFinish();

    //时间线界面
    //有新的图片加载上来
    void slotOneImgReady(const QString &path, QPixmap pix);
    //滚动条定时器
    void onScrollTimerOut();

    void onSyncListviewModelData(QStringList paths, QString albumName, int actionType);
    //处理时间线悬浮按钮与其他时间在滑动时的状态同步
    void onScrollbarValueChanged(int value);

    void onDoubleClicked(const QModelIndex &index);
    void onClicked(const QModelIndex &index);
    //设置所有选择按钮是否可见
    void slotChangeAllSelectBtnVisible(bool visible);//1050
public:
    void updateThumbnailView(QString updatePath = "");
    // zy 新算法
    void cutPixmap(ItemInfo &iteminfo);
    // 响应时间线悬浮栏的按钮选中操作
    void timeLimeFloatBtnClicked(const QString &date, bool isSelect);

private:
    void initConnections();
    void updateMenuContents();
    void appendAction(int id, const QString &text, const QString &shortcut);
    void initMenuAction();
    DMenu *createAlbumMenu();
    void resizeEvent(QResizeEvent *e) override;
    bool eventFilter(QObject *obj, QEvent *e) override;
    QPixmap getDamagedPixmap();
    //获取当前index所属时间线的时间和数量
    QStringList getCurrentIndexTime(const QModelIndex &index);
    //获取当前时间线内的图片选中状态
    bool getCurrentIndexSelectStatus(const QModelIndex &index, bool isPic);
    //判断是都全是选中类型
    bool isAllSelectType(ItemInfoType type);//1050
    //隐藏指定选中类型
    void hideAllSelectType(ItemInfoType type);//1050

    int m_iBaseHeight = 0;

    ThumbnailDelegate *m_delegate = nullptr;

    DMenu *m_pMenu = nullptr;
    QMap<QString, QAction *> m_MenuActionMap;
    DMenu *m_albumMenu = nullptr;

    QStringList m_dragItemPath;
    ThumbnailDelegate::DelegateType m_delegatetype = ThumbnailDelegate::NullType;

    QStringList m_allfileslist;
    bool m_bfirstload = true;
    bool bneedcache = true;
    QListWidgetItem *m_item = nullptr;

    //---触屏判断--------
    // 用于实现触屏滚动视图和框选文件不冲突，手指在屏幕上按下短时间内就开始移动
    // 会被认为触发滚动视图，否则为触发文件选择（时间默认为300毫秒）
    QPointer<QTimer> updateEnableSelectionByMouseTimer;

    // 记录触摸按下事件，在mouse move事件中使用，用于判断手指移动的距离，当大于
    // QPlatformTheme::TouchDoubleTapDistance 的值时认为触发触屏滚动
    QPoint lastTouchBeginPos;

    //触屏状态指示:0,等待模式;1,滑动模式;2,框选模式
    int touchStatus = 0;

    //是否激活click:当处于滑动模式的时候，本轮不执行click
    bool activeClick = true;

public:
    ListViewUseFor m_useFor = Normal;
    QString m_imageType;
    QStandardItemModel *m_model = nullptr;

    int m_rowSizeHint = 0;
    int m_blankItemHeight = 0;//上方空白项高度
    bool m_animationEnable = false;//标题上滑动画是否可执行
    QPropertyAnimation *m_animation = nullptr;
    QTimer *m_scrollTimer = nullptr;
    int m_height = 0;
    int m_onePicWidth = 0;
    bool m_isSelectAllBtn = false; //平板下，是否选中所有,默认未选定
};

#endif // THUMBNAILLISTVIEW_H
