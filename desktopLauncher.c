#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (strcmp(argv[1], "l") == 0 || strcmp(argv[1], "ls") == 0 || strcmp(argv[1], "list") == 0) {
        if (strcmp(argv[2], "w") == 0 || strcmp(argv[2], "wl") == 0 || strcmp(argv[2], "wayland") == 0) {
               system("ls /usr/share/wayland-sessions");
               return 0;
        } else if (strcmp(argv[2], "x") == 0 || strcmp(argv[2], "x11") == 0 || strcmp(argv[2], "xorg") == 0) {
                system("ls /usr/share/xsessions");
                return 0;
        } else { printf("Please input a valid session type: wayland[w, wl, wayland], xorg[x, x11, xorg]\n"); return 0;}
    }

    char *filename;
    char *wl_prefix = "/usr/share/wayland-sessions/";
    char *x_prefix = "/usr/share/xsessions/";
    char *dotdesktop = ".desktop";
    if (strcmp(argv[1], "w") == 0 || strcmp(argv[1], "wl") == 0 || strcmp(argv[1], "wayland") == 0) {
            filename = malloc(strlen(wl_prefix) + strlen(argv[2]) + strlen(".desktop") + 1);
            strcpy(filename, wl_prefix);
            strcat(filename, argv[2]);
            if (strlen(filename) < strlen(dotdesktop) || strcmp(&filename[strlen(filename)-strlen(dotdesktop)], dotdesktop)) {
                strcat(filename, dotdesktop);
            }
    } else if (strcmp(argv[1], "x") == 0 || strcmp(argv[1], "x11") == 0 || strcmp(argv[1], "xorg") == 0) {
        filename = malloc(strlen(x_prefix) + strlen(argv[2]) + strlen(".desktop") + 1);
        strcpy(filename, x_prefix);
        strcat(filename, argv[2]);
        if (strlen(filename) < strlen(".desktop") || strcmp(&filename[strlen(filename)-strlen(".desktop")], ".desktop")) {
            strcat(filename, ".desktop");
        }
    } else { printf("Please input a valid session type: wayland[w, wl, wayland], xorg[x, x11, xorg]\n"); return 0;}

    FILE *file = fopen(filename, "r");
    char line[256];
    char *exec_command = NULL;

    while (fgets(line, sizeof(line), file)) {
        if (strncmp(line, "Exec=", 5) == 0) {
            exec_command = line + 5;
            exec_command[strcspn(exec_command, "\n")] = 0;
            break;
        }
    }
    fclose(file);

    if (exec_command) {
        system(exec_command);
    }

    free(filename);
    return 0;
}
