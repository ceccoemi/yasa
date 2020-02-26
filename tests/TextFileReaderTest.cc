#include <TextFileReader.h>
#include <gtest/gtest.h>
#include <gtest/internal/gtest-internal.h>

#include <experimental/filesystem>
#include <fstream>
#include <stdexcept>
#include <string>

namespace fs = std::experimental::filesystem;

class TextFileReaderTest : public ::testing::Test {
 protected:
  virtual void SetUp() {
    fileName = fs::temp_directory_path() / fs::path("test.txt");
    std::ofstream out(fileName);
    out << "Hello from test.txt\n";
    out.close();
  }

  virtual void TearDown() { fs::remove(fileName); }

  std::string fileName;
};

TEST_F(TextFileReaderTest, throwRuntimeErrorWhenFileDoesNotExist) {
  ASSERT_THROW(TextFileReader("/banana"), std::runtime_error);
}

TEST_F(TextFileReaderTest, throwRuntimeErrorWhenIsNotARegularFile) {
  ASSERT_THROW(TextFileReader("/"), std::runtime_error);
}

TEST_F(TextFileReaderTest, readFileContent) {
  TextFileReader reader(fileName);
  ASSERT_EQ(reader.read(), "Hello from test.txt\n");
}
