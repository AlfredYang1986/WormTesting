#ifndef TITLEWIDGET_H
#define TITLEWIDGET_H

#include <QWidget>
#include <vector>
using std::vector;

class QHBoxLayout;
class titlepushbutton;
class QSpacerItem;

class titlewidget : public QWidget {
public:
    titlewidget();
    ~titlewidget();

    void setUpSubViews();
    virtual QSize sizeHint() const;

private:
    QHBoxLayout* main_layout;
    vector<titlepushbutton*> menu_lst;
    QSpacerItem* right_item;
};

#endif // TITLEWIDGET_H
