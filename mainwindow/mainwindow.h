#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTabWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <map>
using std::map;

class QFrame;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void changeMainContent(const QString& title);

    void startTest(const QJsonObject&);
    void startReport(const QJsonObject&);
    void startReport(const QString&);
    void startCompare(const QString&);

protected:
    void setUpSubviews();

    void createPushWidget();
    void createTestingWidget();
    void createReportWidget();
    void createReportLstWidget();
    void createResourceWidget();
    void createCompareWidget();
    void createSettingWidget();
    void createAboutWidget();

    bool isReadyToChangeMainWidget();
private:
    QWidget* center_widget;
    QVBoxLayout* main_container;
    QWidget* title_widget;

    map<QString, QFrame*> contents;
};

#endif // MAINWINDOW_H
