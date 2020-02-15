#include <SqliteHandle.h>
#include <gtest/gtest.h>
#include <fstream>
#include <map>
#include <stdexcept>
#include <string>
#include <vector>

TEST(sqliteHandleTest, throwRuntimeErrorWhenFilenameIsInvalid) {
  ASSERT_THROW(SqliteHandle("/"), std::runtime_error);
}

TEST(sqliteHandleTest, wrongSqlSyntaxThrowRuntimeError) {
  SqliteHandle db = SqliteHandle("test.db");
  ASSERT_THROW(db.query("WRONG SQL SYNTAX"), std::runtime_error);
}

TEST(sqliteHandleTest, testSimpleQueries) {
  SqliteHandle db = SqliteHandle("test.db");
  db.query(
      "CREATE TABLE testTable("
      "id int PRIMARY KEY NOT NULL,"
      "name VARCHAR(30) NOT NULL);");
  SqliteHandle::QueryResult result =
      db.query("SELECT name FROM sqlite_master WHERE type = 'table';");
  ASSERT_EQ(result["name"], std::vector<std::string>{"testTable"});

  db.query("INSERT INTO testTable(id, name) VALUES(1000, 'John');");
  result = db.query("SELECT * FROM testTable WHERE id = 1000");
  ASSERT_EQ(result["id"], std::vector<std::string>{"1000"});
  ASSERT_EQ(result["name"], std::vector<std::string>{"John"});

  db.query("DROP TABLE TESTTABLE;");
  result = db.query("SELECT name FROM sqlite_master WHERE type = 'table';");
  ASSERT_EQ(result["name"], std::vector<std::string>{});
}
