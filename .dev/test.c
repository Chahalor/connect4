#include <ncurses.h>
#include <string.h>

typedef struct {
	int x1, y1, x2, y2;
	char *label;
} Button;

void draw_button(Button btn) {
	for (int y = btn.y1; y <= btn.y2; y++) {
		for (int x = btn.x1; x <= btn.x2; x++) {
			mvaddch(y, x, ' ');
		}
	}
	mvprintw((btn.y1 + btn.y2)/2, (btn.x1 + btn.x2 - strlen(btn.label))/2, "%s", btn.label);
	box(stdscr, 0, 0); // Juste pour une bordure globale
}

int is_inside(Button btn, int x, int y) {
	return x >= btn.x1 && x <= btn.x2 && y >= btn.y1 && y <= btn.y2;
}

int main(void) {
	register int nb_press = 0;
	initscr();
	cbreak();
	noecho();
	keypad(stdscr, TRUE);
	mousemask(ALL_MOUSE_EVENTS, NULL);

	Button my_button = {10, 5, 30, 7, "Cliquer ici"};

	draw_button(my_button);
	refresh();

	MEVENT event;
	while (1) {
		int ch = getch();
		if (ch == 'q')
			break;
		if (ch == KEY_MOUSE) {
			if (getmouse(&event) == OK) {
				if (is_inside(my_button, event.x, event.y)) {
					mvprintw(10, 5, "Bouton pressé ! (%d)", ++nb_press);
				}
			}
		}
	}

	endwin();
	return 0;
}
