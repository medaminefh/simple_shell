#!/bin/bash
betty *.c
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh
