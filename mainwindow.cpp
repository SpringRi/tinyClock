#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QTime>
#include <QTimer>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    timer = nullptr;

    player = new QMediaPlayer;

}

MainWindow::~MainWindow()
{
    delete ui;

    delete player;
}

void MainWindow::on_pushButton_clicked()
{
    quint64 minutes_left = ui->lineEdit->text().toULong();
    QString minutes_left_str = QString::number(minutes_left);
    ui->lcdNumber->display(minutes_left_str);

    // 如果 toULong 函数返回值为0，表示转换成整数失败，可能是输入的内容的问题
    if (minutes_left == 0){
        return;
    }

    // 此处需要启动计时器
    start_clock(minutes_left);

}

void MainWindow::slots_show_time()
{
    seconds_left -= 1;

    QTime t(0,0,0);
    t = t.addSecs(seconds_left);

    QString time_left_str = t.toString("hh:mm:ss");

    ui->lcdNumber->display(time_left_str);

    // 时间到
    if (seconds_left == 0){
        // 关闭定时器
        timer->stop();

        stop_clock();

        bell_ring();

    }
}

void MainWindow::start_clock(quint64 minute_num)
{

    seconds_left = minute_num * 60;

    // 每次 槽函数 被调用都要创建一个新的 timer
    timer = new QTimer(this);

    connect(timer, &QTimer::timeout, this, &MainWindow::slots_show_time);

    //connect(timer, &QTimer::timeout, this, slots_show_time);
    timer->start(1000);
}

void MainWindow::stop_clock()
{

    // 结束定时器
    disconnect(timer, &QTimer::timeout, this, &MainWindow::slots_show_time);

    if (timer != nullptr){
        // C++ 里要使用 delete，此处使用 free 程序会崩溃，不是马上崩
        delete timer;
        // 释放后一定要清空指针
        timer = nullptr;
    }

    return;
}

void MainWindow::bell_ring()
{
    player->setVolume(40);
    player->setMedia(QUrl::fromLocalFile("/home/john/Music/CloudMusic/Soulostar - In Time.mp3"));
    player->play();

    // 响铃 20s 即可关闭
    QTimer::singleShot(20000, player, SLOT(player->stop()));

}
