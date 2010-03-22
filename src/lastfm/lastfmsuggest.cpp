#include "lastfmsuggest.h"

// Last.fm images
#define LASTFMIMG  "http://userserve-ak.last.fm/serve/34s/%1"

// Last.fm suggest
#define LASTFMSUGG "http://www.last.fm/search/autocomplete?q=%1&force=1"

LastFmSuggest::LastFmSuggest(QLineEdit *parent): QObject(parent), editor(parent)
{
    popup = new QTreeWidget;
    popup->setWindowFlags(Qt::Popup);
    popup->setFocusPolicy(Qt::NoFocus);
    popup->setFocusProxy(parent);
    popup->setMouseTracking(true);

    popup->setColumnCount(3);
    popup->setUniformRowHeights(true);
    popup->setRootIsDecorated(false);
    popup->setEditTriggers(QTreeWidget::NoEditTriggers);
    popup->setSelectionBehavior(QTreeWidget::SelectRows);
    popup->setFrameStyle(QFrame::Box | QFrame::Plain);
    popup->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    popup->header()->hide();

    popup->installEventFilter(this);

    connect(popup, SIGNAL(itemClicked(QTreeWidgetItem*,int)),
            SLOT(doneCompletion()));

    timer = new QTimer(this);
    timer->setSingleShot(true);
    timer->setInterval(500);
    connect(timer, SIGNAL(timeout()), SLOT(autoSuggest()));
    connect(editor, SIGNAL(textEdited(QString)), timer, SLOT(start()));

    connect(&networkManager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(handleNetworkData(QNetworkReply*)));

}

LastFmSuggest::~LastFmSuggest()
{
    delete popup;
}

bool LastFmSuggest::eventFilter(QObject *obj, QEvent *ev)
{
    if (obj != popup)
        return false;

    if (ev->type() == QEvent::MouseButtonPress) {
        popup->hide();
        editor->setFocus();
        return true;
    }

    if (ev->type() == QEvent::KeyPress) {

        bool consumed = false;
        int key = static_cast<QKeyEvent*>(ev)->key();
        switch (key) {
        case Qt::Key_Enter:
        case Qt::Key_Return:
            doneCompletion();
            consumed = true;

        case Qt::Key_Escape:
            editor->setFocus();
            popup->hide();
            consumed = true;

        case Qt::Key_Up:
        case Qt::Key_Down:
        case Qt::Key_Home:
        case Qt::Key_End:
        case Qt::Key_PageUp:
        case Qt::Key_PageDown:
            break;

        default:
            editor->setFocus();
            editor->event(ev);
            popup->hide();
            break;
        }

        return consumed;
    }

    return false;
}

void LastFmSuggest::showCompletion(const QStringList &artists, const QStringList &images, const QStringList &albums, const QStringList &tracks, const QStringList &restypes)
{

    if (artists.isEmpty() || artists.count() != images.count())
        return;

    popup->setUpdatesEnabled(false);
    popup->clear();
    titles.clear();

    for (int i = 0; i < artists.count(); ++i) {
        QTreeWidgetItem * item;
        item = new QTreeWidgetItem(popup);

        //item->setIcon(0,QIcon(":/resources/Badge.png"));

        //item->setText(1, artists[i]);

        imgLoader *art = new imgLoader();
        popup->setItemWidget(item,0,art);
        art->loadImage( QString(LASTFMIMG).arg(images[i]) );

        title *tit = new title();
        titles.append( tit );
        popup->setItemWidget(item,1,tit);
        tit->setInfo( artists[i], albums[i], tracks[i], restypes[i] );
    }

    popup->setCurrentItem(popup->topLevelItem(0));
    popup->resizeColumnToContents(0);
    popup->resizeColumnToContents(1);
    popup->adjustSize();
    popup->setUpdatesEnabled(true);

    int h = popup->sizeHintForRow(0) * qMin(7, artists.count()) + 3;
    popup->resize(popup->width(), h);

    popup->move(editor->mapToGlobal(QPoint(0, editor->height())));
    popup->setFocus();
    popup->show();
}

void LastFmSuggest::doneCompletion()
{
    timer->stop();
    popup->hide();
    editor->setFocus();

    QTreeWidgetItem *item = popup->currentItem();
    int ind = popup->indexOfTopLevelItem(item);
    if (item) {
        editor->setText( titles.at(ind)->getText() );
        QMetaObject::invokeMethod(editor, "returnPressed");
    }

}

void LastFmSuggest::autoSuggest()
{
    QString str = editor->text();
    //QString url = QString(GSUGGEST_URL).arg(str);
    QString url = QString(LASTFMSUGG).arg(str);
    networkManager.get(QNetworkRequest(QString(url)));
}

void LastFmSuggest::preventSuggest()
{
    timer->stop();
}

void LastFmSuggest::handleNetworkData(QNetworkReply *networkReply)
{
    QUrl url = networkReply->url();
    if (!networkReply->error()) {

        QStringList artists;
        QStringList images;
        QStringList albums;
        QStringList tracks;
        QStringList restypes;

        int i = -1;
        bool canFillLists = false,
            isFillOpen = false;

        QByteArray response(networkReply->readAll());
        THJsonStreamReader reader( response );
        while (!reader.atEnd()) {
                switch (reader.readNext()) {
                        case THJsonStreamReader::NoToken:
                                break;
                        case THJsonStreamReader::Invalid:
                                break;
                        case THJsonStreamReader::PropertyNumerical:
                                if(canFillLists){
                                    if(reader.name() == "restype" )
                                        if( reader.value().toInt() == 32 ) { // Tag
                                            i--;
                                        } else {
                                            restypes.append( reader.value().toString() );
                                        }
                                }
                                break;
                        case THJsonStreamReader::PropertyString:
                                if(canFillLists){

                                    if(reader.name() == "artist" )
                                            artists.append( QString::fromUtf8( reader.value().toByteArray() ) );
                                    if(reader.name() == "image" )
                                            images.append(  reader.value().toString() );
                                    if(reader.name() == "album" )
                                            albums.append(  QString::fromUtf8( reader.value().toByteArray() ) );
                                    if(reader.name() == "track" )
                                            tracks.append(  QString::fromUtf8( reader.value().toByteArray() ) );

                                }
                                break;
                        case THJsonStreamReader::PropertyFalse:
                                break;
                        case THJsonStreamReader::PropertyTrue:
                                break;
                        case THJsonStreamReader::PropertyNull:
                                break;
                        case THJsonStreamReader::Object:
                                if(canFillLists && !isFillOpen){
                                    i++;
                                    isFillOpen = true;
                                }
                                break;
                        case THJsonStreamReader::ObjectEnd:
                                if(canFillLists && isFillOpen){

                                    while( artists.count() <= i)
                                        artists << "";
                                    while( images.count() <= i)
                                        images << "";
                                    while( albums.count() <= i)
                                        albums << "";
                                    while( tracks.count() <= i)
                                        tracks << "";
                                    while( restypes.count() <= i)
                                        restypes << "0";

                                    isFillOpen = false;
                                }
                                break;
                        case THJsonStreamReader::Array:
                                canFillLists = true;
                                break;
                        case THJsonStreamReader::ArrayEnd:
                                canFillLists = false;
                                break;
                }
        }

        showCompletion(artists, images, albums, tracks, restypes);
    }

    networkReply->deleteLater();
}
