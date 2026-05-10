#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "headers.h"
#include "database.h"
#include "AbstractTab.h"
#include "AuthorsTab.h"
#include "BooksTab.h"
#include "GenresTab.h"

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
    bool setUpTabs();
    void initSubscriptions();

private slots:
    void on_AuthorsTable_customContextMenuRequested(const QPoint &pos);
    void onTabChange();
    void onAddBtnClick();
    void onEditBtnClick();
    void onRemoveBtnClick();

private:
    Ui::MainWindow *ui;
    QSqlDatabase db;

    QSqlTableModel* authorsModel;
    QSqlTableModel* genresModel;
    QSqlRelationalTableModel* booksModel;
    QSqlRelationalTableModel* bookGenresModel;

    DataBaseManager* manager;

    AbstractTab* currentTab;

    AuthorsTab* authorsTab;
    BooksTab* booksTab;
    GenresTab* genresTab;
};
#endif // MAINWINDOW_H
