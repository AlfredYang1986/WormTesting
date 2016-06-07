#ifndef SEARCHRESULTTABLEWIDGET_H
#define SEARCHRESULTTABLEWIDGET_H

#include <QTableWidget>

class searchresulttablewidget : public QTableWidget {
public:
    searchresulttablewidget();
    ~searchresulttablewidget();

protected:
    void setUpSubviews();
};

#endif // SEARCHRESULTTABLEWIDGET_H
