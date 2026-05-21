# ПРОЕКТ QT LIBRARY

## СТРУКТУРА:
*(Описание классов и файлов проекта)*

- **`AbstractTab.h`** - виртуальный класс, интерфейс для управления вкладками `AuthorsTab.h`, `BooksTab.h` и `GenresTab.h`
- **`AuthorsTab`, `BooksTab` и `GenresTab`** - наследники `AbstractTab`, реализуют логику работы программы (создание, редактирование и удаление записей)
- **`BookDialog.h`** - класс кастомного диалога для окна добавления и редактирования книги
- **`CodeStatus.h`** - `enum` с кодами возврата для `DataBaseManager` и методов классов `AuthorsTab`, `BooksTab` и `GenresTab`
- **`database.h`** - singleton класс `DataBaseManager` (менеджер для управления базой данных). Реализует всю логику добавления/редактирования/удаления записей на уровне БД
- **`DialogsData.h`** - POD-классы, отвечают за группировку данных диалоговых окон для их дальнейшей передачи в методы класса `DataBaseManager`
- **`headers.h`** - подключает основные зависимости
- **`mainwindow.h`** - главное окно

## СХЕМА БАЗЫ ДАННЫХ
![Схема БД](https://github.com/user-attachments/assets/956038f5-9dc5-4ab0-90f2-c4b73bdb91bc)

## ИНТЕРФЕЙС

### Вкладки
![Вкладка 1](https://github.com/user-attachments/assets/9872483a-6b3d-43c3-81fb-8c1c9852ac42)
![Вкладка 2](https://github.com/user-attachments/assets/223d4c83-d7a2-44e6-931c-1cc0098d3ab4)
![Вкладка 3](https://github.com/user-attachments/assets/6313f36c-a1db-47f6-ad56-246346015c7c)

### Добавление автора, жанра, книги
![Добавление 1](https://github.com/user-attachments/assets/8618c7a6-cf27-406c-8400-a418f3cc927b)
![Добавление 2](https://github.com/user-attachments/assets/12305e7a-7116-42ec-be6c-ef21225a7a8b)
![Добавление 3](https://github.com/user-attachments/assets/98d240e9-5588-4735-ae94-dc1457a8b618)
![Добавление 4](https://github.com/user-attachments/assets/760e0e92-fd70-4b67-be1b-5c78a1fc0fa4)
![Добавление 5](https://github.com/user-attachments/assets/698fb7a5-aa89-4f50-a2b7-3ff7476d6161)
![Добавление 6](https://github.com/user-attachments/assets/896b4c7a-7ed6-478f-9215-325345c478ee)
![Добавление 7](https://github.com/user-attachments/assets/d0be6467-25d3-4379-8b3b-cee461def0e1)
![Добавление 8](https://github.com/user-attachments/assets/cfa06790-337a-43df-a952-9e2014717207)

### Граничные случаи для авторов (редактирование и удаление)
![Авторы 1](https://github.com/user-attachments/assets/3b582cef-a7d0-4e9b-9060-8f91df08d115)
![Авторы 2](https://github.com/user-attachments/assets/2174f312-38ba-4a29-bab9-714f3cf2c8ac)
![Авторы 3](https://github.com/user-attachments/assets/1beb4b66-3091-4a21-bc11-781ed6c8f73f)
![Авторы 4](https://github.com/user-attachments/assets/991ebbe6-2f75-40ea-9e9f-d1d8424e8881)
![Авторы 5](https://github.com/user-attachments/assets/645eefd1-2f78-41bf-984b-30545398f705)
![Авторы 6](https://github.com/user-attachments/assets/df0a047c-fb78-4b31-8f47-49f31f2436c3)
![Авторы 7](https://github.com/user-attachments/assets/b96512ed-d416-46e8-9ab9-e4e23de3adfc)
![Авторы 8](https://github.com/user-attachments/assets/d3606233-beed-4f1c-bef0-2515cfffd2d3)

### Граничные случаи для жанров (редактирование и удаление)
![Жанры 1](https://github.com/user-attachments/assets/09424c2c-4a9c-4c1a-9b91-04e6b72e83a8)
![Жанры 2](https://github.com/user-attachments/assets/11f2392d-3921-4233-b330-bf16b023ce02)
![Жанры 3](https://github.com/user-attachments/assets/26c9b351-1cc2-4e3b-b036-0f23432fe30f)
![Жанры 4](https://github.com/user-attachments/assets/db65d3a6-452b-490d-9597-6901a6143f81)
![Жанры 5](https://github.com/user-attachments/assets/9f4c0d0f-c620-4769-8ba5-785921ee3677)

### Граничные случаи для книг (редактирование и удаление)
![Книги 1](https://github.com/user-attachments/assets/9a1f7c94-1cac-4c63-8f76-e941ee37f464)
![Книги 2](https://github.com/user-attachments/assets/046c7117-74af-4f81-a2ce-f4863b62db82)
![Книги 3](https://github.com/user-attachments/assets/ed08b060-8a0a-47be-9d6a-4230828c5f29)
![Книги 4](https://github.com/user-attachments/assets/2e171616-580d-44cd-8f89-7fcc7e7cb598)
![Книги 5](https://github.com/user-attachments/assets/56d71a0b-2eed-4df2-8ad7-0265aeb1c5bf)
![Книги 6](https://github.com/user-attachments/assets/f307c987-2db6-44c4-a266-3b6b05b5d04a)
![Книги 7](https://github.com/user-attachments/assets/9fc6aa5b-68bb-4c93-999f-d526821adcbf)
![Книги 8](https://github.com/user-attachments/assets/e3d58d4d-403c-424d-b292-9ccb0095593a)
![Книги 9](https://github.com/user-attachments/assets/f47d24a3-aca4-4618-a89b-59bd83e64215)
![Книги 10](https://github.com/user-attachments/assets/71a7fa5b-b743-4edb-aa85-3df3126450e5)
