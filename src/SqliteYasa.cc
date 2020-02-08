#include "SqliteYasa.h"

#include <sqlite3.h>
#include <stddef.h>
#include <unistd.h>
#include <stdexcept>

SqliteYasa::SqliteYasa(std::string dbName) {
	SqliteYasa::dbName = dbName;
	sqlite3 *db;
	int rst = sqlite3_open(SqliteYasa::dbName.c_str(), &db);
	if (rst) {
		throw std::runtime_error(sqlite3_errmsg(db));
	}
	sqlite3_close(db);
}

std::string SqliteYasa::getDbPath() {
	// TODO smarter way to determine pathSize
	size_t pathSize = 100 + SqliteYasa::dbName.size();
	char cwd[pathSize];
	getcwd(cwd, pathSize);
	return std::string(cwd) + "/" + SqliteYasa::dbName;
}
