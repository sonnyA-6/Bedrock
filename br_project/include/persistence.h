#ifndef BEDROCK_PERSISTENCE_H
#define BEDROCK_PERSISTENCE_H
#include "bst.h"
#include "db.h"

//Main functions
int db_save(Database *db, const char *filepath);
int db_load(Database *db, const char *filepath);

#endif //BEDROCK_PERSISTENCE_H
