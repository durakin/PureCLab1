#include <stdio.h>
#include <time.h>
#include <malloc.h>
#include <stdbool.h>
#include <windows.h>

    enum OperationsCodes
    {
        FILL_CUSTOM = 1,
        FILL_RANDOM = 2,
        SHOW = 3,
        TASK = 4,
        QUIT = 5
    };
    enum Sizes
    {
        MAX_ARRAY_SIZE = 100,
        MAX_PAIRS_NUMBER = 9900,
        INPUT_SIZE = 256
    };

    typedef struct
    {
        int* Content;
        int Size;
        bool IsFilled;
    } DynArray;

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
        if (fgetsRet == NULL)
        {
            printf("Wrong format!\n");
            continue;
        }
        int inputLength = strlen(input) - 1;
        input[inputLength] = '\0';
        int sscanfRet = sscanf(input, "%d%n", &number, &position);
        if (position != inputLength)
        {
            printf("Wrong format!\n");
            continue;
        }
        if (pChecker && !pChecker(number))
        {
            printf("Wrong format!\n");
            continue;
        }
        if (sscanfRet == 1) break;
        printf("Wrong format!\n");
    }
    return number;
}

bool SizeInputChecker(int size)
{
    return size >= 1 && size <= MAX_ARRAY_SIZE;
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
    DynArray objArray;
    objArray.IsFilled = false;
    int operationCode;
    while (true)
    {
        printf("\n1. Fill array with custom values.\n"
               "2. Fill array with random values.\n"
               "3. Show current value of the array.\n"
               "4. Perform the task and show the result.\n"
               "5. Quit program.\n\n ");
        operationCode = CycleInputInt(
                "Choose the command and enter its number",
                OperationInputChecker);

        if (operationCode == FILL_CUSTOM)
        {
            if (objArray.IsFilled)
            {
                free(objArray.Content);
            }
            objArray.Size = CycleInputInt("Enter number of elements",
                                             SizeInputChecker);
            objArray.Content = (int*) malloc(
                    objArray.Size * sizeof(int));
            printf("Enter elements' values\n");
            for (int i = 0; i < objArray.Size; i++)
            {
                objArray.Content[i] = CycleInputInt("Enter element value",
                                                       NULL);
            }
            objArray.IsFilled = true;
        }

        if (operationCode == FILL_RANDOM)
        {
            if (objArray.IsFilled)
            {
                free(objArray.Content);
            }
            srand((unsigned) time(NULL));
            objArray.Size = CycleInputInt("Enter number of elements",
                                             SizeInputChecker);
            objArray.Content = (int*) malloc(
                    objArray.Size * sizeof(int));
            for (int i = 0; i < objArray.Size; i++)
            {
                objArray.Content[i] = (rand() % 201) - 100;
            }
            objArray.IsFilled = true;
        }

        if (operationCode == SHOW)
        {
            printf("\nElements' values:\n");
            for (int i = 0; i < objArray.Size; i++)
            {
                printf("%d ", objArray.Content[i]);
            }
            printf("\n\n");
        }

        if (operationCode == TASK)
        {
            int taskValue;
            if (!objArray.IsFilled)
            {
                printf("Array is empty\n");
            }
            else
            {
                taskValue = CycleInputInt("\nEnter m value for the task",
                                          TaskValueInputChecker);
                int taskResult[MAX_PAIRS_NUMBER][2];
                int taskResultIter = 0;
                for (int i = 0; i < objArray.Size - 1; i++)
                {
                    for (int j = i + 1; j < objArray.Size; j++)
                    {
                        if (objArray.Content[i] % taskValue ==
                            objArray.Content[j] % taskValue)
                        {
                            taskResult[taskResultIter][0] = objArray.Content[i];
                            taskResult[taskResultIter][1] = objArray.Content[j];
                            taskResultIter++;
                            taskResult[taskResultIter][1] = objArray.Content[i];
                            taskResult[taskResultIter][0] = objArray.Content[j];
                            taskResultIter++;
                        }
                    }
                }
                if (taskResultIter == 0)
                {
                    printf("\nNo such pairs!\n");
                }
                else
                {
                    printf("\nPairs:\n");
                    for (int i = 0; i < taskResultIter; i++)
                    {
                        bool pairWasPrinted;
                        pairWasPrinted = false;
                        for (int j = i - 1; j >= 0; j--)
                        {
                            if (taskResult[i][0] == taskResult[j][0] &&
                                taskResult[i][1] == taskResult[j][1])
                            {
                                pairWasPrinted = true;
                            }
                        }
                        if (!pairWasPrinted)
                        {
                            printf("%d and %d;\n", taskResult[i][0],
                                   taskResult[i][1]);
                        }
                    }
                }
            }
            printf("\n");
        }

        if (operationCode == QUIT)
        {
            break;
        }
    }
    if (objArray.IsFilled)
    {
        free(objArray.Content);
        objArray.IsFilled = false;
    }
    return 0;
}
