#include "YasaDb.h"

#include <sqlite3.h>
#include <stddef.h>
#include <unistd.h>
#include <stdexcept>

YasaDb::YasaDb(std::string dbName) {
	YasaDb::dbName = dbName;
	sqlite3 *db;
	int rst = sqlite3_open(YasaDb::dbName.c_str(), &db);
	if (rst) {
		throw std::runtime_error(sqlite3_errmsg(db));
	}
	sqlite3_close(db);
}

std::string YasaDb::getDbPath() {
	// TODO smarter way to determine pathSize
	size_t pathSize = 100 + YasaDb::dbName.size();
	char cwd[pathSize];
	getcwd(cwd, pathSize);
	return std::string(cwd) + "/" + YasaDb::dbName;
}
