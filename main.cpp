#include "mainwindow/mainwindow.h"
#include <QApplication>
#include <QSplashScreen>
#include <QTime>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QSplashScreen* splash = new QSplashScreen;
    splash->setPixmap(QPixmap(":/resource/splash_screen.png"));
    splash->show();

    Qt::Alignment topRight = Qt::AlignRight || Qt::AlignTop;
    splash->showMessage(QStringLiteral("Setting Database ..."));

    QTime dieTime = QTime::currentTime().addMSecs(3000);
    while( QTime::currentTime() < dieTime )
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);

    MainWindow w;
    w.show();
    splash->finish(&w);

    return a.exec();
}
