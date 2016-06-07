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

protected:
    void setUpSubviews();

    void createTestingWidget();
    void createReportWidget();
    void createReportLstWidget();
    void createResourceWidget();
    void createCompareWidget();

private:
    QWidget* center_widget;
    QVBoxLayout* main_container;
    QWidget* title_widget;

    map<QString, QFrame*> contents;
};

#endif // MAINWINDOW_H
