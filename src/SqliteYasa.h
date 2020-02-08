#pragma once

#include <string>

class SqliteYasa {
public:
	SqliteYasa(std::string dbName);

	std::string getDbPath();

private:
	std::string dbName;
};
