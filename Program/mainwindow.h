#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>
#include <QAudioSource>
#include <QAudioFormat>
#include <QTimer>
#include <QElapsedTimer>
#include <QMap>
#include <QInputDialog>
#include <QDialog>
#include <QPainter>
#include "frequencydetector.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

// ============================================================
// НОВОЕ ОКНО ДЛЯ ОТОБРАЖЕНИЯ БОЛТОВ
// ============================================================
class BoltsViewDialog : public QDialog
{
    Q_OBJECT

public:
    explicit BoltsViewDialog(QWidget *parent = nullptr);
    ~BoltsViewDialog();

    void setBoltsData(int wrongLug, bool needTighten, float detectedFreq, float targetFreq, int drumType, int plasticType, bool snareWireOn);
    void paintEvent(QPaintEvent *event) override;

private:
    int m_wrongLug;
    bool m_needTighten;
    float m_detectedFreq;
    float m_targetFreq;
    int m_drumType;
    int m_plasticType;
    bool m_snareWireOn;
};

// ============================================================
// ОСНОВНОЙ КЛАСС
// ============================================================
struct Drummer {
    QString name;
    QString band;
    float snareFreq;
    float snareResoFreq;
    float kickFreq;
    float kickResoFreq;
    float tom1Freq;
    float tom1ResoFreq;
    float tom2Freq;
    float tom2ResoFreq;
    float floorTomFreq;
    float floorTomResoFreq;
    QString description;
};

struct DrumDimensions {
    int diameter;
    int depth;
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onRecordButtonClicked();
    void onDrummerChanged(int index);
    void onDrumChanged(int index);
    void onPlasticChanged(int index);
    void onDurationChanged(int index);
    void onSnareWireChanged(int index);
    void onStatsButtonClicked();
    void onExportButtonClicked();
    void onImportButtonClicked();
    void onSettingsExportButtonClicked();
    void onSettingsImportButtonClicked();
    void onCalibrateButtonClicked();
    void onReadyButtonClicked();
    void onDimensionsButtonClicked();
    void onShowBoltsButtonClicked();

private:
    Ui::MainWindow *ui;
    FrequencyDetector* detector;

    QVector<Drummer> drummers;
    QMap<int, DrumDimensions> drumDimensions;
    int currentDrummerIndex;
    int currentDrumType;
    int currentPlasticType;
    float currentTargetFreq;
    float currentTolerance;
    float calibrationOffset;
    bool lastWasCorrect;
    int recordDurationSeconds;

    // Данные для отображения болтов
    int lastWrongLug;
    bool lastNeedTighten;

    QAudioSource* audioSource;
    QIODevice* audioDevice;
    QVector<float> audioBuffer;
    QTimer* spectrumTimer;
    QElapsedTimer recordTimer;
    QTimer* progressTimer;

    void loadDrummers();
    void loadDefaultDimensions();
    void updateDisplay();
    void startRecording();
    void stopRecording();
    void processRecordedAudio();
    void drawSpectrum(const QVector<float>& data);
    void updateSpectrumDisplay();
    void appendLog(const QString& message);
    void drawDrumScheme(float detectedFreq, float targetFreq, int wrongLug = -1, bool needTighten = true);
    void drawLugBolts(QPainter& painter, int cx, int cy, int radius, int wrongLug, bool needTighten, float diffPercent);
    void drawSnareWire(QPainter& painter, int cx, int cy, int radius);
    void updateReadyButton(bool isCorrect);
    void updatePlasticAppearance(int plasticType);
    void exportSettings(const QString& filename);
    void importSettings(const QString& filename);
};

#endif // MAINWINDOW_H
