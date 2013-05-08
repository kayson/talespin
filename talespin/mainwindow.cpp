#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QSettings>
#include <QtGui>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->myVisualisationTW->hide();

    ui->settingsWidget->hide();
    ui->groupWidget->hide();
    ui->myVisualisationWidget->hide();
    ui->startVisualisationPushButton->hide();

    ui->monthsRB->setChecked(true);

    ui->panelGL->showGrid(false);
    ui->panelGL->showNumbers(false);

    ui->progressBar->reset();
    ui->progressBar->setTextVisible(false);

    ui->myVisualisationTW->header()->close();

    ui->treeWidget->setColumnCount(2);
    ui->treeWidget->header()->close();
    ui->treeWidget->setSelectionMode(QAbstractItemView::MultiSelection);

    ui->label_11->hide();
    ui->label_12->hide();
    ui->timeRadioButton->setChecked(true);
    ui->groupBox_6->setDisabled(true);

    ui->numberOfGrids->hide();
    ui->numberOfGridsLineEdit->hide();

    //ui->addMultipleItems->setSelectionMode(QAbstractItemView::MultiSelection);

    QString firstItem;
    firstItem = QString::fromUtf8("Välj typ");
    ui->ticketComboBox->addItem(firstItem);

    QString firstItem2;
    firstItem2 = QString::fromUtf8("Välj artikel");
    ui->shopComboBox->addItem(firstItem2);

    QString firstItem3;
    firstItem3 = QString::fromUtf8("Välj artikel");
    ui->restaurantComboBox->addItem(firstItem3);

    QString placeholderText;
    placeholderText = QString::fromUtf8("Fritext sök...");
    ui->searchAllArticles->setPlaceholderText(placeholderText);
    //*[mandatoryField = "true"]{background-color: yellow}
    ui->searchAllArticles->setStyleSheet("color: blue;"
                                         "background-color: yellow;"
                                         "selection-color:red;"
                                         "selection-background-color: blue;");

    QPixmap pixmap4(":/MyFiles/pic/triangleButton.png");

    QIcon triangleButtonIcon;
    triangleButtonIcon.addPixmap(pixmap4);
    ui->startVisualisationPushButton->setIcon(triangleButtonIcon);
    ui->startVisualisationPushButton->setIconSize(QSize(120,400));
    ui->startVisualisationPushButton->setMask(pixmap4.mask());

    ui->addVisualisationPushButton->setIcon(triangleButtonIcon);
    ui->addVisualisationPushButton->setIconSize(QSize(120,400));
    ui->addVisualisationPushButton->setMask(pixmap4.mask());


    QPixmap pixmap(":/MyFiles/pic/lines.png");
    ui->lineLabel->setPixmap(pixmap);
    ui->lineLabel->setScaledContents(true);

    QPixmap pixmap2(":/MyFiles/pic/bars.png");
    ui->barLabel->setPixmap(pixmap2);
    ui->barLabel->setScaledContents(true);

    ui->barspacingLabel->setPixmap(pixmap2);
    ui->barspacingLabel->setScaledContents(true);

    ui->barwidthLabel->setPixmap(pixmap2);
    ui->barwidthLabel->setScaledContents(true);

    ui->zoomLabel->setPixmap(pixmap2);
    ui->zoomLabel->setScaledContents(true);

    ui->particleLabel->setPixmap(pixmap2);
    ui->particleLabel->setScaledContents(true);

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


void MainWindow::on_addVisualisationPushButton_clicked()
{

    float num = 0;
    QString article = ui->searchAllArticles->text();
    bool found = false;

    if(ui->treeWidget->topLevelItemCount() == 0)
    {
        int i = ui->treeWidget->topLevelItemCount()+1;
        QString s = QString::number(i);
        AddRoot("Grupp " + s);
    }

    if(db.open())
    {
        QSqlQuery query(db);
        query.setForwardOnly(true);

        query.prepare(" SELECT count(*) FROM View_utb_transactions WHERE ArticleName = :article");
        query.bindValue(":article", article);

        query.exec();
        query.next();
        num = query.value(0).toInt();

        if(num > 0)
        {
            found = true;
        }

        if(found)
        {
            QString item;
            item = ui->searchAllArticles->text();
            AddChild(getRoot(),item);
            ui->searchAllArticles->clear();
        }

        if(ui->selectAllTicketCheckBox->isChecked() && query.exec("SELECT ArticleName FROM View_utb_Articles WHERE ArticleGroup IN (1100, 1700, 1800, 2300)"))
        {

            while(query.next())
            {
                AddChild(getRoot(),query.value(0).toString());
            }
        }

        if(ui->selectAllRestaurantCheckBox->isChecked() && query.exec(" SELECT ArticleName FROM View_utb_Articles WHERE ArticleGroup IN (3100, 3102, 3210, 3220, 3240, 3250, 3260) "))
        {

            while(query.next())
            {
                AddChild(getRoot(),query.value(0).toString());
            }
        }

        if(ui->selectAllShopCheckBox->isChecked() && query.exec(" SELECT ArticleName FROM View_utb_Articles WHERE ArticleGroup IN (110, 140, 150, 160, 170, 180, 190, 200, 210, 300, 500, 600, 700, 3270, 9991, 9992) "))
        {

            while(query.next())
            {
                AddChild(getRoot(),query.value(0).toString());
            }
        }

        if(ui->ticketComboBox->currentIndex())
        {
            QString selectedItem = ui->ticketComboBox->currentText();
            AddChild(getRoot(),selectedItem);
            ui->ticketComboBox->setCurrentIndex(0);
        }

        if(ui->restaurantComboBox->currentIndex())
        {
            QString selectedItem = ui->restaurantComboBox->currentText();
            AddChild(getRoot(),selectedItem);
            ui->restaurantComboBox->setCurrentIndex(0);
        }

        if(ui->shopComboBox->currentIndex())
        {
            QString selectedItem = ui->shopComboBox->currentText();
            AddChild(getRoot(),selectedItem);
            ui->shopComboBox->setCurrentIndex(0);
        }

        ui->groupWidget->show();
        ui->startVisualisationPushButton->show();
    }
}




void MainWindow::on_startVisualisationPushButton_clicked()
{
    QString year = ui->typeYear->text();
    QString month = ui->typeMonth->text();

    if(!db.open()) return;

    if(ui->panelGL->ParticleMgr->IDcounter == 0)
    {
        if(ui->monthsRB->isChecked())
            ui->panelGL->ParticleMgr->numOftimeInterval = 12;
        if(ui->quartersRB->isChecked())
            ui->panelGL->ParticleMgr->numOftimeInterval = 4;
        if(ui->daysRB->isChecked())
            ui->panelGL->ParticleMgr->numOftimeInterval = 31;
    }

    for (int i = 0; i <= ui->treeWidget->topLevelItemCount()-1; i++)
    {
        bool found = true;
        QString groupName = ui->treeWidget->topLevelItem(i)->text(0);
        QString article;

//        QTreeWidgetItem *topItem = new QTreeWidgetItem(ui->myVisualisationTW);
//        topItem->setText(0,groupName + " " + ui->typeYear->text());
//        ui->myVisualisationTW->addTopLevelItem(topItem);

        for(int timeInterval = 1;timeInterval <= ui->panelGL->ParticleMgr->numOftimeInterval; timeInterval++)
        {
            int num = 0;
            int sumprice = 0;

            for (int j = 0; j <= ui->treeWidget->topLevelItem(i)->childCount()-1; j++)
            {
                article = ui->treeWidget->topLevelItem(i)->child(j)->text(0);

               //AddChild(topItem,article);

                QSqlQuery query(db);
                query.setForwardOnly(true);

                if(ui->panelGL->ParticleMgr->numOftimeInterval == 31)
                {
                    query.prepare(" SELECT sum(Amount), sum(RowTotal) FROM View_utb_transactions WHERE ArticleName = :article AND DATEPART(month, Date) = :month AND DATEPART(day, Date) = :timeInterval ");
                    query.bindValue(":article", article);
                    query.bindValue(":month", month);
                    query.bindValue(":timeInterval", timeInterval);
                }
                else
                {
                    if(ui->panelGL->ParticleMgr->numOftimeInterval == 12)
                        query.prepare(" SELECT sum(Amount), sum(RowTotal) FROM View_utb_transactions WHERE ArticleName = :article AND DATEPART(year, Date) = :year AND DATEPART(month, Date) = :timeInterval ");
                    if(ui->panelGL->ParticleMgr->numOftimeInterval == 4)
                        query.prepare(" SELECT sum(Amount), sum(RowTotal) FROM View_utb_transactions WHERE ArticleName = :article AND DATEPART(year, Date) = :year AND DATEPART(quarter, Date) = :timeInterval ");
                    query.bindValue(":article", article);
                    query.bindValue(":year", year);
                    query.bindValue(":timeInterval", timeInterval);
                }

                query.exec();
                query.next();
                num += query.value(0).toInt();
                sumprice += query.value(1).toInt();

            }

            if(ui->panelGL->ParticleMgr->IDcounter == 0)
                ui->panelGL->ParticleMgr->addContainer(timeInterval, num, sumprice, glm::vec4(1.0f,0.0f,0.0f,0.8f));
            else if(ui->panelGL->ParticleMgr->IDcounter == 1)
                ui->panelGL->ParticleMgr->addContainer(timeInterval, num, sumprice, glm::vec4(0.0f,1.0f,0.0f,0.8f));
            else if(ui->panelGL->ParticleMgr->IDcounter == 2)
                ui->panelGL->ParticleMgr->addContainer(timeInterval, num, sumprice, glm::vec4(0.0f,0.0f,1.0f,0.8f));

            ui->panelGL->ParticleMgr->update();
            ui->progressBar->setRange(0,ui->panelGL->ParticleMgr->numOftimeInterval);
            ui->progressBar->setValue(timeInterval);

        }

        if(found)
        {
            QTreeWidgetItem *topItem = new QTreeWidgetItem(ui->myVisualisationTW);
            topItem->setText(0,groupName + " " + ui->typeYear->text());
            ui->myVisualisationTW->addTopLevelItem(topItem);

            for (int j = 0; j <= ui->treeWidget->topLevelItem(i)->childCount()-1; j++)
            {
                article = ui->treeWidget->topLevelItem(i)->child(j)->text(0);
                AddChild(topItem,article);
            }

            ui->listWidget->addItem(groupName + " " + ui->typeYear->text());
            ui->daysRB->setDisabled(true);
            ui->monthsRB->setDisabled(true);
            ui->quartersRB->setDisabled(true);

            ui->panelGL->ParticleMgr->IDcounter++;
        }

    }
    ui->treeWidget->clear();
    ui->marketingWidget->hide();
    ui->addVisualisationPushButton->hide();
    ui->groupWidget->hide();
    ui->startVisualisationPushButton->hide();
    ui->myVisualisationWidget->show();
}

void MainWindow::on_removeVisualisation_clicked()
{
//    if(ui->listWidget->count() > 0)
//    {
//        if(!ui->listWidget->currentItem())
//            return;

//        QListWidgetItem *itm = ui->listWidget->currentItem();
//        if(itm->isSelected())
//        {
//            ui->panelGL->ParticleMgr->removeContainers(itm->listWidget()->currentRow());
//            qDeleteAll(ui->listWidget->selectedItems());
//            ui->panelGL->ParticleMgr->number--;
//            ui->panelGL->ParticleMgr->update();
//            if(ui->panelGL->ParticleMgr->IDcounter == 0)
//            {
//                ui->daysRB->setEnabled(true);
//                ui->monthsRB->setEnabled(true);
//                ui->quartersRB->setEnabled(true);
//            }

//        }
//     }

    QTreeWidgetItem *itm = ui->myVisualisationTW->currentItem();
    if(!itm->parent())
    {
        qDebug() << ui->panelGL->ParticleMgr->IDcounter;
        qDebug() << ui->myVisualisationTW->currentColumn();
//        ui->panelGL->ParticleMgr->removeContainers(0);
        //ui->panelGL->ParticleMgr->removeContainers(ui->myVisualisationTW->currentIndex());
        qDeleteAll(ui->myVisualisationTW->selectedItems());
//        ui->panelGL->ParticleMgr->number--;
//        ui->panelGL->ParticleMgr->update();

        ui->panelGL->ParticleMgr->IDcounter--;

        if(ui->panelGL->ParticleMgr->IDcounter == 0)
        {
            ui->daysRB->setEnabled(true);
            ui->monthsRB->setEnabled(true);
            ui->quartersRB->setEnabled(true);
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


void MainWindow::on_timeRadioButton_clicked()
{
    ui->horizontalSpacer->changeSize(0,0);
    ui->label_11->hide();
    ui->label_12->hide();
    ui->groupBox_6->setDisabled(true);
}

void MainWindow::on_periodRadioButton_clicked()
{
    ui->horizontalSpacer->changeSize(10,0);
    ui->label_11->show();
    ui->label_12->show();
    ui->groupBox_6->setEnabled(true);


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


void MainWindow::on_showMainWindowCheckBox_clicked(bool checked)
{
    if (checked == false)
    {
        ui->myVisualisationWidget->hide();
    }
    else
    {
        ui->myVisualisationWidget->show();
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
//    //ui->addMultipleItems->addItem(arg1);
//    if(ui->treeWidget->topLevelItemCount() == 0)
//    {
//        int i = ui->treeWidget->topLevelItemCount()+1;
//        QString s = QString::number(i);
//        AddRoot("Grupp " + s);
//    }
//    AddChild(getRoot(),arg1);
}

void MainWindow::on_restaurantComboBox_activated(const QString &arg1)
{
//    if(ui->treeWidget->topLevelItemCount() == 0)
//    {
//        int i = ui->treeWidget->topLevelItemCount()+1;
//        QString s = QString::number(i);
//        AddRoot("Grupp " + s);
//    }
//    AddChild(getRoot(),arg1);
}

void MainWindow::on_shopComboBox_activated(const QString &arg1)
{
//    if(ui->treeWidget->topLevelItemCount() == 0)
//    {
//        int i = ui->treeWidget->topLevelItemCount()+1;
//        QString s = QString::number(i);
//        AddRoot("Grupp " + s);
//    }
//    AddChild(getRoot(),arg1);
}

void MainWindow::on_showComboBox_activated(const QString &arg1)
{
//    if(ui->treeWidget->topLevelItemCount() == 0)
//    {
//        int i = ui->treeWidget->topLevelItemCount()+1;
//        QString s = QString::number(i);
//        AddRoot("Grupp " + s);
//    }
//    AddChild(getRoot(),arg1);
}

void MainWindow::on_searchAllArticles_returnPressed()
{
//    float num = 0;
//    QString article = ui->searchAllArticles->text();
//    bool found = false;

//    if(db.open())
//    {
//        QSqlQuery query(db);
//        query.setForwardOnly(true);

//        query.prepare(" SELECT count(*) FROM View_utb_transactions WHERE ArticleName = :article");
//        query.bindValue(":article", article);

//        query.exec();
//        query.next();
//        num = query.value(0).toInt();

//    }

//    if(num > 0)
//    {
//        found = true;
//    }


//    if(found)
//    {
//        QString item;
//        item = ui->searchAllArticles->text();

//        if(ui->treeWidget->topLevelItemCount() == 0)
//        {
//            int i = ui->treeWidget->topLevelItemCount()+1;
//            QString s = QString::number(i);
//            AddRoot("Grupp " + s);
//        }
//        AddChild(getRoot(),item);
//    }

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
    itm->setIcon(1,QIcon(":/MyFiles/pic/bars.png"));
    itm->setExpanded(true);
    itm->setFlags(itm->flags()| (Qt::ItemIsEditable));

    ui->treeWidget->resizeColumnToContents(1);

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


void MainWindow::on_gridCheckBox_toggled(bool checked)
{
    ui->panelGL->showGrid(checked);
}

void MainWindow::on_numbersCheckBox_toggled(bool checked)
{
    ui->panelGL->showNumbers(checked);
}

void MainWindow::on_advanceSettingsAction_triggered()
{
    ui->settingsWidget->show();
    ui->marketingWidget->hide();
    ui->addVisualisationPushButton->hide();
}

void MainWindow::on_createNewAction_triggered()
{
    ui->marketingWidget->show();
    ui->addVisualisationPushButton->show();
    ui->settingsWidget->hide();

}

void MainWindow::on_zoomSlider_valueChanged(int value)
{
    ui->panelGL->zoom(value);
}

void MainWindow::on_closeAction_triggered()
{
    qApp->exit();
}

void MainWindow::on_radioButton_toggled(bool checked)
{
    ui->panelGL->ParticleMgr->entType = QUANTITY;
    ui->panelGL->ParticleMgr->update();
}

void MainWindow::on_radioButton_2_toggled(bool checked)
{
    ui->panelGL->ParticleMgr->entType = EARNINGS;
    ui->panelGL->ParticleMgr->update();
}

void MainWindow::on_radioButton_3_toggled(bool checked)
{
    ui->panelGL->ParticleMgr->entType = MEAN;
    ui->panelGL->ParticleMgr->update();

}
