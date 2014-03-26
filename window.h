#ifndef WINDOW_H
#define WINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QDebug>
#include <QClipboard>

#define Q_CONNECT(a,b,c,d) connect(a,SIGNAL(b),c,SLOT(d))

namespace Ui {
class Window;
}

class Window : public QMainWindow
{
    Q_OBJECT

public:
    explicit Window(QWidget *parent = 0);
    ~Window();

private slots:
    void onButtonClicked(bool checked);
    void printPerm();
    void copyPerm();

private:
    Ui::Window *ui;
    unsigned char user;
    unsigned char group;
    unsigned char world;
};

#endif // WINDOW_H
