#ifndef HIDE_H
#define HIDE_H

#include <QMainWindow>

namespace Ui {
class hide;
}

class hide : public QMainWindow
{
    Q_OBJECT

public:
    explicit hide(QWidget *parent = nullptr);
    ~hide();
    void paintEvent(QPaintEvent *);
signals:
    void chooseBack();//返回信号

private:
    Ui::hide *ui;
};

#endif // HIDE_H
