#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    setAttribute(Qt::WA_DeleteOnClose);

    ui->setupUi(this);
    bool isDBSet = setUpDatabase();
    if (!isDBSet)
        return;

    DataBaseManager* manager = DataBaseManager::getInstance();
    Status isTablesCreated = manager->createTables();
    if (isTablesCreated == Status::DB_SETUP_FAILED)
        return;

    bool isModelsSet = setUpModels();
    if (!isModelsSet)
        return;

    setUpTabs();
    initSubscriptions();
}

MainWindow::~MainWindow()
{
    db.close();
    delete ui;
    qDebug() << "БД закрыта успешно!";
}

bool MainWindow::setUpDatabase() {
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
    authorsModel->setHeaderData(1, Qt::Horizontal, "Имя автора");

    genresModel = new QSqlTableModel(this, db);
    genresModel->setTable("genres");
    genresModel->setEditStrategy(QSqlTableModel::OnFieldChange);
    bool isSelected2 = genresModel->select();
    genresModel->setHeaderData(1, Qt::Horizontal, "Жанр");

    booksModel = new QSqlRelationalTableModel(this, db);
    booksModel->setTable("books");
    booksModel->setEditStrategy(QSqlTableModel::OnFieldChange);
    bool isSelected3 = booksModel->select();
    booksModel->setHeaderData(2, Qt::Horizontal, "Книга");

    bookGenresModel = new QSqlRelationalTableModel(this, db);
    bookGenresModel->setTable("books_genres");
    bookGenresModel->setEditStrategy(QSqlTableModel::OnFieldChange);
    bool isSelected4 = bookGenresModel->select();

    currentModel = authorsModel;

    if (!(isSelected1 && isSelected2 && isSelected3 && isSelected4)){
        qDebug() << "Ошибка выбора одной из моделей";
        return false;
    }
    qDebug() << "Модели выбраны успешно!";
    return true;
}

bool MainWindow::setUpTabs() {
    authorsTab = new AuthorsTab(ui->authorsTableView);
    ui->authorsTableView->setModel(authorsModel);
    ui->authorsTableView->hideColumn(0);

    booksTab = new BooksTab(ui->booksTableView);
    ui->booksTableView->setModel(booksModel);
    ui->booksTableView->hideColumn(0);
    ui->booksTableView->hideColumn(1);

    genresTab = new GenresTab(ui->genresTableView);
    ui->genresTableView->setModel(genresModel);
    ui->genresTableView->hideColumn(0);

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
            currentModel = authorsModel;
            break;
        case 1:
            currentTab = booksTab;
            currentModel = booksModel;
            break;
        case 2:
            currentTab = genresTab;
            currentModel = genresModel;
            break;
    }

};

void MainWindow::onAddBtnClick() {
    bool isOk = currentTab->AddRecord();
    if (isOk)
        currentModel->select();
    else
        qDebug() << "Ошибка: запись не была добавлена!";
};

void MainWindow::onEditBtnClick() {
    bool isOk = currentTab->EditRecord();
    if (isOk)
        currentModel->select();
    else
        qDebug() << "Ошибка: запись не была изменена!";
};

void MainWindow::onRemoveBtnClick() {
    bool isOk = currentTab->RemoveRecord();
    if (isOk)
        currentModel->select();
    else
        qDebug() << "Ошибка: запись не была удалена!";
};

void MainWindow::on_AuthorsTable_customContextMenuRequested(const QPoint &pos)
{

}

