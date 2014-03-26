#include "window.h"
#include "ui_window.h"

Window::Window(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Window)
{
    user = group = world = 0;

    ui->setupUi(this);
    ui->buttons->button(QDialogButtonBox::Ok)->setText("Copy");

    connect(ui->buttons, SIGNAL(rejected()), this, SLOT(close()));
    connect(ui->buttons, SIGNAL(accepted()), this, SLOT(copyPerm()));

    Q_CONNECT(ui->ur,clicked(bool),this,onButtonClicked(bool));
    Q_CONNECT(ui->uw,clicked(bool),this,onButtonClicked(bool));
    Q_CONNECT(ui->ux,clicked(bool),this,onButtonClicked(bool));
    Q_CONNECT(ui->gr,clicked(bool),this,onButtonClicked(bool));
    Q_CONNECT(ui->gw,clicked(bool),this,onButtonClicked(bool));
    Q_CONNECT(ui->gx,clicked(bool),this,onButtonClicked(bool));
    Q_CONNECT(ui->wr,clicked(bool),this,onButtonClicked(bool));
    Q_CONNECT(ui->ww,clicked(bool),this,onButtonClicked(bool));
    Q_CONNECT(ui->wx,clicked(bool),this,onButtonClicked(bool));

    printPerm();

    setWindowTitle("QPermCalc");
}

Window::~Window()
{
    delete ui;
}

void Window::onButtonClicked(bool checked)
{
    QString name = sender()->objectName();
    unsigned char value = 0;
    unsigned char *object = 0;

    // check for read|write|execute
    if(name.endsWith('r')) value = 4;
    else if(name.endsWith('w')) value = 2;
    else if(name.endsWith('x')) value = 1;

    // check for user|goup|world
    if(name.startsWith('u')) object = &user;
    else if(name.startsWith('g')) object = &group;
    else if(name.startsWith('w')) object = &world;

    // check if checked or unchecked
    if(checked) *object += value;
    else *object -= value;

    printPerm();
}

void Window::printPerm()
{
    ui->perm->setText(QString("%1%2%3").arg(user).arg(group).arg(world));
}

void Window::copyPerm()
{
    QClipboard *clipboard = QApplication::clipboard();
    clipboard->setText(ui->perm->text());
}
