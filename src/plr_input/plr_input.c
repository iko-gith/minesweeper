#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#include "plr_input.h"

void clear_input() {
    int c = getchar();
    while ( c != '\n' && c != EOF )
        c = getchar();
}

void print_help() {
    printf("");
}

int get_plr_input(int *x, int *y) {
    char cmd;
    *x = -1;
    *y = -1;

    printf("\nPC Input: ");
    
    if (scanf(" %c", &cmd) != 1) {
        clear_input();
	return ACTION_INVALID;
    }

    cmd = toupper(cmd);
    switch(cmd) {
        case 'H':
	    // Вывод комманд, позже    
	    break;
	case 'N':
	    return ACTION_NEW_GAME;
	case 'R':
            if (scanf("%d %d", x, y) == 2)
                return ACTION_REVEAL;
	    break;
	case 'F':
	    if (scanf("%d %d", x, y) == 2)
		return ACTION_FLAG;
	    break;
	case 'Q':
	    return ACTION_QUIT;
	default:
	    break;
    }

    clear_input();
    return ACTION_INVALID;
}
