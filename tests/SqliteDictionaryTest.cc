#include <DbHandler.h>
#include <Sentiment.h>
#include <SqliteDictionary.h>
#include <gmock/gmock-actions.h>
#include <gmock/gmock-matchers.h>
#include <gmock/gmock-spec-builders.h>
#include <gtest/gtest.h>

#include "MockDbHandler.h"

using ::testing::AllOf;
using ::testing::HasSubstr;
using ::testing::Return;

TEST(sqliteDictionaryTest, sizeOfEmptyDictionary) {
  MockDbHandler dbHandler;
  EXPECT_CALL(dbHandler, query(HasSubstr("CREATE"))).Times(2);
  DbHandler::QueryResult queryResult{{"COUNT(*)", {"0"}}};
  EXPECT_CALL(dbHandler, query(HasSubstr("COUNT")))
      .Times(2)
      .WillRepeatedly(Return(queryResult));

  SqliteDictionary dictionary(&dbHandler);
  ASSERT_EQ(dictionary.size(), 0);
}

TEST(sqliteDictionaryTest, sizeOfADictionaryWithOneWord) {
  MockDbHandler dbHandler;
  EXPECT_CALL(dbHandler, query(HasSubstr("CREATE"))).Times(2);
  EXPECT_CALL(dbHandler, query(HasSubstr("INSERT"))).Times(1);
  DbHandler::QueryResult positivesCount{{"COUNT(*)", {"1"}}};
  EXPECT_CALL(dbHandler,
              query(AllOf(HasSubstr("COUNT"), HasSubstr("positives"))))
      .Times(1)
      .WillRepeatedly(Return(positivesCount));
  DbHandler::QueryResult negativesCount{{"COUNT(*)", {"0"}}};
  EXPECT_CALL(dbHandler,
              query(AllOf(HasSubstr("COUNT"), HasSubstr("negatives"))))
      .Times(1)
      .WillRepeatedly(Return(negativesCount));

  SqliteDictionary dictionary(&dbHandler);
  dictionary.add("banana", Sentiment::positive);
  ASSERT_EQ(dictionary.size(), 1);
}

TEST(sqliteDictionaryTest, sizeOfASqliteDictionaryTwoWords) {
  MockDbHandler dbHandler;
  EXPECT_CALL(dbHandler, query(HasSubstr("CREATE"))).Times(2);
  EXPECT_CALL(dbHandler, query(HasSubstr("INSERT"))).Times(2);
  EXPECT_CALL(dbHandler,
              query(AllOf(HasSubstr("COUNT"), HasSubstr("positives"))))
      .Times(3)
      .WillOnce(Return(DbHandler::QueryResult{{"COUNT(*)", {"0"}}}))
      .WillRepeatedly(Return(DbHandler::QueryResult{{"COUNT(*)", {"1"}}}));
  EXPECT_CALL(dbHandler,
              query(AllOf(HasSubstr("COUNT"), HasSubstr("negatives"))))
      .Times(3)
      .WillOnce(Return(DbHandler::QueryResult{{"COUNT(*)", {"0"}}}))
      .WillOnce(Return(DbHandler::QueryResult{{"COUNT(*)", {"0"}}}))
      .WillRepeatedly(Return(DbHandler::QueryResult{{"COUNT(*)", {"1"}}}));

  SqliteDictionary dictionary(&dbHandler);
  ASSERT_EQ(dictionary.size(), 0);
  dictionary.add("banana", Sentiment::positive);
  ASSERT_EQ(dictionary.size(), 1);
  dictionary.add("banana", Sentiment::negative);
  ASSERT_EQ(dictionary.size(), 2);
}

TEST(sqliteDictionaryTest, positivesCount) {
  MockDbHandler dbHandler;
  EXPECT_CALL(dbHandler, query(HasSubstr("CREATE"))).Times(2);
  EXPECT_CALL(dbHandler, query(HasSubstr("INSERT"))).Times(3);
  EXPECT_CALL(dbHandler,
              query(AllOf(HasSubstr("COUNT"), HasSubstr("positives"))))
      .Times(3)
      .WillOnce(Return(DbHandler::QueryResult{{"COUNT(*)", {"0"}}}))
      .WillOnce(Return(DbHandler::QueryResult{{"COUNT(*)", {"1"}}}))
      .WillRepeatedly(Return(DbHandler::QueryResult{{"COUNT(*)", {"3"}}}));

  SqliteDictionary dictionary(&dbHandler);
  ASSERT_EQ(dictionary.positivesCount(), 0);
  dictionary.add("banana", Sentiment::positive);
  ASSERT_EQ(dictionary.positivesCount(), 1);
  dictionary.add("banana", Sentiment::positive);
  dictionary.add("banana", Sentiment::positive);
  ASSERT_EQ(dictionary.positivesCount(), 3);
}

TEST(sqliteDictionaryTest, negativesCount) {
  MockDbHandler dbHandler;
  EXPECT_CALL(dbHandler, query(HasSubstr("CREATE"))).Times(2);
  EXPECT_CALL(dbHandler, query(HasSubstr("INSERT"))).Times(3);
  EXPECT_CALL(dbHandler,
              query(AllOf(HasSubstr("COUNT"), HasSubstr("negatives"))))
      .Times(3)
      .WillOnce(Return(DbHandler::QueryResult{{"COUNT(*)", {"0"}}}))
      .WillOnce(Return(DbHandler::QueryResult{{"COUNT(*)", {"1"}}}))
      .WillRepeatedly(Return(DbHandler::QueryResult{{"COUNT(*)", {"3"}}}));

  SqliteDictionary dictionary(&dbHandler);
  ASSERT_EQ(dictionary.negativesCount(), 0);
  dictionary.add("banana", Sentiment::negative);
  ASSERT_EQ(dictionary.negativesCount(), 1);
  dictionary.add("banana", Sentiment::negative);
  dictionary.add("banana", Sentiment::negative);
  ASSERT_EQ(dictionary.negativesCount(), 3);
}

TEST(sqliteDictionaryTest, positivesCountOfAWord) {
  MockDbHandler dbHandler;
  EXPECT_CALL(dbHandler, query(HasSubstr("CREATE"))).Times(2);
  EXPECT_CALL(dbHandler, query(HasSubstr("INSERT"))).Times(3);
  EXPECT_CALL(dbHandler,
              query(AllOf(HasSubstr("COUNT"), HasSubstr("positives"))))
      .Times(4)
      .WillOnce(Return(DbHandler::QueryResult{{"COUNT(*)", {"0"}}}))
      .WillOnce(Return(DbHandler::QueryResult{{"COUNT(*)", {"1"}}}))
      .WillOnce(Return(DbHandler::QueryResult{{"COUNT(*)", {"3"}}}))
      .WillOnce(Return(DbHandler::QueryResult{{"COUNT(*)", {"0"}}}));

  SqliteDictionary dictionary(&dbHandler);
  ASSERT_EQ(dictionary.positivesCount("banana"), 0);
  dictionary.add("banana", Sentiment::positive);
  ASSERT_EQ(dictionary.positivesCount("banana"), 1);
  dictionary.add("banana", Sentiment::positive);
  dictionary.add("banana", Sentiment::positive);
  ASSERT_EQ(dictionary.positivesCount("banana"), 3);
  ASSERT_EQ(dictionary.positivesCount("apple"), 0);
}

TEST(sqliteDictionaryTest, negativesCountOfAWord) {
  MockDbHandler dbHandler;
  EXPECT_CALL(dbHandler, query(HasSubstr("CREATE"))).Times(2);
  EXPECT_CALL(dbHandler, query(HasSubstr("INSERT"))).Times(3);
  EXPECT_CALL(dbHandler,
              query(AllOf(HasSubstr("COUNT"), HasSubstr("negatives"))))
      .Times(4)
      .WillOnce(Return(DbHandler::QueryResult{{"COUNT(*)", {"0"}}}))
      .WillOnce(Return(DbHandler::QueryResult{{"COUNT(*)", {"1"}}}))
      .WillOnce(Return(DbHandler::QueryResult{{"COUNT(*)", {"3"}}}))
      .WillOnce(Return(DbHandler::QueryResult{{"COUNT(*)", {"0"}}}));

  SqliteDictionary dictionary(&dbHandler);
  ASSERT_EQ(dictionary.negativesCount("banana"), 0);
  dictionary.add("banana", Sentiment::negative);
  ASSERT_EQ(dictionary.negativesCount("banana"), 1);
  dictionary.add("banana", Sentiment::negative);
  dictionary.add("banana", Sentiment::negative);
  ASSERT_EQ(dictionary.negativesCount("banana"), 3);
  ASSERT_EQ(dictionary.negativesCount("apple"), 0);
}

TEST(sqliteDictionaryTest, resetDictionary) {
  MockDbHandler dbHandler;
  EXPECT_CALL(dbHandler, query(HasSubstr("CREATE"))).Times(2);
  EXPECT_CALL(dbHandler, query(HasSubstr("INSERT"))).Times(2);
  EXPECT_CALL(dbHandler,
              query(AllOf(HasSubstr("COUNT"), HasSubstr("positives"))))
      .Times(2)
      .WillOnce(Return(DbHandler::QueryResult{{"COUNT(*)", {"1"}}}))
      .WillRepeatedly(Return(DbHandler::QueryResult{{"COUNT(*)", {"0"}}}));
  EXPECT_CALL(dbHandler,
              query(AllOf(HasSubstr("COUNT"), HasSubstr("negatives"))))
      .Times(2)
      .WillOnce(Return(DbHandler::QueryResult{{"COUNT(*)", {"1"}}}))
      .WillRepeatedly(Return(DbHandler::QueryResult{{"COUNT(*)", {"0"}}}));
  EXPECT_CALL(dbHandler, query(HasSubstr("DELETE"))).Times(1);

  SqliteDictionary dictionary(&dbHandler);
  dictionary.add("banana", Sentiment::positive);
  dictionary.add("banana", Sentiment::negative);
  ASSERT_EQ(dictionary.size(), 2);
  dictionary.reset();
  ASSERT_EQ(dictionary.size(), 0);
}
