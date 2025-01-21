#include <stdio.h>

static const char base[] = "`\n"
"#include <stdio.h>\n"
"int main() {\n"
"`\n"
"<!DOCTYPE html>\n"
"<html lang=\"en\">\n"
"<head>\n"
"    <meta charset=\"UTF-8\">\n"
"    <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\n"
"    <title>Document</title>\n"
"</head>\n"
"<body>\n"
"\n"
"</body>\n"
"</html>\n"
"`}`\n";


int main(int argc, char **argv) {
    printf(base);
    return 0;
}