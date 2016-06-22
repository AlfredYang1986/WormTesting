#-------------------------------------------------
#
# Project created by QtCreator 2016-06-06T19:01:43
#
#-------------------------------------------------

QT       += core gui
QT	 += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = WormTesting
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow/mainwindow.cpp\
        titlewidget/titlewidget.cpp \
        titlewidget/titlepushbutton.cpp \
        starttesting/starttestingpage.cpp \
    starttesting/sampledetailwidget.cpp \
    starttesting/wormtreewidget.cpp \
    starttesting/imgcomparepane.cpp \
    reporting/reportingcontainer.cpp \
    reporting/reportingdetailcontainer.cpp \
    reporting/detailpane.cpp \
    reporting/samplereportingpane.cpp \
    reporting/reportingimgpane.cpp \
    reportlst/reportlstcontainer.cpp \
    reportlst/searchtreewidget.cpp \
    reportlst/searchresulttablewidget.cpp \
    sampleresource/sampleresourcecontainer.cpp \
    proxy/patientproxy.cpp \
    proxy/sampleproxy.cpp \
    proxy/wormproxy.cpp \
    proxy/fileoptproxy.cpp \
    proxy/proxymanager.cpp \
    starttesting/samplesearchingwidget.cpp \
    pushwidget/pushwidget.cpp \
    sampleresource/resourcetreewidget.cpp

HEADERS  += mainwindow/mainwindow.h\
        titlewidget/titlewidget.h \
        titlewidget/titlepushbutton.h \
        tools/helptools.hpp \
        starttesting/starttestingpage.h \
    starttesting/sampledetailwidget.h \
    starttesting/wormtreewidget.h \
    starttesting/imgcomparepane.h \
    reporting/reportingcontainer.h \
    reporting/reportingdetailcontainer.h \
    reporting/detailpane.h \
    reporting/samplereportingpane.h \
    reporting/reportingimgpane.h \
    reportlst/reportlstcontainer.h \
    reportlst/searchtreewidget.h \
    reportlst/searchresulttablewidget.h \
    sampleresource/sampleresourcecontainer.h \
    proxy/patientproxy.h \
    proxy/sampleproxy.h \
    proxy/wormproxy.h \
    proxy/fileoptproxy.h \
    proxy/proxymanager.h \
    starttesting/samplesearchingwidget.h \
    pushwidget/pushwidget.h \
    sampleresource/resourcetreewidget.h

FORMS    +=

RESOURCES += \
    res.qrc
