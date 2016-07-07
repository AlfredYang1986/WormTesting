#-------------------------------------------------
#
# Project created by QtCreator 2016-06-06T19:01:43
#
#-------------------------------------------------

QT       += core gui
QT	 += network
QT	 += multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = WormTesting
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow/mainwindow.cpp\
        titlewidget/titlewidget.cpp \
        titlewidget/titlepushbutton.cpp \
        starttesting/starttestingpage.cpp \
    starttesting/imgcomparepane.cpp \
    reporting/reportingcontainer.cpp \
    reporting/samplereportingpane.cpp \
    reporting/reportingimgpane.cpp \
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
    reportlst/searchresulttablewidget.cpp

HEADERS  += mainwindow/mainwindow.h\
        titlewidget/titlewidget.h \
        titlewidget/titlepushbutton.h \
        tools/helptools.hpp \
        starttesting/starttestingpage.h \
    starttesting/imgcomparepane.h \
    reporting/reportingcontainer.h \
    reporting/samplereportingpane.h \
    reporting/reportingimgpane.h \
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
    reportlst/searchresulttablewidget.h

FORMS    +=

RESOURCES += \
    res.qrc

INCLUDEPATH += /usr/local/opt/include

LIBS += /usr/local/lib/libopencv_core.dylib \
        /usr/local/lib/libopencv_highgui.dylib \
        /usr/local/lib/libopencv_imgproc.dylib
