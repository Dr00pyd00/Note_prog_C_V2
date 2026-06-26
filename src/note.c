
#include "note.h"

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <sqlite3.h>


/* add a note to the db */
int add_note(sqlite3 *db, char *content) {
    int re;
    
    sqlite3_stmt *stmt;

    re = sqlite3_prepare_v2(db,"INSERT INTO notes (content) VALUES (?);",
            -1, &stmt, NULL);
    if ( re != SQLITE_OK ) {
        fprintf(stderr, "failed prepare: %s\n", sqlite3_errmsg(db));
        return -1;
    }

    re = sqlite3_bind_text(stmt, 1, content, -1, SQLITE_STATIC);
    if ( re != SQLITE_OK ) {
        fprintf(stderr, "failed bind: %s\n", sqlite3_errmsg(db));
        sqlite3_finalize(stmt);
        return -1;
    }

    re = sqlite3_step(stmt);
    if ( re != SQLITE_DONE ) {
        fprintf(stderr, "failed step: %s\n", sqlite3_errmsg(db));
        sqlite3_finalize(stmt);
        return -1;
    }
    sqlite3_finalize(stmt);

    return 0;
}


/* delete the entire table
        return 0 in sucess else return -1 */
int drop_table(sqlite3 *db) {
    char *err = NULL;
    int re = sqlite3_exec(db,
            "DROP TABLE IF EXISTS notes;",
            NULL,
            NULL,
            &err
            );
    if ( re != SQLITE_OK ) {
        fprintf(stderr,"drop table failed: %s\n", err);
        sqlite3_free(err);
        sqlite3_close(db);
        return -1;
    }
    return 0;
}


/* printf all the notes in the database 
    return 0 on success else return -1 */
int see_all(sqlite3 *db) {
    int re;
    printf("# ======= Notes: ============== #\n");

    sqlite3_stmt *stmt;
    re =sqlite3_prepare_v2(db, "SELECT * FROM notes;", -1, &stmt, NULL);
    if ( re != SQLITE_OK ) {
        fprintf(stderr, "failed prepare: %s\n", sqlite3_errmsg(db));
        return -1;
    }

    while( sqlite3_step(stmt) == SQLITE_ROW) {
        int id = sqlite3_column_int(stmt, 0);
        const char *content = (const char*)sqlite3_column_text(stmt,1);
        printf("%d:\n  %s\n",id,content);
        printf("\n< --------------------------------- >\n");
    }
    sqlite3_finalize(stmt);

    return 0;
}

/* take note id and delete it from db
   return 0 on sucess, return 1 if note doesnt exist,
   else return -1 */
int delete_note_by_id(sqlite3 *db, int id) {
    int re;

    sqlite3_stmt *stmt;

    re = sqlite3_prepare_v2(db, "DELETE FROM notes WHERE id=(?);",
            -1, &stmt, NULL);
    if ( re != SQLITE_OK ) {
        fprintf(stderr, "failed prepare: %s\n", sqlite3_errmsg(db));
        return -1;
    }

    re = sqlite3_bind_int(stmt, 1, id);
    if ( re != SQLITE_OK ) {
        fprintf(stderr, "failed bind: %s\n", sqlite3_errmsg(db));
        sqlite3_finalize(stmt);
        return -1;
    }

    re = sqlite3_step(stmt);
    if ( re != SQLITE_DONE ) {
        fprintf(stderr, "failed step: %s\n", sqlite3_errmsg(db));
        sqlite3_finalize(stmt);
        return -1;
    }
        /* if no move = mean nothing delete because note not existed */
    if ( sqlite3_changes(db) == 0 ) {
        sqlite3_finalize(stmt);
        return 1;
    }

    sqlite3_finalize(stmt);
    return 0;
}


/* show detail of note by ID
   return 0 and printf the content in success,
   if note dont exist return 1,
   if error return -1 */
int see_detail_note_by_id(sqlite3 *db, int id) {
    int re;

    sqlite3_stmt *stmt;

    re = sqlite3_prepare_v2(db, "SELECT * FROM notes WHERE id=(?);",
            -1, &stmt, NULL);
    if ( re != SQLITE_OK ) {
        fprintf(stderr, "failed prepare: %s\n", sqlite3_errmsg(db));
        return -1;
    }

    re = sqlite3_bind_int(stmt, 1, id);
    if ( re != SQLITE_OK ) {
        fprintf(stderr, "failed bind: %s\n", sqlite3_errmsg(db));
        sqlite3_finalize(stmt);
        return -1;
    }
    
    re = sqlite3_step(stmt);
    if ( re == SQLITE_ROW ) {
        int id = sqlite3_column_int(stmt, 0);
        const char *content = (const char *)sqlite3_column_text(stmt, 1);
        printf("# ========= Detail Note %d ============= #\n", id);
        printf("%s\n", content);
    }
    else if ( re == SQLITE_DONE ) {
        sqlite3_finalize(stmt);
        return 1;
    }

    sqlite3_finalize(stmt);
    return 0;
}



