#include "../src/YasaDb.h"

#include <gtest/gtest.h>
#include <fstream>
#include <stdexcept>
#include <string>

TEST(yasaDbTest, throwRuntimeErrorWhenFilenameIsInvalid) {
	ASSERT_THROW(YasaDb("/"), std::runtime_error);
}

TEST(yasaDbTest, getDbPath) {
	YasaDb db = YasaDb("test.db");
	std::string path = db.getDbPath();
	ASSERT_EQ(path.front(), '/');
	ASSERT_NE(path.rfind("test.db"), std::string::npos);
	std::ifstream infile(path);
	ASSERT_TRUE(infile.good());
}

TEST(yasaDbTest, testDbFileCreation) {
	YasaDb db = YasaDb("test.db");
	std::string path = db.getDbPath();
	std::ifstream infile(path);
	ASSERT_TRUE(infile.good());
}
