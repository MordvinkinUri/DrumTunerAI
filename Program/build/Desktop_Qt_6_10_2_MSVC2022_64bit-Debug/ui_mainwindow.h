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
    QLabel *labelSnareWire;
    QComboBox *snareWireCombo;
    QLabel *targetLabel;
    QLabel *infoLabel;
    QPushButton *recordButton;
    QPushButton *readyButton;
    QLabel *statusLabel;
    QPushButton *dimensionsButton;
    QPushButton *showBoltsButton;
    QLabel *labelSeparator1;
    QPushButton *calibrateButton;
    QPushButton *statsButton;
    QLabel *labelSeparator2;
    QPushButton *exportButton;
    QPushButton *importButton;
    QPushButton *settingsExportButton;
    QPushButton *settingsImportButton;
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
        MainWindow->resize(1350, 950);
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

        labelSnareWire = new QLabel(controlGroup);
        labelSnareWire->setObjectName("labelSnareWire");

        verticalLayout->addWidget(labelSnareWire);

        snareWireCombo = new QComboBox(controlGroup);
        snareWireCombo->setObjectName("snareWireCombo");

        verticalLayout->addWidget(snareWireCombo);

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

        dimensionsButton = new QPushButton(controlGroup);
        dimensionsButton->setObjectName("dimensionsButton");

        verticalLayout->addWidget(dimensionsButton);

        showBoltsButton = new QPushButton(controlGroup);
        showBoltsButton->setObjectName("showBoltsButton");

        verticalLayout->addWidget(showBoltsButton);

        labelSeparator1 = new QLabel(controlGroup);
        labelSeparator1->setObjectName("labelSeparator1");
        labelSeparator1->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(labelSeparator1);

        calibrateButton = new QPushButton(controlGroup);
        calibrateButton->setObjectName("calibrateButton");

        verticalLayout->addWidget(calibrateButton);

        statsButton = new QPushButton(controlGroup);
        statsButton->setObjectName("statsButton");

        verticalLayout->addWidget(statsButton);

        labelSeparator2 = new QLabel(controlGroup);
        labelSeparator2->setObjectName("labelSeparator2");
        labelSeparator2->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(labelSeparator2);

        exportButton = new QPushButton(controlGroup);
        exportButton->setObjectName("exportButton");

        verticalLayout->addWidget(exportButton);

        importButton = new QPushButton(controlGroup);
        importButton->setObjectName("importButton");

        verticalLayout->addWidget(importButton);

        settingsExportButton = new QPushButton(controlGroup);
        settingsExportButton->setObjectName("settingsExportButton");

        verticalLayout->addWidget(settingsExportButton);

        settingsImportButton = new QPushButton(controlGroup);
        settingsImportButton->setObjectName("settingsImportButton");

        verticalLayout->addWidget(settingsImportButton);


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
        schemeLabel->setMinimumSize(QSize(550, 550));

        verticalLayout_2->addWidget(schemeLabel);

        plasticInfoLabel = new QLabel(resultGroup);
        plasticInfoLabel->setObjectName("plasticInfoLabel");
        plasticInfoLabel->setMinimumSize(QSize(0, 100));
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
        controlGroup->setTitle(QCoreApplication::translate("MainWindow", "\342\232\231\357\270\217 \320\235\320\220\320\241\320\242\320\240\320\236\320\231\320\232\320\230", nullptr));
        labelDrummer->setText(QCoreApplication::translate("MainWindow", "\360\237\245\201 \320\233\320\265\320\263\320\265\320\275\320\264\320\260\321\200\320\275\321\213\320\271 \320\261\320\260\321\200\320\260\320\261\320\260\320\275\321\211\320\270\320\272:", nullptr));
        labelDrum->setText(QCoreApplication::translate("MainWindow", "\360\237\216\247 \320\221\320\260\321\200\320\260\320\261\320\260\320\275:", nullptr));
        labelPlastic->setText(QCoreApplication::translate("MainWindow", "\360\237\216\232\357\270\217 \320\242\320\270\320\277 \320\277\320\273\320\260\321\201\321\202\320\270\320\272\320\260:", nullptr));
        labelDuration->setText(QCoreApplication::translate("MainWindow", "\342\217\261\357\270\217 \320\224\320\273\320\270\321\202\320\265\320\273\321\214\320\275\320\276\321\201\321\202\321\214 \320\267\320\260\320\277\320\270\321\201\320\270:", nullptr));
        labelSnareWire->setText(QCoreApplication::translate("MainWindow", "\360\237\224\230 \320\237\320\276\320\264\321\201\321\202\321\200\321\203\320\275\320\275\320\270\320\272:", nullptr));
        targetLabel->setText(QCoreApplication::translate("MainWindow", "\360\237\216\257 \320\246\320\265\320\273\321\214: ---", nullptr));
        targetLabel->setStyleSheet(QCoreApplication::translate("MainWindow", "font-weight: bold; color: #FFD700;", nullptr));
        infoLabel->setText(QCoreApplication::translate("MainWindow", "\320\222\321\213\320\261\320\265\321\200\320\270\321\202\320\265 \320\261\320\260\321\200\320\260\320\261\320\260\320\275\321\211\320\270\320\272\320\260", nullptr));
        recordButton->setText(QCoreApplication::translate("MainWindow", "\360\237\216\244 \320\227\320\220\320\237\320\230\320\241\320\220\320\242\320\254", nullptr));
        recordButton->setStyleSheet(QCoreApplication::translate("MainWindow", "background-color: #4CAF50; color: white; font-weight: bold; padding: 10px; font-size: 14px; border-radius: 5px;", nullptr));
        readyButton->setText(QCoreApplication::translate("MainWindow", "\342\232\240\357\270\217 \320\235\320\225 \320\223\320\236\320\242\320\236\320\222\320\236", nullptr));
        readyButton->setStyleSheet(QCoreApplication::translate("MainWindow", "background-color: #f44336; color: white; font-weight: bold; padding: 10px; font-size: 14px; border-radius: 5px;", nullptr));
        statusLabel->setText(QCoreApplication::translate("MainWindow", "\320\223\320\276\321\202\320\276\320\262", nullptr));
        statusLabel->setStyleSheet(QCoreApplication::translate("MainWindow", "color: #888888;", nullptr));
        dimensionsButton->setText(QCoreApplication::translate("MainWindow", "\360\237\223\217 \320\240\320\260\320\267\320\274\320\265\321\200\321\213 \320\261\320\260\321\200\320\260\320\261\320\260\320\275\320\276\320\262", nullptr));
        dimensionsButton->setStyleSheet(QCoreApplication::translate("MainWindow", "background-color: #2196F3; color: white; font-weight: bold; padding: 8px; border-radius: 5px;", nullptr));
        showBoltsButton->setText(QCoreApplication::translate("MainWindow", "\360\237\224\247 \320\241\321\205\320\265\320\274\320\260 \320\261\320\276\320\273\321\202\320\276\320\262", nullptr));
        showBoltsButton->setStyleSheet(QCoreApplication::translate("MainWindow", "background-color: #9C27B0; color: white; font-weight: bold; padding: 8px; border-radius: 5px;", nullptr));
        labelSeparator1->setText(QCoreApplication::translate("MainWindow", "\342\224\201\342\224\201\342\224\201\342\224\201\342\224\201\342\224\201\342\224\201\342\224\201\342\224\201\342\224\201\342\224\201\342\224\201\342\224\201\342\224\201\342\224\201\342\224\201\342\224\201\342\224\201\342\224\201\342\224\201\342\224\201", nullptr));
        calibrateButton->setText(QCoreApplication::translate("MainWindow", "\360\237\224\247 \320\232\320\260\320\273\320\270\320\261\321\200\320\276\320\262\320\272\320\260 \320\274\320\270\320\272\321\200\320\276\321\204\320\276\320\275\320\260", nullptr));
        calibrateButton->setStyleSheet(QCoreApplication::translate("MainWindow", "background-color: #FF9800; color: white; font-weight: bold; padding: 8px; border-radius: 5px;", nullptr));
        statsButton->setText(QCoreApplication::translate("MainWindow", "\360\237\223\212 \320\237\320\276\320\272\320\260\320\267\320\260\321\202\321\214 \321\201\321\202\320\260\321\202\320\270\321\201\321\202\320\270\320\272\321\203", nullptr));
        statsButton->setStyleSheet(QCoreApplication::translate("MainWindow", "background-color: #607D8B; color: white; font-weight: bold; padding: 8px; border-radius: 5px;", nullptr));
        labelSeparator2->setText(QCoreApplication::translate("MainWindow", "\342\224\201\342\224\201\342\224\201\342\224\201\342\224\201\342\224\201\342\224\201\342\224\201\342\224\201\342\224\201\342\224\201\342\224\201\342\224\201\342\224\201\342\224\201\342\224\201\342\224\201\342\224\201\342\224\201\342\224\201\342\224\201", nullptr));
        exportButton->setText(QCoreApplication::translate("MainWindow", "\360\237\222\276 \320\255\320\272\321\201\320\277\320\276\321\200\321\202 \320\264\320\260\320\275\320\275\321\213\321\205 \320\276\320\261\321\203\321\207\320\265\320\275\320\270\321\217", nullptr));
        exportButton->setStyleSheet(QCoreApplication::translate("MainWindow", "background-color: #3F51B5; color: white; font-weight: bold; padding: 8px; border-radius: 5px;", nullptr));
        importButton->setText(QCoreApplication::translate("MainWindow", "\360\237\223\202 \320\230\320\274\320\277\320\276\321\200\321\202 \320\264\320\260\320\275\320\275\321\213\321\205 \320\276\320\261\321\203\321\207\320\265\320\275\320\270\321\217", nullptr));
        importButton->setStyleSheet(QCoreApplication::translate("MainWindow", "background-color: #3F51B5; color: white; font-weight: bold; padding: 8px; border-radius: 5px;", nullptr));
        settingsExportButton->setText(QCoreApplication::translate("MainWindow", "\360\237\222\276 \320\255\320\272\321\201\320\277\320\276\321\200\321\202 \320\275\320\260\321\201\321\202\321\200\320\276\320\265\320\272", nullptr));
        settingsExportButton->setStyleSheet(QCoreApplication::translate("MainWindow", "background-color: #009688; color: white; font-weight: bold; padding: 8px; border-radius: 5px;", nullptr));
        settingsImportButton->setText(QCoreApplication::translate("MainWindow", "\360\237\223\202 \320\230\320\274\320\277\320\276\321\200\321\202 \320\275\320\260\321\201\321\202\321\200\320\276\320\265\320\272", nullptr));
        settingsImportButton->setStyleSheet(QCoreApplication::translate("MainWindow", "background-color: #009688; color: white; font-weight: bold; padding: 8px; border-radius: 5px;", nullptr));
        resultGroup->setTitle(QCoreApplication::translate("MainWindow", "\360\237\247\240 \320\240\320\225\320\227\320\243\320\233\320\254\320\242\320\220\320\242 \320\220\320\235\320\220\320\233\320\230\320\227\320\220", nullptr));
        detectedLabel->setText(QCoreApplication::translate("MainWindow", "\360\237\216\265 \320\236\320\261\320\275\320\260\321\200\321\203\320\266\320\265\320\275\320\276: ---", nullptr));
        detectedLabel->setStyleSheet(QCoreApplication::translate("MainWindow", "font-size: 24px; font-weight: bold; color: #FFD700;", nullptr));
        resultLabel->setText(QCoreApplication::translate("MainWindow", "---", nullptr));
        resultLabel->setStyleSheet(QCoreApplication::translate("MainWindow", "font-size: 12px; color: #CCCCCC;", nullptr));
        spectrumLabel->setText(QCoreApplication::translate("MainWindow", "\320\241\320\277\320\265\320\272\321\202\321\200", nullptr));
        spectrumLabel->setStyleSheet(QCoreApplication::translate("MainWindow", "background-color: black; border-radius: 5px;", nullptr));
        schemeLabel->setText(QCoreApplication::translate("MainWindow", "\320\241\321\205\320\265\320\274\320\260 \320\261\320\260\321\200\320\260\320\261\320\260\320\275\320\260", nullptr));
        schemeLabel->setStyleSheet(QCoreApplication::translate("MainWindow", "background-color: #2D2D2D; border-radius: 10px;", nullptr));
        plasticInfoLabel->setText(QCoreApplication::translate("MainWindow", "\320\230\320\275\321\204\320\276\321\200\320\274\320\260\321\206\320\270\321\217 \320\276 \320\277\320\273\320\260\321\201\321\202\320\270\320\272\320\265", nullptr));
        plasticInfoLabel->setStyleSheet(QCoreApplication::translate("MainWindow", "background-color: #2D2D2D; border-radius: 8px; padding: 10px;", nullptr));
        logTextEdit->setStyleSheet(QCoreApplication::translate("MainWindow", "background-color: #1E1E1E; color: #00FF00; font-family: monospace; border-radius: 5px;", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
