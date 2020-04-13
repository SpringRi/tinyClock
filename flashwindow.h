#ifndef FLASHWINDOW_H
#define FLASHWINDOW_H

#include <QWidget>

namespace Ui {
class FlashWindow;
}

class FlashWindow : public QWidget
{
    Q_OBJECT

public:
    explicit FlashWindow(QWidget *parent = nullptr);
    ~FlashWindow();

private:
    Ui::FlashWindow *ui;
};

#endif // FLASHWINDOW_H
