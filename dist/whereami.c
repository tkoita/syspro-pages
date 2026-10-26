/* whereami.c ---- 自分の 0 / 1 / 2 がどこにつながっているかをカーネルに聞く
 *
 * 第3週目 Stage B-4 で配布するプログラム。
 * 報告は 2番（標準エラー出力）に出しているので、1番をパイプやファイルに
 * 差し替えても画面に残る。そこが観察のポイント。
 *
 *   gcc -Wall -o whereami whereami.c
 *   ./whereami                  → 3本とも端末
 *   ./whereami | cat            → 1番だけ変わる
 *   echo hi | ./whereami        → 0番だけ変わる
 *   ./whereami > log.txt        → 報告は画面に残る（2番だから）
 *   ./whereami 2> log.txt ; cat log.txt
 */
#include <stdio.h>
#include <unistd.h>

void report(int fd, const char *name)
{
    if (isatty(fd))
        fprintf(stderr, "fd %d (%s) : 端末です  -> %s\n", fd, name, ttyname(fd));
    else
        fprintf(stderr, "fd %d (%s) : 端末ではありません\n", fd, name);
}

int main(void)
{
    report(0, "標準入力      ");
    report(1, "標準出力      ");
    report(2, "標準エラー出力");
    return 0;
}
