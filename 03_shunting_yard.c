/* Alper Görünme - 2210205349 */
#include <stdio.h>
#include <ctype.h>

int derece(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

int main() {
    char infix[] = "x+y*z", stack[10];
    int top = -1;
    printf("Postfix: ");
    for (int i = 0; infix[i]; i++) {
        if (isalnum(infix[i])) printf("%c", infix[i]);
        else {
            while (top != -1 && derece(stack[top]) >= derece(infix[i])) printf("%c", stack[top--]);
            stack[++top] = infix[i];
        }
    }
    while (top != -1) printf("%c", stack[top--]);
    return 0;
}
