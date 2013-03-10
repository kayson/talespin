#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    fullscreen = false;
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::keyPressEvent(QKeyEvent *event)
{
    switch (event->key())
    {
        case Qt::Key_Escape:
            close();
            break;
    }

}

void MainWindow::addBar()
{
    float num = ui->spinBox->value();
    QString col = ui->comboBox->currentText();
    if(col == "Red")
        ui->panelGL->ParticleMgr->AddParticleContainer(num, glm::vec4(1.0f,0.0f,0.0f,1.0f));
    else if(col == "Green")
        ui->panelGL->ParticleMgr->AddParticleContainer(num, glm::vec4(0.0f,1.0f,0.0f,1.0f));
    else if(col == "Blue")
        ui->panelGL->ParticleMgr->AddParticleContainer(num, glm::vec4(0.0f,0.0f,1.0f,1.0f));

    ui->panelGL->ParticleMgr->update();
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
