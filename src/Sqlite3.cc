#include "Sqlite3.h"

#include <sqlite3.h>
#include <stddef.h>
#include <unistd.h>
#include <stdexcept>

Sqlite3::Sqlite3(std::string dbName) {
	Sqlite3::dbName = dbName;
	sqlite3 *db;
	int rst = sqlite3_open(Sqlite3::dbName.c_str(), &db);
	if (rst) {
		throw std::runtime_error(sqlite3_errmsg(db));
	}
	sqlite3_close(db);
}

std::string Sqlite3::getDbPath() {
	// TODO smarter way to determine pathSize
	size_t pathSize = 100 + Sqlite3::dbName.size();
	char cwd[pathSize];
	getcwd(cwd, pathSize);
	return std::string(cwd) + "/" + Sqlite3::dbName;
}
