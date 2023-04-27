#include "cli.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../controllers/task_list.h"
#include "../models/tasks.h"

void run_cli() {
    char* line = NULL;
    size_t len = 0;
    TaskList task_list = task_list_new();
    while (true) {
        getline(&line, &len, stdin);
        char* command = strtok(line, " \n");
        if (strcmp(command, "Q") == 0) {
            break;
        } else if (strcmp(command, "RT") == 0) {
            char* description = strtok(NULL, "\n");
            char* id = task_list_add_task(task_list, description);
            printf("Tarefa criada com identificador %s.\n", id);
        } else if (strcmp(command, "LT") == 0) {
            Task* tasks = task_list_get_tasks(task_list);
            int num_tasks = task_list_get_num_tasks(task_list);
            for (int i = 0; i < num_tasks; i++) {
                Task task = tasks[i];
                if (task != NULL) {
                    printf("%s %s %s\n", task_get_id(task), task_get_description(task), task_get_status(task));
                }
            }
        } else if (strcmp(command, "MT") == 0) {
            char* id = strtok(NULL, "\n");
            task_list_complete_task(task_list, id);
            printf("Tarefa %s marcada como completa.\n", id);
        } else {
            printf("Instrução inválida.\n");
        }
        free(line);
        line = NULL;
    }
    if (line != NULL) {
        free(line);
    }
    task_list_destroy(task_list);
}
