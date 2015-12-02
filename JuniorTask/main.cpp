#include <QCoreApplication>
#include <QTimer>
#include "processor.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Processor proc;

    QObject::connect(&proc, SIGNAL(finishedWork()), &a, SLOT(quit()));
    QTimer::singleShot(0, &proc, SLOT(loadData()));

    return a.exec();
}

