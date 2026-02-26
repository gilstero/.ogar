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
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

// get opt
#include <getopt.h>
#include <unistd.h>


// define all of my helper functions
int is_ogar(const char *path);
int x_method();
int z_method();
int c_method();
int q_method();
int a_method();
int v_method();
int X_method();
int compress();

// functions
