#include <QDesktopServices>
#include <QUrl>


#include "lastfmsuggest.h"
#include "searchbox.h"

SearchBox::SearchBox(QWidget *parent): QLineEdit(parent)
{
    completer = new LastFmSuggest(this);

    connect(this, SIGNAL(returnPressed()),this, SLOT(doSearch()));

    setWindowTitle("Search with Google");

    adjustSize();
    resize(400, height());
    setFocus();
}
void SearchBox::doSearch()
{
    completer->preventSuggest();
    QString url = QString("%1").arg(text());
    QDesktopServices::openUrl(QUrl(url));
}
