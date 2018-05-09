#include "mywindow.h"
#include "ui_mywindow.h"

MyWindow::MyWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MyWindow), httpManager()
{
    // TODO : MAKE THESE CONSTANTS

    faceOptions = QString("{\"requests\":[{\"image\":{\"content\":\"\"},\"features\":[{\"type\":\"FACE_DETECTION\",\"maxResults\":4}]}]}");
    webOptions = QString("{\"requests\":[{\"image\":{\"content\":\"\"},\"features\":[{\"type\":\"WEB_DETECTION\",\"maxResults\":1}]}]}");
    requestOptions = QString("{\"image\":{\"content\":\"\"},\"features\":[{\"type\":\"WEB_DETECTION\",\"maxResults\":1}]}");
    ui->setupUi(this);


    QPixmap img("/home/eece435l/EECE437/Individual_Project/test_image.jpeg");
    ui->verticalLayout->setAlignment(Qt::AlignCenter);
    ui->imageLabel->setPixmap(img);
    ui->imageLabel->setAlignment(Qt::AlignCenter);

    wikiText = "Wikipedia Page not Available.";
    ui->wikiLabel->setWordWrap(true);
    ui->wikiLabel->setText(stripHtml("<div><b>Arya Stark</b> is a <a href=\"/wiki/Fictional_character\" class=\"mw-redirect\" title=\"Fictional character\">fictional character</a> in American author <a href=\"/wiki/George_R._R._Martin\" title=\"George R. R. Martin\">George R. R. Martin</a>'s award-winning <i><a href=\"/wiki/A_Song_of_Ice_and_Fire\" title=\"A Song of Ice and Fire\">A Song of Ice and Fire</a></i> <a href=\"/wiki/Epic_fantasy\" class=\"mw-redirect\" title=\"Epic fantasy\">epic fantasy</a> novel series. She is a prominent <a href=\"/wiki/Narrative_mode#Third-person_view\" class=\"mw-redirect\" title=\"Narrative mode\">point of view</a> character in the novels, with the third most viewpoint chapters overall out of all the characters in the series so far, and is the only viewpoint character to appear in every published book of the series.\\n\\nIntroduced in 1996's <i><a href=\"/wiki/A_Game_of_Thrones\" title=\"A Game of Thrones\">A Game of Thrones</a></i>, Arya is the younger daughter and third child of Lord <a href=\"/wiki/Ned_Stark\" title=\"Ned Stark\">Eddard Stark</a> and his wife Lady <a href=\"/wiki/Catelyn_Stark\" title=\"Catelyn Stark\">Catelyn Stark</a>. She is <a href=\"/wiki/Tomboy\" title=\"Tomboy\">tomboyish</a>, headstrong, feisty, independent, disdains traditional female pursuits, and is often mistaken for a boy. She wields a <a href=\"/wiki/Smallsword\" class=\"mw-redirect\" title=\"Smallsword\">smallsword</a> named Needle, a gift from her half-brother, <a href=\"/wiki/Jon_Snow_(character)\" title=\"Jon Snow (character)\">Jon Snow</a>, and is trained in the Braavosi style of sword fighting by Syrio Forel.\\n\\nArya is portrayed by <a href=\"/wiki/Maisie_Williams\" title=\"Maisie Williams\">Maisie Williams</a> in <a href=\"/wiki/HBO\" title=\"HBO\">HBO</a>'s <a href=\"/wiki/Emmy\" class=\"mw-redirect\" title=\"Emmy\">Emmy</a>-winning television adaptation of the novel series, <i><a href=\"/wiki/Game_of_Thrones\" title=\"Game of Thrones\">Game of Thrones</a></i>.<sup id=\"cite_ref-1\" class=\"reference\"><a href=\"#cite_note-1\">[1]</a></sup><sup id=\"cite_ref-\\&quot;From_2-0\" class=\"reference\"><a href=\"#cite_note-\\&quot;From-2\">[2]</a></sup> Her performance has garnered critical acclaim, particularly in the <a href=\"/wiki/Game_of_Thrones_(season_2)\" title=\"Game of Thrones (season 2)\">second season</a> for her work opposite veteran actor <a href=\"/wiki/Charles_Dance\" title=\"Charles Dance\">Charles Dance</a> (<a href=\"/wiki/Tywin_Lannister\" title=\"Tywin Lannister\">Tywin Lannister</a>) when she served as his cupbearer.<sup id=\"cite_ref-3\" class=\"reference\"><a href=\"#cite_note-3\">[3]</a></sup> She is among the most popular characters in either version of the story.<sup id=\"cite_ref-4\" class=\"reference\"><a href=\"#cite_note-4\">[4]</a></sup><sup id=\"cite_ref-\\&quot;Rolling_5-0\" class=\"reference\"><a href=\"#cite_note-\\&quot;Rolling-5\">[5]</a></sup> Williams was nominated for a <a href=\"/wiki/Primetime_Emmy_Award\" title=\"Primetime Emmy Award\">Primetime Emmy Award</a> for <a href=\"/wiki/Primetime_Emmy_Award_for_Outstanding_Supporting_Actress_in_a_Drama_Series\" title=\"Primetime Emmy Award for Outstanding Supporting Actress in a Drama Series\">Outstanding Supporting Actress in a Drama Series</a> for the role in 2016.<sup id=\"cite_ref-\\&quot;2016Emmy\\&quot;_6-0\" class=\"reference\"><a href=\"#cite_note-\\&quot;2016Emmy\\&quot;-6\">[6]</a></sup> She and the rest of the cast were nominated for <a href=\"/wiki/Screen_Actors_Guild_Award\" title=\"Screen Actors Guild Award\">Screen Actors Guild Awards</a> for <a href=\"/wiki/Screen_Actors_Guild_Award_for_Outstanding_Performance_by_an_Ensemble_in_a_Drama_Series\" title=\"Screen Actors Guild Award for Outstanding Performance by an Ensemble in a Drama Series\">Outstanding Performance by an Ensemble in a Drama Series</a> in 2012, 2014, 2015 and 2016.</p>\n<div class=\"mw-references-wrap\">\n<ol class=\"references\">\n<li id=\"cite_note-1\"><span class=\"mw-cite-backlink\"><b><a href=\"#cite_ref-1\">^</a></b></span> <span class=\"reference-text\"><cite class=\"citation web\"><a rel=\"nofollow\" class=\"external text\" href=\"http://www.hbo.com/game-of-thrones/index.html#/game-of-thrones/cast-and-crew/index.html\">\"Game of Thrones: Cast &amp; Crew\"</a>. <a href=\"/wiki/HBO\" title=\"HBO\">HBO</a><span class=\"reference-accessdate\">. Retrieved <span class=\"nowrap\">June 6,</span> 2012</span>.</cite><span title=\"ctx_ver=Z39.88-2004&amp;rft_val_fmt=info%3Aofi%2Ffmt%3Akev%3Amtx%3Abook&amp;rft.genre=unknown&amp;rft.btitle=Game+of+Thrones%3A+Cast+%26+Crew&amp;rft.pub=HBO&amp;rft_id=http%3A%2F%2Fwww.hbo.com%2Fgame-of-thrones%2Findex.html%23%2Fgame-of-thrones%2Fcast-and-crew%2Findex.html&amp;rfr_id=info%3Asid%2Fen.wikipedia.org%3AAPI\" class=\"Z3988\"><span style=\"display:none;\">&#160;</span></span></span></li>\n<li id=\"cite_note-\\&quot;From-2\"><span class=\"mw-cite-backlink\"><b><a href=\"#cite_ref-\\&quot;From_2-0\">^</a></b></span> <span class=\"reference-text\"><cite class=\"citation web\">Martin, George R. R. (July 16, 2010). <a rel=\"nofollow\" class=\"external text\" href=\"https://web.archive.org/web/20160307150640/http://grrm.livejournal.com/164794.html\">\"From HBO\"</a>. Archived from <a rel=\"nofollow\" class=\"external text\" href=\"http://grrm.livejournal.com/164794.html\">the original</a> on March 7, 2016<span class=\"reference-accessdate\">. Retrieved <span class=\"nowrap\">May 28,</span> 2012</span>.</cite><span title=\"ctx_ver=Z39.88-2004&amp;rft_val_fmt=info%3Aofi%2Ffmt%3Akev%3Amtx%3Abook&amp;rft.genre=unknown&amp;rft.btitle=From+HBO&amp;rft.date=2010-07-16&amp;rft.aulast=Martin&amp;rft.aufirst=George+R.+R.&amp;rft_id=http%3A%2F%2Fgrrm.livejournal.com%2F164794.html&amp;rfr_id=info%3Asid%2Fen.wikipedia.org%3AAPI\" class=\"Z3988\"><span style=\"display:none;\">&#160;</span></span></span></li>\n<li id=\"cite_note-3\"><span class=\"mw-cite-backlink\"><b><a href=\"#cite_ref-3\">^</a></b></span> <span class=\"reference-text\"><cite class=\"citation news\"><a rel=\"nofollow\" class=\"external text\" href=\"https://www.rollingstone.com/movies/lists/game-changers-the-10-biggest-changes-between-game-of-thrones-and-the-books-20120515/the-tywin-and-arya-show-19691231\">\"The Tywin and Arya Show\"</a>. <i><a href=\"/wiki/Rolling_Stone_magazine\" class=\"mw-redirect\" title=\"Rolling Stone magazine\">Rolling Stone magazine</a></i>. May 15, 2012<span class=\"reference-accessdate\">. Retrieved <span class=\"nowrap\">May 19,</span> 2013</span>.</cite><span title=\"ctx_ver=Z39.88-2004&amp;rft_val_fmt=info%3Aofi%2Ffmt%3Akev%3Amtx%3Ajournal&amp;rft.genre=article&amp;rft.jtitle=Rolling+Stone+magazine&amp;rft.atitle=The+Tywin+and+Arya+Show&amp;rft.date=2012-05-15&amp;rft_id=https%3A%2F%2Fwww.rollingstone.com%2Fmovies%2Flists%2Fgame-changers-the-10-biggest-changes-between-game-of-thrones-and-the-books-20120515%2Fthe-tywin-and-arya-show-19691231&amp;rfr_id=info%3Asid%2Fen.wikipedia.org%3AAPI\" class=\"Z3988\"><span style=\"display:none;\">&#160;</span></span></span></li>\n<li id=\"cite_note-4\"><span class=\"mw-cite-backlink\"><b><a href=\"#cite_ref-4\">^</a></b></span> <span class=\"reference-text\"><cite class=\"citation web\">Erickson, Christine (June 12, 2014). <a rel=\"nofollow\" class=\"external text\" href=\"http://mashable.com/2014/06/12/most-popular-game-of-thrones-characters/\">\"Ranking the Most Popular Characters in 'Game of Thrones<span style=\"padding-right:0.2em;\">'</span>\"</a>. <i><a href=\"/wiki/Mashable\" title=\"Mashable\">Mashable</a></i>. Mashable.com<span class=\"reference-accessdate\">. Retrieved <span class=\"nowrap\">September 24,</span> 2014</span>.</cite><span title=\"ctx_ver=Z39.88-2004&amp;rft_val_fmt=info%3Aofi%2Ffmt%3Akev%3Amtx%3Ajournal&amp;rft.genre=unknown&amp;rft.jtitle=Mashable&amp;rft.atitle=Ranking+the+Most+Popular+Characters+in+%27Game+of+Thrones%27&amp;rft.date=2014-06-12&amp;rft.aulast=Erickson&amp;rft.aufirst=Christine&amp;rft_id=http%3A%2F%2Fmashable.com%2F2014%2F06%2F12%2Fmost-popular-game-of-thrones-characters%2F&amp;rfr_id=info%3Asid%2Fen.wikipedia.org%3AAPI\" class=\"Z3988\"><span style=\"display:none;\">&#160;</span></span></span></li>\n<li id=\"cite_note-\\&quot;Rolling-5\"><span class=\"mw-cite-backlink\"><b><a href=\"#cite_ref-\\&quot;Rolling_5-0\">^</a></b></span> <span class=\"reference-text\"><cite class=\"citation web\"><a rel=\"nofollow\" class=\"external text\" href=\"https://www.rollingstone.com/tv/lists/top-40-game-of-thrones-characters-ranked-20140331\">\"Top 40 'Game of Thrones' Characters, Ranked\"</a>. <i><a href=\"/wiki/Rolling_Stone\" title=\"Rolling Stone\">Rolling Stone</a></i>. <a href=\"/wiki/Jann_Wenner\" title=\"Jann Wenner\">Jann Wenner</a>. March 31, 2014<span class=\"reference-accessdate\">. Retrieved <span class=\"nowrap\">September 24,</span> 2014</span>.</cite><span title=\"ctx_ver=Z39.88-2004&amp;rft_val_fmt=info%3Aofi%2Ffmt%3Akev%3Amtx%3Ajournal&amp;rft.genre=unknown&amp;rft.jtitle=Rolling+Stone&amp;rft.atitle=Top+40+%27Game+of+Thrones%27+Characters%2C+Ranked&amp;rft.date=2014-03-31&amp;rft_id=https%3A%2F%2Fwww.rollingstone.com%2Ftv%2Flists%2Ftop-40-game-of-thrones-characters-ranked-20140331&amp;rfr_id=info%3Asid%2Fen.wikipedia.org%3AAPI\" class=\"Z3988\"><span style=\"display:none;\">&#160;</span></span></span></li>\n<li id=\"cite_note-\\&quot;2016Emmy\\&quot;-6\"><span class=\"mw-cite-backlink\"><b><a href=\"#cite_ref-\\&quot;2016Emmy\\&quot;_6-0\">^</a></b></span> <span class=\"reference-text\"><cite class=\"citation web\">Rice, Lynette (July 14, 2016). <a rel=\"nofollow\" class=\"external text\" href=\"http://www.ew.com/article/2016/07/14/emmys-nominations-2016\">\"Emmy nominations 2016: See the full list\"</a>. <i>Entertainment Weekly</i><span class=\"reference-accessdate\">. Retrieved <span class=\"nowrap\">July 14,</span> 2016</span>.</cite><span title=\"ctx_ver=Z39.88-2004&amp;rft_val_fmt=info%3Aofi%2Ffmt%3Akev%3Amtx%3Ajournal&amp;rft.genre=unknown&amp;rft.jtitle=Entertainment+Weekly&amp;rft.atitle=Emmy+nominations+2016%3A+See+the+full+list&amp;rft.date=2016-07-14&amp;rft.aulast=Rice&amp;rft.aufirst=Lynette&amp;rft_id=http%3A%2F%2Fwww.ew.com%2Farticle%2F2016%2F07%2F14%2Femmys-nominations-2016&amp;rfr_id=info%3Asid%2Fen.wikipedia.org%3AAPI\" class=\"Z3988\"><span style=\"display:none;\">&#160;</span></span></span></li>\n</ol>\n</div>\n\n\n<!-- \nNewPP limit report\nParsed by mw1344\nCached time: 20180509044707\nCache expiry: 1900800\nDynamic content: false\nCPU time usage: 0.080 seconds\nReal time usage: 0.097 seconds\nPreprocessor visited node count: 280/1000000\nPreprocessor generated node count: 0/1500000\nPost‐expand include size: 9415/2097152 bytes\nTemplate argument size: 104/2097152 bytes\nHighest expansion depth: 12/40\nExpensive parser function count: 1/500\nUnstrip recursion depth: 0/20\nUnstrip post‐expand size: 604/5000000 bytes\nLua time usage: 0.036/10.000 seconds\nLua memory usage: 2.57 MB/50 MB\n-->\n<!--\nTransclusion expansion time report (%,ms,calls,template)\n100.00%   84.054      1 -total\n 54.57%   45.866      5 Template:Cite_web\n 29.96%   25.185      1 Template:Use_mdy_dates\n 11.89%    9.992      1 Template:DMCA\n 10.00%    8.404      1 Template:Dated_maintenance_category\n  6.79%    5.705      1 Template:FULLROOTPAGENAME\n  5.82%    4.890      1 Template:Cite_news\n  4.76%    4.004      1 Template:Ns_has_subpages\n  1.14%    0.956      1 Template:Infobox_character\\n\n-->\n</div>"));

    httpStuff(QString("/home/eece435l/EECE437/Individual_Project/test_image.jpeg"));

}

QString MyWindow::stripHtml(QString  text)
{
    QXmlStreamReader xml(text);
    QString newtext = "";
    while (!xml.atEnd()) {
        if ( xml.readNext() == QXmlStreamReader::Characters ) {
            newtext += xml.text();
        }
    }
    return newtext;
}

MyWindow::~MyWindow()
{
    delete ui;
//    delete reply;
    httpManager.deleteLater();
}

/*
 *  Takes in the path to an image and returns the image as a base64-encoded string
 *  Used to send the image to the Google Cloud Vision API
 */
QString MyWindow::imageFileToBase64(QString filepath)
{
    QFile* file = new QFile(filepath);
    file->open(QIODevice::ReadOnly);
    QByteArray image = file->readAll();

    QString encoded = QString(image.toBase64());
    return encoded;
}


QJsonObject MyWindow::setRequestJson(QString filepath)
{
    QJsonDocument json = QJsonDocument::fromJson(requestOptions.toUtf8());
    QJsonObject object= json.object();
    QJsonObject imageObject;
    QString image = imageFileToBase64(filepath);
    imageObject.insert("content", QJsonValue(image));
    object.insert("image", QJsonValue(imageObject));
    return object;

}

// TODO: Refactor these into one function that takes detection type as a paramater

QJsonDocument MyWindow::getFaceDetectOptions(QString filepath)
{
    QJsonDocument faceDetectOptions = QJsonDocument::fromJson(faceOptions.toUtf8());
    QJsonObject object = faceDetectOptions.object();
    QJsonArray requests;
    requests.append(QJsonValue(setRequestJson(filepath)));
    object.insert("requests", QJsonValue(requests));
    faceDetectOptions.setObject(object);
    return faceDetectOptions;

}

QJsonDocument MyWindow::getWebDetectOptions(QString filepath)
{
    QJsonDocument webDetectOptions = QJsonDocument::fromJson(webOptions.toUtf8());
    QJsonObject object = webDetectOptions.object();
    QJsonArray requests;
    requests.append(QJsonValue(setRequestJson(filepath)));
    object.insert("requests", QJsonValue(requests));
    webDetectOptions.setObject(object);
    return webDetectOptions;

}

// TODO: Refactor all the http request functions so that I have on general purpose function where I give it a link and a callback

// Very Temporary function to figure out http stuff
void MyWindow::httpStuff(QString filepath)
{
    QUrl url("https://vision.googleapis.com/v1/images:annotate?key=AIzaSyAXZPVTxMkXOUNm735BRKK4_EKApSV0qwA");

    QNetworkRequest req(url);

    req.setRawHeader("Content-Type", "application/json");
    reply = httpManager.post(req, getWebDetectOptions(filepath).toJson());

    connect(reply, &QNetworkReply::finished, this, &MyWindow::httpFinished);
    //qDebug() << QString(reply->readAll());

    //while(reply->isRunning()) {}


}

// Parses a JSON response from Google Cloud Vision Api and retrieves the best estimate of the
// actor (or character)
QString MyWindow::getActorName(QJsonDocument response)
{
    QJsonArray array =response.object()["responses"].toArray();
    QJsonObject result =array[0].toObject()["webDetection"].toObject()["webEntities"].toArray()[0].toObject();
    QString name = result["description"].toString();

    actorName = name;
    ui->actorLabel->setText("Portrayed By:  " + actorName);

    return name;

}

// Gets the wikiepdia page content of the character in question
// Used MediaWiki REST Api
// Currently only works if the character has their own wikipedia page
// TODO: Use search and get page info of top result for characters that only have sections
// in ther pages
void MyWindow::getWikiData(QString name)
{
    QString urlString= "https://wikipedia.org/w/api.php?action=query&format=json&prop=revisions&rvprop=content&titles=" + name ;
    QUrl url(urlString);
    reply = httpManager.get(QNetworkRequest(url));
    connect(reply, &QNetworkReply::finished, this, &MyWindow::wikiFinished);
}

void MyWindow::wikiFinished()
{
    disconnect(reply, &QNetworkReply::finished, this, &MyWindow::wikiFinished);
    reply->deleteLater();

}

// Gets tmdb cast list from tmdb id and mediaType
// Uses TMDB Api
void MyWindow::getCastList(int id, QString mediaType)
{
    // TODO: Make a static constant
    QString apiKey("f48f8706be43280f7a6e97457bfa4f20");
    QString urlString = "https://api.themoviedb.org/3/" + mediaType + "/" + QString::number(id) +  "/credits?api_key=" + apiKey;
    QUrl url(urlString);
    reply = httpManager.get(QNetworkRequest(url));
    connect(reply, &QNetworkReply::finished, this, &MyWindow::castListFinished);
}
// Gets Character Name from TMDB cast JSON object and actor (or character) name
QString MyWindow::getCharacterName(QString name, QJsonArray cast)
{
    //TODO: Use iterator instead
    QJsonObject info;
    //qDebug() << cast;
    for (int i = 0; i < cast.size(); i++)
    {
        info = cast.at(i).toObject();

        if (info["name"].toString() == name || info["character"].toString() == name) break;
    }
    //SUPER temporary right here. TODO: CHANGE
    characterName = info["character"].toString();
    ui->characterLabel->setText("Character:  "+characterName);
    return info["character"].toString();
}

void MyWindow::castListFinished()
{
    disconnect(reply, &QNetworkReply::finished, this, &MyWindow::castListFinished);
    QJsonDocument json = QJsonDocument::fromJson(reply->readAll());
    getCharacterName(actorName, json.object()["cast"].toArray());
    reply->deleteLater();


}

// Gets TMDB id and media_type from name of movie or show
void MyWindow::getTMDBData(QString mediaName)
{
    // TODO: Make a static constant
    QString apiKey("f48f8706be43280f7a6e97457bfa4f20");
    QString urlString = "https://api.themoviedb.org/3/search/multi?api_key=" + apiKey + "&query=" + mediaName;
    QUrl url(urlString);
    reply = httpManager.get(QNetworkRequest(url));
    connect(reply, &QNetworkReply::finished, this, &MyWindow::tmdbFinished);
}

//TODO: Split this into two functions. one that returns id and one that returns media_type and then call both from tmdbFinished
// and call next function from there instead of doing it from here. Or change the name.

//TODO: Handle case where no result is found here.

void MyWindow::parseTMDBData(QJsonObject json)
{
    QJsonObject result = json["results"].toArray()[0].toObject();
    int id = result["id"].toInt();
    QString mediaType = result["media_type"].toString();
    getCastList(id, mediaType);

}

void MyWindow::tmdbFinished()
{
    disconnect(reply, &QNetworkReply::finished, this, &MyWindow::tmdbFinished);
    QJsonDocument json = QJsonDocument::fromJson(reply->readAll());
    reply->deleteLater();
    parseTMDBData(json.object());


}

void MyWindow::httpFinished()
{
    disconnect(reply, &QNetworkReply::finished, this, &MyWindow::httpFinished);
    QJsonDocument json = QJsonDocument::fromJson(reply->readAll());

    reply->deleteLater();
    getActorName(json);
    getTMDBData("Game of Thrones");


}

//void MyWindow::loadImage(QString filepath, QPixmap & image)
//{
//    image.load(filepath);

//}

void MyWindow::on_pushButton_clicked()
{
    //qDebug() <<QString(reply->readAll());
}
