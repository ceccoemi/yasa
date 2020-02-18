#include <QueryResult.h>
#include <Sentiment.h>
#include <SqliteDictionary.h>
#include <gmock/gmock-actions.h>
#include <gmock/gmock-matchers.h>
#include <gmock/gmock-spec-builders.h>
#include <gtest/gtest.h>

#include "MockSqliteHandler.h"

using ::testing::AllOf;
using ::testing::HasSubstr;
using ::testing::Return;

TEST(SqliteDictionaryTest, sizeOfEmptyDictionary) {
  MockSqliteHandler handler;
  EXPECT_CALL(handler, query(HasSubstr("CREATE"))).Times(2);
  QueryResult queryResult{{"COUNT(*)", {"0"}}};
  EXPECT_CALL(handler, query(HasSubstr("COUNT")))
      .Times(2)
      .WillRepeatedly(Return(queryResult));

  SqliteDictionary<MockSqliteHandler> dictionary(&handler);
  ASSERT_EQ(dictionary.size(), 0);
}

TEST(SqliteDictionaryTest, sizeOfADictionaryWithOneWord) {
  MockSqliteHandler handler;
  EXPECT_CALL(handler, query(HasSubstr("CREATE"))).Times(2);
  EXPECT_CALL(handler, query(HasSubstr("INSERT"))).Times(1);
  QueryResult positivesCount{{"COUNT(*)", {"1"}}};
  EXPECT_CALL(handler, query(AllOf(HasSubstr("COUNT"), HasSubstr("positives"))))
      .Times(1)
      .WillRepeatedly(Return(positivesCount));
  QueryResult negativesCount{{"COUNT(*)", {"0"}}};
  EXPECT_CALL(handler, query(AllOf(HasSubstr("COUNT"), HasSubstr("negatives"))))
      .Times(1)
      .WillRepeatedly(Return(negativesCount));

  SqliteDictionary<MockSqliteHandler> dictionary(&handler);
  dictionary.add("banana", Sentiment::positive);
  ASSERT_EQ(dictionary.size(), 1);
}

TEST(SqliteDictionaryTest, sizeOfASqliteDictionaryTwoWords) {
  MockSqliteHandler handler;
  EXPECT_CALL(handler, query(HasSubstr("CREATE"))).Times(2);
  EXPECT_CALL(handler, query(HasSubstr("INSERT"))).Times(2);
  EXPECT_CALL(handler, query(AllOf(HasSubstr("COUNT"), HasSubstr("positives"))))
      .Times(3)
      .WillOnce(Return(QueryResult{{"COUNT(*)", {"0"}}}))
      .WillRepeatedly(Return(QueryResult{{"COUNT(*)", {"1"}}}));
  EXPECT_CALL(handler, query(AllOf(HasSubstr("COUNT"), HasSubstr("negatives"))))
      .Times(3)
      .WillOnce(Return(QueryResult{{"COUNT(*)", {"0"}}}))
      .WillOnce(Return(QueryResult{{"COUNT(*)", {"0"}}}))
      .WillRepeatedly(Return(QueryResult{{"COUNT(*)", {"1"}}}));

  SqliteDictionary<MockSqliteHandler> dictionary(&handler);
  ASSERT_EQ(dictionary.size(), 0);
  dictionary.add("banana", Sentiment::positive);
  ASSERT_EQ(dictionary.size(), 1);
  dictionary.add("banana", Sentiment::negative);
  ASSERT_EQ(dictionary.size(), 2);
}

TEST(SqliteDictionaryTest, positivesCount) {
  MockSqliteHandler handler;
  EXPECT_CALL(handler, query(HasSubstr("CREATE"))).Times(2);
  EXPECT_CALL(handler, query(HasSubstr("INSERT"))).Times(3);
  EXPECT_CALL(handler, query(AllOf(HasSubstr("COUNT"), HasSubstr("positives"))))
      .Times(3)
      .WillOnce(Return(QueryResult{{"COUNT(*)", {"0"}}}))
      .WillOnce(Return(QueryResult{{"COUNT(*)", {"1"}}}))
      .WillRepeatedly(Return(QueryResult{{"COUNT(*)", {"3"}}}));

  SqliteDictionary<MockSqliteHandler> dictionary(&handler);
  ASSERT_EQ(dictionary.positivesCount(), 0);
  dictionary.add("banana", Sentiment::positive);
  ASSERT_EQ(dictionary.positivesCount(), 1);
  dictionary.add("banana", Sentiment::positive);
  dictionary.add("banana", Sentiment::positive);
  ASSERT_EQ(dictionary.positivesCount(), 3);
}

TEST(SqliteDictionaryTest, negativesCount) {
  MockSqliteHandler handler;
  EXPECT_CALL(handler, query(HasSubstr("CREATE"))).Times(2);
  EXPECT_CALL(handler, query(HasSubstr("INSERT"))).Times(3);
  EXPECT_CALL(handler, query(AllOf(HasSubstr("COUNT"), HasSubstr("negatives"))))
      .Times(3)
      .WillOnce(Return(QueryResult{{"COUNT(*)", {"0"}}}))
      .WillOnce(Return(QueryResult{{"COUNT(*)", {"1"}}}))
      .WillRepeatedly(Return(QueryResult{{"COUNT(*)", {"3"}}}));

  SqliteDictionary<MockSqliteHandler> dictionary(&handler);
  ASSERT_EQ(dictionary.negativesCount(), 0);
  dictionary.add("banana", Sentiment::negative);
  ASSERT_EQ(dictionary.negativesCount(), 1);
  dictionary.add("banana", Sentiment::negative);
  dictionary.add("banana", Sentiment::negative);
  ASSERT_EQ(dictionary.negativesCount(), 3);
}

TEST(SqliteDictionaryTest, positivesCountOfAWord) {
  MockSqliteHandler handler;
  EXPECT_CALL(handler, query(HasSubstr("CREATE"))).Times(2);
  EXPECT_CALL(handler, query(HasSubstr("INSERT"))).Times(3);
  EXPECT_CALL(handler, query(AllOf(HasSubstr("COUNT"), HasSubstr("positives"))))
      .Times(4)
      .WillOnce(Return(QueryResult{{"COUNT(*)", {"0"}}}))
      .WillOnce(Return(QueryResult{{"COUNT(*)", {"1"}}}))
      .WillOnce(Return(QueryResult{{"COUNT(*)", {"3"}}}))
      .WillOnce(Return(QueryResult{{"COUNT(*)", {"0"}}}));

  SqliteDictionary<MockSqliteHandler> dictionary(&handler);
  ASSERT_EQ(dictionary.positivesCount("banana"), 0);
  dictionary.add("banana", Sentiment::positive);
  ASSERT_EQ(dictionary.positivesCount("banana"), 1);
  dictionary.add("banana", Sentiment::positive);
  dictionary.add("banana", Sentiment::positive);
  ASSERT_EQ(dictionary.positivesCount("banana"), 3);
  ASSERT_EQ(dictionary.positivesCount("apple"), 0);
}

TEST(SqliteDictionaryTest, negativesCountOfAWord) {
  MockSqliteHandler handler;
  EXPECT_CALL(handler, query(HasSubstr("CREATE"))).Times(2);
  EXPECT_CALL(handler, query(HasSubstr("INSERT"))).Times(3);
  EXPECT_CALL(handler, query(AllOf(HasSubstr("COUNT"), HasSubstr("negatives"))))
      .Times(4)
      .WillOnce(Return(QueryResult{{"COUNT(*)", {"0"}}}))
      .WillOnce(Return(QueryResult{{"COUNT(*)", {"1"}}}))
      .WillOnce(Return(QueryResult{{"COUNT(*)", {"3"}}}))
      .WillOnce(Return(QueryResult{{"COUNT(*)", {"0"}}}));

  SqliteDictionary<MockSqliteHandler> dictionary(&handler);
  ASSERT_EQ(dictionary.negativesCount("banana"), 0);
  dictionary.add("banana", Sentiment::negative);
  ASSERT_EQ(dictionary.negativesCount("banana"), 1);
  dictionary.add("banana", Sentiment::negative);
  dictionary.add("banana", Sentiment::negative);
  ASSERT_EQ(dictionary.negativesCount("banana"), 3);
  ASSERT_EQ(dictionary.negativesCount("apple"), 0);
}

TEST(SqliteDictionaryTest, resetDictionary) {
  MockSqliteHandler handler;
  EXPECT_CALL(handler, query(HasSubstr("CREATE"))).Times(2);
  EXPECT_CALL(handler, query(HasSubstr("INSERT"))).Times(2);
  EXPECT_CALL(handler, query(AllOf(HasSubstr("COUNT"), HasSubstr("positives"))))
      .Times(2)
      .WillOnce(Return(QueryResult{{"COUNT(*)", {"1"}}}))
      .WillRepeatedly(Return(QueryResult{{"COUNT(*)", {"0"}}}));
  EXPECT_CALL(handler, query(AllOf(HasSubstr("COUNT"), HasSubstr("negatives"))))
      .Times(2)
      .WillOnce(Return(QueryResult{{"COUNT(*)", {"1"}}}))
      .WillRepeatedly(Return(QueryResult{{"COUNT(*)", {"0"}}}));
  EXPECT_CALL(handler, query(HasSubstr("DELETE"))).Times(1);

  SqliteDictionary<MockSqliteHandler> dictionary(&handler);
  dictionary.add("banana", Sentiment::positive);
  dictionary.add("banana", Sentiment::negative);
  ASSERT_EQ(dictionary.size(), 2);
  dictionary.reset();
  ASSERT_EQ(dictionary.size(), 0);
}
