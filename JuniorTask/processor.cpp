#include "processor.h"
#include <QtNetwork>
#include <QSettings>
#include <QVariant>
#include <iostream>

Processor::Processor(QObject *parent) :
    QObject(parent)
   ,mManager{nullptr}
{
}

// Prints out mText by mCount times
void Processor::printData()
{
    std::cout << "Printing information:" << std::endl;
    for(int i = 0; i < mCount; i++)
    {
        std::cout << mText.toStdString() << std::endl;
    }
    emit finishedWork();
}

// Saves mText and mCount to specified register
void Processor::saveData()
{
    QSettings settings("HKEY_CURRENT_USER\\Software\\Test",
                       QSettings::NativeFormat);
    settings.setValue("text", mText);
    settings.setValue("count", mCount);
}

// Loads data for mText and mCount
void Processor::loadData()
{
    QSettings settings("HKEY_CURRENT_USER\\Software\\Test",
                       QSettings::NativeFormat);
    // Checking, if application is running for the forst time
    if(settings.contains("text") && settings.contains("count"))
    {
        std::cout << "Loading data from register..." << std::endl;
        mText = settings.value("text").toString();
        mCount = settings.value("count").toInt();
        printData();
    }
    else
    {
        mManager = new QNetworkAccessManager(this);
        connect(mManager, SIGNAL(finished(QNetworkReply*)),
                this, SLOT(parseJSON(QNetworkReply*)));
        std::cout << "Loading object from server..." << std::endl;
        mManager->get(QNetworkRequest(QUrl("http://dev.smartpelican.com/"
                                           "public/test_task/cpp.json")));
    }
}

// Parses JSON object, saves parsed object in members of class,
// saves members to register and prints out members
void Processor::parseJSON(QNetworkReply* response)
{
    QByteArray data;
    if(response->isReadable())
    {
        data = response->readAll();
    }
    delete response;

    QJsonDocument jsonDoc = QJsonDocument::fromJson(data);
    if(jsonDoc.isObject())
    {
        mText = jsonDoc.object()["text"].toString();
        mCount = jsonDoc.object()["count"].toInt();
    }
    else
    {
        std::cout << "Gotten reply is not an object." << std::endl;
    }

    saveData();
    printData();
}
