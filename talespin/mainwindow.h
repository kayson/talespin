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
    void AddChild(QTreeWidgetItem *parent, QString name, QString secondName);
    QTreeWidgetItem* getRoot();
    
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    void saveSettings();
    void loadSettings();
    bool comboBoxItemCanged();
    QSqlQueryModel *model, *model2, *model3, *model4;
    QCompleter *StringCompleter;
    void setRoundedCorners(int radius_tl, int radius_tr, int radius_bl, int radius_br);

protected:
    void keyPressEvent( QKeyEvent *event );
    QSqlDatabase db;

private slots:
    void on_barChartRadioButton_toggled(bool checked);
    void on_lineGraphRadioButton_toggled(bool checked);
    void on_addVisualisationPushButton_clicked();
    void on_startVisualisationPushButton_clicked();
    void on_removeVisualisation_clicked();
    void on_periodRadioButton_clicked();
    void on_timeRadioButton_clicked();
    void on_clearBars_clicked();
    void on_particleRadiusSlider_valueChanged(int value);
    void on_barSpacingSlider_valueChanged(int value);
    void on_barWidthSlider_valueChanged(int value);
    void on_timePositionSlider_valueChanged(int value);
    void on_circleVisualisationRadioButton_toggled(bool checked);
    void on_showMainWindowCheckBox_clicked(bool checked);

    void on_numberOfGridsLineEdit_textChanged(const QString &arg1);

    void removeItems();
    void on_newGroupPushButton_clicked();

    void on_gridCheckBox_toggled(bool checked);
    void on_numbersCheckBox_toggled(bool checked);
    void on_advanceSettingsAction_triggered();
    void on_createNewAction_triggered();
    void on_zoomSlider_valueChanged(int value);
    void on_closeAction_triggered();

    void on_radioButton_toggled(bool checked);
    void on_radioButton_2_toggled(bool checked);
    void on_radioButton_3_toggled(bool checked);

    void on_typeYearLE_editingFinished();
    void on_removePushButton_clicked();
    void on_quartersRB_toggled(bool checked);
    void on_monthsRB_toggled(bool checked);
};

#endif // MAINWINDOW_H
