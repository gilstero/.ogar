/*
Created by Olin Gilster S'26
This work is subject to the MIT License (https://opensource.org/licenses/MIT)
*/

// import statements for files
#include "ogar.h"

// import statements for libraries
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

// get opt
#include <getopt.h>
#include <unistd.h>

static void usage(const char *prog);

int main(int argc, char **argv) {
    int opt;

    char zflag, oflag = 0;

    while((opt = getopt(argc, argv, "c:q:a:vx:Xzo")) != -1) {
        switch(opt) {
            case 'c':
                break;
            case 'q':
                break;
            case 'a':
                break;
            case 'v':
                break; 
            case 'x':
                break;
            case 'X':
                break;

            // default print usage
            default:
                usage(argv[0]);
        }

        
    }


    exit(1);
}

// main usage printout when error
static void usage(const char *prog) {
    fprintf(stderr,
    "Usage:\n"
        "  %s -c archive.ogar\n"
        "  %s -q archive.ogar file1 [file2 ...]       (append)\n"
        "  %s -a archive.ogar                         (append old>10days)\n"
        "  %s -v archive.ogar                         (list)\n"
        "  %s -x archive.ogar filename                (extract one)\n"
        "  %s -X archive.ogar                         (extract all)\n"
        "Options:\n"
        "  -z   compress with deflate\n"
        "  -o   restore metadata on extract (chmod/chown/utimensat)\n",
        prog, prog, prog, prog, prog, prog, prog
    );
    exit(1);
}