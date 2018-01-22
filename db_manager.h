#ifndef DB_MANAGER_H
#define DB_MANAGER_H

#include <QtSql>

class DB_Manager
{
public:
    DB_Manager();
    DB_Manager(const QString& path);
    ~DB_Manager();
    QStringList getListTables();
    QStringList getItems();
    QStringList getItems(const int& id);
    QStringList getItems(const QString& itemsname);
    QStringList getEquipment();
    QStringList getEquipment(const int& id);
    void createTables();
    bool insertIntoItems(const QString& itemsname, const QString& path);
    bool insertIntoEquipment(const int& id, const int& id_item, const int& count);
    bool updateItems(const int& id, const QString& itemsname, const QString& path);
    bool updateItems(const int& id, const QString& itemsname);
    bool updateItems(const QString& itemsname, const QString& path);
    bool updateEquipment(const int& id, const int& newcount);
    bool updateEquipment(const int& id, const QString& itemsname, const int& newcount);
    bool deleteFromItems(const QString& itemsname);
    bool deleteFromEquipment(const int& id);
    bool eraseItems();
    bool eraseEquipment();

private:
    QSqlDatabase db;
    void open(const QString& path);
};

#endif // DB_MANAGER_H
