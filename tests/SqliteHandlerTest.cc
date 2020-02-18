#include <DbHandler.h>
#include <SqliteHandler.h>
#include <gtest/gtest.h>
#include <gtest/internal/gtest-internal.h>
#include <experimental/filesystem>
#include <map>
#include <stdexcept>
#include <string>
#include <vector>

namespace fs = std::experimental::filesystem;

TEST(SqliteHandlerInMemoryTest, wrongSqlSyntaxThrowRuntimeError) {
  SqliteHandler db = SqliteHandler();
  ASSERT_THROW(db.query("WRONG SQL SYNTAX"), std::runtime_error);
}

TEST(SqliteHandlerInMemoryTest, testSimpleQueries) {
  SqliteHandler db = SqliteHandler();
  db.query(
      "CREATE TABLE testTable("
      "id int PRIMARY KEY NOT NULL,"
      "name VARCHAR(30) NOT NULL);");
  SqliteHandler::QueryResult result =
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

class SqliteHandlerDbTest : public ::testing::Test {
 protected:
  virtual void SetUp() {
    dbFileName = fs::temp_directory_path() / fs::path("test.db");
  }

  virtual void TearDown() { fs::remove(dbFileName); }

  std::string dbFileName;
};

TEST_F(SqliteHandlerDbTest, throwRuntimeErrorWhenFilenameIsInvalid) {
  ASSERT_THROW(SqliteHandler("/"), std::runtime_error);
}

TEST_F(SqliteHandlerDbTest, createDbInAFile) {
  ASSERT_FALSE(fs::is_regular_file(dbFileName));
  SqliteHandler db(dbFileName);
  ASSERT_TRUE(fs::is_regular_file(dbFileName));
}

TEST_F(SqliteHandlerDbTest, operateOnTheSameFile) {
  SqliteHandler db1(dbFileName);
  SqliteHandler db2(dbFileName);
  db1.query(
      "CREATE TABLE testTable("
      "id int PRIMARY KEY NOT NULL,"
      "name VARCHAR(30) NOT NULL);");
  SqliteHandler::QueryResult result =
      db2.query("SELECT name FROM sqlite_master WHERE type = 'table';");
  ASSERT_EQ(result["name"], std::vector<std::string>{"testTable"});
}
