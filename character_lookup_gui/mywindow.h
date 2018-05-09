#ifndef MYWINDOW_H
#define MYWINDOW_H

#include <QWidget>
#include <QNetworkAccessManager>
#include <QUrl>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>
#include <QFile>
#include <QNetworkReply>
#include <QXmlStreamReader>



namespace Ui {
class MyWindow;
}

class MyWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MyWindow(QWidget *parent = 0);
    ~MyWindow();
    void httpStuff(QString filepath);
    QJsonDocument getFaceDetectOptions(QString filepath);
    QJsonDocument getWebDetectOptions(QString filepath);
    QJsonObject setRequestJson(QString filepath);
    QString faceOptions;
    QString webOptions;
    QString requestOptions;
    QString imageFileToBase64(QString filepath);

    QString getActorName(QJsonDocument response);
private slots:
    void httpFinished();
    void on_pushButton_clicked();

    void tmdbFinished();
    void castListFinished();
    void wikiFinished();
private:
    Ui::MyWindow *ui;

    //Http Variables
    QNetworkAccessManager httpManager;
    QNetworkReply *reply;

    // UI related strings and images
    QString characterName;
    QString actorName;
    QString wikiText;
    QPixmap image;




    void getTMDBData(QString mediaName);
    void getCastList(int id, QString mediaType);
    void parseTMDBData(QJsonObject json);
    void getWikiData(QString name);
    QString getCharacterName(QString name, QJsonArray cast);
    QString stripHtml(QString text);
};

#endif // MYWINDOW_H
