/* This file is part of regetopt.
   reGetopt is licensed under GNU GPL v3 or MIT License. */

#include <stdio.h>

#include "include/regetopt.h"

static struct re_option options[] = {{"foobar", re_no_argument, NULL, 'f'},
                                     {"foobaz", re_no_argument, NULL, 'b'},
                                     {"baz", re_required_argument, NULL, 'z'},
                                     {"help", re_no_argument, NULL, 'h'},
                                     {"help!", re_no_argument, NULL, 'H'},
                                     {"version", re_no_argument, NULL, 'v'},
                                     {0, 0, 0, 0}};

static void print_usage() {
    puts("usage: sample [OPTION]... [REST]...\n"
         "  --foobar, -f       do foobar\n"
         "  --foobaz, -b       do foobaz\n"
         "  --baz ARG, -z ARG  do baz\n"
         "  --help, -h         help?\n"
         "  --help!            print usage\n"
         "  --version          version?\n"
         "===================================");
}

int main(int argc, char **argv) {
    for (;;) {
        int opt = regetopt(argc, argv, "fbz:h", options, NULL);
        if (opt < 0) {
            break;
        }
        switch (opt) {
        case 'f':
            puts("foobar");
            break;

        case 'b':
            puts("foobaz");
            break;

        case 'z':
            printf("baz: %s\n", re_optarg);
            break;

        case 'H':
            puts("help!");
            print_usage();
            break;


        case 'h':
            puts("help (to print usage, execute with --help! option)");
            break;

        case 'v':
            puts("version");
            break;

        case '?':
            puts("unknown option read.");
            return 1;

        case ':':
            puts("argument not given.");
            return 1;
        }
    }

    puts("\nremaining arguments:");
    for (int i = re_optind; i < argc; ++i) {
        printf("- %s\n", argv[i]);
    }
}
