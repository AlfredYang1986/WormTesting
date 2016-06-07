#ifndef WORMTREEWIDGET_H
#define WORMTREEWIDGET_H

#include <QFrame>
#include <QTreeWidget>

class wormtreewidget : public QTreeWidget {
    Q_OBJECT

public:
    wormtreewidget();
    ~wormtreewidget();

    virtual QSize sizeHint() const;
protected:
    void setUpSubviews();

private:
};

#endif // WORMTREEWIDGET_H
