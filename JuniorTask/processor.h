#ifndef PROCESSOR_H
#define PROCESSOR_H

#include <QObject>
#include <QString>

class QNetworkAccessManager;
class QNetworkReply;

class Processor : public QObject
{
    Q_OBJECT
public:
    explicit Processor(QObject *parent = 0);
    void printData();
    void saveData();

signals:
    void finishedWork();

public slots:
    void parseJSON(QNetworkReply *response);
    void loadData();

private:
    QString mText;
    int mCount;
    QNetworkAccessManager *mManager;
};

#endif // PROCESSOR_H
