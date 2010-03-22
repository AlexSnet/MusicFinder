#include "imgloader.h"

imgLoader::imgLoader(QWidget* parent)
    : QWidget(parent)
{
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    setFocusPolicy(Qt::NoFocus);

    setSize( QSize(40,38) );

    // Main layout
    layout = new QGridLayout(this);
    // Process indicator
    pin = new QProgressIndicator(this);
    plb = new QLabel();
    plb->setMargin(0);
    // Image loader
    connect(&networkManager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(handleNetworkData(QNetworkReply*)));
}

void imgLoader::setSize( QSize size )
{
    setMinimumSize( size.width(), size.height() );
    setMaximumSize( size.width(), size.height() );
    resize( size.width(), size.height() );
    width = size.width();
    height = size.height();
}

void imgLoader::loadImage(QString url)
{
    initIndicator();
    networkManager.get(QNetworkRequest(QString(url)));
}

void imgLoader::initIndicator()
{
    layout->addWidget(pin,0,0,0,0,Qt::AlignCenter);
    layout->setContentsMargins(0,0,0,0);
    pin->startAnimation();
}

QSize imgLoader::sizeHint() const
{
    return QSize(width,height);
}

void imgLoader::paintEvent(QPaintEvent * /*event*/)
{

}

void imgLoader::handleNetworkData(QNetworkReply *networkReply)
{
    QUrl url = networkReply->url();
    QPixmap cover;
    pix = QPixmap(width-6,height-6);

    if (!networkReply->error()) {
        QByteArray response(networkReply->readAll());
        cover.loadFromData(response);
    } else {
        cover.load(":/resources/noimage.jpg");
    }

    QPainter p(&pix);
    QPixmap jew(":/resources/cdjewel.png");

    //p.drawPixmap(x,y,w,h,QPixmap);
    p.drawPixmap(0,0,pix.width(),pix.height(), cover);
    p.drawPixmap(0,0,pix.width(),pix.height(), jew);

    plb->setPixmap(pix);
    layout->removeWidget(pin);

    layout->addWidget( plb ,0,0,0,0,Qt::AlignCenter);

    networkReply->deleteLater();
}
