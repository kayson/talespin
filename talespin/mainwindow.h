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
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private:
    Ui::MainWindow *ui;
    bool fullscreen;

protected:
    void keyPressEvent( QKeyEvent *event );

public slots:
    void addBar();
    void fullScreen();
};

#endif // MAINWINDOW_H
