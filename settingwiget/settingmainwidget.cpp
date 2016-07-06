#include "settingmainwidget.h"
#include <QVBoxLayout>
#include <QPushButton>
#include "reportingdialog.h"
#include "addsampleresourcedialog.h"
#include "deletesampleresourcedialog.h"
#include "addpatienttypedialog.h"
#include "deletepatienttypedialog.h"
#include "updatewormdesdialog.h"
#include "uploadwormimgdialog.h"

settingmainwidget::settingmainwidget() {
    this->setUpSubviews();
}

settingmainwidget::~settingmainwidget() {
    main_layout->deleteLater();
}

QSize settingmainwidget::sizeHint() const {
    return QSize(300, 300);
}

void settingmainwidget::setUpSubviews() {
    main_layout = new QVBoxLayout;

    {
        QPushButton* btn = new QPushButton("修改报告项目");
        btn->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        QObject::connect(btn, SIGNAL(released()), this, SLOT(showReportingSettingDialog()));
        main_layout->addWidget(btn);
    }

    QHBoxLayout* resource = new QHBoxLayout;
    {
        QPushButton* btn = new QPushButton("添加样本来源");
        btn->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        QObject::connect(btn, SIGNAL(released()), this, SLOT(showAddSampleTypeDialog()));
        resource->addWidget(btn);
    }

    {
        QPushButton* btn = new QPushButton("删除样本来源");
        btn->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        QObject::connect(btn, SIGNAL(released()), this, SLOT(showdeleteSampleTypeDialog()));
        resource->addWidget(btn);
    }
    resource->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum));
    main_layout->addLayout(resource);

    QHBoxLayout* patient = new QHBoxLayout;
    {
        QPushButton* btn = new QPushButton("添加病人来源");
        btn->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        QObject::connect(btn, SIGNAL(released()), this, SLOT(showAddPatientTypeDialog()));
        patient->addWidget(btn);
    }

    {
        QPushButton* btn = new QPushButton("删除病人来源");
        btn->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        QObject::connect(btn, SIGNAL(released()), this, SLOT(showdeletePatientTypeDialog()));
        patient->addWidget(btn);
    }
    patient->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum));
    main_layout->addLayout(patient);

    QHBoxLayout* sample = new QHBoxLayout;
    {
        QPushButton* btn = new QPushButton("添加图片样本描述");
        btn->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        QObject::connect(btn, SIGNAL(released()), this, SLOT(showUpdateWormDescriptionDialog()));
        sample->addWidget(btn);
    }

    {
        QPushButton* btn = new QPushButton("添加样本图片");
        btn->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        QObject::connect(btn, SIGNAL(released()), this, SLOT(showAddWormImgDialog()));
        sample->addWidget(btn);
    }

    {
        QPushButton* btn = new QPushButton("删除样本图片");
        btn->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        QObject::connect(btn, SIGNAL(released()), this, SLOT(showdeletePatientTypeDialog()));
        sample->addWidget(btn);
    }
    sample->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum));
    main_layout->addLayout(sample);

    main_layout->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Minimum, QSizePolicy::Expanding));
    this->setLayout(main_layout);

    this->setStyleSheet("QPushButton {"
                            "width: 100px;"
                            "height: 30px;"
                            "color: white;"
                            "font-size: 14px;"
                            "background-color: #1bd7ff;"
                            "border: 1px solid #1bd7ff;"
                        "}");
}

void settingmainwidget::showReportingSettingDialog() {
    reportingdialog* dlg = new reportingdialog;
    dlg->exec();
}

void settingmainwidget::showAddSampleTypeDialog() {
    addsampleresourcedialog* dlg = new addsampleresourcedialog;
    dlg->exec();
}

void settingmainwidget::showdeleteSampleTypeDialog() {
    deletesampleresourcedialog* dlg = new deletesampleresourcedialog;
    dlg->exec();
}

void settingmainwidget::showAddPatientTypeDialog() {
    addpatienttypedialog* dlg = new addpatienttypedialog;
    dlg->exec();
}

void settingmainwidget::showdeletePatientTypeDialog() {
    deletepatienttypedialog* dlg = new deletepatienttypedialog;
    dlg->exec();
}

void settingmainwidget::showUpdateWormDescriptionDialog() {
    updatewormdesdialog* dlg = new updatewormdesdialog;
    dlg->exec();
}

void settingmainwidget::showAddWormImgDialog() {
    uploadwormimgdialog* dlg = new uploadwormimgdialog;
    dlg->exec();
}

void settingmainwidget::showDeleteWormImgDialog() {

}
