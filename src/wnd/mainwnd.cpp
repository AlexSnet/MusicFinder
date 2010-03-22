#include "mainwnd.h"
#include "ui_mainwnd.h"

mainWnd::mainWnd(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::mainWnd)
{
    ui->setupUi(this);

    search = new SearchBox();
    ui->toolBar->addWidget( search );

    lpanel = new leftpanel();
    ui->layout->addWidget( lpanel );
}

mainWnd::~mainWnd()
{
    delete ui;
}

void mainWnd::changeEvent(QEvent *e)
{
    QMainWindow::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}
