#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QSettings>
#include <QtGui>
#include <QFontDatabase>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


        QStringList list;
        list << "Roboto-Bold.ttf" << "Roboto-Medium.ttf" << "Roboto-Regular.ttf";
        int fontID(-1);
        bool fontWarningShown(false);
        for (QStringList::const_iterator constIterator = list.constBegin(); constIterator != list.constEnd(); ++constIterator)
        {
            QFile res(":/MyFiles/" + *constIterator);
            if (res.open(QIODevice::ReadOnly) == false)
            {
                if (fontWarningShown == false)
                {
                    QMessageBox::warning(0, "Application", (QString)"Impossible heje " + QChar(0x00AB) + " RobotoMedium " + QChar(0x00BB) + ".");
                    fontWarningShown = true;
                }
            }
            else
            {
                fontID = QFontDatabase::addApplicationFontFromData(res.readAll());
                if (fontID == -1 && fontWarningShown == false)
                {
                    QMessageBox::warning(0, "Application", (QString)"hej hej monika " + QChar(0x00AB) + " Roboto-Medium " + QChar(0x00BB) + ".");
                    fontWarningShown = true;
                }
            }
        }


    ui->addVisualisationPushButton->setDisabled(true);

    ui->settingsWidget->hide();
    ui->groupWidget->hide();
    ui->myVisualisationWidget->hide();
    ui->startVisualisationPushButton->hide();

    ui->monthsRB->setChecked(true);

    ui->panelGL->showGrid(false);
    ui->panelGL->showNumbers(false);

    ui->progressBar->reset();
    ui->progressBar->setTextVisible(false);

    ui->myVisualisationTW->setColumnCount(2);
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
//    ui->searchAllArticles->setStyleSheet("color: blue;"
//                                         "background-color: yellow;"
//                                         "selection-color:red;"
//                                         "selection-background-color: blue;");

    QString placeholderYear;
    placeholderYear =  QString::fromUtf8("ÅR");
    ui->typeYearLE->setPlaceholderText(placeholderYear);

    QStringList CompletionYear;
    CompletionYear << "2010" << "2011" << "2012";
    StringCompleter = new QCompleter(CompletionYear,this);
    StringCompleter->setCaseSensitivity(Qt::CaseInsensitive);
    ui->typeYearLE->setCompleter(StringCompleter);

    QString placeholderMonth;
    placeholderMonth =  QString::fromUtf8("MÅNAD");
    ui->typeMonthLE->setPlaceholderText(placeholderMonth);

    QStringList CompletionMonth;

    for (int i = 0; i <= 12; i++)
    {
        QString s = QString::number(i);
        CompletionMonth << s;
    }

    StringCompleter = new QCompleter(CompletionMonth,this);
    StringCompleter->setCaseSensitivity(Qt::CaseInsensitive);
    ui->typeMonthLE->setCompleter(StringCompleter);

    QString placeholderDay;
    placeholderDay =  QString::fromUtf8("DAG");
    ui->typeDayLE->setPlaceholderText(placeholderDay);

    QStringList CompletionDay;

    for (int i = 0; i <= 31; i++)
    {
        QString s = QString::number(i);
        CompletionDay << s;
    }

    StringCompleter = new QCompleter(CompletionDay,this);
    StringCompleter->setCaseSensitivity(Qt::CaseInsensitive);
    ui->typeDayLE->setCompleter(StringCompleter);


    QPixmap pixmap4(":/MyFiles/pic/iconTriangle.png");
    QIcon triangleButtonIcon;
    triangleButtonIcon.addPixmap(pixmap4);

    ui->addVisualisationPushButton->setIcon(triangleButtonIcon);
    ui->addVisualisationPushButton->setIconSize(QSize(100,450));
    ui->addVisualisationPushButton->setMask(pixmap4.mask());

    ui->startVisualisationPushButton->setIcon(triangleButtonIcon);
    ui->startVisualisationPushButton->setIconSize(QSize(100,450));
    ui->startVisualisationPushButton->setMask(pixmap4.mask());


    QPixmap pixmap(":/MyFiles/pic/iconLines.png");
    ui->lineLabel->setPixmap(pixmap);
    ui->lineLabel->setScaledContents(true);

    QPixmap pixmap2(":/MyFiles/pic/iconBars.png");
    ui->barLabel->setPixmap(pixmap2);
    ui->barLabel->setScaledContents(true);

    ui->barspacingLabel->setPixmap(pixmap2);
    ui->barspacingLabel->setScaledContents(true);

    QPixmap barWidthPixmap(":/MyFiles/pic/iconBarWidth.png");
    ui->barwidthLabel->setPixmap(barWidthPixmap);
    ui->barwidthLabel->setScaledContents(true);

    ui->zoomLabel->setPixmap(pixmap2);
    ui->zoomLabel->setScaledContents(true);

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
    settings.setValue("barSpace", ui->barSpacingSlider->value());
}

void MainWindow::loadSettings()
{
    QSettings settings("Visualiseringscenter C", "ViC");

    resize(settings.value("windowSize", QSize(1537, 677)).toSize());
    move(settings.value("windowPos", QPoint(200, 200)).toPoint());

    ui->barWidthSlider->setValue(settings.value("barWidth", 10).toInt());
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
            AddChild(getRoot(),item, ui->typeYearLE->text());
            ui->searchAllArticles->clear();
        }

        if(ui->selectAllTicketCheckBox->isChecked() && query.exec("SELECT ArticleName FROM View_utb_Articles WHERE ArticleGroup IN (1100, 1700, 1800, 2300)"))
        {

            while(query.next())
            {
                //AddChild(getRoot(),query.value(0).toString());
            }
        }

        if(ui->selectAllRestaurantCheckBox->isChecked() && query.exec(" SELECT ArticleName FROM View_utb_Articles WHERE ArticleGroup IN (3100, 3102, 3210, 3220, 3240, 3250, 3260) "))
        {

            while(query.next())
            {
                //AddChild(getRoot(),query.value(0).toString());
            }
        }

        if(ui->selectAllShopCheckBox->isChecked() && query.exec(" SELECT ArticleName FROM View_utb_Articles WHERE ArticleGroup IN (110, 140, 150, 160, 170, 180, 190, 200, 210, 300, 500, 600, 700, 3270, 9991, 9992) "))
        {

            while(query.next())
            {
                //AddChild(getRoot(),query.value(0).toString());
            }
        }

        if(ui->ticketComboBox->currentIndex())
        {
            QString selectedItem = ui->ticketComboBox->currentText();
            AddChild(getRoot(),selectedItem, ui->typeYearLE->text());
            ui->ticketComboBox->setCurrentIndex(0);
        }

        if(ui->restaurantComboBox->currentIndex())
        {
            QString selectedItem = ui->restaurantComboBox->currentText();
            AddChild(getRoot(),selectedItem, ui->typeYearLE->text());
            ui->restaurantComboBox->setCurrentIndex(0);
        }

        if(ui->shopComboBox->currentIndex())
        {
            QString selectedItem = ui->shopComboBox->currentText();
            AddChild(getRoot(),selectedItem, ui->typeYearLE->text());
            ui->shopComboBox->setCurrentIndex(0);
        }

        ui->groupWidget->show();
        ui->startVisualisationPushButton->show();

    }
}




void MainWindow::on_startVisualisationPushButton_clicked()
{
    QString year = ui->typeYearLE->text();
    QString month = ui->typeMonthLE->text();

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
                article = ui->treeWidget->topLevelItem(i)->child(j)->text(0).toLatin1();
                qDebug() << article;
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
            if(ui->treeWidget->topLevelItem(i)->childCount() > 0)
            {
                if(ui->panelGL->ParticleMgr->IDcounter == 0)
                    ui->panelGL->ParticleMgr->addContainer(timeInterval, num, sumprice, glm::vec4(0.0f, (1.0f/255.0f)*161.0f, (1.0f/255.0f)*221.0f, 1.0f));
                else if(ui->panelGL->ParticleMgr->IDcounter == 1)
                    ui->panelGL->ParticleMgr->addContainer(timeInterval, num, sumprice, glm::vec4((1.0f/255.0f)*195.0f, (1.0f/255.0f)*7.0f, (1.0f/255.0f)*89.0f, 1.0f));
                else if(ui->panelGL->ParticleMgr->IDcounter == 2)
                    ui->panelGL->ParticleMgr->addContainer(timeInterval, num, sumprice, glm::vec4((1.0f/255.0f)*255.0f, (1.0f/255.0f)*202.0f, (1.0f/255.0f)*54.0f, 1.0f));
                else if(ui->panelGL->ParticleMgr->IDcounter == 3)
                    ui->panelGL->ParticleMgr->addContainer(timeInterval, num, sumprice, glm::vec4((1.0f/255.0f)*12.0f, (1.0f/255.0f)*174.0f, (1.0f/255.0f)*50.0f, 1.0f));

                ui->panelGL->ParticleMgr->update();
                ui->progressBar->setRange(0,ui->panelGL->ParticleMgr->numOftimeInterval);
                ui->progressBar->setValue(timeInterval);
            }
        }

        if(found && ui->treeWidget->topLevelItem(i)->childCount() > 0)
        {
            QPixmap pixmap(":/MyFiles/pic/iconRemove.png");
            if(ui->panelGL->ParticleMgr->IDcounter == 0)
                pixmap.fill(QColor(0,161,221));
            else if(ui->panelGL->ParticleMgr->IDcounter == 1)
                pixmap.fill(QColor(195,7,89));
            else if(ui->panelGL->ParticleMgr->IDcounter == 2)
                pixmap.fill(QColor(255,202,54));
            else if(ui->panelGL->ParticleMgr->IDcounter == 3)
                pixmap.fill(QColor(12,174,50));

            //pixmap.setMask(pixmap);
            QLabel *indicatorColor = new QLabel();

//            indicatorColor->setAutoFillBackground(true);
//            QColor(1,0,1);

            indicatorColor->setPixmap(pixmap);
            indicatorColor->setMinimumSize(15,15);
            indicatorColor->setMaximumSize(15,15);
            //indicatorColor->setMask(pixmap);
            QTreeWidgetItem *topItem = new QTreeWidgetItem(ui->myVisualisationTW);
            topItem->setText(0,groupName + " " + ui->typeYearLE->text());
            ui->myVisualisationTW->addTopLevelItem(topItem);
            ui->myVisualisationTW->setItemWidget(topItem,1,indicatorColor);
            ui->myVisualisationTW->header()->resizeSection(0,130);
            ui->myVisualisationTW->header()->resizeSection(1,20);

            for (int j = 0; j <= ui->treeWidget->topLevelItem(i)->childCount()-1; j++)
            {
                article = ui->treeWidget->topLevelItem(i)->child(j)->text(0);
                AddChild(topItem,article, ui->typeYearLE->text());
            }

            ui->daysRB->setDisabled(true);
            ui->monthsRB->setDisabled(true);
            ui->quartersRB->setDisabled(true);

            ui->panelGL->ParticleMgr->IDcounter++;
        }

    }
    ui->treeWidget->clear();
    ui->marketingWidget->hide();
    ui->addVisualisationPushButton->hide();
    ui->addVisualisationPushButton->setDisabled(true);
    ui->groupWidget->hide();
    ui->startVisualisationPushButton->hide();
    ui->myVisualisationWidget->show();
    ui->typeYearLE->clear();
}

void MainWindow::on_removeVisualisation_clicked()
{
    if(ui->myVisualisationTW->topLevelItemCount() > 0)
    {
        if(!ui->myVisualisationTW->currentItem())
            return;

        QTreeWidgetItem *itm = ui->myVisualisationTW->currentItem();
        if(!itm->parent() && itm->isSelected())
        {

            ui->panelGL->ParticleMgr->removeContainers(ui->myVisualisationTW->currentIndex().row());

            qDeleteAll(ui->myVisualisationTW->selectedItems());
            ui->panelGL->ParticleMgr->number--;
            ui->panelGL->ParticleMgr->update();

            //ui->panelGL->ParticleMgr->IDcounter--;

            if(ui->panelGL->ParticleMgr->IDcounter == 0)
            {
                ui->daysRB->setEnabled(true);
                ui->monthsRB->setEnabled(true);
                ui->quartersRB->setEnabled(true);
            }
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
    //ui->timePositionSlider->setEnabled(checked);
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


QTreeWidgetItem* MainWindow::getRoot()
{
    QTreeWidgetItem *treeItem = ui->treeWidget->topLevelItem(ui->treeWidget->topLevelItemCount()-1);
    return treeItem;
}

void MainWindow::AddRoot(QString name)
{
    QTreeWidgetItem *itm = new QTreeWidgetItem(ui->treeWidget);
    itm->setText(0,name);    
    itm->setExpanded(true);
    itm->setFlags(itm->flags()| (Qt::ItemIsEditable));

    QPixmap pixmap(":/MyFiles/pic/iconRemove.png");
    QIcon removeIcon;
    removeIcon.addPixmap(pixmap);
    QToolButton *rButton = new QToolButton();
    rButton->setIcon(removeIcon);
    rButton->setIconSize(QSize(20,20));
    //rButton->setMask(pixmap.mask());
    rButton->setMinimumSize(25,25);
    rButton->setMaximumSize(25,25);
    //ui->treeWidget->resizeColumnToContents(0);
    ui->treeWidget->setItemWidget(itm,1,rButton);
    ui->treeWidget->header()->resizeSection(0,210);
    ui->treeWidget->header()->resizeSection(1,20);

//    ui->addVisualisationPushButton->setMask(pixmap4.mask());

    ui->treeWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);


    QObject::connect(rButton,SIGNAL(clicked()),this,SLOT(setFocus()));
    QObject::connect(rButton,SIGNAL(clicked()),this,SLOT(removeItems()));


}

void MainWindow::AddChild(QTreeWidgetItem *parent, QString name, QString secondName)
{
    QTreeWidgetItem *itm = new QTreeWidgetItem();
    itm->setText(0,name);
    itm->setBackground(0,*(new QBrush(Qt::red,Qt::Dense6Pattern)));
    itm->setText(1,secondName);
    parent->addChild(itm);
}

void MainWindow::removeItems()
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
    ui->panelGL->ParticleMgr->changeEntity();
    ui->panelGL->ParticleMgr->update();
}

void MainWindow::on_radioButton_2_toggled(bool checked)
{
    ui->panelGL->ParticleMgr->entType = EARNINGS;
    ui->panelGL->ParticleMgr->changeEntity();
    ui->panelGL->ParticleMgr->update();
}

void MainWindow::on_radioButton_3_toggled(bool checked)
{
    ui->panelGL->ParticleMgr->entType = MEAN;
    ui->panelGL->ParticleMgr->changeEntity();
    ui->panelGL->ParticleMgr->update();

}

bool MainWindow::comboBoxItemCanged()
{
  int initialIndex = 0;
  int currentTicketIndex = ui->ticketComboBox->currentIndex();
  int currentRestaurantIndex = ui->restaurantComboBox->currentIndex();
  int currentShopIndex = ui->shopComboBox->currentIndex();
  qDebug() << initialIndex << currentTicketIndex << currentRestaurantIndex << currentShopIndex;
  if(initialIndex == currentTicketIndex && initialIndex == currentRestaurantIndex && initialIndex == currentShopIndex)
      return false;
  else
      return true;

}

void MainWindow::on_typeYearLE_editingFinished()
{
    //ui->ticketComboBox->editTextChanged();
    if(!ui->typeYearLE->text().isEmpty() && !ui->searchAllArticles->text().isEmpty() || ui->selectAllTicketCheckBox->isChecked() || comboBoxItemCanged() )
    {
        ui->addVisualisationPushButton->setEnabled(true);
        //ui->addVisualisationPushButton->setStyleSheet("QPushButton{background-color:red; } QPushButton:focus{background-color:blue;}");
        QPixmap pixmap4(":/MyFiles/pic/iconTriangle.png");
        QIcon triangleButtonIcon;

        triangleButtonIcon.addPixmap(pixmap4);
        ui->addVisualisationPushButton->setIcon(triangleButtonIcon);
        ui->addVisualisationPushButton->setIconSize(QSize(100,450));
        ui->addVisualisationPushButton->setMask(pixmap4.mask());
     }
}

void MainWindow::setRoundedCorners(int radius_tl, int radius_tr, int radius_bl, int radius_br) {
    QRegion region(0, 0, width(), height(), QRegion::Rectangle);

    // top left
    QRegion round (0, 0, 2*radius_tl, 2*radius_tl, QRegion::Ellipse);
    QRegion corner(0, 0, radius_tl, radius_tl, QRegion::Rectangle);
    region = region.subtracted(corner.subtracted(round));

    // top right
    round = QRegion(width()-2*radius_tr, 0, 2*radius_tr, 2*radius_tr, QRegion::Ellipse);
    corner = QRegion(width()-radius_tr, 0, radius_tr, radius_tr, QRegion::Rectangle);
    region = region.subtracted(corner.subtracted(round));

    // bottom right
    round = QRegion(width()-2*radius_br, height()-2*radius_br, 2*radius_br, 2*radius_br, QRegion::Ellipse);
    corner = QRegion(width()-radius_br, height()-radius_br, radius_br, radius_br, QRegion::Rectangle);
    region = region.subtracted(corner.subtracted(round));

    // bottom left
    round = QRegion(0, height()-2*radius_bl, 2*radius_bl, 2*radius_bl, QRegion::Ellipse);
    corner = QRegion(0, height()-radius_bl, radius_bl, radius_bl, QRegion::Rectangle);
    region = region.subtracted(corner.subtracted(round));

    setMask(region);
}


void MainWindow::on_removePushButton_clicked()
{
    ui->treeWidget->clear();
}


void MainWindow::on_quartersRB_toggled(bool checked)
{
    if(checked)
    {
        ui->typeMonthLE->setDisabled(true);
        ui->typeDayLE->setDisabled(true);
    }

}

void MainWindow::on_monthsRB_toggled(bool checked)
{
    if(checked)
    {
        ui->typeMonthLE->setEnabled(true);
        ui->typeDayLE->setDisabled(true);
    }

}

void MainWindow::on_checkBox_toggled(bool checked)
{
    if(checked)
    {
        ui->zoomSlider->setDisabled(true);
    }
    else
    {
        ui->zoomSlider->setEnabled(true);
    }
}

void MainWindow::on_advanceSettingsAction_toggled(bool arg1)
{
    if(arg1)
    {
        ui->settingsWidget->show();
    }
    else
    {
        ui->settingsWidget->hide();
    }
}
