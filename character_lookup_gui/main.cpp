#include "mainwindow.h"
#include <QApplication>
#include <QNetworkAccessManager>
#include <QUrl>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>
#include <QFile>
#include <QNetworkReply>
#include <mywindow.h>



int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    /* Handle Command-line arguments
     * arguments[0] : Filepath to image
     * arguments[1] : Title of Movie or Series
     * arguments[2] (Optional) : Season
     * arguments[3] (Optional) : Episode
     */
    QStringList arguments = app.arguments();



    MyWindow w;
    w.show();

    return app.exec();

}

