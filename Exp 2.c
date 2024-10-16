#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100  // Maximum size of the stack

// Stack structure definition for operators
struct Stack {
    int top;
    char items[MAX];
};

// Function to initialize the stack
void initStack(struct Stack* s) {
    s->top = -1;
}

// Function to check if the stack is empty
int isEmpty(struct Stack* s) {
    return s->top == -1;
}

// Function to check if the stack is full
int isFull(struct Stack* s) {
    return s->top == MAX - 1;
}

// Function to push an operator onto the stack
void push(struct Stack* s, char op) {
    if (isFull(s)) {
        printf("Stack overflow! Cannot push %c.\n", op);
        return;
    }
    s->items[++(s->top)] = op;
}

// Function to pop an operator from the stack
char pop(struct Stack* s) {
    if (isEmpty(s)) {
        printf("Stack underflow! Cannot pop element.\n");
        return -1;  // Error code for underflow
    }
    return s->items[(s->top)--];
}

// Function to get the top element of the stack without popping it
char peek(struct Stack* s) {
    if (isEmpty(s)) {
        return -1;  // Return -1 if stack is empty
    }
    return s->items[s->top];
}

// Function to determine precedence of operators
int precedence(char op) {
    if (op == '+' || op == '-') {
        return 1;  // Lower precedence
    } else if (op == '*' || op == '/') {
        return 2;  // Higher precedence
    }
    return 0;  // Parentheses and invalid characters
}

// Function to check if the character is an operator
int isOperator(char ch) {
    return (ch == '+' || ch == '-' || ch == '*' || ch == '/');
}

// Function to convert infix expression to postfix expression
void infixToPostfix(char* infix, char* postfix) {
    struct Stack s;
    initStack(&s);
    int i, j = 0;  // `i` for infix traversal, `j` for postfix output

    for (i = 0; infix[i] != '\0'; i++) {
        char ch = infix[i];

        // If the character is an operand, add it to the postfix output
        if (isalnum(ch)) {
            postfix[j++] = ch;
        }
        // If the character is '(', push it to the stack
        else if (ch == '(') {
            push(&s, ch);
        }
        // If the character is ')', pop until '(' is encountered
        else if (ch == ')') {
            while (!isEmpty(&s) && peek(&s) != '(') {
                postfix[j++] = pop(&s);
            }
            pop(&s);  // Remove '(' from stack
        }
        // If the character is an operator
        else if (isOperator(ch)) {
            while (!isEmpty(&s) && precedence(peek(&s)) >= precedence(ch)) {
                postfix[j++] = pop(&s);
            }
            push(&s, ch);  // Push the current operator to the stack
        }
    }

    // Pop all remaining operators in the stack
    while (!isEmpty(&s)) {
        postfix[j++] = pop(&s);
    }

    postfix[j] = '\0';  // Null-terminate the postfix expression
}

// Main function to test the algorithm
int main() {
    char infix[MAX], postfix[MAX];

    printf("Enter infix expression: ");
    scanf("%s", infix);

    infixToPostfix(infix, postfix);

    printf("Postfix expression: %s\n", postfix);

    return 0;
}
