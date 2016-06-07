#ifndef SEARCHTREEWIDGET_H
#define SEARCHTREEWIDGET_H

#include <QFrame>
#include <QTreeWidget>

class searchtreewidget : public QTreeWidget {
    Q_OBJECT

public:
    searchtreewidget();
    ~searchtreewidget();

    virtual QSize sizeHint() const;
protected:
    void setUpSubviews();

private:
};

#endif // SEARCHTREEWIDGET_H
