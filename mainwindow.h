#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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

private:
    Ui::MainWindow *ui;

    void start_clock(quint64 minute_num);
    void stop_clock();

    // 使用一个类成员来记录还有多少秒数，方便在槽函数中获取
    quint64 seconds_left;

    QTimer *timer;

};
#endif // MAINWINDOW_H
