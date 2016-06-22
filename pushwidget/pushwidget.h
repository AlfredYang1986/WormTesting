#ifndef PUSHWIDGET_H
#define PUSHWIDGET_H

#include <QFrame>

class QVBoxLayout;
class QLineEdit;
class QComboBox;

class pushwidget : public QFrame {
    Q_OBJECT

Q_SIGNALS:

protected Q_SLOTS:
    void sampleBtnClick();
    void sampleCancelBtnClick();
    void patientBtnClick();
    void patientCancelBtnClick();

    void pushPatientSuccess(const QJsonObject& patient);
    void pushSampleSuccess(const QJsonObject& Sample);

private:
    QVBoxLayout* main_layout;

    QLineEdit* sample_id_edit;
    QLineEdit* sample_resource_edit;
    QLineEdit* sample_patient_id_edit;

    QLineEdit* patient_id_edit;
    QLineEdit* patient_name_edit;
//    QLineEdit* patient_gender_edit;
    QComboBox *patient_gender_box;
    QLineEdit* patient_age_edit;

public:
    pushwidget();
    ~pushwidget();

    void setUpSubviews();

protected:
    virtual QSize sizeHint() const;
};

#endif // PUSHWIDGET_H
