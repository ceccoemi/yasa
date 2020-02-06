#include "Vocabulary.h"

#include <cstdio>
#include <sqlite3.h>

namespace yasa {

static int callback(void *NotUsed, int argc, char **argv, char **azColName) {
	int i;
	for (i = 0; i < argc; i++) {
		printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
	}
	printf("\n");
	return 0;
}

Vocabulary::Vocabulary() {
	sqlite3 *db;
	char *zErrMsg = 0;
	int rc;
	char *sql;

	rc = sqlite3_open("yasa.db", &db);

	sql = "create table vocabulary("
			"word varchar(30) primary key not null,"
			"positives int not null,"
			"negatives int not null);";

	rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);

	if (rc != SQLITE_OK) {
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	} else {
		fprintf(stdout, "Table created successfully\n");
	}
	sqlite3_close(db);
}

void Vocabulary::addWord(std::string word, Sentiment sentiment) {
	// puppa
}

int Vocabulary::getPositiveCount(std::string word) {
	return 1;
}

}  // namespace yasa
