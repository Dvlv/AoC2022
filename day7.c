#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct dir dir_t;

typedef struct dirfile {
    size_t size;
    char* name;
} dirfile_t;

struct dir {
    char name[50];
    int current_file_idx;
    dir_t *parent;
    dirfile_t files[50];
}; 

int is_parsing_ls = 0;
dir_t *current_working_dir = NULL;
dir_t *all_files[100]; 
int all_files_index = 0; // I should learn to do this with malloc

void execute_cd(char dirname[]) {

}

void toggle_parsing_ls() {
    is_parsing_ls = is_parsing_ls ? 0 : 1;
}
void parse_command(char current_line[]) {
    // this looks ridiculous but eh
    if (current_line[2] == 'c' && current_line[3] == 'd') {
        printf("found cd %s\n", current_line);
        execute_cd(&current_line[5]);
    } else if (current_line[2] == 'l' && current_line[3] == 's') {
        printf("found ls %s\n", current_line);
        toggle_parsing_ls();
    } else {
        printf("dunno what to do with %s\n", current_line);
    }
}


void parse_ls_line(char current_line[]) {
    if (current_line[0] == '$') {
        // no longer in ls output
        toggle_parsing_ls();
        return parse_command(current_line);
    }

    if (current_line[0] == 'd' && current_line[1] == 'i' && current_line[2] == 'r') {
        printf("parsing dir %s\n", current_line);
        // dir name, add to current working dir
        char dn[50];
        int len_to_cpy = strlen(&current_line[4]);
        len_to_cpy--;
        dir_t new_dir;
        strncpy(new_dir.name, &current_line[4], len_to_cpy);
        new_dir.name[len_to_cpy] = '\0';
        new_dir.current_file_idx = 0;

        all_files[all_files_index] = &new_dir;
        all_files_index++;
    } else {
        printf("parsing file %s\n", current_line);
        char fname[50];
        size_t sze;
        sscanf(current_line, "%d %s", &sze, fname);
        dirfile_t new_file = {.name = fname, .size = sze};
        current_working_dir->files[current_working_dir->current_file_idx] = new_file;
        current_working_dir->current_file_idx++;
        printf("cwd files: %d, name: %s", current_working_dir->current_file_idx, current_working_dir->name);
    }

}

void print_all_files() {

    for (int i = 0; i < 100; i++) {
        dir_t *fld = all_files[i];
        if (fld->name == NULL || fld->name == "" || fld->name == " ") {
            continue;
        }
        printf("dir: %s, files: %d", fld->name, fld->current_file_idx);
        if (fld->parent != NULL) {
            printf("parent: %s\n", fld->parent->name);
        } else {
            printf("\n");
        }
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
        if (current_line[0] == '$') {
            parse_command(current_line);
        } else if (is_parsing_ls) {
            parse_ls_line(current_line);
        }
    }

    fclose(f);
    print_all_files();
}


