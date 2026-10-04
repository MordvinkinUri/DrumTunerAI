/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.10.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout;
    QGroupBox *controlGroup;
    QVBoxLayout *verticalLayout;
    QLabel *labelDrummer;
    QComboBox *drummerCombo;
    QLabel *labelDrum;
    QComboBox *drumCombo;
    QLabel *labelPlastic;
    QComboBox *plasticCombo;
    QLabel *labelDuration;
    QComboBox *durationCombo;
    QLabel *targetLabel;
    QLabel *infoLabel;
    QPushButton *recordButton;
    QPushButton *readyButton;
    QLabel *statusLabel;
    QHBoxLayout *buttonLayout;
    QPushButton *calibrateButton;
    QPushButton *statsButton;
    QPushButton *exportButton;
    QPushButton *dimensionsButton;
    QGroupBox *resultGroup;
    QVBoxLayout *verticalLayout_2;
    QLabel *detectedLabel;
    QLabel *resultLabel;
    QLabel *spectrumLabel;
    QLabel *schemeLabel;
    QLabel *plasticInfoLabel;
    QTextEdit *logTextEdit;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1200, 900);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        horizontalLayout = new QHBoxLayout(centralwidget);
        horizontalLayout->setObjectName("horizontalLayout");
        controlGroup = new QGroupBox(centralwidget);
        controlGroup->setObjectName("controlGroup");
        verticalLayout = new QVBoxLayout(controlGroup);
        verticalLayout->setObjectName("verticalLayout");
        labelDrummer = new QLabel(controlGroup);
        labelDrummer->setObjectName("labelDrummer");

        verticalLayout->addWidget(labelDrummer);

        drummerCombo = new QComboBox(controlGroup);
        drummerCombo->setObjectName("drummerCombo");

        verticalLayout->addWidget(drummerCombo);

        labelDrum = new QLabel(controlGroup);
        labelDrum->setObjectName("labelDrum");

        verticalLayout->addWidget(labelDrum);

        drumCombo = new QComboBox(controlGroup);
        drumCombo->setObjectName("drumCombo");

        verticalLayout->addWidget(drumCombo);

        labelPlastic = new QLabel(controlGroup);
        labelPlastic->setObjectName("labelPlastic");

        verticalLayout->addWidget(labelPlastic);

        plasticCombo = new QComboBox(controlGroup);
        plasticCombo->setObjectName("plasticCombo");

        verticalLayout->addWidget(plasticCombo);

        labelDuration = new QLabel(controlGroup);
        labelDuration->setObjectName("labelDuration");

        verticalLayout->addWidget(labelDuration);

        durationCombo = new QComboBox(controlGroup);
        durationCombo->setObjectName("durationCombo");

        verticalLayout->addWidget(durationCombo);

        targetLabel = new QLabel(controlGroup);
        targetLabel->setObjectName("targetLabel");

        verticalLayout->addWidget(targetLabel);

        infoLabel = new QLabel(controlGroup);
        infoLabel->setObjectName("infoLabel");
        infoLabel->setWordWrap(true);

        verticalLayout->addWidget(infoLabel);

        recordButton = new QPushButton(controlGroup);
        recordButton->setObjectName("recordButton");

        verticalLayout->addWidget(recordButton);

        readyButton = new QPushButton(controlGroup);
        readyButton->setObjectName("readyButton");

        verticalLayout->addWidget(readyButton);

        statusLabel = new QLabel(controlGroup);
        statusLabel->setObjectName("statusLabel");

        verticalLayout->addWidget(statusLabel);

        buttonLayout = new QHBoxLayout();
        buttonLayout->setObjectName("buttonLayout");
        calibrateButton = new QPushButton(controlGroup);
        calibrateButton->setObjectName("calibrateButton");

        buttonLayout->addWidget(calibrateButton);

        statsButton = new QPushButton(controlGroup);
        statsButton->setObjectName("statsButton");

        buttonLayout->addWidget(statsButton);

        exportButton = new QPushButton(controlGroup);
        exportButton->setObjectName("exportButton");

        buttonLayout->addWidget(exportButton);

        dimensionsButton = new QPushButton(controlGroup);
        dimensionsButton->setObjectName("dimensionsButton");

        buttonLayout->addWidget(dimensionsButton);


        verticalLayout->addLayout(buttonLayout);


        horizontalLayout->addWidget(controlGroup);

        resultGroup = new QGroupBox(centralwidget);
        resultGroup->setObjectName("resultGroup");
        verticalLayout_2 = new QVBoxLayout(resultGroup);
        verticalLayout_2->setObjectName("verticalLayout_2");
        detectedLabel = new QLabel(resultGroup);
        detectedLabel->setObjectName("detectedLabel");

        verticalLayout_2->addWidget(detectedLabel);

        resultLabel = new QLabel(resultGroup);
        resultLabel->setObjectName("resultLabel");
        resultLabel->setWordWrap(true);

        verticalLayout_2->addWidget(resultLabel);

        spectrumLabel = new QLabel(resultGroup);
        spectrumLabel->setObjectName("spectrumLabel");
        spectrumLabel->setMinimumSize(QSize(0, 150));

        verticalLayout_2->addWidget(spectrumLabel);

        schemeLabel = new QLabel(resultGroup);
        schemeLabel->setObjectName("schemeLabel");
        schemeLabel->setMinimumSize(QSize(450, 450));

        verticalLayout_2->addWidget(schemeLabel);

        plasticInfoLabel = new QLabel(resultGroup);
        plasticInfoLabel->setObjectName("plasticInfoLabel");
        plasticInfoLabel->setMinimumSize(QSize(0, 120));
        plasticInfoLabel->setWordWrap(true);

        verticalLayout_2->addWidget(plasticInfoLabel);

        logTextEdit = new QTextEdit(resultGroup);
        logTextEdit->setObjectName("logTextEdit");
        logTextEdit->setMinimumSize(QSize(0, 150));
        logTextEdit->setReadOnly(true);

        verticalLayout_2->addWidget(logTextEdit);


        horizontalLayout->addWidget(resultGroup);

        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Drum Tuner AI", nullptr));
        controlGroup->setTitle(QCoreApplication::translate("MainWindow", "Settings", nullptr));
        labelDrummer->setText(QCoreApplication::translate("MainWindow", "Legendary Drummer:", nullptr));
        labelDrum->setText(QCoreApplication::translate("MainWindow", "Drum:", nullptr));
        labelPlastic->setText(QCoreApplication::translate("MainWindow", "Plastic Type:", nullptr));
        labelDuration->setText(QCoreApplication::translate("MainWindow", "Record Duration:", nullptr));
        targetLabel->setText(QCoreApplication::translate("MainWindow", "Target: ---", nullptr));
        infoLabel->setText(QCoreApplication::translate("MainWindow", "Select drummer", nullptr));
        recordButton->setText(QCoreApplication::translate("MainWindow", "RECORD", nullptr));
        readyButton->setText(QCoreApplication::translate("MainWindow", "\342\232\240\357\270\217 NOT READY", nullptr));
        statusLabel->setText(QCoreApplication::translate("MainWindow", "Ready", nullptr));
        calibrateButton->setText(QCoreApplication::translate("MainWindow", "Calibrate", nullptr));
        statsButton->setText(QCoreApplication::translate("MainWindow", "Statistics", nullptr));
        exportButton->setText(QCoreApplication::translate("MainWindow", "Export", nullptr));
        dimensionsButton->setText(QCoreApplication::translate("MainWindow", "Dimensions", nullptr));
        resultGroup->setTitle(QCoreApplication::translate("MainWindow", "Result", nullptr));
        detectedLabel->setText(QCoreApplication::translate("MainWindow", "Detected: ---", nullptr));
        resultLabel->setText(QCoreApplication::translate("MainWindow", "---", nullptr));
        spectrumLabel->setText(QCoreApplication::translate("MainWindow", "Spectrum", nullptr));
        schemeLabel->setText(QCoreApplication::translate("MainWindow", "Drum scheme", nullptr));
        plasticInfoLabel->setText(QCoreApplication::translate("MainWindow", "Plastic info", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
