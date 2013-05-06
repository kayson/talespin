#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QSettings>
#include <QtGui>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->progressBar->reset();
    ui->progressBar->setTextVisible(false);

    ui->treeWidget->setColumnCount(1);
    ui->treeWidget->header()->close();
    ui->treeWidget->setSelectionMode(QAbstractItemView::MultiSelection);

    ui->label_11->hide();
    ui->label_12->hide();
    ui->groupBox_6->hide();
    ui->period->setChecked(true);

    ui->numberOfGrids->hide();
    ui->numberOfGridsLineEdit->hide();
    ui->selectAllTicketToolButton->setFont(QFont("Arial", 8));
    ui->chooseAllShopToolButton->setFont(QFont("Arial", 8));
    ui->chooseAllRestaurantToolButton->setFont(QFont("Arial", 8));
    ui->chooseAllShowToolButton->setFont(QFont("Arial", 8));

    //ui->addMultipleItems->setSelectionMode(QAbstractItemView::MultiSelection);

    QString placeholderText;
    placeholderText = QString::fromUtf8("Fritext sök...");
    ui->searchAllArticles->setPlaceholderText(placeholderText);
    //*[mandatoryField = "true"]{background-color: yellow}
    ui->searchAllArticles->setStyleSheet("color: blue;"
                                         "background-color: yellow;"
                                         "selection-color:red;"
                                         "selection-background-color: blue;");

//    QImage img(":/MyFiles/pic/earth.jpg");
    QPixmap pixmap4(":/MyFiles/pic/triangleButton.png");
//    QIcon ButtonIcon;
//    ButtonIcon.addPixmap(pixmap4);
//    ui->testButton->setIcon(ButtonIcon);
//    ui->testButton->setIconSize(pixmap4.rect().size());

    QIcon triangleButtonIcon;
    triangleButtonIcon.addPixmap(pixmap4);
    ui->startVisualisationPushButton->setIcon(triangleButtonIcon);
    ui->startVisualisationPushButton->setIconSize(QSize(120,400));
    ui->startVisualisationPushButton->setMask(pixmap4.mask());

//    ui->testButton->setIcon(QIcon(":/MyFiles/pic/transstring.png"));
//    ui->testButton->setIconSize(QSize(150,40));

//    ui->testButton->setIconSize(img.size());
//    ui->testButton->resize(img.size());
//    ui->testButton->setMask(pixmap4.mask());

    QPixmap pixmap(":/MyFiles/pic/lines.png");
    ui->lineLabel->setPixmap(pixmap);
    ui->lineLabel->setScaledContents(true);

    QPixmap pixmap2(":/MyFiles/pic/bars.png");
    ui->barLabel->setPixmap(pixmap2);
    ui->barLabel->setScaledContents(true);

    QPixmap pixmap3(":/MyFiles/pic/expand.png");
    QIcon icon;
    icon.addPixmap(pixmap3);
    ui->iconToolButton->setIcon(icon);

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

void MainWindow::on_startVisualisationPushButton_clicked()
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

        for (int i = 0; i <= ui->treeWidget->topLevelItemCount()-1; i++)
        {
            for (int j = 0; j <= ui->treeWidget->topLevelItem(i)->childCount()-1; j++)
            {
                QString article = ui->treeWidget->topLevelItem(i)->child(j)->text(0);
                //QString article = ui->searchAllArticles->text();

                bool found = false;
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
                        found = true;
                        if(col == "Red")
                            ui->panelGL->ParticleMgr->addContainer(month, num, glm::vec4(1.0f,0.0f,0.0f,0.8f));
                        else if(col == "Green")
                            ui->panelGL->ParticleMgr->addContainer(month, num, glm::vec4(0.0f,1.0f,0.0f,0.8f));
                        else if(col == "Blue")
                            ui->panelGL->ParticleMgr->addContainer(month, num, glm::vec4(0.0f,0.0f,1.0f,0.8f));

                        ui->panelGL->ParticleMgr->update();
                        ui->progressBar->setRange(0,12);
                        ui->progressBar->setValue(month);
                    }
                }
                if(found)
                {
                    ui->listWidget->addItem(article + " " + ui->typeYear->text());
                    //ui->treeWidget->topLevelItem(i)->setHidden(true);
                    ui->panelGL->ParticleMgr->numOftimeInterval = 12;
                    ui->panelGL->ParticleMgr->IDcounter++;
                }
            }
        }
        ui->treeWidget->clear();
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
    ui->gridCheckBox->setDisabled(false);
    ui->panelGL->ParticleMgr->update();
}

void MainWindow::on_lineGraphRadioButton_toggled(bool checked)
{
    ui->panelGL->ParticleMgr->visType = LINES;
    ui->gridCheckBox->setDisabled(false);
    ui->panelGL->ParticleMgr->update();
}

void MainWindow::on_circleVisualisationRadioButton_toggled(bool checked)
{
    ui->timePositionSlider->setEnabled(checked);
    ui->panelGL->ParticleMgr->visType = CIRCLES;
    ui->panelGL->_drawGrid->hideGrid = false;
    ui->gridCheckBox->setChecked(false);
    ui->gridCheckBox->setDisabled(true);
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

void MainWindow::on_gridCheckBox_clicked(bool checked)
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

void MainWindow::on_numbersCheckBox_clicked(bool checked)
{
    if (checked == true)
    {
        ui->panelGL->showNumbers(checked);
    }
    else
    {
        ui->panelGL->showNumbers(checked);
    }
}

void MainWindow::on_showMainWindowCheckBox_clicked(bool checked)
{
    if (checked == false)
    {
        ui->groupWidget->hide();
        ui->widget_2->hide();
        ui->marketingWidget->hide();
    }
    else
    {
        ui->groupWidget->show();
        ui->widget_2->show();
        ui->marketingWidget->show();
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
    //ui->addMultipleItems->addItem(arg1);
    if(ui->treeWidget->topLevelItemCount() == 0)
    {
        int i = ui->treeWidget->topLevelItemCount()+1;
        QString s = QString::number(i);
        AddRoot("Grupp " + s);
    }
    AddChild(getRoot(),arg1);
}

void MainWindow::on_restaurantComboBox_activated(const QString &arg1)
{
    if(ui->treeWidget->topLevelItemCount() == 0)
    {
        int i = ui->treeWidget->topLevelItemCount()+1;
        QString s = QString::number(i);
        AddRoot("Grupp " + s);
    }
    AddChild(getRoot(),arg1);
}

void MainWindow::on_shopComboBox_activated(const QString &arg1)
{
    if(ui->treeWidget->topLevelItemCount() == 0)
    {
        int i = ui->treeWidget->topLevelItemCount()+1;
        QString s = QString::number(i);
        AddRoot("Grupp " + s);
    }
    AddChild(getRoot(),arg1);
}

void MainWindow::on_showComboBox_activated(const QString &arg1)
{
    if(ui->treeWidget->topLevelItemCount() == 0)
    {
        int i = ui->treeWidget->topLevelItemCount()+1;
        QString s = QString::number(i);
        AddRoot("Grupp " + s);
    }
    AddChild(getRoot(),arg1);
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

        if(ui->treeWidget->topLevelItemCount() == 0)
        {
            int i = ui->treeWidget->topLevelItemCount()+1;
            QString s = QString::number(i);
            AddRoot("Grupp " + s);
        }
        AddChild(getRoot(),item);
    }

}

void MainWindow::on_selectAllTicketToolButton_clicked()
{
    if(db.open())
    {
        QSqlQuery query(db);
        query.setForwardOnly(true);

        if(query.exec("SELECT ArticleName FROM View_utb_Articles WHERE ArticleGroup IN (1100, 1700, 1800, 2300)"))
        {

            while(query.next())
            {
                if(ui->treeWidget->topLevelItemCount() == 0)
                {
                    int i = ui->treeWidget->topLevelItemCount()+1;
                    QString s = QString::number(i);
                    AddRoot("Grupp " + s);
                }
                AddChild(getRoot(),query.value(0).toString());
            }
        }
    }
}

void MainWindow::on_chooseAllRestaurantToolButton_clicked()
{
    if(db.open())
    {
        QSqlQuery query(db);
        query.setForwardOnly(true);

        if(query.exec(" SELECT ArticleName FROM View_utb_Articles WHERE ArticleGroup IN (3100, 3102, 3210, 3220, 3240, 3250, 3260) "))
        {

            while(query.next())
            {
                if(ui->treeWidget->topLevelItemCount() == 0)
                {
                    int i = ui->treeWidget->topLevelItemCount()+1;
                    QString s = QString::number(i);
                    AddRoot("Grupp " + s);
                }
                AddChild(getRoot(),query.value(0).toString());
            }
        }
    }
}

void MainWindow::on_chooseAllShopToolButton_clicked()
{
    if(db.open())
    {
        QSqlQuery query(db);
        query.setForwardOnly(true);

        if(query.exec(" SELECT ArticleName FROM View_utb_Articles WHERE ArticleGroup IN (110, 140, 150, 160, 170, 180, 190, 200, 210, 300, 500, 600, 700, 3270, 9991, 9992) "))
        {

            while(query.next())
            {
                if(ui->treeWidget->topLevelItemCount() == 0)
                {
                    int i = ui->treeWidget->topLevelItemCount()+1;
                    QString s = QString::number(i);
                    AddRoot("Grupp " + s);
                }
                AddChild(getRoot(),query.value(0).toString());
            }
        }
    }
}


QTreeWidgetItem* MainWindow::getRoot()
{
    QTreeWidgetItem *treeItem = ui->treeWidget->topLevelItem(ui->treeWidget->topLevelItemCount()-1);
    return treeItem;
}

void MainWindow::AddRoot(QString name)
{
    QTreeWidgetItem *itm = new QTreeWidgetItem(ui->treeWidget);
    itm->setText(0,name);
    itm->setFlags(itm->flags()| (Qt::ItemIsEditable));
}

void MainWindow::AddChild(QTreeWidgetItem *parent, QString name)
{
    QTreeWidgetItem *itm = new QTreeWidgetItem();
    itm->setText(0,name);
    parent->addChild(itm);
}

void MainWindow::on_removePushButton_clicked()
{
    if(ui->treeWidget->topLevelItemCount() > 0)
    {
        if(!ui->treeWidget->currentItem())
            return;

        QTreeWidgetItem *itm = ui->treeWidget->currentItem();
        if(itm->isSelected())
        {
            qDeleteAll(ui->treeWidget->selectedItems());
        }
    }
}

void MainWindow::on_newGroupPushButton_clicked()
{
    int i = ui->treeWidget->topLevelItemCount()+1;
    QString s = QString::number(i);
    AddRoot("Grupp " + s);
    ui->treeWidget->resizeColumnToContents(i);
}
