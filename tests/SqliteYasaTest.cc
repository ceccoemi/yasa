#include "../src/SqliteYasa.h"

#include <gtest/gtest.h>
#include <fstream>
#include <stdexcept>
#include <string>

TEST(yasaDbTest, throwRuntimeErrorWhenFilenameIsInvalid) {
	ASSERT_THROW(SqliteYasa("/"), std::runtime_error);
}

TEST(yasaDbTest, getDbPath) {
	SqliteYasa db = SqliteYasa("test.db");
	std::string path = db.getDbPath();
	ASSERT_EQ(path.front(), '/');
	ASSERT_NE(path.rfind("test.db"), std::string::npos);
	std::ifstream infile(path);
	ASSERT_TRUE(infile.good());
}

TEST(yasaDbTest, testDbFileCreation) {
	SqliteYasa db = SqliteYasa("test.db");
	std::string path = db.getDbPath();
	std::ifstream infile(path);
	ASSERT_TRUE(infile.good());
}
