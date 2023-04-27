#include "task_list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../utils/list.h"

struct TaskList_ {
    List tasks;
};

TaskList task_list_new() {
    TaskList task_list = malloc(sizeof(struct TaskList_));
    task_list->tasks = list_create();
    return task_list;
}

void task_list_destroy(TaskList task_list) {
    list_destroy(task_list->tasks, NULL);
    free(task_list);
}

char* _generate_id(TaskList task_list) {
    char* id = malloc(sizeof(char) * 10);
    sprintf(id, "%d", list_size(task_list->tasks));
    return id;
}

char* task_list_add_task(TaskList task_list, char* description) {
    char* id = _generate_id(task_list);
    Task task = task_new(id, description);
    free(id);
    list_insert_last(task_list->tasks, task);
    return task_get_id(task);
}

bool equal_tasks(void* e1, void* e2) {
    Task t1 = (Task)e1;
    Task t2 = (Task)e2;
    return task_get_id(t1) == task_get_id(t2);
}

void task_list_complete_task(TaskList task_list, char* id) {
    Task temp_task = task_new(id, NULL);
    int pos = list_find(task_list->tasks, equal_tasks, temp_task);
    Task task = list_get(task_list->tasks, pos);
    task_set_completed(task);
}

int task_list_get_num_tasks(TaskList task_list) {
    return list_size(task_list->tasks);
}

Task* task_list_get_tasks(TaskList task_list) {
    return task_list->tasks;
}
