/* more02.c ---- 自作 more バージョン 0.2 */
#include <stdio.h>
#include <stdlib.h>

#define PAGELEN 24
#define LINELEN 512

void do_more(FILE *fp);
int  ask_user(FILE *cmd);

int main(int ac, char *av[])
{
    FILE *fp;
    if (ac == 1) {
        do_more(stdin);
    } else {
        while (--ac) {
            if ((fp = fopen(*++av, "r")) != NULL) {
                do_more(fp);
                fclose(fp);
            } else {
                perror(*av);
                return 1;
            }
        }
    }
    return 0;
}

void do_more(FILE *fp)
{
    char line[LINELEN];
    int  num_of_lines = 0;
    int  reply;
    FILE *fp_tty;

    fp_tty = fopen("/dev/tty", "r");
    if (fp_tty == NULL) {
        fprintf(stderr, "/dev/tty を開けません\n");
        exit(1);
    }

    while (fgets(line, LINELEN, fp) != NULL) {
        if (num_of_lines == PAGELEN) {
            reply = ask_user(fp_tty);
            if (reply == 0) break;
            num_of_lines -= reply;
        }
        if (fputs(line, stdout) == EOF) exit(1);
        num_of_lines++;
    }
    fclose(fp_tty);
}

int ask_user(FILE *cmd)
{
    int c;
    printf("\033[7m--More--\033[m");
    fflush(stdout);
    c = fgetc(cmd);
    if (c == 'q') return 0;
    if (c == ' ') return PAGELEN;
    return 1;
}
