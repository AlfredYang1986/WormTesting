#ifndef TITLEWIDGET_H
#define TITLEWIDGET_H

#include <QWidget>
#include <QFrame>
#include <vector>
using std::vector;

class QHBoxLayout;
class titlepushbutton;
class QSpacerItem;

class titlewidget : public QFrame {
    Q_OBJECT

public:
    titlewidget();
    ~titlewidget();

    void setUpSubViews();
    virtual QSize sizeHint() const;

    void changeCurrentIndex(int index);
private:
    QHBoxLayout* main_layout;
    vector<titlepushbutton*> menu_lst;
    QSpacerItem* right_item;

signals:
    void changeContentPane(const QString& title);

public slots:
    void menu_btn_cleck(const QString& title);
};

#endif // TITLEWIDGET_H
