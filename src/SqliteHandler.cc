#include "SqliteHandler.h"

void SqliteHandler::openDb(const char *dbName) {
  int rst = sqlite3_open(dbName, &db);
  if (rst != SQLITE_OK) {
    throw std::runtime_error(sqlite3_errmsg(db));
  }
}

// NOLINTNEXTLINE(cppcoreguidelines-pro-type-member-init)
SqliteHandler::SqliteHandler(const std::string &dbName) {
  openDb(dbName.c_str());
}

// NOLINTNEXTLINE(cppcoreguidelines-pro-type-member-init)
SqliteHandler::SqliteHandler() {
  openDb(":memory:");  // in-memory database
}

SqliteHandler::~SqliteHandler() { sqlite3_close(db); }

static int storeQueryResult(void *output, int argc, char **argv,
                            char **colName) {
  auto *result = static_cast<QueryResult *>(output);
  for (int i = 0; i < argc; i++) {
    // NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-pointer-arithmetic)
    result->operator[](colName[i]).push_back(argv[i]);
  }
  return 0;
}

QueryResult SqliteHandler::query(const std::string &sqlQuery) {
  QueryResult queryResult;
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
