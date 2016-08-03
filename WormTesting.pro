#-------------------------------------------------
#
# Project created by QtCreator 2016-06-06T19:01:43
#
#-------------------------------------------------

QT       += core gui
QT	 += network
QT	 += multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
qtHaveModule(printsupport): QT += printsupport

TARGET = Paraview
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow/mainwindow.cpp\
        titlewidget/titlewidget.cpp \
        titlewidget/titlepushbutton.cpp \
        starttesting/starttestingpage.cpp \
    starttesting/imgcomparepane.cpp \
    reporting/reportingcontainer.cpp \
    reportlst/reportlstcontainer.cpp \
    sampleresource/sampleresourcecontainer.cpp \
    proxy/patientproxy.cpp \
    proxy/sampleproxy.cpp \
    proxy/wormproxy.cpp \
    proxy/fileoptproxy.cpp \
    proxy/proxymanager.cpp \
    pushwidget/pushwidget.cpp \
    commonwidget/resourcetreewidget.cpp \
    camera/cameraproxy.cpp \
    pushwidget/samplesearchingwidget.cpp \
    commonwidget/sampledetailwidget.cpp \
    commonwidget/commonimglstwidget.cpp \
    settingwiget/settingmainwidget.cpp \
    settingwiget/reportingdialog.cpp \
    settingwiget/addwormcatdialog.cpp \
    settingwiget/deletewwormcatdialog.cpp \
    settingwiget/addwormdialog.cpp \
    settingwiget/deletewormdialog.cpp \
    settingwiget/addsampleresourcedialog.cpp \
    commonwidget/imglstitem.cpp \
    reporting/reportingdetailwidget.cpp \
    reporting/reportingdetailitem.cpp \
    proxy/configproxy.cpp \
    settingwiget/deletesampleresourcedialog.cpp \
    settingwiget/addpatienttypedialog.cpp \
    settingwiget/deletepatienttypedialog.cpp \
    settingwiget/updatewormdesdialog.cpp \
    settingwiget/uploadwormimgdialog.cpp \
    imgcomparewidget/imagecomparewidget.cpp \
    reportlst/reportsearchconditionwidget.cpp \
    reportlst/searchresulttablewidget.cpp \
    commonwidget/commonimgpreviewwidget.cpp \
    proxy/authproxy.cpp \
    logindialog/logindialog.cpp \
    reporting/printpreviewdialog.cpp \
    settingwiget/addusersdialog.cpp \
    settingwiget/deleteusersdialog.cpp \
    sampleresource/resourceproxy/resourceproxy.cpp \
    sampleresource/resourceproxy/resourceimportdialog.cpp \
    aboutwidget/aboutmainwidget.cpp \
    aboutwidget/descriptionlabel.cpp \
    aboutwidget/aboutuswidget.cpp \
    aboutwidget/declearationwidget.cpp

HEADERS  += mainwindow/mainwindow.h\
        titlewidget/titlewidget.h \
        titlewidget/titlepushbutton.h \
        tools/helptools.hpp \
        starttesting/starttestingpage.h \
    starttesting/imgcomparepane.h \
    reporting/reportingcontainer.h \
    reportlst/reportlstcontainer.h \
    sampleresource/sampleresourcecontainer.h \
    proxy/patientproxy.h \
    proxy/sampleproxy.h \
    proxy/wormproxy.h \
    proxy/fileoptproxy.h \
    proxy/proxymanager.h \
    pushwidget/pushwidget.h \
    commonwidget/resourcetreewidget.h \
    camera/cameraproxy.h \
    camera/qtipl.hpp \
    pushwidget/samplesearchingwidget.h \
    commonwidget/sampledetailwidget.h \
    commonwidget/commonimglstwidget.h \
    settingwiget/settingmainwidget.h \
    settingwiget/reportingdialog.h \
    settingwiget/addwormcatdialog.h \
    settingwiget/deletewwormcatdialog.h \
    settingwiget/addwormdialog.h \
    settingwiget/deletewormdialog.h \
    settingwiget/addsampleresourcedialog.h \
    commonwidget/imglstitem.h \
    reporting/reportingdetailwidget.h \
    reporting/reportingdetailitem.h \
    proxy/configproxy.h \
    settingwiget/deletesampleresourcedialog.h \
    settingwiget/addpatienttypedialog.h \
    settingwiget/deletepatienttypedialog.h \
    settingwiget/updatewormdesdialog.h \
    settingwiget/uploadwormimgdialog.h \
    imgcomparewidget/imagecomparewidget.h \
    reportlst/reportsearchconditionwidget.h \
    reportlst/searchresulttablewidget.h \
    commonwidget/commonimgpreviewwidget.h \
    proxy/authproxy.h \
    logindialog/logindialog.h \
    reporting/printpreviewdialog.h \
    settingwiget/addusersdialog.h \
    settingwiget/deleteusersdialog.h \
    sampleresource/resourceproxy/resourceproxy.h \
    sampleresource/resourceproxy/resourceimportdialog.h \
    aboutwidget/aboutmainwidget.h \
    aboutwidget/descriptionlabel.h \
    aboutwidget/aboutuswidget.h \
    aboutwidget/declearationwidget.h

FORMS    +=

RESOURCES += \
    res.qrc

RC_ICONS = logo.ico
ICON = icon.icns

win32 {
INCLUDEPATH += C:\opencv\build\include

debug {
LIBS += C:\opencv\build\x64\vc14\lib\opencv_core2413.lib \
        C:\opencv\build\x64\vc14\lib\opencv_highgui2413.lib \
        C:\opencv\build\x64\vc14\lib\opencv_imgproc2413.lib
}

release {
LIBS += C:\opencv\build\x64\vc14\lib\opencv_core2413.lib \
        C:\opencv\build\x64\vc14\lib\opencv_highgui2413.lib \
        C:\opencv\build\x64\vc14\lib\opencv_imgproc2413.lib
}
}

mac {
INCLUDEPATH += /usr/local/opt/include

LIBS += /usr/local/lib/libopencv_core.dylib \
        /usr/local/lib/libopencv_highgui.dylib \
        /usr/local/lib/libopencv_imgproc.dylib
}
