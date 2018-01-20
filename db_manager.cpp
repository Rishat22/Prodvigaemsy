#include "db_manager.h"

DB_Manager::DB_Manager()
{
    open("db_playEquipment.sqlite");
}

DB_Manager::DB_Manager(const QString& path)
{
    open(path);
}

void DB_Manager::open(const QString& path)
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(path);
    if (!db.open()) {
        qDebug() << "Database CANNOT open!";
    }
}

QStringList DB_Manager::getListTables()
{
    if(db.isOpen())
        return db.tables();
    return QStringList();
}

void DB_Manager::createTables()
{
    if(db.isOpen())
    {
        QSqlQuery query(db);
        QString   str  = "CREATE TABLE IF NOT EXISTS items("
                         " id INTEGER PRIMARY KEY AUTOINCREMENT, "
                         " name VARCHAR(255) NOT NULL, "
                         " pic VARCHAR(255)"
                         ")";
        if (!query.exec(str)) {
            qDebug() << "Unable to create a table ITEMS: " << query.lastError();
        }
        str  = "CREATE TABLE IF NOT EXISTS equipment("
               "id INTEGER PRIMARY KEY NOT NULL, "
               "id_item INTEGER NOT NULL, "
               "count INTEGER, "
               "FOREIGN KEY (id_item) REFERENCES items(id)"
               ")";
        if (!query.exec(str)) {
            qDebug() << "Unable to create a table EQUIPMENT: "<< query.lastError();
        }
    }
}


bool DB_Manager::insertIntoItems(const QString &itemsname, const QString &path)
{
    if (itemsname.length() < 1 || path.length() < 1)
        return false;
    QSqlQuery query(db);
    query.prepare("INSERT INTO items (name, pic) VALUES (:itemsname, :pic)");
    query.bindValue(":itemsname", itemsname);
    query.bindValue(":pic", path);
    if(query.exec())
        return true;
    else
    {
        qDebug() << "AddItem error: " << query.lastError();
        return false;
    }
}

bool DB_Manager::insertIntoEquipment(const int &id, const int &id_item, const int &count)
{
    if (id < 1 || id_item < 1 || count < 0)
        return false;
    QSqlQuery query(db);
    query.prepare("INSERT INTO equipment (id, id_item, count) VALUES (:id, :id_item, :count)");
    query.bindValue(":id", id);
    query.bindValue(":id_item", id_item);
    query.bindValue(":count", count);
    if(query.exec())
        return true;
    else
    {
        qDebug() << "AddEquipment error: " << query.lastError();
        return false;
    }
}


