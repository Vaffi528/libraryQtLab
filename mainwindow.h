#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "headers.h"
#include "database.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    bool setUpTables();
    bool setUpModels();

private slots:
    void on_AuthorsTable_customContextMenuRequested(const QPoint &pos);

private:
    Ui::MainWindow *ui;
    QSqlDatabase db;

    QSqlTableModel* authorsModel;
    QSqlTableModel* genresModel;
    QSqlRelationalTableModel* booksModel;
    QSqlRelationalTableModel* bookGenresModel;
};
#endif // MAINWINDOW_H
