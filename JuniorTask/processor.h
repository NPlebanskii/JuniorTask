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

private:
    void printData();
    void saveData();

signals:
    /*!
     * \brief finishedWork Emitted when all work is done
     */
    void finishedWork();

public slots:
    /*!
     * \brief parseJSON Parses JSON object, saves parsed object in members
     *  of class
     * \param response Response from server
     */
    void parseJSON(QNetworkReply *response);
    /*!
     * \brief loadData Loads data from server\register
     */
    void loadData();

private:
    QString mText;
    int mCount;
    QNetworkAccessManager *mManager;
};

#endif // PROCESSOR_H
