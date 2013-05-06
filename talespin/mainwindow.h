#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSql/QtSql>
#include <QCompleter>
#include <QDirModel>
#include <QtGui>
#include <QtCore>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

    void AddRoot(QString name);
    void AddChild(QTreeWidgetItem *parent, QString name);
    QTreeWidgetItem* getRoot();
    
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    void saveSettings();
    void loadSettings();
    QSqlQueryModel *model, *model2, *model3, *model4;
    QCompleter *StringCompleter;

protected:
    void keyPressEvent( QKeyEvent *event );
    QSqlDatabase db;

private slots:
    void on_barChartRadioButton_toggled(bool checked);
    void on_lineGraphRadioButton_toggled(bool checked);
    void on_startVisualisationPushButton_clicked();
    void on_removeVisualisation_clicked();
    void on_period_clicked();
    void on_time_clicked();
    void on_clearBars_clicked();
    void on_particleRadiusSlider_valueChanged(int value);
    void on_barSpacingSlider_valueChanged(int value);
    void on_barWidthSlider_valueChanged(int value);
    void on_timePositionSlider_valueChanged(int value);
    void on_gridCheckBox_clicked(bool checked);
    void on_numbersCheckBox_clicked(bool checked);
    void on_circleVisualisationRadioButton_toggled(bool checked);
    void on_showMainWindowCheckBox_clicked(bool checked);

    void on_numberOfGridsLineEdit_textChanged(const QString &arg1);
    void on_ticketComboBox_activated(const QString &arg1);
    void on_restaurantComboBox_activated(const QString &arg1);
    void on_shopComboBox_activated(const QString &arg1);
    void on_showComboBox_activated(const QString &arg1);

    void on_searchAllArticles_returnPressed();
    void on_selectAllTicketToolButton_clicked();
    void on_chooseAllRestaurantToolButton_clicked();
    void on_chooseAllShopToolButton_clicked();
    void on_removePushButton_clicked();
    void on_newGroupPushButton_clicked();
    void on_radioButton_toggled(bool checked);
    void on_radioButton_2_toggled(bool checked);
    void on_radioButton_3_toggled(bool checked);
};

#endif // MAINWINDOW_H
