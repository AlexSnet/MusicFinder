#include "leftpanel.h"

leftpanel::leftpanel(QWidget *parent) :
    QWidget(parent)
{
    // Main Layout
    tree = new QTreeWidget(this);
    tree->setFocusPolicy(Qt::NoFocus);
    tree->setMouseTracking(true);

    tree->setColumnCount(2);
    tree->setUniformRowHeights(true);
    tree->setRootIsDecorated(false);
    tree->setEditTriggers(QTreeWidget::NoEditTriggers);
    tree->setSelectionBehavior(QTreeWidget::SelectRows);
    tree->setFrameStyle(QFrame::Box | QFrame::Plain);
    tree->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    tree->header()->hide();

    for( int i = 0; i<200; i++)
        addItem();

}

void leftpanel::addItem()
{
    QTreeWidgetItem * item;
    item = new QTreeWidgetItem(tree);

    imgLoader *art = new imgLoader();
    tree->setItemWidget(item,0,art);
    art->loadImage( QString("http://a1.twimg.com/profile_images/280171506/noIE_normal.png") );

    title *tit = new title();
    titles.append( tit );
    tree->setItemWidget(item,1,tit);
    tit->setInfo( "" , "", "", "" );
}

QSize leftpanel::sizeHint() const
{
    return tree->sizeHint();
}

void leftpanel::handleNetworkData(QNetworkReply *networkReply)
{
    QUrl url = networkReply->url();
    if (!networkReply->error()) {

    }
    networkReply->deleteLater();
}
