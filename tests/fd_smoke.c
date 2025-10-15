/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_smoke.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seokson <seokson@student.42gyeongsan.kr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 16:58:20 by seokson           #+#    #+#             */
/*   Updated: 2025/10/06 16:58:20 by seokson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include "fd_utils.h"

static int g_total = 0, g_fail = 0;
static void expect(const char *label, int ok)
{
    g_total++;
    if (ok) printf("ok %d - %s\n", g_total, label);
    else { printf("not ok %d - %s\n", g_total, label); g_fail++; }
}

int main(void)
{
    int fd, r;
    char buf[8];

    /* open trunc + ro */
    fd = x_open_trunc("/tmp/fd_t.txt", 0644);
    expect("x_open_trunc create", fd>=0);
    if (fd>=0) { write(fd, "A", 1); x_close(fd); }
    fd = x_open_ro("/tmp/fd_t.txt");
    expect("x_open_ro read", fd>=0);
    if (fd>=0) { r = (int)read(fd, buf, 1); expect("read A", r==1 && buf[0]=='A'); x_close(fd); }

    /* open append */
    fd = x_open_append("/tmp/fd_t.txt", 0644);
    expect("x_open_append", fd>=0);
    if (fd>=0) { write(fd, "B", 1); x_close(fd); }
    fd = open("/tmp/fd_t.txt", O_RDONLY);
    if (fd>=0) { r=(int)read(fd, buf, 2); expect("append makes AB", r==2 && buf[0]=='A' && buf[1]=='B'); x_close(fd); }

    /* pipe + dup2 */
    {
        int p[2];
        expect("x_pipe", x_pipe(p)==0);
        if (p[0]>=0 && p[1]>=0)
        {
            int d = dup(1);
            expect("dup stdout", d>=0);
            expect("dup2 to 5", x_dup2(p[1], 5)>=0);
            write(5, "Z", 1);
            char c='?'; read(p[0], &c, 1);
            expect("read Z from pipe", c=='Z');
            if (d>=0) { x_dup2(d,1); x_close(d);} 
            close_pipe_pair(p);
        }
    }

    printf("1..%d\n", g_total);
    if (g_fail) printf("# summary: %d/%d failed\n", g_fail, g_total);
    else printf("# summary: all %d passed\n", g_total);
    /* cleanup (KEEP=1 이면 유지) */
    if (!getenv("KEEP"))
        unlink("/tmp/fd_t.txt");
    else
        printf("# KEEP=1: artifacts preserved\n");
    return 0;
}
