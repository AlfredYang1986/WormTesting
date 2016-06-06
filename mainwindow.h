#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTabWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void setUpSubviews();

private:
    QWidget* center_widget;
    QVBoxLayout* main_container;
    QWidget* title_widget;
    QWidget* content_widget;
};

#endif // MAINWINDOW_H
