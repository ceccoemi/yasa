#pragma once

#include <string>

class YasaDb {
public:
	YasaDb(std::string dbName);

	std::string getDbPath();

private:
	std::string dbName;
};
