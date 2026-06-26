
#ifndef DB_H
#define DB_H

#include <stddef.h>
#include <sqlite3.h>


/* Functions declarations */

int add_note(sqlite3 *db, char *content);
int drop_table(sqlite3 *db);
int see_all(sqlite3 *db);
int delete_note_by_id(sqlite3 *db, int id);
int see_detail_note_by_id(sqlite3 *db, int id);

#endif

