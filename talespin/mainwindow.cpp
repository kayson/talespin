#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QSettings>
#include <QtGui>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    fullscreen = false;

    db = QSqlDatabase::addDatabase("QODBC");

    db.setDatabaseName("DRIVER=SQL Server;SERVER=62.168.149.41;DATABASE=ActorPLATSBOKVISUALC_utb;UID=Visual_utb;PWD=qwe123!!");

    if (!db.open())
    {
        QMessageBox::critical(0, QObject::tr("Database Error"),
        db.lastError().text());
    }
    else
    {
        QSqlQuery query(db);
        query.setForwardOnly(true);
        query.prepare("SELECT ArticleName FROM View_utb_Articles WHERE EXISTS ( SELECT ArticleName FROM View_utb_transactions )");

        if(query.exec())
        {
            while(query.next())
            {
                ui->comboBox_2->addItem(query.value(0).toString());
            }
        }
    }

    loadSettings();
}

MainWindow::~MainWindow()
{
    saveSettings();
    delete ui;
}

void MainWindow::saveSettings()
{
    QSettings settings("Visualiseringscenter C", "ViC");

    settings.setValue("windowPos", pos());
    settings.setValue("windowSize", size());

    settings.setValue("barWidth", ui->horizontalSlider->value());
    settings.setValue("particleRadius", ui->horizontalSlider_2->value());
    settings.setValue("barSpace", ui->horizontalSlider_3->value());
}

void MainWindow::loadSettings()
{
    QSettings settings("Visualiseringscenter C", "ViC");

    resize(settings.value("windowSize", QSize(1537, 677)).toSize());
    move(settings.value("windowPos", QPoint(200, 200)).toPoint());

    ui->horizontalSlider->setValue(settings.value("barWidth", 10).toInt());
    ui->horizontalSlider_2->setValue(settings.value("particleRadius", 1.0f).toFloat());
    ui->horizontalSlider_3->setValue(settings.value("barSpace", 0).toInt());

}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    switch (event->key())
    {
        case Qt::Key_Escape:
            close();
            break;

        case Qt::Key_Alt:
          // ui->panelGL->drawGrid();
          // ui->panelGL->updateGL();
            break;
    }

}

void MainWindow::addBar()
{
    float num = ui->spinBox->value();
    QString col = ui->comboBox->currentText();

    if(db.open())
    {
        QString article = ui->comboBox_2->currentText();
        qDebug() << article;

        QSqlQuery query(db);

        query.setForwardOnly(true);

        query.prepare("SELECT count(*) FROM View_utb_transactions WHERE ArticleName = :article");
        query.bindValue(":article", article);
        query.exec();
        query.next();
        num = query.value(0).toInt();
    }

    if(col == "Red")
        ui->panelGL->Bars->addBar(num, glm::vec4(1.0f,0.0f,0.0f,1.0f));
    else if(col == "Green")
        ui->panelGL->Bars->addBar(num, glm::vec4(0.0f,1.0f,0.0f,1.0f));
    else if(col == "Blue")
        ui->panelGL->Bars->addBar(num, glm::vec4(0.0f,0.0f,1.0f,1.0f));

    ui->panelGL->Bars->update();
}

void MainWindow::fullScreen()
{
    if(fullscreen)
    {
        showNormal();
        ui->widget->show();
        ui->horizontalLayout->setMargin(9);
        fullscreen = false;
    }
    else
    {
        showFullScreen();
        ui->widget->hide();
        ui->horizontalLayout->setMargin(1);
        fullscreen = true;
    }
}
