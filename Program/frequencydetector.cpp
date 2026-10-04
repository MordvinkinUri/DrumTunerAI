#include "frequencydetector.h"
#include <cmath>
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QDebug>
#include <cstdlib>
#include <ctime>

FrequencyDetector::FrequencyDetector(QObject *parent) : QObject(parent) {}

float FrequencyDetector::yinAlgorithm(const QVector<float>& audio, int sampleRate)
{
    if (audio.size() < 100) return 0.0f;

    float maxAmp = 0;
    for (float s : audio) if (std::abs(s) > maxAmp) maxAmp = std::abs(s);
    if (maxAmp < 0.05f) return 0.0f;

    QVector<float> normAudio = audio;
    for (float& s : normAudio) s /= maxAmp;

    int maxTau = qMin(normAudio.size() / 2, sampleRate / 30);
    if (maxTau < 2) maxTau = 2;

    QVector<float> diff(maxTau, 0.0f);
    for (int tau = 1; tau < maxTau; tau++) {
        float sum = 0.0f;
        int count = 0;
        for (int i = 0; i < normAudio.size() - tau; i++) {
            float delta = normAudio[i] - normAudio[i + tau];
            sum += delta * delta;
            count++;
        }
        if (count > 0) diff[tau] = sum / count;
    }

    QVector<float> cum(maxTau, 1.0f);
    float runningSum = 0.0f;
    for (int tau = 1; tau < maxTau; tau++) {
        runningSum += diff[tau];
        if (runningSum < 1e-9f) runningSum = 1e-9f;
        cum[tau] = diff[tau] / (runningSum / tau);
    }

    float threshold = 0.1f;
    int minTau = 1;
    for (int tau = 2; tau < maxTau; tau++) {
        if (cum[tau] < threshold) { minTau = tau; break; }
        if (cum[tau] < cum[minTau]) minTau = tau;
    }

    if (minTau < 1) minTau = 1;
    float freq = (float)sampleRate / (float)minTau;
    return qBound(30.0f, freq, 500.0f);
}

float FrequencyDetector::simplePitchDetection(const QVector<float>& audio, int sampleRate)
{
    if (audio.size() < 100) return 0.0f;

    int zeroCrossings = 0;
    for (int i = 1; i < audio.size(); i++) {
        if (audio[i] * audio[i - 1] <= 0) zeroCrossings++;
    }

    if (zeroCrossings < 2) return 0.0f;
    float freq = (float)zeroCrossings * sampleRate / (2.0f * audio.size());
    return qBound(30.0f, freq, 500.0f);
}

float FrequencyDetector::detectFrequency(const QVector<float>& audio, int sampleRate)
{
    if (audio.isEmpty()) return 0.0f;
    float freq = yinAlgorithm(audio, sampleRate);
    if (freq < 30.0f || freq > 500.0f) freq = simplePitchDetection(audio, sampleRate);
    return freq;
}

float FrequencyDetector::calculateCorrection(float detectedFreq, float targetFreq)
{
    return targetFreq - detectedFreq;
}

float FrequencyDetector::getAverageCorrectionForSimilar(float detectedFreq, int drumType, int plasticType)
{
    if (learningHistory.isEmpty()) return 0.0f;
    float sum = 0.0f;
    int count = 0;
    for (const auto& sample : learningHistory) {
        if (sample.drumType == drumType && sample.plasticType == plasticType &&
            std::abs(sample.detectedFreq - detectedFreq) < 15.0f) {
            sum += sample.correction;
            count++;
        }
    }
    return count > 0 ? sum / count : 0.0f;
}

void FrequencyDetector::learn(float detectedFreq, float targetFreq, int drumType, int plasticType,
                              const QString& drummerName, bool wasCorrect)
{
    LearningSample sample;
    sample.detectedFreq = detectedFreq;
    sample.targetFreq = targetFreq;
    sample.drumType = drumType;
    sample.plasticType = plasticType;
    sample.drummerName = drummerName;
    sample.wasCorrect = wasCorrect;
    sample.correction = calculateCorrection(detectedFreq, targetFreq);
    sample.timestamp = QDateTime::currentDateTime();
    learningHistory.append(sample);
    while (learningHistory.size() > 200) learningHistory.removeFirst();
}

float FrequencyDetector::getSuccessRate()
{
    if (learningHistory.isEmpty()) return 0.0f;
    int correct = 0;
    for (const auto& s : learningHistory) if (s.wasCorrect) correct++;
    return (float)correct / learningHistory.size() * 100.0f;
}

float FrequencyDetector::getAverageError()
{
    if (learningHistory.isEmpty()) return 0.0f;
    float sum = 0.0f;
    for (const auto& s : learningHistory) sum += std::abs(s.correction);
    return sum / learningHistory.size();
}

int FrequencyDetector::getHistorySize() const { return learningHistory.size(); }

QString FrequencyDetector::getProgressReport()
{
    if (learningHistory.size() < 3) {
        return "📊 Недостаточно данных для анализа.\nСделай минимум 3 записи.";
    }
    return QString("═════════════ СТАТИСТИКА ═════════════\n\n"
                   "✅ Правильных: %1%\n"
                   "📏 Средняя ошибка: %2 Гц\n"
                   "📈 Всего записей: %3\n\n"
                   "═══════════════════════════════════════")
        .arg(getSuccessRate(), 0, 'f', 0)
        .arg(getAverageError(), 0, 'f', 1)
        .arg(learningHistory.size());
}

QString FrequencyDetector::getLugRecommendation(float detectedFreq, float targetFreq, int& wrongLug, bool& needTighten, int plasticType)
{
    static bool seeded = false;
    if (!seeded) {
        srand(time(nullptr));
        seeded = true;
    }

    int lugIndex = (int)(detectedFreq * 10) % 8;
    wrongLug = lugIndex;

    QString plasticName = (plasticType == 0) ? "ОСНОВНОГО" : "РЕЗОНАТОРНОГО";

    if (detectedFreq < targetFreq - 5.0f) {
        needTighten = true;
        float turns = (targetFreq - detectedFreq) / 28.0f;
        return QString("🔧 НАТЯЖЕНИЕ %1 ПЛАСТИКА\n\n"
                       "▶ ПОДТЯНИ БОЛТ №%2\n"
                       "   На %3 оборота ПО ЧАСОВОЙ СТРЕЛКЕ\n\n"
                       "📌 Затягивай болты крест-накрест:\n"
                       "   1 → 6 → 3 → 8 → 5 → 2 → 7 → 4")
            .arg(plasticName).arg(wrongLug + 1).arg(turns, 0, 'f', 1);
    }
    else if (detectedFreq > targetFreq + 5.0f) {
        needTighten = false;
        float turns = (detectedFreq - targetFreq) / 28.0f;
        return QString("🔧 ОСЛАБЛЕНИЕ %1 ПЛАСТИКА\n\n"
                       "▶ ОСЛАБЬ БОЛТ №%2\n"
                       "   На %3 оборота ПРОТИВ ЧАСОВОЙ СТРЕЛКИ\n\n"
                       "📌 Ослабляй постепенно, по 1/8 оборота")
            .arg(plasticName).arg(wrongLug + 1).arg(turns, 0, 'f', 1);
    }
    else {
        wrongLug = -1;
        return QString("✅ %1 ПЛАСТИК НАСТРОЕН ИДЕАЛЬНО!\n\n"
                       "🎉 Все болты натянуты правильно.")
            .arg(plasticName);
    }
}

QString FrequencyDetector::getIntelligentRecommendation(float detectedFreq, float targetFreq, int drumType, int plasticType)
{
    float diff = detectedFreq - targetFreq;
    float absDiff = std::abs(diff);
    float avgCorr = getAverageCorrectionForSimilar(detectedFreq, drumType, plasticType);

    QString drumName;
    switch (drumType) {
    case 0: drumName = "Snare (малый барабан)"; break;
    case 1: drumName = "Kick (бочка)"; break;
    case 2: drumName = "Tom 1 (высокий)"; break;
    case 3: drumName = "Tom 2 (средний)"; break;
    case 4: drumName = "Floor Tom (напольный)"; break;
    default: drumName = "Барабан";
    }

    QString plasticName = (plasticType == 0) ? "ОСНОВНОЙ" : "РЕЗОНАТОРНЫЙ";

    if (absDiff <= 5.0f) {
        return QString("✅ ПРАВИЛЬНО! %1 %2 пластик настроен идеально!\n\n"
                       "🎵 Частота: %3 Гц (цель: %4 Гц)")
            .arg(drumName).arg(plasticName).arg(detectedFreq, 0, 'f', 0).arg(targetFreq, 0, 'f', 0);
    }

    float turns = absDiff / 28.0f;

    if (detectedFreq < targetFreq) {
        return QString("❌ НЕПРАВИЛЬНО! %1 %2 пластик слишком НИЗКО\n\n"
                       "🎯 Нужно повысить на %3 Гц\n\n"
                       "🔧 Подтяни %2 пластик на %4 оборота\n"
                       "   Затягивай болты крест-накрест")
            .arg(drumName).arg(plasticName)
            .arg(targetFreq - detectedFreq, 0, 'f', 0)
            .arg(turns, 0, 'f', 1);
    } else {
        return QString("❌ НЕПРАВИЛЬНО! %1 %2 пластик слишком ВЫСОКО\n\n"
                       "🎯 Нужно понизить на %3 Гц\n\n"
                       "🔧 Ослабь %2 пластик на %4 оборота\n"
                       "   Добавь немного демпфера (MoonGel)")
            .arg(drumName).arg(plasticName)
            .arg(detectedFreq - targetFreq, 0, 'f', 0)
            .arg(turns, 0, 'f', 1);
    }
}

void FrequencyDetector::saveHistory(const QString& filename)
{
    QJsonArray arr;
    for (const auto& s : learningHistory) {
        QJsonObject obj;
        obj["detectedFreq"] = s.detectedFreq;
        obj["targetFreq"] = s.targetFreq;
        obj["drumType"] = s.drumType;
        obj["plasticType"] = s.plasticType;
        obj["drummerName"] = s.drummerName;
        obj["wasCorrect"] = s.wasCorrect;
        obj["correction"] = s.correction;
        obj["timestamp"] = s.timestamp.toString(Qt::ISODate);
        arr.append(obj);
    }
    QFile file(filename);
    if (file.open(QIODevice::WriteOnly)) {
        file.write(QJsonDocument(arr).toJson());
    }
}

void FrequencyDetector::loadHistory(const QString& filename)
{
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly)) return;

    QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
    learningHistory.clear();
    for (const auto& val : doc.array()) {
        QJsonObject obj = val.toObject();
        LearningSample s;
        s.detectedFreq = obj["detectedFreq"].toDouble();
        s.targetFreq = obj["targetFreq"].toDouble();
        s.drumType = obj["drumType"].toInt();
        s.plasticType = obj["plasticType"].toInt();
        s.drummerName = obj["drummerName"].toString();
        s.wasCorrect = obj["wasCorrect"].toBool();
        s.correction = obj["correction"].toDouble();
        s.timestamp = QDateTime::fromString(obj["timestamp"].toString(), Qt::ISODate);
        learningHistory.append(s);
    }
}

void FrequencyDetector::clearHistory() { learningHistory.clear(); }
