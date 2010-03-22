#ifndef TITLE_H
#define TITLE_H

#include <QWidget>
#include <QGridLayout>
#include <QObject>
#include <QLabel>

class title : public QWidget
{
    Q_OBJECT
public:
    title(QWidget* parent = 0);
    virtual QSize sizeHint() const;
    void setInfo(const QString artist, const QString album, const QString track, const QString restype);
    QString getText();

protected:
    QGridLayout* layout;
private:
    static const uint width = 166;
    static const uint height = 48;

    // Info
    QString iartist;
    QString ialbum;
    QString itrack;
    QString irestype;

};

#endif // TITLE_H
