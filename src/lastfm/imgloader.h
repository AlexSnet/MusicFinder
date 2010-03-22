#ifndef IMGLOADER_H
#define IMGLOADER_H

#include <QWidget>
#include <QGridLayout>
#include <QtNetwork>
#include <QObject>
#include <QLabel>
#include <QPainter>

QT_BEGIN_NAMESPACE
class QNetworkReply;
QT_END_NAMESPACE

#include "../3tdparty/QProgressIndicator/QProgressIndicator.h"

class imgLoader : public QWidget
{
    Q_OBJECT

public:
    imgLoader(QWidget* parent = 0);
    void setSize( QSize size );
    virtual QSize sizeHint() const;
    void loadImage(QString url);

public slots:
    void handleNetworkData(QNetworkReply *networkReply);

protected:
    QGridLayout* layout;
    QProgressIndicator* pin;
    QPixmap pix;
    QLabel* plb;
    virtual void paintEvent(QPaintEvent * event);

private:
    int width;
    int height;
    QNetworkAccessManager networkManager;
    void initIndicator();
};

#endif // IMGLOADER_H
