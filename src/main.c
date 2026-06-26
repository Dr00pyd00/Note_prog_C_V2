#include "note.h"
#include "db.h"

#include <stdio.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>



int main(int argc, char **argv) {

    /* Setup PATH, DB and the table for notes =================================== */
    char db_path[256];
    size_t db_pathSize = sizeof(db_path);
    sqlite3 *db = NULL;
    int exit_no = 0;

    int re = build_note_path(db_path, db_pathSize);
    if ( re != 0 ) {
        fprintf(stderr, "build failed\n");
        exit_no = 1; goto cleanup;
    }
    db = create_db(db_path);
    if ( db == NULL ) { exit_no = 2; goto cleanup; }
    
    re = create_table(db);
    if ( re == -1) { exit_no = 3; goto cleanup; }
    

    /* Setup Args =========================================== */
    if ( argc < 2 ) {
        printf("Usages:\n"
                "notes <text>       : to add a note\n"
                "notes all          : to see all notes\n"
                "note del <note_id> : delete note by id\n"
                "note see <note_id> : see detail note by id\n"
                "notes reset        : to delete all notes\n"
              );
        exit_no = 4; goto cleanup;
    }
    char *cmd = argv[1];

    /* Gestions */
    if ( strcmp(cmd, "all") == 0 ) {
        see_all(db);
    }
    else if ( strcmp(cmd, "reset") == 0 ) {
        printf("notes reset\n");
        drop_table(db);
    }
    else if ( strcmp(cmd, "del") == 0 ) {
        if ( argc < 3 ) {
            fprintf(stderr, "You need specify ID not to delete.\n"
                    "./ del <note_id>\n");
            exit_no = 5; goto cleanup;
        }
        /* check if arg is a int ... */
        char *endptr;
        int id = (int)strtol(argv[2], &endptr, 10);
        if ( argv[2] == endptr || *endptr != '\0' ) {
            fprintf(stderr, "Note ID to del must be integer\n");
            exit_no = 6; goto cleanup;
        }
        re = delete_note_by_id(db, id);
        if ( re == 1 ) {
            fprintf(stdout, "note ID:%d doesnt exist...\n",id);
            exit_no = 7; goto cleanup;
        }
        else if ( re == -1 ) { exit_no = 8; goto cleanup; } /* error occured during deletion */
        
        printf("note ID:%d deleted!\n", id);

    }
    else if ( strcmp(cmd, "see") == 0 ) {
        if ( argc < 3 ) {
            fprintf(stderr, "You need specify ID not to see detailes.\n"
                    "./ see <note_id>\n");
            exit_no = 9; goto cleanup;
        }
        /* check if arg is a int ... */
        char *endptr;
        int id = (int)strtol(argv[2], &endptr, 10);
        if ( argv[2] == endptr || *endptr != '\0' ) {
            fprintf(stderr, "Note ID to see must be integer\n");
            exit_no = 10; goto cleanup;
        }
        re = see_detail_note_by_id(db, id);
        if ( re == 1 ) {
            fprintf(stdout, "note ID:%d doesnt exist...\n",id);
            exit_no = 11; goto cleanup;
        }
        else if ( re == -1 ) { exit_no = 12; goto cleanup; } /* error occured during deletion */
        

    }
    else {
        add_note(db, cmd);
    }


    /* close the db */
cleanup:
    if (db) sqlite3_close(db);
    return exit_no;

}
