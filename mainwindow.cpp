#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    bool isTablesSet = setUpTables();
    if (!isTablesSet)
        return;

    DataBaseManager manager;
    bool isCreated = manager.createTables();
    if (!isCreated)
        return;

    bool isModelsSet = setUpModels();
    if (!isModelsSet)
        return;
}

bool MainWindow::setUpTables() {
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("library.db");
    if (!db.open()) {
        qDebug() << "Ошибка открытия базы данных:" << db.lastError().text();
        return false;
    }
    qDebug() << "БД открыта успешно!";
    return true;
}

bool MainWindow::setUpModels() {
    authorsModel = new QSqlTableModel(this, db);
    authorsModel->setTable("authors");
    authorsModel->setEditStrategy(QSqlTableModel::OnFieldChange);
    bool isSelected1 = authorsModel->select();

    genresModel = new QSqlTableModel(this, db);
    genresModel->setTable("genres");
    genresModel->setEditStrategy(QSqlTableModel::OnFieldChange);
    bool isSelected2 = genresModel->select();

    booksModel = new QSqlRelationalTableModel(this, db);
    booksModel->setTable("books");
    booksModel->setEditStrategy(QSqlTableModel::OnFieldChange);
    bool isSelected3 = booksModel->select();

    bookGenresModel = new QSqlRelationalTableModel(this, db);
    bookGenresModel->setTable("books_genres");
    bookGenresModel->setEditStrategy(QSqlTableModel::OnFieldChange);
    bool isSelected4 = bookGenresModel->select();


    if (!(isSelected1 && isSelected2 && isSelected3 && isSelected4)){
        qDebug() << "Ошибка выбора одной из моделей";
        return false;
    }
    qDebug() << "Модели выбраны успешно!";
    return true;
}


MainWindow::~MainWindow()
{
    delete ui;
    db.close();
}

void MainWindow::on_AuthorsTable_customContextMenuRequested(const QPoint &pos)
{

}

