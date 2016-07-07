#ifndef SAMPLEDETAILWIDGET_H
#define SAMPLEDETAILWIDGET_H

#include <QFrame>

class QLineEdit;
class QComboBox;
class QFormLayout;

class sampledetailwidget : public QFrame {
    Q_OBJECT

Q_SIGNALS:
    void didFinishEditPatientID(const QString&);
    void didFinishEditSampleID(const QString&);

protected Q_SLOTS:
    void didFinishEditPatientID_slot();
    void didFinishEditSampleID_slot();

    void sampleBtnClick();
    void sampleCancelBtnClick();

    void queryPatientTypeSuccess(const QJsonArray&);
    void querySampleResourceTypeSuccess(const QJsonArray&);

public:
    sampledetailwidget();
    ~sampledetailwidget();

    void setUpSubviews();

    virtual QSize sizeHint() const;

    void queryPatientSuccess(const QJsonObject& patitent);
    void querySampleSuccess(const QJsonObject& sample);

    QString queryCurrentSampleId() const;
private:
    QLineEdit* sample_id_edit;
    QComboBox* sample_resource_box;
    QLineEdit* sample_index_edit;
    QLineEdit* sample_section_edit;
    QLineEdit* sample_query_doctor_edit;
    QLineEdit* sample_pre_test_doctor_edit;
    QLineEdit* sample_testing_doctor_edit;
    QLineEdit* sample_post_test_doctor_edit;
    QLineEdit* sample_start_date_edit;
    QLineEdit* sample_end_date_edit;
    QLineEdit* sample_pre_test_date_edit;
    QLineEdit* sample_testing_date_edit;
    QLineEdit* sample_reporting_date_edit;

    QLineEdit* patient_id_edit;
    QLineEdit* patient_name_edit;
    QComboBox* patient_gender_box;
    QComboBox* patient_type;
    QLineEdit* patient_age_edit;
    QLineEdit* patient_section_edit;
    QLineEdit* patient_section_id_edit;
    QLineEdit* patient_section_bed_id_edit;

    QFormLayout* main_layout;
};

#endif // SAMPLEDETAILWIDGET_H
