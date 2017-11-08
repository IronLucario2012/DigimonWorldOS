#ifndef GAMEOVERWINDOW_H
#define GAMEOVERWINDOW_H

#include <QDialog>

namespace Ui {
class GameOverWindow;
}

class GameOverWindow : public QDialog
{
    Q_OBJECT

public:
    explicit GameOverWindow(QWidget *parent = 0);
    ~GameOverWindow();

    void setMessage(int vic);

private slots:
    void on_OKButton_released();

private:
    Ui::GameOverWindow *ui;
};

#endif // GAMEOVERWINDOW_H
