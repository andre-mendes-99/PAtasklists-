#include "tasks.h"
#include <stdlib.h>
#include <string.h>

struct Task_ {
    char* id;
    char* description;
    char* status;
};

Task task_new(char* id, char* description) {
    Task task = malloc(sizeof(struct Task_));
    task->id = strdup(id);
    task->description = strdup(description);
    task->status = strdup("Por completar");
    return task;
}

void task_destroy(Task task) {
    free(task->id);
    free(task->description);
    free(task->status);
    free(task);
}

char* task_get_id(Task task) {
    return task->id;
}

char* task_get_description(Task task) {
    return task->description;
}

char* task_get_status(Task task) {
    return task->status;
}

void task_set_completed(Task task) {
    free(task->status);
    task->status = strdup("Completa");
}
