#ifndef DETAILPANE_H
#define DETAILPANE_H

#include <QFrame>
#include <vector>
using std::vector;

class QHBoxLayout;

class detailpane : public QFrame {
    Q_OBJECT

public:
    detailpane(const vector<QString>& vec);
    ~detailpane();

//    virtual QSize sizeHint() const;

protected:
    void setUpSubviews();

private:
    QHBoxLayout* main_layout;

    vector<QString> _vec;
};

#endif // DETAILPANE_H
