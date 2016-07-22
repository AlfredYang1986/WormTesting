#include "mainwindow/mainwindow.h"
#include <QApplication>
#include <QSplashScreen>
#include <QTime>
#include "logindialog/logindialog.h"
#include <QTextCodec>
#include <QFileInfo>

int main(int argc, char *argv[])
{

    //path ============info@seatrix.com
    QTextCodec *xcodec = QTextCodec::codecForLocale();
    QString exeDir = xcodec->toUnicode( QByteArray(argv[0]) ) ;
    QString BKE_CURRENT_DIR = QFileInfo(exeDir).path() ;
    QStringList  libpath;

    libpath << BKE_CURRENT_DIR + QString::fromLocal8Bit("/plugins/platforms");
    libpath << BKE_CURRENT_DIR + QString::fromLocal8Bit("/plugins/imageformats");
    libpath << BKE_CURRENT_DIR + QString::fromLocal8Bit("/plugins");
    libpath << BKE_CURRENT_DIR;
    libpath << QApplication::libraryPaths();
    QApplication::setLibraryPaths(libpath) ;
    //=========================

    QApplication a(argc, argv);

    QSplashScreen* splash = new QSplashScreen;
    splash->setPixmap(QPixmap(":/resource/splash_screen.png"));
    splash->show();

    // Qt::Alignment topRight = Qt::AlignRight | Qt::AlignTop;
    // splash->showMessage(QStringLiteral("Setting Database ..."));

    QTime dieTime = QTime::currentTime().addMSecs(3000);
    while( QTime::currentTime() < dieTime )
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);

//    logindialog* dlg = new logindialog;
//    splash->finish(dlg);

    MainWindow w;
    w.showLoginDialog();
//    dlg->show();
//    w.show();
    splash->finish(&w);

    return a.exec();
}
