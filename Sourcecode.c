#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LEN 256
#define INITIAL_CAPACITY 10

typedef struct {
    char **lines;      // dynamic array of strings
    int line_count;
    int capacity;
    char filename[256];
} TextBuffer;

void init_buffer(TextBuffer *buf) {
    buf->lines = (char **)malloc(INITIAL_CAPACITY * sizeof(char *));
    if (!buf->lines) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    buf->line_count = 0;
    buf->capacity = INITIAL_CAPACITY;
    buf->filename[0] = '\0';
}

void ensure_capacity(TextBuffer *buf) {
    if (buf->line_count >= buf->capacity) {
        int new_cap = buf->capacity * 2;
        char **new_lines = (char **)realloc(buf->lines, new_cap * sizeof(char *));
        if (!new_lines) {
            printf("Realloc failed!\n");
            exit(1);
        }
        buf->lines = new_lines;
        buf->capacity = new_cap;
    }
}

void free_buffer(TextBuffer *buf) {
    for (int i = 0; i < buf->line_count; i++) {
        free(buf->lines[i]);
    }
    free(buf->lines);
    buf->lines = NULL;
    buf->line_count = 0;
    buf->capacity = 0;
}

void display_buffer(const TextBuffer *buf) {
    if (buf->line_count == 0) {
        printf("\n[File is empty]\n");
        return;
    }
    printf("\n------ File Content ------\n");
    for (int i = 0; i < buf->line_count; i++) {
        printf("%3d: %s", i + 1, buf->lines[i]);
    }
    printf("\n--------------------------\n");
}

void insert_line(TextBuffer *buf, const char *line, int position) {
    if (position < 1 || position > buf->line_count + 1) {
        printf("Invalid position!\n");
        return;
    }
    ensure_capacity(buf);

    // shift lines down from position-1
    for (int i = buf->line_count; i >= position; i--) {
        buf->lines[i] = buf->lines[i - 1];
    }

    buf->lines[position - 1] = (char *)malloc(strlen(line) + 1);
    if (!buf->lines[position - 1]) {
        printf("Memory allocation failed!\n");
        return;
    }
    strcpy(buf->lines[position - 1], line);
    buf->line_count++;
}

void delete_line(TextBuffer *buf, int position) {
    if (position < 1 || position > buf->line_count) {
        printf("Invalid position!\n");
        return;
    }

    free(buf->lines[position - 1]);

    for (int i = position - 1; i < buf->line_count - 1; i++) {
        buf->lines[i] = buf->lines[i + 1];
    }

    buf->line_count--;
}

void load_file(TextBuffer *buf, const char *filename) {
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        printf("File not found. Creating new file on save.\n");
        strcpy(buf->filename, filename);
        return;
    }

    strcpy(buf->filename, filename);
    char temp[MAX_LINE_LEN];

    while (fgets(temp, sizeof(temp), fp)) {
        insert_line(buf, temp, buf->line_count + 1);
    }

    fclose(fp);
    printf("File loaded successfully.\n");
}

void save_file(const TextBuffer *buf) {
    if (buf->filename[0] == '\0') {
        printf("Enter filename to save: ");
        scanf("%255s", (char *)buf->filename); // cast to remove const warning
    }

    FILE *fp = fopen(buf->filename, "w");
    if (!fp) {
        printf("Error opening file for writing!\n");
        return;
    }

    for (int i = 0; i < buf->line_count; i++) {
        fputs(buf->lines[i], fp);
    }

    fclose(fp);
    printf("File saved as %s\n", buf->filename);
}

void clear_input_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
        // discard
    }
}

int main() {
    TextBuffer buf;
    init_buffer(&buf);

    int choice;
    char filename[256];
    char line[MAX_LINE_LEN];
    int pos;

    while (1) {
        printf("\n=== MINI TEXT EDITOR ===\n");
        printf("1. Open/Load File\n");
        printf("2. Display File\n");
        printf("3. Insert Line\n");
        printf("4. Delete Line\n");
        printf("5. Save File\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input!\n");
            clear_input_buffer();
            continue;
        }

        clear_input_buffer(); // clear leftover newline

        switch (choice) {
            case 1:
                printf("Enter filename: ");
                scanf("%255s", filename);
                clear_input_buffer();
                free_buffer(&buf);  // free old content
                init_buffer(&buf);  // re-init
                load_file(&buf, filename);
                break;

            case 2:
                display_buffer(&buf);
                break;

            case 3:
                printf("Enter position to insert (1 to %d): ", buf.line_count + 1);
                scanf("%d", &pos);
                clear_input_buffer();
                printf("Enter text: ");
                if (fgets(line, sizeof(line), stdin) == NULL) {
                    printf("Error reading line.\n");
                    break;
                }
                insert_line(&buf, line, pos);
                break;

            case 4:
                printf("Enter line number to delete (1 to %d): ", buf.line_count);
                scanf("%d", &pos);
                clear_input_buffer();
                delete_line(&buf, pos);
                break;

            case 5:
                save_file(&buf);
                break;

            case 6:
                free_buffer(&buf);
                printf("Exiting...\n");
                return 0;

            default:
                printf("Invalid choice! Try again.\n");
        }
    }

    return 0;
}
