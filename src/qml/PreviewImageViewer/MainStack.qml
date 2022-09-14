import QtQuick 2.11
import QtQuick.Window 2.11
import QtQuick.Controls 2.4
import org.deepin.dtk 1.0

Rectangle {

    property alias source: mainView.source
    property alias sourcePaths: mainView.sourcePaths
    property alias currentIndex: mainView.currentIndex
    property alias iconName: titleRect.iconName
    property int currentWidgetIndex: 0
    Control {
        id: backcontrol
        hoverEnabled: true // 开启 Hover 属性
        property Palette backgroundColor: Palette {
            normal: "#F8F8F8"
            normalDark:"#000000"
        }
    }
    //标题栏
    ViewTopTitle{
         id: titleRect
         z: parent.z+1
    }

    id: stackView

    onSourcePathsChanged:  {
        if(sourcePaths > 0 && currentWidgetIndex == 0){
            currentWidgetIndex = 1
        }

    }



//    property alias source: imageViewer.source
//    initialItem: rect
    anchors.fill: parent

    OpenImageWidget{
        anchors.fill: parent
        visible: currentWidgetIndex===0?true:false

    }

    FullThumbnail{
        anchors.fill: parent
        visible: currentWidgetIndex===1?true:false
        id :mainView
    }

    SliderShow{
        id:sliderMainShow
        visible: currentWidgetIndex===2?true:false
        anchors.fill: parent
    }

//    interactive: false
//    currentIndex: currentWidgetIndex

}