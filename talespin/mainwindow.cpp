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
        query.prepare(" SELECT ArticleName FROM View_utb_Articles ");

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

        break;
    }

}

void MainWindow::addBar()
{
    QString year = ui->lineEdit->text();

    float num = 0;
    QString col = ui->comboBox->currentText();
    QString article = ui->comboBox_2->currentText();

    for(int month = 1;month <= 12; month++)
    {
        if(db.open())
        {
            QSqlQuery query(db);

            query.setForwardOnly(true);

            query.prepare(" SELECT count(*) FROM View_utb_transactions WHERE ArticleName = :article AND DATEPART(year, Date) = :year AND DATEPART(month, Date) = :month ");
            query.bindValue(":article", article);
            query.bindValue(":year", year);
            query.bindValue(":month", month);
            query.exec();
            query.next();
            num = query.value(0).toInt();
        }

        if(num > 0)
        {
            if(col == "Red")
                ui->panelGL->ParticleMgr->addContainer(month, num, glm::vec4(1.0f,0.0f,0.0f,0.8f));
            else if(col == "Green")
                ui->panelGL->ParticleMgr->addContainer(month, num, glm::vec4(0.0f,1.0f,0.0f,0.8f));
            else if(col == "Blue")
                ui->panelGL->ParticleMgr->addContainer(month, num, glm::vec4(0.0f,0.0f,1.0f,0.8f));

            ui->panelGL->ParticleMgr->update();
        }
    }


    ui->panelGL->ParticleMgr->IDcounter++;

    ui->listWidget->addItem(article);
    ui->listWidget->setSelectionMode(QAbstractItemView::MultiSelection );
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


void MainWindow::on_pushButton_3_clicked()
{
    if(ui->listWidget->count() > 0)
    {
        if(!ui->listWidget->currentItem())
            return;
        //qDeleteAll(ui->listWidget->selectedItems());
        //qDebug() << ui->listWidget->currentRow()+1;

        QListWidgetItem *itm = ui->listWidget->currentItem();
        //if(ui->listWidget->currentRow()+1)
        if(itm->isSelected())
        {
           ui->panelGL->ParticleMgr->removeContainers(itm->listWidget()->currentRow());
           qDeleteAll(ui->listWidget->selectedItems());
          // ui->panelGL->ParticleMgr->removeContainers(ui->listWidget->currentRow()+1);
        }
     }


}

void MainWindow::on_radioButton_toggled(bool checked)
{
    ui->panelGL->ParticleMgr->visType = BARCHART;
    ui->checkBox->setDisabled(false);
    ui->panelGL->ParticleMgr->update();
}

void MainWindow::on_radioButton_2_toggled(bool checked)
{
    ui->panelGL->ParticleMgr->visType = LINES;
    ui->checkBox->setDisabled(false);
    ui->panelGL->ParticleMgr->update();
}

void MainWindow::on_radioButton_3_toggled(bool checked)
{
    ui->panelGL->ParticleMgr->visType = CIRCLES;
    ui->panelGL->_drawGrid->visible = false;
    ui->checkBox->setChecked(false);
    ui->checkBox->setDisabled(true);
    ui->panelGL->ParticleMgr->update();
}
