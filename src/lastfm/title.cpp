#include "title.h"

title::title(QWidget* parent)
    : QWidget(parent)
{
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    setFocusPolicy(Qt::NoFocus);

    setMinimumSize(width, height);
    setMaximumSize(width, height);
    resize(width, height);

    // Main layout
    layout = new QGridLayout(this);
    layout->setMargin(0);
}

QSize title::sizeHint() const
{
    return QSize(width,height);
}

QString title::getText(){
    if( irestype == "6" ) { // Artist
        return QString( iartist );
    }
    if( irestype == "8" ) { // Album
        return QString( iartist + " - " + ialbum );
    }
    if( irestype == "9" ) { // Track
        return QString( iartist + " - " + itrack );
    }
    return QString("");
}

void title::setInfo(const QString artist, const QString album, const QString track, const QString restype)
{
    iartist = artist;
    ialbum = album;
    itrack = track;
    irestype = restype;

    if( restype == "6" ) { // Artist
        QLabel *aRt = new QLabel(artist);
        aRt->setMargin(10);
        aRt->setStyleSheet("color:black;font-weight:bold;font-size:12px;");

        layout->addWidget( aRt ,0,0,0,0, Qt::AlignLeft | Qt::AlignVCenter );
    }
    if( restype == "8" ) { // Album
        QLabel *aRt = new QLabel(artist);
        aRt->setMargin(10);
        aRt->setStyleSheet("color:gray;font-size:10px;padding:0;");

        QLabel *aLb = new QLabel(album);
        aLb->setMargin(10);
        aLb->setStyleSheet("color:black;font-weight:bold;font-size:12px;");

        layout->addWidget( aLb, 0,0,0,0, Qt::AlignLeft | Qt::AlignTop );
        layout->addWidget( aRt, 0,0,0,0, Qt::AlignLeft | Qt::AlignBottom );
    }
    if( restype == "9" ) { // Track
        QLabel *aRt = new QLabel(artist);
        aRt->setMargin(10);
        aRt->setStyleSheet("color:gray;font-size:10px;padding:0;");

        QLabel *tRk = new QLabel(track);
        tRk->setMargin(10);
        tRk->setStyleSheet("color:black;font-weight:bold;font-size:12px;");

        layout->addWidget( tRk, 0,0,0,0, Qt::AlignLeft | Qt::AlignTop );
        layout->addWidget( aRt, 0,0,0,0, Qt::AlignLeft | Qt::AlignBottom );
    }
}
