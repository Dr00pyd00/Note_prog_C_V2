#include "db.h"

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <sqlite3.h>



/* Create the path of the sqlite3 */ 
/* fill a buffer with the right path 
   return 0 on success else return -1 */
int build_note_path(char *buf, size_t bufSize) {
    
    char * homePath = getenv("HOME");
    if (!homePath) return -1;

    int n = snprintf(buf, bufSize, "%s/.%s", homePath, DATABASE_NAME);
    if ( n >= (int)bufSize ) return -1;

    return 0;
}


/* create the database
    take the path and create the db 
    return the sqlite3 pointeur  on success elese return NULL 
    you NEED to sqlite3_free(database) at the end !
*/
sqlite3* create_db(char *path) {
    sqlite3 *db;
    int re = sqlite3_open(path, &db);
    if ( re != SQLITE_OK ) {
        fprintf(stderr, "error to open db\n");
        sqlite3_close(db);
        return NULL;
    }
    return db;
}


/* create a table if not existe at the path 
    return 0 on success else return -1  */
int create_table(sqlite3 *db) {
    
    char *err = NULL;
    int re = sqlite3_exec(
            db,
            "CREATE TABLE IF NOT EXISTS notes (id INTEGER PRIMARY KEY, content TEXT);",
            NULL, NULL, &err);
    if ( re != SQLITE_OK ) {
        fprintf(stderr, "create table failed: %s\n", err);
        sqlite3_free(err);
        sqlite3_close(db);
        return -1;
    }
    return 0;
}


/* initialization of db + table */
// int init_db_table(sqlite3 *db) {
//     int re = create_db(db);
//     if ( re != 0 ) {
//         fprintf(stderr, "databate creation failed\n");
//         return -1;
//     }
//     re = create_table(db);
//     if ( re != 0 ) {
//         fprintf(stderr, "table creation failed\n");
//         return -1;
//     }
//     return 0;
// }

