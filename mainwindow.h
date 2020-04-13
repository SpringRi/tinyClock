#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QMediaPlayer>
#include <QDateTime>
#include <QQueue>

#include "flashwindow.h"
#include "duration.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();
    void slots_show_time();
    void renew(); //一次提示之后，恢复界面

private:
    Ui::MainWindow *ui;

    FlashWindow * flashwindow;

    void start_clock(quint64 minute_num);
    void stop_clock();
    void bell_ring();
    void duration_display();

    // 使用一个类成员来记录还有多少秒数，方便在槽函数中获取
    quint64 seconds_left;

    // 记录 计时起始时间 的容器
    QList<Duration> duration_list;
    Duration current_duration;
    QDateTime current_start_time; // from 时间
    QDateTime current_stop_time; // to 时间

    QTimer *timer;

    QMediaPlayer *player;

    quint64 prompt_time_length; // 时间到时，提示的时长（音乐，动画等）

};
#endif // MAINWINDOW_H
