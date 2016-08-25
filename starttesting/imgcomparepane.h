#ifndef IMGCOMPAREPANE_H
#define IMGCOMPAREPANE_H

#include <QFrame>

class QVBoxLayout;
class QLabel;
class QComboBox;
class QPushButton;

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
    void startTesting(bool bTesting);

    int currentCameraIndex() const;
protected:
    void setUpSubviews();

private:
    QVBoxLayout* main_layout;
    QLabel* photo_preview;

    QComboBox* box;
    QPushButton* title_take_photo;
};

#endif // IMGCOMPAREPANE_H
