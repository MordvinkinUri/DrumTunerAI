#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMediaDevices>
#include <QAudioSource>
#include <QMessageBox>
#include <QFileDialog>
#include <QDateTime>
#include <QDate>
#include <QTextStream>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QPainter>
#include <QDebug>
#include <random>
#include <cmath>

// ============================================================
// РЕАЛИЗАЦИЯ ОКНА БОЛТОВ
// ============================================================
BoltsViewDialog::BoltsViewDialog(QWidget *parent)
    : QDialog(parent)
    , m_wrongLug(-1)
    , m_needTighten(true)
    , m_detectedFreq(0)
    , m_targetFreq(0)
    , m_drumType(0)
    , m_plasticType(0)
    , m_snareWireOn(true)
{
    setWindowTitle("🔧 Схема болтов барабана");
    setFixedSize(600, 650);
    setStyleSheet("background-color: #1E1E1E;");
    setModal(false);
}

BoltsViewDialog::~BoltsViewDialog() {}

void BoltsViewDialog::setBoltsData(int wrongLug, bool needTighten, float detectedFreq, float targetFreq, int drumType, int plasticType, bool snareWireOn)
{
    m_wrongLug = wrongLug;
    m_needTighten = needTighten;
    m_detectedFreq = detectedFreq;
    m_targetFreq = targetFreq;
    m_drumType = drumType;
    m_plasticType = plasticType;
    m_snareWireOn = snareWireOn;
    update();
}

void BoltsViewDialog::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.fillRect(rect(), QColor(30, 30, 30));

    int w = width();
    int h = height();
    int cx = w / 2;
    int cy = h / 2 - 30;
    int radius = 180;

    // Заголовок
    painter.setPen(QPen(Qt::white, 2));
    painter.setFont(QFont("Arial", 16, QFont::Bold));
    painter.drawText(cx - 150, 30, "СХЕМА РАСПОЛОЖЕНИЯ БОЛТОВ");

    // Тип барабана
    painter.setPen(QPen(QColor(200, 200, 100), 1));
    painter.setFont(QFont("Arial", 12));
    QString drumName;
    switch(m_drumType) {
    case 0: drumName = "🥁 Snare (малый барабан)"; break;
    case 1: drumName = "🦶 Kick (бочка)"; break;
    case 2: drumName = "🎧 Tom 1 (высокий)"; break;
    case 3: drumName = "🎧 Tom 2 (средний)"; break;
    case 4: drumName = "🎧 Floor Tom (напольный)"; break;
    default: drumName = "Барабан";
    }
    painter.drawText(cx - 150, 55, drumName);

    // Обод барабана
    painter.setPen(QPen(Qt::white, 3));
    painter.setBrush(QBrush(QColor(60, 60, 60)));
    painter.drawEllipse(cx - radius, cy - radius, radius * 2, radius * 2);

    // Пластик
    painter.setBrush(QBrush(QColor(220, 220, 220, 60)));
    painter.drawEllipse(cx - radius + 15, cy - radius + 15, radius * 2 - 30, radius * 2 - 30);

    // Болты
    QPoint lugPositions[8];
    for (int i = 0; i < 8; i++) {
        double angle = i * 45.0 * M_PI / 180.0;
        lugPositions[i] = QPoint(cx + (radius + 25) * cos(angle), cy + (radius + 25) * sin(angle));
    }

    // Степень расстройки
    float diff = qAbs(m_detectedFreq - m_targetFreq);
    float diffPercent = (m_targetFreq > 0) ? qMin(100.0f, diff / m_targetFreq * 100.0f) : 0;

    for (int i = 0; i < 8; i++) {
        QColor lugColor;

        if (m_wrongLug == i) {
            if (m_needTighten) {
                lugColor = QColor(255, 50, 50);  // Красный - подтянуть
            } else {
                lugColor = QColor(255, 150, 50); // Оранжевый - ослабить
            }
        } else if (diffPercent > 20) {
            int intensity = 100 + (int)diffPercent;
            lugColor = QColor(255, 255 - intensity, 0);
        } else {
            lugColor = QColor(100, 100, 100);
        }

        // Рисуем болт
        painter.setPen(QPen(Qt::black, 2));
        painter.setBrush(QBrush(lugColor));
        painter.drawEllipse(lugPositions[i], 28, 28);

        // Номер болта
        painter.setPen(QPen(Qt::white, 2));
        painter.setFont(QFont("Arial", 14, QFont::Bold));
        painter.drawText(lugPositions[i] - QPoint(8, 8), QString::number(i + 1));

        // Стрелка направления
        if (m_wrongLug == i) {
            painter.setPen(QPen(m_needTighten ? Qt::green : Qt::red, 3));
            if (m_needTighten) {
                // Стрелка вверх (подтянуть)
                painter.drawLine(lugPositions[i].x(), lugPositions[i].y() - 35,
                                 lugPositions[i].x(), lugPositions[i].y() - 60);
                painter.drawLine(lugPositions[i].x() - 8, lugPositions[i].y() - 48,
                                 lugPositions[i].x(), lugPositions[i].y() - 60);
                painter.drawLine(lugPositions[i].x() + 8, lugPositions[i].y() - 48,
                                 lugPositions[i].x(), lugPositions[i].y() - 60);
            } else {
                // Стрелка вниз (ослабить)
                painter.drawLine(lugPositions[i].x(), lugPositions[i].y() + 35,
                                 lugPositions[i].x(), lugPositions[i].y() + 60);
                painter.drawLine(lugPositions[i].x() - 8, lugPositions[i].y() + 48,
                                 lugPositions[i].x(), lugPositions[i].y() + 60);
                painter.drawLine(lugPositions[i].x() + 8, lugPositions[i].y() + 48,
                                 lugPositions[i].x(), lugPositions[i].y() + 60);
            }
        }
    }

    // Номера болтов в круг
    painter.setPen(QPen(QColor(150, 150, 150), 1));
    for (int i = 0; i < 8; i++) {
        double angle = i * 45.0 * M_PI / 180.0;
        int x = cx + (radius + 55) * cos(angle);
        int y = cy + (radius + 55) * sin(angle);
        painter.drawText(x - 15, y + 5, QString("Болт %1").arg(i + 1));
    }

    // Легенда
    int legendY = cy + radius + 80;
    painter.setPen(QPen(Qt::white, 1));
    painter.setFont(QFont("Arial", 10));

    painter.fillRect(cx - 120, legendY, 20, 20, QColor(255, 50, 50));
    painter.drawText(cx - 90, legendY + 15, "- Требуется подтянуть");

    painter.fillRect(cx - 120, legendY + 25, 20, 20, QColor(255, 150, 50));
    painter.drawText(cx - 90, legendY + 40, "- Требуется ослабить");

    painter.fillRect(cx - 120, legendY + 50, 20, 20, QColor(100, 100, 100));
    painter.drawText(cx - 90, legendY + 65, "- Норма");

    painter.fillRect(cx - 120, legendY + 75, 20, 20, QColor(255, 200, 0));
    painter.drawText(cx - 90, legendY + 90, "- Требует внимания");

    // Информация о расстройке
    painter.setPen(QPen(QColor(100, 200, 255), 1));
    painter.setFont(QFont("Arial", 11, QFont::Bold));
    painter.drawText(cx - 150, legendY + 115,
                     QString("Обнаружено: %1 Гц").arg(m_detectedFreq, 0, 'f', 0));
    painter.drawText(cx - 150, legendY + 135,
                     QString("Цель: %1 Гц").arg(m_targetFreq, 0, 'f', 0));
    painter.drawText(cx - 150, legendY + 155,
                     QString("Отклонение: %1 Гц").arg(diff, 0, 'f', 0));

    // Рекомендация
    if (m_wrongLug >= 0) {
        painter.setPen(QPen(m_needTighten ? Qt::green : Qt::red, 2));
        painter.setFont(QFont("Arial", 12, QFont::Bold));
        if (m_needTighten) {
            painter.drawText(cx - 150, legendY + 185,
                             "▶ ПОДТЯНИ БОЛТ " + QString::number(m_wrongLug + 1));
        } else {
            painter.drawText(cx - 150, legendY + 185,
                             "▶ ОСЛАБЬ БОЛТ " + QString::number(m_wrongLug + 1));
        }
    } else {
        painter.setPen(QPen(Qt::green, 2));
        painter.drawText(cx - 150, legendY + 185, "✓ НАСТРОЙКА ИДЕАЛЬНА");
    }

    painter.setPen(QPen(QColor(150, 150, 150), 1));
    painter.setFont(QFont("Arial", 10));
    painter.drawText(cx - 150, legendY + 215,
                     "Совет: затягивай болты крест-накрест");
    painter.drawText(cx - 150, legendY + 235,
                     "Порядок: 1 → 6 → 3 → 8 → 5 → 2 → 7 → 4");

    // Подструнник для малого барабана
    if (m_drumType == 0 && m_snareWireOn) {
        painter.setPen(QPen(QColor(200, 180, 100), 1));
        painter.drawText(cx + 50, cy + radius + 80, "🔘 Подструнник");
        painter.drawText(cx + 50, cy + radius + 100, "включён");
    }
}

// ============================================================
// ОСНОВНОЙ КЛАСС MAINWINDOW
// ============================================================
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , audioSource(nullptr)
    , audioDevice(nullptr)
    , currentDrummerIndex(0)
    , currentDrumType(0)
    , currentPlasticType(0)
    , currentTargetFreq(200.0f)
    , currentTolerance(5.0f)
    , calibrationOffset(0.0f)
    , lastWasCorrect(false)
    , recordDurationSeconds(30)
    , progressTimer(nullptr)
    , lastWrongLug(-1)
    , lastNeedTighten(true)
{
    ui->setupUi(this);

    // Установка текстов на русском
    ui->controlGroup->setTitle("⚙️ НАСТРОЙКИ");
    ui->labelDrummer->setText("🥁 Легендарный барабанщик:");
    ui->labelDrum->setText("🎧 Барабан:");
    ui->labelPlastic->setText("🎚️ Тип пластика:");
    ui->labelDuration->setText("⏱️ Длительность записи:");
    ui->labelSnareWire->setText("🔘 Подструнник:");
    ui->recordButton->setText("🎤 ЗАПИСАТЬ");
    ui->calibrateButton->setText("🔧 Калибровка");
    ui->statsButton->setText("📊 Статистика");
    ui->exportButton->setText("💾 Экспорт данных");
    ui->importButton->setText("📂 Импорт данных");
    ui->settingsExportButton->setText("💾 Экспорт настроек");
    ui->settingsImportButton->setText("📂 Импорт настроек");
    ui->dimensionsButton->setText("📏 Размеры барабанов");
    ui->showBoltsButton->setText("🔧 Схема болтов");
    ui->resultGroup->setTitle("🧠 РЕЗУЛЬТАТ АНАЛИЗА");
    ui->detectedLabel->setText("🎵 Обнаружено: ---");
    ui->spectrumLabel->setText("Спектр");
    ui->schemeLabel->setText("Схема настройки");
    ui->plasticInfoLabel->setText("Выберите тип пластика");

    // Добавляем выбор пластика
    ui->plasticCombo->addItem("🎯 Основной (верхний) пластик");
    ui->plasticCombo->addItem("🎚️ Резонаторный (нижний) пластик");

    // Добавляем выбор подструнника
    ui->snareWireCombo->addItem("🔘 Подструнник ВКЛЮЧЁН (стандарт)");
    ui->snareWireCombo->addItem("⚪ Подструнник ВЫКЛЮЧЁН (off)");
    ui->snareWireCombo->setCurrentIndex(0);

    // Добавляем выбор длительности записи
    ui->durationCombo->addItem("⚡ 5 секунд");
    ui->durationCombo->addItem("⏱️ 10 секунд");
    ui->durationCombo->addItem("📏 15 секунд");
    ui->durationCombo->addItem("🎯 20 секунд");
    ui->durationCombo->addItem("🔥 30 секунд");
    ui->durationCombo->setCurrentIndex(4);

    // Загружаем стандартные размеры
    loadDefaultDimensions();

    updateReadyButton(false);
    updatePlasticAppearance(0);

    // Подключение сигналов
    connect(ui->drummerCombo, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &MainWindow::onDrummerChanged);
    connect(ui->drumCombo, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &MainWindow::onDrumChanged);
    connect(ui->plasticCombo, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &MainWindow::onPlasticChanged);
    connect(ui->durationCombo, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &MainWindow::onDurationChanged);
    connect(ui->snareWireCombo, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &MainWindow::onSnareWireChanged);
    connect(ui->recordButton, &QPushButton::clicked,
            this, &MainWindow::onRecordButtonClicked);
    connect(ui->calibrateButton, &QPushButton::clicked,
            this, &MainWindow::onCalibrateButtonClicked);
    connect(ui->statsButton, &QPushButton::clicked,
            this, &MainWindow::onStatsButtonClicked);
    connect(ui->exportButton, &QPushButton::clicked,
            this, &MainWindow::onExportButtonClicked);
    connect(ui->importButton, &QPushButton::clicked,
            this, &MainWindow::onImportButtonClicked);
    connect(ui->settingsExportButton, &QPushButton::clicked,
            this, &MainWindow::onSettingsExportButtonClicked);
    connect(ui->settingsImportButton, &QPushButton::clicked,
            this, &MainWindow::onSettingsImportButtonClicked);
    connect(ui->readyButton, &QPushButton::clicked,
            this, &MainWindow::onReadyButtonClicked);
    connect(ui->dimensionsButton, &QPushButton::clicked,
            this, &MainWindow::onDimensionsButtonClicked);
    connect(ui->showBoltsButton, &QPushButton::clicked,
            this, &MainWindow::onShowBoltsButtonClicked);

    setWindowTitle("🥁 Drum Tuner AI - Настройка барабанов с ИИ");
    setFixedSize(1350, 950);
    setStyleSheet("QMainWindow { background-color: #1E1E1E; }");

    detector = new FrequencyDetector(this);
    loadDrummers();
    updateDisplay();

    spectrumTimer = new QTimer(this);
    connect(spectrumTimer, &QTimer::timeout, this, &MainWindow::updateSpectrumDisplay);
    spectrumTimer->start(50);

    detector->loadHistory("drum_history.json");

    appendLog("✅ Программа запущена");
    appendLog("🎸 Загружено 10 легендарных барабанщиков");
    appendLog("📏 Доступны настройки размеров барабанов");
    appendLog("🔘 Добавлена визуализация подструнника (слева)");
    appendLog("🔧 Добавлено отдельное окно со схемой болтов");
    appendLog("⏱️ Длительность записи: 30 секунд");
    appendLog("💾 Доступен импорт/экспорт данных и настроек");
}

MainWindow::~MainWindow()
{
    detector->saveHistory("drum_history.json");
    if (audioSource) {
        if (audioSource->state() == QAudio::ActiveState) {
            audioSource->stop();
        }
        delete audioSource;
    }
    if (progressTimer) delete progressTimer;
    delete ui;
}

void MainWindow::onShowBoltsButtonClicked()
{
    static BoltsViewDialog *boltsDialog = nullptr;
    if (!boltsDialog) {
        boltsDialog = new BoltsViewDialog(this);
    }

    bool snareWireOn = (ui->snareWireCombo->currentIndex() == 0);
    boltsDialog->setBoltsData(lastWrongLug, lastNeedTighten,
                              ui->detectedLabel->text().mid(15).toFloat(),
                              currentTargetFreq,
                              currentDrumType, currentPlasticType, snareWireOn);
    boltsDialog->show();
    boltsDialog->raise();
    boltsDialog->activateWindow();

    appendLog("🔧 Открыто окно со схемой болтов");
}

// ============================================================
// ОСТАЛЬНЫЕ МЕТОДЫ (без изменений, но для полноты кода)
// ============================================================
void MainWindow::exportSettings(const QString& filename)
{
    QJsonObject obj;
    obj["currentDrummerIndex"] = currentDrummerIndex;
    obj["currentDrumType"] = currentDrumType;
    obj["currentPlasticType"] = currentPlasticType;
    obj["recordDurationSeconds"] = recordDurationSeconds;
    obj["calibrationOffset"] = calibrationOffset;
    obj["snareWireEnabled"] = (ui->snareWireCombo->currentIndex() == 0);

    QJsonArray dimsArray;
    for (int i = 0; i < 5; i++) {
        QJsonObject dim;
        dim["diameter"] = drumDimensions[i].diameter;
        dim["depth"] = drumDimensions[i].depth;
        dimsArray.append(dim);
    }
    obj["drumDimensions"] = dimsArray;

    QFile file(filename);
    if (file.open(QIODevice::WriteOnly)) {
        file.write(QJsonDocument(obj).toJson());
        appendLog(QString("💾 Настройки экспортированы в %1").arg(filename));
    }
}

void MainWindow::importSettings(const QString& filename)
{
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly)) return;

    QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
    QJsonObject obj = doc.object();

    if (obj.contains("currentDrummerIndex")) {
        currentDrummerIndex = obj["currentDrummerIndex"].toInt();
        ui->drummerCombo->setCurrentIndex(currentDrummerIndex);
    }
    if (obj.contains("currentDrumType")) {
        currentDrumType = obj["currentDrumType"].toInt();
        ui->drumCombo->setCurrentIndex(currentDrumType);
    }
    if (obj.contains("currentPlasticType")) {
        currentPlasticType = obj["currentPlasticType"].toInt();
        ui->plasticCombo->setCurrentIndex(currentPlasticType);
    }
    if (obj.contains("recordDurationSeconds")) {
        recordDurationSeconds = obj["recordDurationSeconds"].toInt();
        int idx = 4;
        if (recordDurationSeconds == 5) idx = 0;
        else if (recordDurationSeconds == 10) idx = 1;
        else if (recordDurationSeconds == 15) idx = 2;
        else if (recordDurationSeconds == 20) idx = 3;
        else if (recordDurationSeconds == 30) idx = 4;
        ui->durationCombo->setCurrentIndex(idx);
    }
    if (obj.contains("calibrationOffset")) calibrationOffset = obj["calibrationOffset"].toDouble();
    if (obj.contains("snareWireEnabled")) ui->snareWireCombo->setCurrentIndex(obj["snareWireEnabled"].toBool() ? 0 : 1);

    if (obj.contains("drumDimensions")) {
        QJsonArray dimsArray = obj["drumDimensions"].toArray();
        for (int i = 0; i < dimsArray.size() && i < 5; i++) {
            QJsonObject dim = dimsArray[i].toObject();
            drumDimensions[i].diameter = dim["diameter"].toInt();
            drumDimensions[i].depth = dim["depth"].toInt();
        }
    }
    updateDisplay();
    appendLog(QString("📂 Настройки импортированы из %1").arg(filename));
}

void MainWindow::onSnareWireChanged(int index)
{
    appendLog(index == 0 ? "🔘 Подструнник ВКЛЮЧЁН" : "⚪ Подструнник ВЫКЛЮЧЁН");
    updateDisplay();
    drawDrumScheme(currentTargetFreq, currentTargetFreq, -1, true);
}

void MainWindow::loadDefaultDimensions()
{
    drumDimensions[0] = {14, 5};
    drumDimensions[1] = {22, 16};
    drumDimensions[2] = {10, 7};
    drumDimensions[3] = {12, 8};
    drumDimensions[4] = {16, 14};
}

void MainWindow::updatePlasticAppearance(int plasticType)
{
    if (plasticType == 0) {
        ui->plasticInfoLabel->setText("🎯 ОСНОВНОЙ (ВЕРХНИЙ) ПЛАСТИК\n\n• Отвечает за атаку и высоту звука\n• Настраивается первым\n• Затягивай болты крест-накрест");
        ui->plasticInfoLabel->setStyleSheet("QLabel { background-color: #2D2D2D; color: #FFD700; padding: 10px; border-radius: 8px; font-weight: bold; }");
    } else {
        ui->plasticInfoLabel->setText("🎚️ РЕЗОНАТОРНЫЙ (НИЖНИЙ) ПЛАСТИК\n\n• Отвечает за сустейн и резонанс\n• Настраивается ПОСЛЕ основного\n• Должен быть на 5-10 Гц ВЫШЕ основного");
        ui->plasticInfoLabel->setStyleSheet("QLabel { background-color: #2D2D2D; color: #87CEEB; padding: 10px; border-radius: 8px; font-weight: bold; }");
    }
}

void MainWindow::updateReadyButton(bool isCorrect)
{
    lastWasCorrect = isCorrect;
    if (isCorrect) {
        ui->readyButton->setText("✅ ГОТОВО");
        ui->readyButton->setStyleSheet("QPushButton { background-color: #4CAF50; color: white; font-weight: bold; padding: 10px; border-radius: 5px; font-size: 14px; }");
    } else {
        ui->readyButton->setText("⚠️ НЕ ГОТОВО");
        ui->readyButton->setStyleSheet("QPushButton { background-color: #f44336; color: white; font-weight: bold; padding: 10px; border-radius: 5px; font-size: 14px; }");
    }
}

void MainWindow::onReadyButtonClicked()
{
    QString plasticName = (currentPlasticType == 0) ? "основной" : "резонаторный";
    if (lastWasCorrect) {
        QMessageBox::information(this, "Готово", QString("✅ %1 пластик настроен правильно!").arg(plasticName));
    } else {
        QMessageBox::information(this, "Не готово", QString("⚠️ %1 пластик настроен НЕ правильно!").arg(plasticName));
    }
}

void MainWindow::onDimensionsButtonClicked()
{
    bool ok;
    int diameter = QInputDialog::getInt(this, "Диаметр", QString("Диаметр (%1):").arg(ui->drumCombo->currentText()), drumDimensions[currentDrumType].diameter, 6, 28, 1, &ok);
    if (ok) {
        int depth = QInputDialog::getInt(this, "Глубина", QString("Глубина (%1):").arg(ui->drumCombo->currentText()), drumDimensions[currentDrumType].depth, 3, 24, 1, &ok);
        if (ok) {
            drumDimensions[currentDrumType].diameter = diameter;
            drumDimensions[currentDrumType].depth = depth;
            appendLog(QString("📏 Размеры: ∅%1\" × %2\"").arg(diameter).arg(depth));
            updateDisplay();
            drawDrumScheme(currentTargetFreq, currentTargetFreq, -1, true);
        }
    }
}

void MainWindow::onDurationChanged(int index)
{
    switch(index) {
    case 0: recordDurationSeconds = 5; break;
    case 1: recordDurationSeconds = 10; break;
    case 2: recordDurationSeconds = 15; break;
    case 3: recordDurationSeconds = 20; break;
    case 4: recordDurationSeconds = 30; break;
    default: recordDurationSeconds = 30;
    }
    appendLog(QString("⏱️ Длительность записи: %1 сек").arg(recordDurationSeconds));
}

void MainWindow::loadDrummers()
{
    drummers = {
        {"Lars Ulrich", "Metallica", 200.0f, 208.0f, 65.0f, 70.0f, 145.0f, 152.0f, 125.0f, 132.0f, 95.0f, 102.0f, "Резкий, мощный звук"},
        {"Dave Lombardo", "Slayer", 210.0f, 218.0f, 60.0f, 65.0f, 150.0f, 158.0f, 130.0f, 138.0f, 100.0f, 108.0f, "Агрессивный, быстрый"},
        {"Nicko McBrain", "Iron Maiden", 195.0f, 203.0f, 70.0f, 75.0f, 140.0f, 147.0f, 120.0f, 127.0f, 90.0f, 97.0f, "Тёплый, живой звук"},
        {"Mike Portnoy", "Dream Theater", 200.0f, 208.0f, 55.0f, 60.0f, 135.0f, 142.0f, 115.0f, 122.0f, 85.0f, 92.0f, "Точный, техничный"},
        {"Joey Jordison", "Slipknot", 205.0f, 213.0f, 52.0f, 57.0f, 140.0f, 147.0f, 120.0f, 127.0f, 90.0f, 97.0f, "Очень высокий, злой"},
        {"Tomas Haake", "Meshuggah", 190.0f, 198.0f, 45.0f, 50.0f, 125.0f, 132.0f, 105.0f, 112.0f, 75.0f, 82.0f, "Тяжелый, механический"},
        {"Chris Adler", "Lamb of God", 195.0f, 203.0f, 58.0f, 63.0f, 140.0f, 147.0f, 120.0f, 127.0f, 90.0f, 97.0f, "Агрессивный грув"},
        {"Brann Dailor", "Mastodon", 190.0f, 198.0f, 52.0f, 57.0f, 135.0f, 142.0f, 115.0f, 122.0f, 85.0f, 92.0f, "Техничный, джазовый"},
        {"Mario Duplantier", "Gojira", 200.0f, 208.0f, 55.0f, 60.0f, 140.0f, 147.0f, 120.0f, 127.0f, 90.0f, 97.0f, "Мощный, точный"}
    };

    for (const auto& d : drummers) ui->drummerCombo->addItem(QString("%1 (%2)").arg(d.name, d.band));
    ui->drumCombo->addItem("🥁 Snare (малый барабан)");
    ui->drumCombo->addItem("🦶 Kick (бочка)");
    ui->drumCombo->addItem("🎧 Tom 1 (высокий)");
    ui->drumCombo->addItem("🎧 Tom 2 (средний)");
    ui->drumCombo->addItem("🎧 Floor Tom (напольный)");
}

void MainWindow::updateDisplay()
{
    if (currentDrummerIndex < 0 || currentDrummerIndex >= drummers.size()) return;
    const Drummer& d = drummers[currentDrummerIndex];

    switch (currentDrumType) {
    case 0: currentTargetFreq = (currentPlasticType == 0) ? d.snareFreq : d.snareResoFreq; break;
    case 1: currentTargetFreq = (currentPlasticType == 0) ? d.kickFreq : d.kickResoFreq; break;
    case 2: currentTargetFreq = (currentPlasticType == 0) ? d.tom1Freq : d.tom1ResoFreq; break;
    case 3: currentTargetFreq = (currentPlasticType == 0) ? d.tom2Freq : d.tom2ResoFreq; break;
    case 4: currentTargetFreq = (currentPlasticType == 0) ? d.floorTomFreq : d.floorTomResoFreq; break;
    default: currentTargetFreq = d.snareFreq;
    }
    currentTolerance = (currentDrumType == 1) ? 3.0f : 5.0f;

    QString plasticText = (currentPlasticType == 0) ? "Основной" : "Резонаторный";
    QString dimText = QString("∅%1\" × %2\"").arg(drumDimensions[currentDrumType].diameter).arg(drumDimensions[currentDrumType].depth);
    QString snareWireText = (ui->snareWireCombo->currentIndex() == 0) ? "🔘 Включён" : "⚪ Выключён";

    ui->targetLabel->setText(QString("🎯 Цель: %1 Гц (±%2 Гц) - %3").arg(currentTargetFreq, 0, 'f', 0).arg(currentTolerance).arg(plasticText));
    ui->infoLabel->setText(QString("🥁 %1 (%2)\n📝 %3\n📏 %4\n🔘 Подструнник: %5").arg(d.name, d.band, d.description, dimText, snareWireText));
    ui->statusLabel->setText(QString("✅ Готов | Цель: %1 Гц | %2 пластик | Запись: %3 сек").arg(currentTargetFreq, 0, 'f', 0).arg(plasticText).arg(recordDurationSeconds));

    updateReadyButton(false);
    drawDrumScheme(currentTargetFreq, currentTargetFreq, -1, true);
}

void MainWindow::drawLugBolts(QPainter& painter, int cx, int cy, int radius, int wrongLug, bool needTighten, float diffPercent)
{
    Q_UNUSED(diffPercent);
    QPoint lugPositions[8];
    for (int i = 0; i < 8; i++) {
        double angle = i * 45.0 * M_PI / 180.0;
        lugPositions[i] = QPoint(cx + (radius + 25) * cos(angle), cy + (radius + 25) * sin(angle));
    }

    for (int i = 0; i < 8; i++) {
        QColor lugColor = (wrongLug == i) ? (needTighten ? QColor(255, 50, 50) : QColor(255, 150, 50)) : QColor(120, 120, 120);
        painter.setPen(QPen(Qt::black, 2));
        painter.setBrush(QBrush(lugColor));
        painter.drawEllipse(lugPositions[i], 20, 20);
        painter.setPen(QPen(Qt::white, 1));
        painter.drawText(lugPositions[i] - QPoint(6, 6), QString::number(i + 1));

        if (wrongLug == i) {
            painter.setPen(QPen(needTighten ? Qt::green : Qt::red, 2));
            if (needTighten) {
                painter.drawLine(lugPositions[i].x(), lugPositions[i].y() - 22, lugPositions[i].x(), lugPositions[i].y() - 44);
                painter.drawLine(lugPositions[i].x() - 5, lugPositions[i].y() - 33, lugPositions[i].x(), lugPositions[i].y() - 44);
                painter.drawLine(lugPositions[i].x() + 5, lugPositions[i].y() - 33, lugPositions[i].x(), lugPositions[i].y() - 44);
            } else {
                painter.drawLine(lugPositions[i].x(), lugPositions[i].y() + 22, lugPositions[i].x(), lugPositions[i].y() + 44);
                painter.drawLine(lugPositions[i].x() - 5, lugPositions[i].y() + 33, lugPositions[i].x(), lugPositions[i].y() + 44);
                painter.drawLine(lugPositions[i].x() + 5, lugPositions[i].y() + 33, lugPositions[i].x(), lugPositions[i].y() + 44);
            }
        }
    }
}

void MainWindow::drawSnareWire(QPainter& painter, int cx, int cy, int radius)
{
    int wireX = cx - radius - 90;
    int wireY = cy - 35;
    painter.setPen(QPen(QColor(220, 220, 220), 2));
    painter.setBrush(QBrush(QColor(60, 60, 60)));
    painter.drawRect(wireX, wireY, 80, 70);
    painter.setPen(QPen(Qt::white, 1));
    painter.drawText(wireX + 5, wireY + 15, "ПОДСТРУННИК");
    painter.setPen(QPen(QColor(200, 180, 100), 1));
    for (int i = 0; i < 8; i++) painter.drawLine(wireX + 10, wireY + 25 + i * 5, wireX + 70, wireY + 25 + i * 5);
    painter.setPen(QPen(Qt::gray, 2));
    painter.drawLine(wireX + 5, wireY + 22, wireX + 75, wireY + 22);
    painter.drawLine(wireX + 5, wireY + 60, wireX + 75, wireY + 60);
    painter.setPen(QPen(QColor(100, 200, 255), 1));
    painter.drawText(wireX + 5, wireY + 85, "← слева от");
    painter.drawText(wireX + 10, wireY + 95, "барабанщика");
}

void MainWindow::drawDrumScheme(float detectedFreq, float targetFreq, int wrongLug, bool needTighten)
{
    if (!ui->schemeLabel) return;
    int w = 550, h = 550;
    QPixmap pixmap(w, h);
    pixmap.fill(QColor(35, 35, 35));
    QPainter painter(&pixmap);
    painter.setRenderHint(QPainter::Antialiasing);
    int cx = w/2, cy = h/2, r = 140;

    painter.setPen(QPen(Qt::white, 3));
    painter.setBrush(QBrush(QColor(80, 80, 80)));
    painter.drawEllipse(cx - r, cy - r, r*2, r*2);
    painter.setBrush(QBrush(QColor(220, 220, 220, 100)));
    painter.drawEllipse(cx - r + 12, cy - r + 12, r*2 - 24, r*2 - 24);

    float diff = detectedFreq - targetFreq;
    float diffPercent = (targetFreq > 0) ? qMin(100.0f, std::abs(diff) / targetFreq * 100.0f) : 0;
    drawLugBolts(painter, cx, cy, r, wrongLug, needTighten, diffPercent);

    if (currentDrumType == 0 && ui->snareWireCombo->currentIndex() == 0) drawSnareWire(painter, cx, cy, r);

    painter.setPen(QPen(Qt::white, 2));
    painter.drawText(cx - 100, cy - r - 25, (currentPlasticType == 0) ? "ОСНОВНОЙ пластик" : "РЕЗОНАТОРНЫЙ пластик");
    painter.drawText(cx - 60, cy + r + 45, "Вид сверху");
    painter.drawText(cx - 90, cy + r + 75, "Болты 1-8 по кругу");

    if (wrongLug >= 0) {
        painter.setPen(QPen(needTighten ? QColor(100, 255, 100) : QColor(255, 100, 100), 2));
        painter.drawText(cx - 120, cy + r + 105, needTighten ? "▲ ПОДТЯНУТЬ" : "▼ ОСЛАБИТЬ");
    } else {
        painter.setPen(QPen(QColor(100, 255, 100), 2));
        painter.drawText(cx - 90, cy + r + 105, "✓ НАСТРОЙКА ИДЕАЛЬНА");
    }

    painter.setPen(QPen(QColor(150, 150, 150), 1));
    painter.drawText(cx - 140, cy + r + 135, "Совет: затягивай болты крест-накрест");
    if (currentPlasticType == 1) {
        painter.setPen(QPen(QColor(100, 200, 255), 1));
        painter.drawText(cx - 130, cy + r + 165, "💡 Резонаторный пластик должен быть ВЫШЕ основного на 5-10 Гц");
    }
    ui->schemeLabel->setPixmap(pixmap);
}

void MainWindow::appendLog(const QString& msg)
{
    ui->logTextEdit->append(QString("[%1] %2").arg(QDateTime::currentDateTime().toString("hh:mm:ss"), msg));
}

void MainWindow::startRecording()
{
    QAudioFormat format;
    format.setSampleRate(44100);
    format.setChannelCount(1);
    format.setSampleFormat(QAudioFormat::Int16);

    const QList<QAudioDevice> devices = QMediaDevices::audioInputs();
    if (devices.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Микрофон не найден!");
        return;
    }

    const QAudioDevice& device = devices.first();
    if (!device.isFormatSupported(format)) format = device.preferredFormat();

    audioSource = new QAudioSource(device, format, this);
    int bufferSize = format.sampleRate() * recordDurationSeconds * format.bytesPerFrame();
    audioBuffer.reserve(bufferSize / sizeof(short));
    audioDevice = audioSource->start();
    recordTimer.start();

    int elapsed = 0;
    progressTimer = new QTimer(this);
    connect(progressTimer, &QTimer::timeout, this, [this, elapsed]() mutable {
        elapsed++;
        if (elapsed <= recordDurationSeconds) ui->statusLabel->setText(QString("🔴 Запись... %1/%2 сек").arg(elapsed).arg(recordDurationSeconds));
    });
    progressTimer->start(1000);

    ui->recordButton->setEnabled(false);
    ui->recordButton->setText("🔴 ЗАПИСЬ...");
    ui->statusLabel->setStyleSheet("color: red; font-weight: bold;");
    appendLog(QString("🎤 Начата запись (%1 сек)").arg(recordDurationSeconds));
    QTimer::singleShot(recordDurationSeconds * 1000, this, &MainWindow::stopRecording);
}

void MainWindow::stopRecording()
{
    if (progressTimer) { progressTimer->stop(); delete progressTimer; progressTimer = nullptr; }
    if (!audioSource) return;
    audioSource->stop();
    appendLog(QString("⏹️ Запись завершена (%1 сек)").arg(recordTimer.elapsed() / 1000));

    if (audioDevice) {
        QByteArray data = audioDevice->readAll();
        const short* samples = reinterpret_cast<const short*>(data.constData());
        int sampleCount = data.size() / sizeof(short);
        if (sampleCount > 100) {
            audioBuffer.resize(sampleCount);
            for (int i = 0; i < sampleCount; i++) audioBuffer[i] = samples[i] / 32768.0f;
            float maxAmp = 0;
            for (float s : audioBuffer) if (std::abs(s) > maxAmp) maxAmp = std::abs(s);
            appendLog(QString("🎧 Амплитуда: %1").arg(maxAmp, 0, 'f', 2));
            if (maxAmp > 0.05f) {
                processRecordedAudio();
                drawSpectrum(audioBuffer);
            } else {
                ui->resultLabel->setText("❌ Слишком тихий удар!");
                updateReadyButton(false);
            }
        }
    }
    delete audioSource;
    audioSource = nullptr;
    audioDevice = nullptr;
    ui->recordButton->setEnabled(true);
    ui->recordButton->setText("🎤 ЗАПИСАТЬ");
    ui->statusLabel->setStyleSheet("color: #888888;");
    ui->statusLabel->setText(QString("✅ Готов | Цель: %1 Гц").arg(currentTargetFreq, 0, 'f', 0));
}

void MainWindow::processRecordedAudio()
{
    float detectedFreq = detector->detectFrequency(audioBuffer, 44100);
    detectedFreq += calibrationOffset;
    ui->detectedLabel->setText(QString("🎵 Обнаружено: %1 Гц").arg(detectedFreq, 0, 'f', 0));

    bool wasCorrect = std::abs(detectedFreq - currentTargetFreq) <= currentTolerance;
    detector->learn(detectedFreq, currentTargetFreq, currentDrumType, currentPlasticType, drummers[currentDrummerIndex].name, wasCorrect);
    updateReadyButton(wasCorrect);

    int wrongLug = -1;
    bool needTighten = true;
    QString lugText = detector->getLugRecommendation(detectedFreq, currentTargetFreq, wrongLug, needTighten, currentPlasticType);
    lastWrongLug = wrongLug;
    lastNeedTighten = needTighten;

    drawDrumScheme(detectedFreq, currentTargetFreq, wrongLug, needTighten);
    ui->resultLabel->setText(detector->getIntelligentRecommendation(detectedFreq, currentTargetFreq, currentDrumType, currentPlasticType) + "\n\n" + lugText);
    appendLog(QString("🧠 %1 Гц -> %2 Гц (%3 пластик) - %4").arg(detectedFreq, 0, 'f', 0).arg(currentTargetFreq, 0, 'f', 0).arg(currentPlasticType == 0 ? "основной" : "резонаторный").arg(wasCorrect ? "✅" : "❌"));
}

void MainWindow::drawSpectrum(const QVector<float>& data)
{
    if (!ui->spectrumLabel) return;
    QPixmap pixmap(ui->spectrumLabel->size());
    if (pixmap.isNull()) return;
    pixmap.fill(Qt::black);
    QPainter painter(&pixmap);
    int w = pixmap.width(), h = pixmap.height();
    if (w <= 0) w = 400; if (h <= 0) h = 150;
    int step = qMax(1, data.size() / w);
    for (int x = 0; x < w && x * step < data.size(); x++) {
        float amp = 0;
        for (int j = 0; j < step && x * step + j < data.size(); j++) amp += std::abs(data[x * step + j]);
        amp /= step; if (amp > 1.0f) amp = 1.0f;
        int barHeight = qMin(h, (int)(amp * h * 2));
        if (barHeight < 1) barHeight = 1;
        QColor color = (amp > 0.5f) ? Qt::red : (amp > 0.2f) ? Qt::yellow : Qt::green;
        painter.fillRect(x, h - barHeight, 2, barHeight, color);
    }
    int targetX = (int)(w * (currentTargetFreq / 500.0f));
    if (targetX > 0 && targetX < w) {
        painter.setPen(QPen(Qt::red, 2, Qt::DashLine));
        painter.drawLine(targetX, 0, targetX, h);
    }
    ui->spectrumLabel->setPixmap(pixmap);
}

void MainWindow::updateSpectrumDisplay()
{
    if (!audioSource && !audioBuffer.isEmpty()) drawSpectrum(audioBuffer);
    else if (!audioSource) {
        QVector<float> fake(44100);
        static std::random_device rd;
        static std::mt19937 gen(rd());
        static std::uniform_real_distribution<> dis(0.0, 0.3);
        for (int i = 0; i < fake.size(); i++) fake[i] = dis(gen);
        drawSpectrum(fake);
    }
}

void MainWindow::onRecordButtonClicked() { startRecording(); }
void MainWindow::onDrummerChanged(int idx) { if (idx >= 0 && idx < drummers.size()) { currentDrummerIndex = idx; updateDisplay(); } }
void MainWindow::onDrumChanged(int idx) { if (idx >= 0 && idx <= 4) { currentDrumType = idx; updateDisplay(); drawDrumScheme(currentTargetFreq, currentTargetFreq, -1, true); } }
void MainWindow::onPlasticChanged(int idx) { if (idx >= 0 && idx <= 1) { currentPlasticType = idx; updateDisplay(); updatePlasticAppearance(idx); } }
void MainWindow::onStatsButtonClicked() { QMessageBox::information(this, "Статистика", detector->getProgressReport()); }
void MainWindow::onCalibrateButtonClicked() { startRecording(); }
void MainWindow::onExportButtonClicked()
{
    QString fn = QFileDialog::getSaveFileName(this, "Экспорт данных обучения", QString("drum_training_%1.json").arg(QDate::currentDate().toString("yyyyMMdd")), "JSON (*.json)");
    if (!fn.isEmpty()) { detector->saveHistory(fn); appendLog(QString("💾 Данные обучения экспортированы в %1").arg(fn)); QMessageBox::information(this, "Экспорт", "Данные экспортированы!"); }
}
void MainWindow::onImportButtonClicked()
{
    QString fn = QFileDialog::getOpenFileName(this, "Импорт данных обучения", "", "JSON (*.json)");
    if (!fn.isEmpty()) { detector->loadHistory(fn); appendLog(QString("📂 Данные обучения импортированы из %1").arg(fn)); QMessageBox::information(this, "Импорт", "Данные импортированы!"); }
}
void MainWindow::onSettingsExportButtonClicked()
{
    QString fn = QFileDialog::getSaveFileName(this, "Экспорт настроек", QString("drum_settings_%1.json").arg(QDate::currentDate().toString("yyyyMMdd")), "JSON (*.json)");
    if (!fn.isEmpty()) { exportSettings(fn); QMessageBox::information(this, "Экспорт", "Настройки экспортированы!"); }
}
void MainWindow::onSettingsImportButtonClicked()
{
    QString fn = QFileDialog::getOpenFileName(this, "Импорт настроек", "", "JSON (*.json)");
    if (!fn.isEmpty()) { importSettings(fn); QMessageBox::information(this, "Импорт", "Настройки импортированы!"); }
}
