#include "mainwindow.h"
#include <QApplication>

#include <QtGui>
#include <QtSql/QtSql>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    QTableWidget* table = new QTableWidget();
    table->setWindowTitle("Connect to Sql Database Example");

    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");

    db.setDatabaseName("DRIVER=SQL Server;SERVER=62.168.149.41;DATABASE=ActorPLATSBOKVISUALC_utb;UID=Visual_utb;PWD=");

    if (!db.open())
    {
        QMessageBox::critical(0, QObject::tr("Database Error"),
        db.lastError().text());
    }
    else
    {
        QSqlQuery query("SELECT * FROM View_utb_Events");

        int rows = query.numRowsAffected();
        int columns = query.record().count();

        table->setColumnCount(columns);
        table->setRowCount(rows);
        query.next();

        for(int i = 0; i < rows; i++)
        {
            for(int j = 0; j < columns; j++)
            {
                table->setItem(i,j,new QTableWidgetItem(query.value(j).toString()));
            }
            query.next();
        }
        table->show();
    }

    return a.exec();
}
