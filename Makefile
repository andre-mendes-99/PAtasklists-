bin/main: main.c controllers/task_list.c models/tasks.c views/cli.c utils/singly_linked_list.c
	gcc -g $^ -o $@

clear:
	rm bin/*
