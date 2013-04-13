#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSql/QtSql>
#include <QCompleter>
#include <QDirModel>

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
    void saveSettings();
    void loadSettings();
    QCompleter *StringCompleter;

protected:
    void keyPressEvent( QKeyEvent *event );
    QSqlDatabase db;

public slots:
    void addBar();
    void fullScreen();
private slots:
    void on_pushButton_3_clicked();
};

#endif // MAINWINDOW_H
