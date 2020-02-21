#include <stdio.h>
#include <time.h>
#include <malloc.h>
#include <stdbool.h>
#include <windows.h>

#define FILL_CUSTOM 1
#define FILL_RANDOM 2
#define SHOW 3
#define TASK 4
#define QUIT 5

typedef struct
{
    int* Content;
    int Size;
    bool IsFilled;
} DynArray;


#define INPUT_SIZE 256

int CycleInputInt(char* stringToOutput, bool(* pChecker)(int))
{
    int number;
    int position;
    char input[INPUT_SIZE];
    while (true)
    {
        printf("%s\n", stringToOutput);
        fflush(stdout);
        char* fgetsRet = fgets(input, INPUT_SIZE, stdin);
        if (fgetsRet == NULL) continue;
        int inputLength = strlen(input) - 1;
        input[inputLength] = '\0';
        int sscanfRet = sscanf(input, "%d%n", &number, &position);
        if (position != inputLength) continue;
        if (pChecker && !pChecker(number)) continue;
        if (sscanfRet == 1) break;
        printf("Wrong format!\n");
    }
    return number;
}


bool SizeInputChecker(int size)
{
    return size >= 1;
}

bool OperationInputChecker(int operationCode)
{
    return operationCode >= FILL_CUSTOM && operationCode <= QUIT;
}

bool TaskValueInputChecker(int taskValue)
{
    return taskValue != 0;
}

int main()
{
    DynArray objectArray;
    objectArray.IsFilled = false;
    int operationCode;
    while (1)
    {
        printf("1. Fill array with custom values.\n"
               "2. Fill array with random values.\n"
               "3. Show current value of the array.\n"
               "4. Perform the task and show the result.\n"
               "5. Quit program.\n ");
        operationCode = CycleInputInt(
                "Choose the command and enter its number",
                OperationInputChecker);
        // Ручное заполнение массива
        if (operationCode == FILL_CUSTOM)
        {
            if (objectArray.IsFilled)
            {
                free(objectArray.Content);
            }
            objectArray.Size = CycleInputInt("Enter number of elements",
                                             SizeInputChecker);
            objectArray.Content = (int*) malloc(
                    objectArray.Size * sizeof(int));
            printf("Enter elements' values\n");
            for (int i = 0; i < objectArray.Size; i++)
            {
                objectArray.Content[i] = CycleInputInt("Enter element value",
                                                       NULL);
            }
            objectArray.IsFilled = true;
        }
        // Случайное заполнение массива
        if (operationCode == FILL_RANDOM)
        {
            if (objectArray.IsFilled)
            {
                free(objectArray.Content);
            }
            srand((unsigned) time(NULL));
            objectArray.Size = CycleInputInt("Enter number of elements",
                                             SizeInputChecker);
            objectArray.Content = (int*) malloc(
                    objectArray.Size * sizeof(int));
            for (int i = 0; i < objectArray.Size; i++)
            {
                objectArray.Content[i] = (rand() % 201) - 100;
            }
            objectArray.IsFilled = true;
        }
        // Вывод массива
        if (operationCode == SHOW)
        {
            for (int i = 0; i < objectArray.Size; i++)
            {
                printf("%d ", objectArray.Content[i]);
            }
            printf("\n");
        }
        // Выполнение задачи
        if (operationCode == TASK)
        {
            int taskValue;
            if (!objectArray.IsFilled)
            {
                printf("Array is empty\n");
            }
            else
            {
                taskValue = CycleInputInt("Enter m value for the task",
                                          TaskValueInputChecker);
                int arraySize = objectArray.Size * (objectArray.Size - 1) / 2;
                int taskResult[1000][2];
                int taskResultIter = 0;
                for (int i = 0; i < objectArray.Size - 1; i++)
                {
                    for (int j = i + 1; j < objectArray.Size; j++)
                    {
                        if (objectArray.Content[i] % taskValue ==
                            objectArray.Content[j] % taskValue)
                        {
                            taskResult[taskResultIter][0] = objectArray.Content[i];
                            taskResult[taskResultIter][1] = objectArray.Content[j];
                            taskResultIter++;
                        }
                    }
                }
                for (int i = 0; i < taskResultIter; i++)
                {
                    printf("%d and %d;\n", taskResult[i][0],
                           taskResult[i][1]);
                }
            }
            return 0;
        }
        if (operationCode == QUIT)
        {
            break;
        }
    }
    if (objectArray.IsFilled)
    {
        free(objectArray.Content);
        objectArray.IsFilled = false;
    }
    return 0;
}
