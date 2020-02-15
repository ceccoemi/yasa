#include "SqliteHandle.h"

#include <stdexcept>

void SqliteHandle::openDb(const char *dbName) {
  int rst = sqlite3_open(dbName, &db);
  if (rst != SQLITE_OK) {
    throw std::runtime_error(sqlite3_errmsg(db));
  }
}

SqliteHandle::SqliteHandle(const std::string &dbName) {
  openDb(dbName.c_str());
}

SqliteHandle::SqliteHandle() {
  openDb(":memory:");  // in-memory database
}

SqliteHandle::~SqliteHandle() { sqlite3_close(db); }

static int storeQueryResult(void *output, int argc, char **argv,
                            char **colName) {
  auto *result = static_cast<SqliteHandle::QueryResult *>(output);
  for (int i = 0; i < argc; i++) {
    result->operator[](colName[i]).push_back(argv[i]);
  }
  return 0;
}

SqliteHandle::QueryResult SqliteHandle::query(const std::string &sqlQuery) {
  SqliteHandle::QueryResult queryResult;
  char *errorMessage;
  int rst = sqlite3_exec(db, sqlQuery.c_str(), storeQueryResult,
                         static_cast<void *>(&queryResult), &errorMessage);
  if (rst != SQLITE_OK) {
    std::string msg = errorMessage;
    sqlite3_free(errorMessage);
    throw std::runtime_error(msg);
  }
  return queryResult;
}
