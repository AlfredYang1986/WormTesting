#ifndef DECLEARATIONWIDGET_H
#define DECLEARATIONWIDGET_H

#include <QLabel>

class declearationwidget : public QLabel {
    Q_OBJECT

public:
    declearationwidget();
    ~declearationwidget();

protected:
    void setupDeclearation();
};

#endif // DECLEARATIONWIDGET_H
