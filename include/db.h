

#include <stddef.h>
#include <sqlite3.h>


#define DATABASE_NAME       "notes_v2.db"



/* Functions declarations */

int build_note_path(char *buf, size_t bufSize);

sqlite3* create_db(char *path);

int create_table(sqlite3 *db);
