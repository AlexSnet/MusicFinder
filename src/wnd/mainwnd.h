#ifndef MAINWND_H
#define MAINWND_H

#include <QMainWindow>

#include "../lastfm/searchbox.h"
#include "../widgets/leftpanel.h"

namespace Ui {
    class mainWnd;
}


class mainWnd : public QMainWindow {
    Q_OBJECT
public:
    mainWnd(QWidget *parent = 0);
    ~mainWnd();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::mainWnd *ui;
    SearchBox *search;
    leftpanel *lpanel;
};

#endif // MAINWND_H
