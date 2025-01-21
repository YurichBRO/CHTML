#include <stdio.h>
#include <stdlib.h>

void write_symbol(FILE *out, char symbol) {
    fprintf(out, "putchar(%i);\n", symbol);
}

void write_template(FILE *out, char symbol) {
    fputc(symbol, out);
}

void write_template_string(FILE *out, char *str) {
    for (int i = 0; str[i] != '\0'; i++) {
        fputc(str[i], out);
    }
}

void chtml2c(FILE *in, FILE *out) {
    unsigned char inside = 0;
    unsigned char escaped = 0;
    char c;
    while ((c = fgetc(in)) != EOF) {
        if (escaped) {
            if (inside) {
                write_template(out, c);
            } else {
                write_symbol(out, c);
            }
            escaped = 0;
            continue;
        }
        if (c == '\\') {
            escaped = 1;
            continue;
        }
        if (c == '`') {
            inside = !inside;
            continue;
        }
        if (inside) {
            write_template(out, c);
        } else {
            write_symbol(out, c);
        }
    }
    fclose(out);
    fclose(in);
}

int main(int argc, char **argv) {
    if (argc != 4) {
        printf("Usage: %s <directory> <input_file> <output_file>\n", argv[0]);
        return 1;
    }
    char input_path[1024];
    char output_path[1024];
    sprintf(input_path, "%s/%s", argv[1], argv[2]);
    sprintf(output_path, "%s/%s", argv[1], argv[3]);
    
    FILE *in = fopen(input_path, "r");
    if (in == NULL) {
        printf("Error opening input file\n");
        return 1;
    }
    
    FILE *out = fopen(output_path, "w");
    if (out == NULL) {
        printf("Error opening output file\n");
        fclose(in);
        return 1;
    }
    
    chtml2c(in, out);
    
    char command[1024];
    sprintf(command, "gcc -o %s.exe %s", output_path, output_path);
    system(command);
    return 0;
}