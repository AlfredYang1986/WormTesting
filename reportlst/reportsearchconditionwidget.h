#ifndef REPORTSEARCHCONDITIONWIDGET_H
#define REPORTSEARCHCONDITIONWIDGET_H

#include <QFrame>
#include <QJsonObject>

class QVBoxLayout;
class QFormLayout;
class QGroupBox;
class QComboBox;
class QLineEdit;

class reportsearchconditionwidget : public QFrame {
    Q_OBJECT

Q_SIGNALS:
    void sampleConditionSearchSuccessSignal(const QJsonArray&);

protected Q_SLOTS:
    void queryWormCatSuccess(const QJsonObject&);
    void searchBtnClicked();
    void sampleConditionSearchSuccess(const QJsonArray&);

protected:
    virtual void showEvent(QShowEvent *);
    virtual void hideEvent(QHideEvent *);

private:
    QVBoxLayout* main_layout;
    QGroupBox* gb;

    QComboBox* time_box;
    QComboBox* testing_doctor_box;
    QComboBox* doctor_box;
    QComboBox* worm_box;

    QLineEdit* sample_id_edit;
    QLineEdit* patient_id_edit;
    QLineEdit* patient_name_edit;
    QLineEdit* patient_age_edit;
    QLineEdit* patient_section_edit;

    void pushConditions(QJsonObject&);

public:
    reportsearchconditionwidget();
    ~reportsearchconditionwidget();

    virtual QSize sizeHint() const;
    void setUpSubviews();
};

#endif // REPORTSEARCHCONDITIONWIDGET_H
