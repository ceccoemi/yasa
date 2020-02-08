#include "../src/SqliteYasa.h"

#include <gtest/gtest.h>
#include <fstream>
#include <map>
#include <stdexcept>
#include <string>
#include <vector>

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

TEST(yasaDbTest, wrongSqlSyntaxThrowRuntimeError) {
	SqliteYasa db = SqliteYasa("test.db");
	ASSERT_THROW(db.query("WRONG SQL SYNTAX"), std::runtime_error);
}

TEST(yasaDbTest, testSimpleQueries) {
	SqliteYasa db = SqliteYasa("test.db");
	db.query("create table testTable("
			"id int primary key not null,"
			"name varchar(30) not null);");
	SqliteYasa::QueryResult result = db.query(
			"select name from sqlite_master where type = 'table';");
	ASSERT_EQ(result["name"], std::vector<std::string> { "testTable" });

	db.query("insert into testTable(id, name) values(1000, 'John');");
	result = db.query("select * from testTable where id = 1000");
	ASSERT_EQ(result["id"], std::vector<std::string> { "1000" });
	ASSERT_EQ(result["name"], std::vector<std::string> { "John" });

	db.query("drop table testTable;");
	result = db.query("select name from sqlite_master where type = 'table';");
	ASSERT_EQ(result["name"], std::vector<std::string> { });
}
