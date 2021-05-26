#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QString dir_path, QWidget *parent = nullptr);
    ~MainWindow();
};
#endif // MAINWINDOW_H
