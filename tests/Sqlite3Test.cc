#include "../src/Sqlite3.h"

#include <gtest/gtest.h>
#include <fstream>
#include <stdexcept>
#include <string>

TEST(sqlite3Test, throwRuntimeErrorWhenFilenameIsInvalid) {
	ASSERT_THROW(Sqlite3("/"), std::runtime_error);
}

TEST(sqlite3Test, getDbPath) {
	Sqlite3 db = Sqlite3("test.db");
	std::string path = db.getDbPath();
	ASSERT_EQ(path.front(), '/');
	ASSERT_NE(path.rfind("test.db"), std::string::npos);
	std::ifstream infile(path);
	ASSERT_TRUE(infile.good());
}

TEST(sqlite3Test, testDbFileCreation) {
	Sqlite3 db = Sqlite3("test.db");
	std::string path = db.getDbPath();
	std::ifstream infile(path);
	ASSERT_TRUE(infile.good());
}
