#ifndef IMGCOMPAREPANE_H
#define IMGCOMPAREPANE_H

#include <QFrame>

class QVBoxLayout;
class QLabel;
class QComboBox;

class imgcomparepane : public QFrame {
    Q_OBJECT

Q_SIGNALS:
    void takeImageSuccess(const QImage&);

protected Q_SLOTS:
    void imageStream(const QImage&);
    void takeImage();
    void changeCurrentCamera(int);

public:
    imgcomparepane();
    ~imgcomparepane();

    virtual QSize sizeHint() const;

    void clearPane();
    int getCurrentCameraIndex() const;
protected:
    void setUpSubviews();

private:
    QVBoxLayout* main_layout;
    QLabel* photo_preview;

    QComboBox* box;
};

#endif // IMGCOMPAREPANE_H
