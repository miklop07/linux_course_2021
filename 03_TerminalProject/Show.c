#include <curses.h>
#include <locale.h>
#include <fcntl.h>

#define DX 3

int main(int argc, char **argv) {
    if (argc == 1) {
        return 0;
    }

    int fd;
    if ((fd = open(argv[1], O_RDONLY)) == -1) {
        printf("Error open file");
        return 0;
    }

    int num_lines = 0;
    char buf;
    while (read(fd, &buf, 1)) {
        if (buf == '\n') {
            ++num_lines;
        }
    }
    ++num_lines;

    initscr();
    noecho();
    cbreak();
    int width = COLS - 2 * DX - 1;

    lseek(fd, 0, 0);
    char file_text[num_lines + 1][width + 2];
    int end_flag = 0;
    int curr_line_pos;
    for (int i = 0; i < num_lines - 1; ++i) {
        curr_line_pos = 0;
        do {
            read(fd, &buf, 1);
            file_text[i][curr_line_pos] = buf;
            ++curr_line_pos;
        } while (buf != '\n' && curr_line_pos < width);
        if (curr_line_pos == width) {
            file_text[i][curr_line_pos] = '\n';
            ++curr_line_pos;
        }
        file_text[i][curr_line_pos] = '\0';
        while (buf != '\n') {
            read(fd, &buf, 1);
        }
    }
    curr_line_pos = 0;
    while (read(fd, &buf, 1) && curr_line_pos < width) {
        putchar(buf);
        file_text[num_lines][curr_line_pos] = buf;
        ++curr_line_pos;
    }
    file_text[num_lines][curr_line_pos] = '\0';

    close(fd);

    WINDOW *win;

    printw("File: %s%d", argv[1], width);
    refresh();

    win = newwin(LINES - 2 * DX, COLS - 2 * DX, DX, DX);
    keypad(win, TRUE);
    scrollok(win, TRUE);
    box(win, 0, 0);
    wmove(win, 1, 0);

    int height = LINES - 3 * DX;
    int last_line = height + 1, start_line = 0;
    for (int i = start_line; i < last_line; ++i) {
        wprintw(win, "  %s", file_text[i]);
    }
    box(win, 0, 0);
    int c = 0;
    while((c = wgetch(win)) != 27) {
        if (c == 32) {
            start_line = last_line;
            last_line = last_line + height + 1;
            if (last_line > num_lines) {
                last_line = num_lines;
            }
        }
        for (int i = start_line; i < last_line; ++i) {
            wprintw(win, "  %s", file_text[i]);
        }
        
        box(win, 0, 0); 
        wrefresh(win);
    }
    endwin();


    return 0;
}