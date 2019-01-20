#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    //默认文本设置
    void setDefaultText();
    //弹窗提示关闭程序
    void closeEvent(QCloseEvent *event);

private slots:
    void on_save_clicked();

    void on_clean_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
