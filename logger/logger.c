#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INPUT_SIZE 259
#define FAIL 1
#define SUCCESS 0
#define NUM_COMMANDS 4

typedef struct {
    FILE *file;
    char filename[MAX_INPUT_SIZE];
} Logger;

typedef enum {
    COMMAND_SUCCESS,
    COMMAND_FAIL,
    COMMAND_EXIT
} CommandResult;

typedef struct {
    char name[MAX_INPUT_SIZE];
    int (*compare)(const char *input, const char *name);
    CommandResult (*execute)(Logger *logger, const char *input);
} Command;

void close_logger(Logger *logger) 
{
    if (logger->file != NULL) 
    {
        fclose(logger->file);
    }
}

int init_logger(Logger *logger, int num_of_args, char *argv[]) 
{
    if (num_of_args > 1) 
    {
        strncpy(logger->filename, argv[1], sizeof(logger->filename) - 1);
       

        logger->file = fopen(logger->filename, "a");
        if (logger->file == NULL) 
        {
            printf("Error opening file, Exiting\n");
            return FAIL;
        }
    } 
    else 
    {
        printf("No filename given, Exiting\n");
        return FAIL;
    }
    close_logger(logger);
    return SUCCESS;
}

int log_message(Logger *logger, const char *message) 
{
    if (fprintf(logger->file, "%s\n", message) < 0) 
    {
        return FAIL;
    }
    return SUCCESS;
}

int compare_full(const char *input, const char *name) {
    return strcmp(input, name) == 0;
}

int compare_first_char(const char *input, const char *name) {
    return strncmp(input, name, 1) == 0;
}

CommandResult execute_remove(Logger *logger, const char *input) {
    (void)input; 
    if (remove(logger->filename) == 0) {
        printf("Log file '%s' removed successfully.\n", logger->filename);
        return COMMAND_SUCCESS;
    } else {
        perror("Error removing log file");
        return COMMAND_FAIL;
    }
}

CommandResult execute_count(Logger *logger, const char *input) {
    FILE *file;
    int lines;
    char ch;

    (void)input; 

    file = fopen(logger->filename, "r");
    if (file == NULL) {
        perror("Error opening file to count lines");
        return COMMAND_FAIL;
    }

    lines = 0;
    while ((ch = fgetc(file)) != EOF) {
        if (ch == '\n') {
            lines++;
        }
    }

    fclose(file);

    printf("The log file '%s' contains %d lines.\n", logger->filename, lines);
    return COMMAND_SUCCESS;
}

CommandResult execute_exit(Logger *logger, const char *input) {
    (void)logger; 
    (void)input;  
    printf("Exiting the program.\n");
    return COMMAND_EXIT;
}

CommandResult execute_prepend(Logger *logger, const char *input) {
    FILE *file;
    char *buffer;
    long file_size;

    /* Open the original file in read mode */
    file = fopen(logger->filename, "r");
    if (file == NULL) {
        perror("Error opening file to prepend");
        return COMMAND_FAIL;
    }

    /* Get the size of the original file */
    fseek(file, 0, SEEK_END);
    file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    /* Allocate buffer for the entire file */
    buffer = (char *)malloc(file_size + 1);
    if (buffer == NULL) {
        perror("Error allocating memory");
        fclose(file);
        return COMMAND_FAIL;
    }

    /* Read the entire file into the buffer */
    fread(buffer, 1, file_size, file);
    buffer[file_size] = '\0';

    fclose(file);

    /* Open the file in write mode to overwrite it */
    file = fopen(logger->filename, "w");
    if (file == NULL) {
        perror("Error opening file to write");
        free(buffer);
        return COMMAND_FAIL;
    }

    /* Write the new data at the beginning */
    fprintf(file, "%s\n", input + 1);  /* Skip the '<' character */

    /* Write the original file content after the new data */
    fwrite(buffer, 1, file_size, file);

    fclose(file);
    free(buffer);

    printf("Prepended the string to the file.\n");
    return COMMAND_SUCCESS;
}

int log_get_input(Logger *logger)
{
    char input[MAX_INPUT_SIZE];
    int command_found;
    int i;

    Command commands[NUM_COMMANDS] = {
        {"-remove", compare_full, execute_remove},
        {"-count", compare_full, execute_count},
        {"-exit", compare_full, execute_exit},
        {"<", compare_first_char, execute_prepend}
    };

    printf("Logging started. Enter strings up to %d characters to log. Type '-exit' to quit\n", MAX_INPUT_SIZE - 3);

    while (1) 
    {
        printf("Enter a string: ");
        if (fgets(input, sizeof(input), stdin) == NULL) 
        {
            perror("Error reading input");
            return FAIL;
        }

        /* Check if the string is too long */
        if (input[strlen(input) - 1] != '\n') 
        {
            int c;
            printf("String too long. Please enter up to %d characters.\n", MAX_INPUT_SIZE - 3);

            /* Clear the stdin buffer */
            while ((c = getchar()) != '\n' && c != EOF);

            continue;
        }

        input[strcspn(input, "\n")] = '\0';

        command_found = 0;
        for (i=0 ; i < NUM_COMMANDS; i++) 
        {
            CommandResult result;
            if (!commands[i].compare(input, commands[i].name)) 
            {
              continue;
            }
            result = commands[i].execute(logger, input);
            if (result == COMMAND_EXIT) 
            {
                return SUCCESS;
            }
            command_found = 1;
            break;
        }

        if (!command_found) 
        {
            logger->file = fopen(logger->filename, "a");
            if (log_message(logger, input) != 0) 
            {
                perror("Error writing to log");
                close_logger(logger);
                return FAIL;
            }
            close_logger(logger);
        }
    }

    printf("Logging ended.\n");
    return SUCCESS;
}

int main(int argc, char *argv[]) 
{
    Logger logger;

    if (init_logger(&logger, argc, argv) != SUCCESS) 
    {
        return FAIL;
    }

    if (log_get_input(&logger) != SUCCESS) 
    {
        return FAIL;
    }

    return SUCCESS;
}

