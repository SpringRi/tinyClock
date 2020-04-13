#include "flashwindow.h"
#include "ui_flashwindow.h"

FlashWindow::FlashWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FlashWindow)
{
    ui->setupUi(this);
}

FlashWindow::~FlashWindow()
{
    delete ui;
}
