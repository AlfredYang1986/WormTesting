#ifndef SETTINGMAINWIDGET_H
#define SETTINGMAINWIDGET_H

#include <QFrame>
class QVBoxLayout;

class settingmainwidget : public QFrame {
    Q_OBJECT

protected Q_SLOTS:
    void showReportingSettingDialog();

private:
    QVBoxLayout* main_layout;

public:
    settingmainwidget();
    ~settingmainwidget();

    virtual QSize sizeHint() const;
    void setUpSubviews();
};

#endif // SETTINGMAINWIDGET_H
