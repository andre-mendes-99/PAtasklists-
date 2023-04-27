#ifndef TASKS_H
#define TASKS_H

typedef struct Task_* Task;

Task task_new(char* id, char* description);

void task_destroy(Task task);

char* task_get_id(Task task);

char* task_get_description(Task task);

char* task_get_status(Task task);

void task_set_completed(Task task);

#endif
