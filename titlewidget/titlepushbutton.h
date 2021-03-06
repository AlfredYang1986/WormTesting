#ifndef TITLEPUSHBUTTON_H
#define TITLEPUSHBUTTON_H

#include <QObject>
#include <QPushButton>

class QVBoxLayout;
class QLabel;

class titlepushbutton : public QPushButton {
    Q_OBJECT
public:
    titlepushbutton(const QString& img, const QString& title);
    ~titlepushbutton();

    void setUpSubviews();
    virtual QSize sizeHint() const;

    const QString& getBtnTitle() const;

signals:
    void didSelectTitle(const QString& title);

private slots:
    void btnClicked();

private:
    QPixmap button_img;
    QString button_title;

    QVBoxLayout* main_layout;
    QLabel* img_label;
    QLabel* title_label;
};

#endif // TITLEPUSHBUTTON_H
