#ifndef TASK_LIST_H
#define TASK_LIST_H

#include "../models/tasks.h"

typedef struct TaskList_* TaskList;

TaskList task_list_new();

void task_list_destroy(TaskList task_list);

char* task_list_add_task(TaskList task_list, char* description);

void task_list_complete_task(TaskList task_list, char* id);

int task_list_get_num_tasks(TaskList task_list);

Task* task_list_get_tasks(TaskList task_list);

#endif
