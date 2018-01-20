#ifndef DB_MANAGER_H
#define DB_MANAGER_H

#include <QtSql>

class DB_Manager
{
public:
    DB_Manager();
    DB_Manager(const QString& path);
    void open(const QString& path);
    ~DB_Manager();
    QStringList getListTables();
    QStringList getAllItems();
    QStringList getEquipment();
    void createTables();
    bool insertIntoItems(const QString& itemsname, const QString& path);
    bool insertIntoEquipment(const int& id, const int& id_item, const int& count);
    bool deleteFromItems(const QString& itemsname);
    bool deleteFromEquipment(const int& id);


private:
    QSqlDatabase db;
};

#endif // DB_MANAGER_H
