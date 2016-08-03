#ifndef DESCRIPTIONLABEL_H
#define DESCRIPTIONLABEL_H

#include <QLabel>


class descriptionlabel : public QLabel {
    Q_OBJECT

public:
    descriptionlabel();
    ~descriptionlabel();

protected:
    void setupDescription();
};

#endif // DESCRIPTIONLABEL_H
