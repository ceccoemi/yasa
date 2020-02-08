#pragma once

#include <string>

class Sqlite3 {
public:
	Sqlite3(std::string dbName);

	std::string getDbPath();

private:
	std::string dbName;
};
