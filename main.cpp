#include "mainwindow/mainwindow.h"
#include <QApplication>
#include <QSplashScreen>
#include <QTime>
#include "logindialog/logindialog.h"
#include <QTextCodec>
#include <QFileInfo>
#include <QProcess>
#include <QDebug>
#include <QMessageBox>

bool startService(QProcess&, const QString&);

int main(int argc, char *argv[])
{
    QProcess proc;

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

    QString service_dir = BKE_CURRENT_DIR + QString::fromLocal8Bit("/WormTestService");
    //=========================

    QApplication a(argc, argv);

    QSplashScreen* splash = new QSplashScreen;
    splash->setPixmap(QPixmap(":/resource/splash_screen.png"));
    splash->show();

    // Qt::Alignment topRight = Qt::AlignRight | Qt::AlignTop;
    // splash->showMessage(QStringLiteral("Setting Database ..."));

    QTime dieTime = QTime::currentTime().addMSecs(1500);
    while( QTime::currentTime() < dieTime )
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);

//    logindialog* dlg = new logindialog;
//    splash->finish(dlg);

    if (startService(proc, service_dir)) {
        MainWindow w;
        w.showLoginDialog();
    //    dlg->show();
    //    w.show();
        splash->finish(&w);
        return a.exec();
    } else {
        exit(-1);
    }
}

bool startService(QProcess& proc, const QString& dir) {
    QStringList arguments;

    qDebug() << dir << endl;
    QString tmp = dir;
    std::replace(tmp.begin(), tmp.end(), '/', '\\');
    qDebug() << tmp << endl;
//    proc.setWorkingDirectory("C:\\Users\\Alfred Yang\\Desktop\\WormTestService");
    proc.setWorkingDirectory(tmp);
    arguments << "/C" << "a.bat";
//    arguments << "play" << "start";
//    proc.start("/usr/local/play/play", arguments);
    proc.start("cmd.exe", arguments);

    // 等待进程启动
    if (!proc.waitForStarted()) {
        qDebug() << QStringLiteral("启动失败\n");
        QMessageBox::warning(NULL, "Error",
                             QStringLiteral("启动失败"),
                             QMessageBox::Ok, QMessageBox::Ok);
        return false;
    }

    // 关闭写通道,因为没有向进程写数据,没用到
    proc.closeWriteChannel();

    // 用于保存进程的控制台输出
    QByteArray procOutput;
    // 等待进程结束
    while (false == proc.waitForFinished()) {
        ;
    }

    // 读取进程输出到控制台的数据
    procOutput = proc.readAll();
    // 输出读到的数据
    qDebug() << procOutput.data() << endl;
    return true;
}
