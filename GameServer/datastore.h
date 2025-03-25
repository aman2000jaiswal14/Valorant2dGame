#ifndef DATASTORE_H
#define DATASTORE_H

#include <QObject>
#include "structures.h"
#include <QList>
#include <QByteArray>
#include <QMutex>
class DataStore : public QObject
{
    Q_OBJECT
public:
    // Get the single instance of the class
    static DataStore& instance()
    {
        static DataStore instance; // This ensures only one instance is created
        return instance;
    }

    // Delete copy constructor and assignment operator to prevent copies
    DataStore(const DataStore&) = delete;
    DataStore& operator=(const DataStore&) = delete;
    STRUCT_ALL_PLAYER_POSITION_INFO allPlayerPosition;
    QList<QByteArray> recvByteArrayList;
    QMutex serverMutex;
private:
    // Private constructor to prevent external instantiation
    DataStore();

    // Add any member variables you need for DataStore
    // Example: int data;
};

#endif // DATASTORE_H
