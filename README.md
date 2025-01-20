# CHTML

A templating engine that combines C and HTML. It compiles to C code and creates an executable that generates HTML output when run.

## Syntax

The template uses HTML as the default language. To embed C code within the template, enclose it in backticks (`). Each backtick toggles between HTML and C mode.
The structure of a template is as follows:

```html
`
[C code that needs to be outside the main function]
START
`
[HTML code]
[C code snippets embedded within HTML as needed]
```

Example:

```html
`
#include <time.h>
START
`
<body>
    <h1>Hello, world!</h1>
    <p>The current time is: `
        time_t t = time(NULL);
        P(ctime(&t));
    `</p>
</body>
```

Important: Any C code that needs to be outside of the main function must be placed before the `START` macro.

## Defined macros

- `START` - Indicates the beginning of the main function and initializes the output file.
- `P(...)` - Functions like printf but writes to the output file.

## Usage

To use the templating engine, you first need to compile it. The engine requires gcc to be installed and accessible in your PATH.

```bash
gcc -o chtml chtml.c
```

The program requires 4 arguments:

1. directory
2. template file
3. output file
4. secondary output file

Example usage:

```bash
./chtml ./test temp.html out.c index.html
```

This command generates two files:

1. `out.c` - The intermediate C code
2. `out.c.exe` - The executable that generates `index.html`

Typically, you'll compile the template once and run the resulting executable whenever you need to generate a new HTML file.
