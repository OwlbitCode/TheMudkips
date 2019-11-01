#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlError>
#include <QDebug>
#include <QSqlQuery>
#include <QSqlError>

/****************************************************************************
 * SQLite FILENAME: ?????.db
 * --------------------------------------------------------------------------
 * TABLES:
 *      Table 1
 *          Data members
 *
 *      Table 2
 ***************************************************************************/
class databaseManager : public QObject
{
public:
    explicit databaseManager();
    ~databaseManager();

    bool openDB();
    //!< Creates and opens a database connection if not open
    /*!< POSTCONDITONS: return database.open(); */

    bool closeDB();
    //!< Closes database connection
    /*!< POSTCONDITONS: return database.isOpen() */

    QSqlError lastError();
    //!< Returns last database related error
    /*!< POSTCONDITONS: return database.lastError(); */

    QSqlDatabase currentDB() const;
    //!< Returns connected database object
    /*!< POSTCONDITONS: return database */

private:
    QSqlDatabase database; // SQL Database Object created for connection
};

#endif // DATABASEMANAGER_H
