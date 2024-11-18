%option noyywrap

%{
    #include <stdbool.h>
    #include <math.h>

    #define MAX_STACK_SIZE 100

    typedef struct {
        int top;
        int array[MAX_STACK_SIZE];
    } Stack;

    /*****************************************/
    /************ STACK FUNCTIONS ************/
    /*****************************************/
    void initStack(Stack* stack) {
        stack->top = -1;
    }

    int isEmpty(Stack* stack) {
        return stack->top == -1;
    }

    int isFull(Stack* stack) {
        return stack->top == MAX_STACK_SIZE - 1;
    }

    int push(Stack* stack, int number) {
        if (isFull(stack)) {
            return 0;
        }

        stack->top++;
        stack->array[stack->top] = number;
        return 1;
    }

    int pop(Stack* stack, int *number) {
        if (isEmpty(stack)) {
            return 0;
        }

        *number = stack->array[stack->top];
        stack->top--;
        return 1;
    }

    /******************************************/
    /******** INPUT HANDLING FUNCTIONS ********/
    /******************************************/
    int wasErrorPrinted = 0;

    void printError(const char* message) {
        if (!wasErrorPrinted) {
            printf("Error: %s\n", message);
            wasErrorPrinted = 1;
        }
    }

    void handleNumber(Stack* stack, const char* yytext) {
        int value = atoi(yytext);
        if (!push(stack, value)) {
            printError("Stack overflow");
        }
    }

    void handleOperator(Stack* stack, char operator) {
        int b, a, result;
        if (!pop(stack, &b) || !pop(stack, &a)) {
            printError("Too few numbers");
            return;
        }

        switch (operator) {
            case '+': result = a + b; break;
            case '-': result = a - b; break;
            case '*': result = a * b; break;
            case '/':
                if (b == 0) {
                    printError("Division by 0");
                    return;
                }
                result = a / b;
                break;
            case '^': result = pow(a, b); break;
            case '%':
                if (b == 0) {
                    printError("Division by 0 in modulo");
                    return;
                }
                result = a % b;
                break;
            default:
                printError("Unrecognized operator");
                return;
        }

        if (!push(stack, result)) {
            printError("Stack overflow");
        }
    }

    void handleInvalidSymbol(const char* yytext) {
        char errorMessage[50];
        snprintf(errorMessage, 50, "Invalid symbol \"%s\"", yytext);
        printError(errorMessage);
    }

    void handleEndOfLine(Stack* stack) {
        int result;
        if (!wasErrorPrinted && stack->top == 0 && pop(stack, &result)) {
            printf("= %d\n", result);
        } else if (stack->top > 0) {
            printError("Too few operators");
        } else {
            printError("Too few numbers");
        }

        wasErrorPrinted = 0;
        initStack(stack);
    }

    Stack stack;
%}

%%

-?[0-9]+                      { handleNumber(&stack, yytext); }
[\+\-\*/\^\%]                 { handleOperator(&stack, yytext[0]); }
[[:blank:]]+                  {}
\n                            { handleEndOfLine(&stack); }
.                             { handleInvalidSymbol(yytext); }

%%

int main() {
    initStack(&stack);

    printf("Please enter equations(one per line):\n");
    yylex();
}
