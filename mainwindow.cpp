#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    setAttribute(Qt::WA_DeleteOnClose);

    ui->setupUi(this);
    bool isTablesSet = setUpTables();
    if (!isTablesSet)
        return;

    manager = new DataBaseManager();
    bool isTablesCreated = manager->createTables();
    if (!isTablesCreated)
        return;

    bool isModelsSet = setUpModels();
    if (!isModelsSet)
        return;

    setUpTabs();
    initSubscriptions();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete manager;

    delete authorsTab;
    delete booksTab;
    delete genresTab;

    db.close();
    qDebug() << "БД закрыта успешно!";
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

bool MainWindow::setUpTabs() {
    authorsTab = new AuthorsTab(ui);
    booksTab = new BooksTab(ui);
    genresTab = new GenresTab(ui);
    currentTab = authorsTab;

    qDebug() << "Вкладки инициализированы успешно!";
    return true;
}

void MainWindow::initSubscriptions(){
    connect(ui->tabs, &QTabWidget::currentChanged, this, &MainWindow::onTabChange);

    connect(ui->addBtn, &QPushButton::clicked, this, &MainWindow::onAddBtnClick);
    connect(ui->editBtn, &QPushButton::clicked, this, &MainWindow::onEditBtnClick);
    connect(ui->removeBtn, &QPushButton::clicked, this, &MainWindow::onRemoveBtnClick);
};


void MainWindow::onTabChange() {
    int currentTabIndex = ui->tabs->currentIndex();

    switch (currentTabIndex) {
        case 0:
            currentTab = authorsTab;
            break;
        case 1:
            currentTab = booksTab;
            break;
        case 2:
            currentTab = genresTab;
            break;
    }

};

void MainWindow::onAddBtnClick() {
    currentTab->AddRecord();
};
void MainWindow::onEditBtnClick() {
    currentTab->EditRecord();
};
void MainWindow::onRemoveBtnClick() {
    currentTab->RemoveRecord();
};

void MainWindow::on_AuthorsTable_customContextMenuRequested(const QPoint &pos)
{

}

