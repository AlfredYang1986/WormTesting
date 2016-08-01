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
#include "addusersdialog.h"
#include "deleteusersdialog.h"
#include <QBitmap>
#include "sampleresource/resourceproxy/resourceproxy.h"
#include "sampleresource/resourceproxy/resourceimportdialog.h"
#include <QMessageBox>

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
        QPushButton* btn = new QPushButton;
        btn->setFixedSize(120, 120);
        btn->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        btn->clearMask();
        btn->setBackgroundRole(QPalette::Base);
        QPixmap m;
        m.load(":resource/setting_report_section.png");
        btn->setIcon(m);
        btn->setIconSize(QSize(120, 120));
        QObject::connect(btn, SIGNAL(released()), this, SLOT(showReportingSettingDialog()));
        main_layout->addWidget(btn);
    }

    QHBoxLayout* resource = new QHBoxLayout;
    {
        QPushButton* btn = new QPushButton;
        btn->setFixedSize(120, 120);
        btn->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        btn->clearMask();
        btn->setBackgroundRole(QPalette::Base);
        QPixmap m;
        m.load(":resource/setting_resource_add.png");
        btn->setIcon(m);
        btn->setIconSize(QSize(120, 120));
        QObject::connect(btn, SIGNAL(released()), this, SLOT(showAddSampleTypeDialog()));
        resource->addWidget(btn);
    }

    {
        QPushButton* btn = new QPushButton;
        btn->setFixedSize(120, 120);
        btn->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        btn->clearMask();
        btn->setBackgroundRole(QPalette::Base);
        QPixmap m;
        m.load(":resource/setting_resource_delete.png");
        btn->setIcon(m);
        btn->setIconSize(QSize(120, 120));
        QObject::connect(btn, SIGNAL(released()), this, SLOT(showdeleteSampleTypeDialog()));
        resource->addWidget(btn);
    }
    resource->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum));
    main_layout->addLayout(resource);

    QHBoxLayout* patient = new QHBoxLayout;
    {
        QPushButton* btn = new QPushButton;
        btn->setFixedSize(120, 120);
        btn->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        btn->clearMask();
        btn->setBackgroundRole(QPalette::Base);
        QPixmap m;
        m.load(":resource/setting_patient_add.png");
        btn->setIcon(m);
        btn->setIconSize(QSize(120, 120));
        QObject::connect(btn, SIGNAL(released()), this, SLOT(showAddPatientTypeDialog()));
        patient->addWidget(btn);
    }

    {
        QPushButton* btn = new QPushButton;
        btn->setFixedSize(120, 120);
        btn->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        btn->clearMask();
        btn->setBackgroundRole(QPalette::Base);
        QPixmap m;
        m.load(":resource/setting_patient_delete.png");
        btn->setIcon(m);
        btn->setIconSize(QSize(120, 120));
        QObject::connect(btn, SIGNAL(released()), this, SLOT(showdeletePatientTypeDialog()));
        patient->addWidget(btn);
    }
    patient->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum));
    main_layout->addLayout(patient);

    QHBoxLayout* sample = new QHBoxLayout;
    {
        QPushButton* btn = new QPushButton;
        btn->setFixedSize(120, 120);
        btn->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        btn->clearMask();
        btn->setBackgroundRole(QPalette::Base);
        QPixmap m;
        m.load(":resource/setting_description_add.png");
        btn->setIcon(m);
        btn->setIconSize(QSize(120, 120));
        QObject::connect(btn, SIGNAL(released()), this, SLOT(showUpdateWormDescriptionDialog()));
        sample->addWidget(btn);
    }

    {
        QPushButton* btn = new QPushButton;
        btn->setFixedSize(120, 120);
        btn->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        btn->clearMask();
        btn->setBackgroundRole(QPalette::Base);
        QPixmap m;
        m.load(":resource/setting_pic_add.png");
        btn->setIcon(m);
        btn->setIconSize(QSize(120, 120));
        QObject::connect(btn, SIGNAL(released()), this, SLOT(showAddWormImgDialog()));
        sample->addWidget(btn);
    }

    {
        //QPushButton* btn = new QPushButton;
        //btn->setFixedSize(120, 120);
        //btn->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        //btn->clearMask();
        //btn->setBackgroundRole(QPalette::Base);
        //QPixmap m;
        //m.load(":resource/setting_pic_delete.png");
        //btn->setIcon(m);
        //btn->setIconSize(QSize(120, 120));
        //QObject::connect(btn, SIGNAL(released()), this, SLOT(showdeletePatientTypeDialog()));
        //sample->addWidget(btn);
    }
    sample->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum));
    main_layout->addLayout(sample);

    QHBoxLayout* users = new QHBoxLayout;
    {
        QPushButton* btn = new QPushButton;
        btn->setFixedSize(120, 120);
        btn->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        btn->clearMask();
        btn->setBackgroundRole(QPalette::Base);
        QPixmap m;
        m.load(":resource/setting_users_add.png");
        btn->setIcon(m);
        btn->setIconSize(QSize(120, 120));
        QObject::connect(btn, SIGNAL(released()), this, SLOT(showUserAddDialog()));
        users->addWidget(btn);
    }

    {
        QPushButton* btn = new QPushButton;
        btn->setFixedSize(120, 120);
        btn->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        btn->clearMask();
        btn->setBackgroundRole(QPalette::Base);
        QPixmap m;
        m.load(":resource/setting_users_delete.png");
        btn->setIcon(m);
        btn->setIconSize(QSize(120, 120));
        QObject::connect(btn, SIGNAL(released()), this, SLOT(showUserDeleteDialog()));
        users->addWidget(btn);
    }

    {
        QPushButton* btn = new QPushButton;
        btn->setFixedSize(120, 120);
        btn->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        btn->clearMask();
        btn->setBackgroundRole(QPalette::Base);
        QPixmap m;
        m.load(":resource/setting_print_config.png");
        btn->setIcon(m);
        btn->setIconSize(QSize(120, 120));
        QObject::connect(btn, SIGNAL(released()), this, SLOT(showdeletePatientTypeDialog()));
        users->addWidget(btn);
    }

    {
        QPushButton* btn = new QPushButton;
        btn->setFixedSize(120, 120);
        btn->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        btn->clearMask();
        btn->setBackgroundRole(QPalette::Base);
        QPixmap m;
        m.load(":resource/sample_resource.png");
        btn->setIcon(m);
        btn->setIconSize(QSize(120, 120));
        QObject::connect(btn, SIGNAL(released()), this, SLOT(startFetchResource()));
        users->addWidget(btn);
    }

    users->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum));
    main_layout->addLayout(users);

    main_layout->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Minimum, QSizePolicy::Expanding));
    this->setLayout(main_layout);

    this->setObjectName("setting_pane");
    this->setStyleSheet("QWidget#setting_pane {"
                            "border-image: url(:resource/setting_bkg.png);"
                            "background-repeat: none;"
                            "background-size: 100% 100%;"
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

void settingmainwidget::showUserAddDialog() {
    addusersdialog* dlg = new addusersdialog;
    dlg->exec();
}

void settingmainwidget::showUserDeleteDialog() {
    deleteusersdialog* dlg = new deleteusersdialog;
    dlg->exec();
}

void settingmainwidget::showPrintConfig() {

}

void settingmainwidget::startFetchResource() {
    resourceimportdialog* dlg = new resourceimportdialog;
    dlg->exec();
}
