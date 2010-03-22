#ifndef LASTFMSUGGEST_H
#define LASTFMSUGGEST_H

#include <QtGui>
#include <QtNetwork>
#include <QObject>

QT_BEGIN_NAMESPACE
class QLineEdit;
class QNetworkReply;
class QTimer;
class QTreeWidget;
QT_END_NAMESPACE

#include "imgloader.h"
#include "title.h"
#include "../3tdparty/jsonstreamreader/jsonstreamreader.h"


class LastFmSuggest : public QObject
{
        Q_OBJECT
public:
    LastFmSuggest(QLineEdit *parent = 0);
    ~LastFmSuggest();
    bool eventFilter(QObject *obj, QEvent *ev);
    void showCompletion(const QStringList &artists, const QStringList &images, const QStringList &albums, const QStringList &tracks, const QStringList &restypes);

public slots:
    void doneCompletion();
    void preventSuggest();
    void autoSuggest();
    void handleNetworkData(QNetworkReply *networkReply);

private:
    QLineEdit *editor;
    QTreeWidget *popup;
    QTimer *timer;
    QNetworkAccessManager networkManager;
    QList<title *> titles;
};

#endif // LASTFMSUGGEST_H
