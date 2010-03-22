#ifndef LEFTPANEL_H
#define LEFTPANEL_H

#include <QtGui>
#include <QWidget>
#include <QGridLayout>
#include <QtNetwork>
#include <QObject>
#include <QLabel>
#include <QPainter>

#include "../lastfm/imgloader.h"
#include "../lastfm/title.h"

QT_BEGIN_NAMESPACE
class QNetworkReply;
class QTreeWidget;
QT_END_NAMESPACE

class leftpanel : public QWidget
{
Q_OBJECT
public:
    leftpanel(QWidget *parent = 0);
    virtual QSize sizeHint() const;

public slots:
    void handleNetworkData(QNetworkReply *networkReply);

protected:
    QTreeWidget* tree;
    void addItem();

private:
    int width;
    int height;
    QList<title *> titles;
    QNetworkAccessManager networkManager;

};

#endif // LEFTPANEL_H
