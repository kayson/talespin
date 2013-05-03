#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QSettings>
#include <QtGui>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->label_11->hide();
    ui->label_12->hide();
    ui->groupBox_6->hide();
    ui->period->setChecked(true);

    ui->numberOfGrids->hide();
    ui->numberOfGridsLineEdit->hide();

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

        if(query.exec(" SELECT ArticleName FROM View_utb_Articles"))
        {
            QStringList CompletionList;
            while(query.next())
            {
                CompletionList << query.value(0).toString();
            }
            StringCompleter = new QCompleter(CompletionList,this);
            StringCompleter->setCaseSensitivity(Qt::CaseInsensitive);
            //StringCompleter->setCompletionMode(QCompleter::InlineCompletion);
            //StringCompleter->setCompletionMode(QCompleter::QCompleter::UnfilteredPopupCompletion);

            ui->searchAllArticles->setCompleter(StringCompleter);
            StringCompleter->setCompletionPrefix( query.value(0).toString().split(" ").back().trimmed().toLower() );

        }
        if(query.exec("SELECT ArticleName FROM View_utb_Articles WHERE ArticleGroup IN (1100, 1700, 1800, 2300)"))
        {
            ui->ticketComboBox->setFont(QFont("Arial", 8));
            while(query.next())
            {
                ui->ticketComboBox->addItem(query.value(0).toString());
            }
        }

        if(query.exec(" SELECT ArticleName FROM View_utb_Articles WHERE ArticleGroup IN (3100, 3102, 3210, 3220, 3240, 3250, 3260) "))
        {
            //ui->restaurantComboBox->setEditable(true);
            ui->restaurantComboBox->setFont(QFont("Arial", 8));
            while(query.next())
            {
                ui->restaurantComboBox->addItem(query.value(0).toString());
            }
        }

        if(query.exec(" SELECT ArticleName FROM View_utb_Articles WHERE ArticleGroup IN (110, 140, 150, 160, 170, 180, 190, 200, 210, 300, 500, 600, 700, 3270, 9991, 9992) "))
        {
            ui->shopComboBox->setFont(QFont("Arial", 8));
            while(query.next())
            {
                ui->shopComboBox->addItem(query.value(0).toString());
            }
        }

        if(query.exec(" SELECT ArticleName FROM View_utb_Articles WHERE ArticleGroup IN (1100, 1700, 1800, 2300) "))
        {
            ui->showComboBox->setFont(QFont("Arial", 8));
            while(query.next())
            {
                ui->showComboBox->addItem(query.value(0).toString());
            }
        }
    }
    loadSettings();
}

MainWindow::~MainWindow()
{
    saveSettings();
    db.close();
    delete ui;
}

void MainWindow::saveSettings()
{
    QSettings settings("Visualiseringscenter C", "ViC");

    settings.setValue("windowPos", pos());
    settings.setValue("windowSize", size());

    settings.setValue("barWidth", ui->barWidthSlider->value());
    settings.setValue("particleRadius", ui->particleRadiusSlider->value());
    settings.setValue("barSpace", ui->barSpacingSlider->value());
}

void MainWindow::loadSettings()
{
    QSettings settings("Visualiseringscenter C", "ViC");

    resize(settings.value("windowSize", QSize(1537, 677)).toSize());
    move(settings.value("windowPos", QPoint(200, 200)).toPoint());

    ui->barWidthSlider->setValue(settings.value("barWidth", 10).toInt());
    ui->particleRadiusSlider->setValue(settings.value("particleRadius", 1.0f).toFloat());
    ui->barSpacingSlider->setValue(settings.value("barSpace", 0).toInt());

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


void MainWindow::on_addToList_clicked()
{
        QString year = ui->typeYear->text();

        float num = 0;
        QString col = ui->comboBox->currentText();
        QString article = ui->searchAllArticles->text();
//        QString article = "(";
//        for(int i = 0; i < ui->addMultipleItems->count(); i++)
//        {

//            QListWidgetItem *item = ui->addMultipleItems->item(i);
//            if(i != 0) article.append(",");

//            article.append("'");
//            article.append(item->text());
//            article.append("'");

//        }
//        article.append(")");
//        qDebug() << article;

        bool found = false;
        for(int month = 1;month <= 12; month++)
        {
            if(db.open())
            {
                QSqlQuery query(db);
                query.setForwardOnly(true);

                query.prepare("SELECT count(*) FROM View_utb_transactions WHERE ArticleName = :article AND DATEPART(year, Date) = :year AND DATEPART(month, Date) = :month");
                query.bindValue(":article", article);
                query.bindValue(":year", year);
                query.bindValue(":month", month);
                query.exec();
                query.next();
                num = query.value(0).toInt();
                qDebug() << num;
            }

            if(num > 0)
            {
                found = true;
                if(col == "Red")
                    ui->panelGL->ParticleMgr->addContainer(month, num, glm::vec4(1.0f,0.0f,0.0f,0.8f));
                else if(col == "Green")
                    ui->panelGL->ParticleMgr->addContainer(month, num, glm::vec4(0.0f,1.0f,0.0f,0.8f));
                else if(col == "Blue")
                    ui->panelGL->ParticleMgr->addContainer(month, num, glm::vec4(0.0f,0.0f,1.0f,0.8f));

                ui->panelGL->ParticleMgr->update();
            }
        }
        if(found)
        {
            ui->listWidget->addItem(article + " " + ui->typeYear->text());
            ui->panelGL->ParticleMgr->numOftimeInterval = 12;
            ui->panelGL->ParticleMgr->IDcounter++;
        }
}

void MainWindow::on_removeVisualisation_clicked()
{
    if(ui->listWidget->count() > 0)
    {
        if(!ui->listWidget->currentItem())
            return;

        QListWidgetItem *itm = ui->listWidget->currentItem();
        if(itm->isSelected())
        {
           ui->panelGL->ParticleMgr->removeContainers(itm->listWidget()->currentRow());
           qDeleteAll(ui->listWidget->selectedItems());
           ui->panelGL->ParticleMgr->number--;
           ui->panelGL->ParticleMgr->update();
        }
     }
}

void MainWindow::on_barChartRadioButton_toggled(bool checked)
{
    ui->panelGL->ParticleMgr->visType = BARCHART;
    ui->checkBox->setDisabled(false);
    ui->panelGL->ParticleMgr->update();
}

void MainWindow::on_lineGraphRadioButton_toggled(bool checked)
{
    ui->panelGL->ParticleMgr->visType = LINES;
    ui->checkBox->setDisabled(false);
    ui->panelGL->ParticleMgr->update();
}

void MainWindow::on_circleVisualisationRadioButton_toggled(bool checked)
{
    ui->timePositionSlider->setEnabled(checked);
    ui->panelGL->ParticleMgr->visType = CIRCLES;
    ui->panelGL->_drawGrid->visible = false;
    ui->checkBox->setChecked(false);
    ui->checkBox->setDisabled(true);
    ui->panelGL->ParticleMgr->update();
}


void MainWindow::on_period_clicked()
{
    ui->label_11->hide();
    ui->label_12->hide();
    ui->groupBox_6->hide();
}

void MainWindow::on_time_clicked()
{
    ui->label_11->show();
    ui->label_12->show();
    ui->groupBox_6->show();
}

void MainWindow::on_clearBars_clicked()
{
    ui->panelGL->ParticleMgr->clearContainers();
}

void MainWindow::on_particleRadiusSlider_valueChanged(int value)
{
    ui->panelGL->particleSize(value);
}

void MainWindow::on_barSpacingSlider_valueChanged(int value)
{
    ui->panelGL->setSpacing(value);
}

void MainWindow::on_barWidthSlider_valueChanged(int value)
{
    ui->panelGL->setNumberOfParticles(value);
}

void MainWindow::on_timePositionSlider_valueChanged(int value)
{
    ui->panelGL->timePositionChanged(value);
}

void MainWindow::on_checkBox_clicked(bool checked)
{
    if (checked == true)
    {
        ui->panelGL->showGrid(checked);
    }
    else
    {
        ui->panelGL->showGrid(checked);
    }
}

void MainWindow::on_showMainWindowCheckBox_clicked(bool checked)
{
    if (checked == false)
    {
        ui->tabWidget_3->hide();
        ui->widget_2->hide();
    }
    else
    {
        ui->tabWidget_3->show();
        ui->widget_2->show();
    }

}

void MainWindow::on_numberOfGridsLineEdit_textChanged(const QString &arg1)
{
    int grid;
    grid = arg1.toInt();
    //ui->panelGL->_drawGrid->numberOfGrids = grid;
}

void MainWindow::on_ticketComboBox_activated(const QString &arg1)
{
    ui->addMultipleItems->addItem(arg1);

}

void MainWindow::on_restaurantComboBox_activated(const QString &arg1)
{
    ui->addMultipleItems->addItem(arg1);
}

void MainWindow::on_shopComboBox_activated(const QString &arg1)
{
    ui->addMultipleItems->addItem(arg1);
}

void MainWindow::on_showComboBox_activated(const QString &arg1)
{
    ui->addMultipleItems->addItem(arg1);
}

void MainWindow::on_searchAllArticles_returnPressed()
{
    float num = 0;
    QString article = ui->searchAllArticles->text();
    bool found = false;

    if(db.open())
    {
        QSqlQuery query(db);
        query.setForwardOnly(true);

        query.prepare(" SELECT count(*) FROM View_utb_transactions WHERE ArticleName = :article");
        query.bindValue(":article", article);

        query.exec();
        query.next();
        num = query.value(0).toInt();

    }

    if(num > 0)
    {
        found = true;
    }


    if(found)
    {
        QString item;
        item = ui->searchAllArticles->text();
        ui->addMultipleItems->addItem(item);
    }

}
