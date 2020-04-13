#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QTime>
#include <QTimer>

#define idebug true

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    timer = nullptr;

    player = new QMediaPlayer;

    flashwindow = new FlashWindow();

    prompt_time_length = 20000; // 20s
    prompt_time_length = 1000; // 20s

    current_duration = Duration();
}

MainWindow::~MainWindow()
{
    delete ui;

    delete player;

    delete flashwindow;
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

    // 可能存在，上一个计时器已经启动，又更新了时间的情况，此时首先应该清除旧的计时器
    if (timer != nullptr){
        stop_clock();
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

        //bell_ring();

        // 应用界面置顶
        this->hide();
        flashwindow->show();

        // 定时进行界面恢复
        QTimer::singleShot(prompt_time_length, this, SLOT(renew()));

        // 写入时间记录到文本框
        duration_display();
    }
}

void MainWindow::renew()
{
    // 界面切换，隐藏flash界面
    this->show();
    flashwindow->hide();
}

void MainWindow::start_clock(quint64 minute_num)
{
    seconds_left = minute_num * 60;

    // 记录本轮起始时间
    current_start_time = QDateTime::currentDateTime();
    current_duration.duration_minutes = minute_num;
    current_duration.from = current_start_time;

    if (idebug == true){
        seconds_left = 2;
    }

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

    // 记录本轮终止时间
    current_stop_time = QDateTime::currentDateTime();
    current_duration.to = current_stop_time;

    // 将本轮时长加入记录容器
    duration_list.append(current_duration);

    return;
}

void MainWindow::bell_ring()
{
    player->setVolume(60);
    player->setMedia(QUrl::fromLocalFile("/home/john/Music/CloudMusic/Soulostar - In Time.mp3"));
    player->play();

    // 响铃 20s 即可关闭音乐
    // singleShot 的槽函数直接使用对象的成员函数即可，不应 如下
    // QTimer::singleShot(20000, player, SLOT(player->stop()));
    QTimer::singleShot(prompt_time_length, player, SLOT(stop()));

}

void MainWindow::duration_display()
{
    // 时间段信息已经在 start_clock 和 stop_clock 函数中记录，此时只需要读取并显示

    // 输出到表格中

    int row_num = duration_list.length();

    // tableWidget 需要先设置行列值才能显示
    ui->tableWidget->setColumnCount(3);//设置3列
    ui->tableWidget->setRowCount(row_num);//行数由时间片的数量决定

    QStringList header;
    header<<"开始时间"<<"结束时间"<<"时长";
    ui->tableWidget->setHorizontalHeaderLabels(header);
    ui->tableWidget->horizontalHeader()->setStretchLastSection(true); //设置表头充满表格的宽度

    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows); //设置选择行为时每次一行
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers); //设置表格内容不可编辑

    for(int i = 0; i < duration_list.length(); i++){
        QString from_str = duration_list[i].from.toString("h:m:s ap");
        QString to_str = duration_list[i].to.toString("h:m:s ap");
        QString minutes_num = QString::number(duration_list[i].duration_minutes) + QString("分钟");

        ui->tableWidget->setItem(i, 0, new QTableWidgetItem(from_str));
        ui->tableWidget->setItem(i, 1, new QTableWidgetItem(to_str));
        ui->tableWidget->setItem(i, 2, new QTableWidgetItem(minutes_num));
    }

    // 设置单元格居中对齐
    for (int i = 0; i < row_num; i++){
        for (int j = 0; j < 3; j++){
            ui->tableWidget->item(i,j)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
        }
    }

    ui->tableWidget->show();

}
