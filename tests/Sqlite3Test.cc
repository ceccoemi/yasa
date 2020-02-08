#include <gtest/gtest.h>
#include <iostream>

#include <Sqlite3.h>

TEST(sqlite3Test, throwRuntimeErrorWhenFilenameIsInvalid) {
	ASSERT_THROW(Sqlite3("/"), std::runtime_error);
}

TEST(sqlite3Test, getDbPath) {
	Sqlite3 db = Sqlite3("test.db");
	std::string path = db.getDbPath();
	ASSERT_EQ(path.front(), '/');
	ASSERT_NE(path.rfind("test.db"), std::string::npos);
}
