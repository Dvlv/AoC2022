#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NUM_DIRS 100

typedef struct dir dir_t;

typedef struct dirfile {
    size_t size;
    char name[50];
} dirfile_t;

struct dir {
    char name[50];
    int current_file_idx;
    dir_t *parent;
    dirfile_t *files[50];
}; 

int is_parsing_ls = 0;
dir_t *current_working_dir = NULL;
dir_t *all_files[MAX_NUM_DIRS]; 
int all_files_index = 0; // I should learn to do this with malloc


void print_all_files() {

    for (int i = 0; i < MAX_NUM_DIRS; i++) {
        dir_t *fld = all_files[i];
        if (fld->name == NULL || fld->name == "" || fld->name == " ") {
            continue;
        }
        printf("dir: %s, files: %d ", fld->name, fld->current_file_idx);
        if (fld->parent != NULL) {
            printf("parent: %s\n", fld->parent->name);
        } else {
            printf("\n");
        }
    }
}

dir_t* find_dir_by_name(char dirname[]) {
    printf("looking for %s\n", dirname);
    print_all_files();
    for (int i = 0; i < MAX_NUM_DIRS; i++) {
        dir_t *d = all_files[i];
        if (d != NULL && strcmp(d->name, dirname) == 0) {
            printf("found dir!\n");
            return all_files[i];
        }
    }

    return NULL;
}

void execute_cd(char dirname[]) {
    int second_last_char = strlen(dirname) - 1;
    if (dirname[second_last_char] == '\n') {
        dirname[second_last_char] = '\0';
    }

    printf("executing cd to %s\n", dirname);
    current_working_dir = find_dir_by_name(dirname);
}

void toggle_parsing_ls(int is_ls) {
    is_parsing_ls = is_ls;
}
void parse_command(char current_line[]) {
    // this looks ridiculous but eh
    if (current_line[2] == 'c' && current_line[3] == 'd') {
        execute_cd(&current_line[5]);
    } else if (current_line[2] == 'l' && current_line[3] == 's') {
        toggle_parsing_ls(1);
    } else {
        printf("dunno what to do with %s\n", current_line);
    }
}


void parse_ls_line(char current_line[]) {
    if (current_line[0] == 'd' && current_line[1] == 'i' && current_line[2] == 'r') {
        // dir name, add to current working dir
        char dn[50];
        int len_to_cpy = strlen(&current_line[4]);
        len_to_cpy--;

        dir_t *new_dir = (dir_t*) malloc(sizeof(dir_t));
        memcpy(new_dir->name, &current_line[4], len_to_cpy);
        new_dir->name[len_to_cpy] = '\0';
        new_dir->current_file_idx = 0;
        new_dir->parent = current_working_dir;

        all_files[all_files_index] = new_dir;
        all_files_index++;

        print_all_files();
    } else {
        printf("parsing file 2: %s\n", current_line);
        char fname[50];
        size_t sze;
        sscanf(current_line, "%d %s", &sze, fname);

        int len_to_cpy = strlen(fname);
        len_to_cpy--;

        dirfile_t *new_file = (dirfile_t*) malloc(sizeof(dirfile_t));
        strncpy(new_file->name, fname, len_to_cpy);
        new_file->name[len_to_cpy] = '\0';
        new_file->size = sze;

        // current working dir segfaulting;
        current_working_dir->files[current_working_dir->current_file_idx] = new_file;
        current_working_dir->current_file_idx++;
        printf("cwd files: %d, name: %s\n", current_working_dir->current_file_idx, current_working_dir->name);
    }

}



int main() {

    FILE *f = fopen("input7.txt", "r");

    if (f == NULL) {
        printf("Failed to open file!");
        return 1;
    }

    char *current_line;
    size_t n = 100;

    dir_t root_dir = {.name = "/", .parent = NULL, .current_file_idx=0};
    current_working_dir = &root_dir;

    all_files[all_files_index] = &root_dir;
    all_files_index++;

    while((getline(&current_line, &n, f)) > 0) {
        printf("   Current line: %s", current_line);
        if (current_line[0] == '$') {
            toggle_parsing_ls(0);
            parse_command(current_line);
        } else if (is_parsing_ls) {
            parse_ls_line(current_line);
        }
    }

    // do I need to free my mallocs before exiting? I imagine the OS takes care of that.
    fclose(f);
    print_all_files();
}

