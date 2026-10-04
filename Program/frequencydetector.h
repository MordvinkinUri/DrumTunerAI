#ifndef FREQUENCYDETECTOR_H
#define FREQUENCYDETECTOR_H

#include <QObject>
#include <QVector>
#include <QString>
#include <QDateTime>

struct LearningSample {
    float detectedFreq;
    float targetFreq;
    int drumType;
    int plasticType;
    QString drummerName;
    bool wasCorrect;
    float correction;
    QDateTime timestamp;
};

class FrequencyDetector : public QObject
{
    Q_OBJECT

public:
    explicit FrequencyDetector(QObject *parent = nullptr);

    float detectFrequency(const QVector<float>& audio, int sampleRate);
    float yinAlgorithm(const QVector<float>& audio, int sampleRate);
    float simplePitchDetection(const QVector<float>& audio, int sampleRate);

    void learn(float detectedFreq, float targetFreq, int drumType, int plasticType,
               const QString& drummerName, bool wasCorrect);

    QString getIntelligentRecommendation(float detectedFreq, float targetFreq, int drumType, int plasticType);
    QString getProgressReport();
    QString getLugRecommendation(float detectedFreq, float targetFreq, int& wrongLug, bool& needTighten, int plasticType);

    float getSuccessRate();
    float getAverageError();
    int getHistorySize() const;

    void saveHistory(const QString& filename);
    void loadHistory(const QString& filename);
    void clearHistory();

    QVector<LearningSample> getHistory() const { return learningHistory; }
    void setHistory(const QVector<LearningSample>& history) { learningHistory = history; }

private:
    QVector<LearningSample> learningHistory;
    float calculateCorrection(float detectedFreq, float targetFreq);
    float getAverageCorrectionForSimilar(float detectedFreq, int drumType, int plasticType);
};

#endif // FREQUENCYDETECTOR_H
