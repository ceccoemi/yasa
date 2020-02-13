#include "SqliteYasa.h"

#include <sqlite3.h>
#include <stddef.h>
#include <unistd.h>
#include <stdexcept>

sqlite3 *openDb(const char *dbName) {
  sqlite3 *db;
  int rst = sqlite3_open(dbName, &db);
  if (rst) {
    throw std::runtime_error(sqlite3_errmsg(db));
  }
  return db;
}

SqliteYasa::SqliteYasa(std::string dbName) {
  this->dbName = dbName;
  sqlite3 *db = openDb(this->dbName.c_str());
  sqlite3_close(db);
}

static int storeQueryResult(void *output, int argc, char **argv,
                            char **colName) {
  SqliteYasa::QueryResult *result =
      static_cast<SqliteYasa::QueryResult *>(output);
  for (int i = 0; i < argc; i++) {
    result->operator[](colName[i]).push_back(argv[i]);
  }
  return 0;
}

SqliteYasa::QueryResult SqliteYasa::query(std::string sqlQuery) {
  sqlite3 *db = openDb(dbName.c_str());
  SqliteYasa::QueryResult queryResult;
  char *errorMessage;
  int rst = sqlite3_exec(db, sqlQuery.c_str(), storeQueryResult,
                         static_cast<void *>(&queryResult), &errorMessage);
  if (rst != SQLITE_OK) {
    std::string msg = errorMessage;
    sqlite3_free(errorMessage);
    sqlite3_close(db);
    throw std::runtime_error(msg);
  }
  sqlite3_close(db);
  return queryResult;
}
