#include "Sqlite3.h"

#include <sqlite3.h>
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
	char cwd[128];
	getcwd(cwd, 128);
	return std::string(cwd) + "/" + Sqlite3::dbName;
}
