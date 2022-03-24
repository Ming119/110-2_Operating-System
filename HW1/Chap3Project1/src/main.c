/*
 *  Chap3Project1/src/main.c  
 *
 *  Programming Project Chap.3 Project 1
 *  UNIX Shell and History Feature
 * 
 */

#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>

#ifndef BUF_SIZE
#define BUF_SIZE 64
#endif

typedef struct history_t {
    int  order;
    char command[7];
    struct history_t *next;
} history_t;

int argc = 0;
history_t *head = NULL;

char **splitString(char *str, char *delims);
void history(int n, char *command);
void execute(char **args, char *command);
void displayHistory();

char **splitString(char *str, char *delims)
{
    argc = 0;
    char **res = malloc(BUF_SIZE * sizeof(char*));
    char *token = strtok(str, delims);

    while (token != NULL)
    {
        res[argc++] = token;
        token = strtok(NULL, delims);
    }

    return res;
}

void history(int n, char *command)
{
    if (n == 0)
    {
        if (head == NULL)
        {
            history_t *h = malloc(sizeof(history_t));
            h->order = 1;
            sprintf(h->command, "%s", command);
            head = h;
        
        } else
        {   
            history_t *h = head;
            while (h->next != NULL)
            {
                h->order++;
                h = h->next;
            }

            history_t *nh = malloc(sizeof(history_t));
            nh->order = 1;
            sprintf(nh->command, "%s", command);
            h->order++;
            h->next = nh;
        }

    } else
    {   
        if (head == NULL)
        {
            printf("No commands in history.\n");
            return;
        }

        history_t *h = head;
        while (h != NULL && h->order != n)
        {
            h = h->next;
        }

        if (h == NULL || h->order != n)
        {
            printf("No such command in history.\n");
            return;
        }

        char *tmp = malloc(strlen(h->command) + 1);
        strcpy(tmp, h->command);
        char **args = splitString(tmp, " ");
        execute(args, h->command);
        free(tmp);
    }
}

void execute(char **args, char *command)
{
    pid_t pid = fork();
    if (pid < 0)
    {
        perror("Fork Error");
        exit(EXIT_FAILURE);

    } else if (pid == 0)
    {
        execvp(args[0], args);

    } else
    {
        history(0, command);
        wait(NULL);
    }
}

void displayHistory()
{
    if (head == NULL)
    {
        printf("No commands in history.\n");
        return;
    }

    history_t *h = head;
    while (h != NULL)
    {
        printf("%d\t%s\n", h->order, h->command);
        h = h->next;
    }
}

int main(void)
{
    int flag = 0;
    char inputBuffer[BUF_SIZE];
    char command[BUF_SIZE];
    char **args;

    while (1)
    {
        flag = 0;
        printf("osh> ");
        fflush(stdout);
        scanf("%[^\n]%*c", inputBuffer);

        strcpy(command, inputBuffer);

        args = splitString(inputBuffer, " ");

        if (!strcmp(args[0], "exit"))
        {   
            history_t *h = head;
            while (h != NULL)
            {
                head = h->next;
                free(h);
                h = head;
            }
            exit(EXIT_SUCCESS);
        }

        if (!strcmp(args[0], "history"))
        {
            displayHistory();

        } else if (!strcmp(args[0], "!!"))
        {
            history(1, NULL);

        } else if (args[0][0] == '!' && isdigit(args[0][1]))
        {   
            history(args[0][1] - '0', NULL);

        } else
        {
            execute(args, command);
        }

        free(args);


        /**
        * After reading user input, the steps are:
        * (1) fork a child process using fork()
        * (2) the child process will invoke execvp()
        * (3) if command included &, parent will invoke wait()
        */
    }

    exit(EXIT_SUCCESS);
}