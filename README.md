# CHTML

A templating engine that combines C and HTML. It compiles to C code and creates an executable that generates HTML output when run.

## Syntax

The template uses HTML as the default language. To embed C code within the template, enclose it in backticks (`). Each backtick toggles between HTML and C mode.
The structure of a template is as follows:

Example:

```html
`
#include <stdio.h>
#include <time.h>
int main() {
`
<body>
    <h1>Hello, world!</h1>
    <p>The current time is: `
        time_t t = time(NULL);
        printf(ctime(&t));
    `</p>
</body>
`}`
```

Important: Any text outside the backticks is later converted into C code, that's why it needs to be inside of the main function.

### Escaping

You can prefix any character with a backslash to escape it. Note, that any backslashes that are supposed to be interpreted literally need to be escaped. Example:

```html
<p>This is a backslash: \</p>   <!--incorrect-->
<p>This is a backslash: \\</p>  <!--correct-->
`
printf("newline: \n");   // incorrect
printf("newline: \\n");  // correct
`
```

## Usage

To use the templating engine, you first need to compile it. The engine requires gcc to be installed and accessible in your PATH.

```bash
gcc -o chtml chtml.c
```

The program requires 3 arguments:

1. directory
2. template file
3. output file

Example usage:

```bash
./chtml ./test temp.html out.c
```

This command generates two files:

1. `./test/out.c` - The intermediate C code
2. `./test/out.c.exe` - The executable that generates the HTML output

Typically, you'll compile the template once and run the resulting executable whenever you need to generate a new HTML file.

To use the generated HTML you can redirect it by piping or redirection operator:

```bash
./test/out.c.exe | grep "Hello"
./test/out.c.exe > output.html
```

## Changelog

1.0.0 - Initial release. Uses secondary file for HTML output. Accepted 4 arguments.
2.0.0 - Uses stdout for HTML output. Accepted 3 arguments (got rid of secondary file).
2.1.0 - Added basegen.c for generating a base template.
