#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define size 80

enum {nocomments, openedcomment, closedcomment};
char openedbrackets[] = {"({[\0"};
char closedbrackets[] = {")}]\0"};

int InArray(char* arr, char arg){
    int res = -1;
    for (int i = 0; arr[i] != '\0'; ++i){
        if (arg == arr[i]){
            res = i;
            break;
        }
    }
    return res;
}
struct stack{
    char data[size];
    int stacksize;
};

struct stack bracketstack;

void push(struct stack* astack, char arg){
    astack->data[astack->stacksize] = arg;
    astack->stacksize++;
}

void pop(struct stack* astack){
    astack->data[astack->stacksize] = 0;
    astack->stacksize--;
}

char peek(struct stack* astack){
    return (astack->data[astack->stacksize - 1]);
}

bool checkbrackets(char* astr){
    bool res = 1;
    for (int i = 0; astr[i] != '\0'; ++i){
        if (InArray(openedbrackets,astr[i]) != -1) push(&bracketstack, astr[i]);
        else if (InArray(closedbrackets,astr[i]) != -1){
            if (InArray(closedbrackets,astr[i]) == InArray(openedbrackets,peek(&bracketstack))) pop(&bracketstack);
            else res = 0;
        }
    }
    return res;
}

int checkcomments(char* astr){
    int res = nocomments;
    for (int i = 0; astr[i] != '\0'; ++i){
        if ((astr[i] == '/') && (astr[i+1] == '*')){
            res = openedcomment;
            astr[i] = '(';
            astr[i+1] = '(';
        }
        if ((astr[i] == '*') && (astr[i+1] == '/')){
            if (res == openedcomment) res = nocomments; else res = closedcomment;
            astr[i] = ')';
            astr[i+1] = ')';
        }
    }
    return res;
};

bool checkescapesequence(char* astr){
    bool res = true;
    for (int i = 0; astr[i] != '\0'; ++i){
        if (astr[i] == '\\') {
            switch (astr[i + 1]) {
                case 'a':;
                case 'b':;
                case 'f':;
                case 'n':;
                case 'r':;
                case 't':;
                case 'v':;
                case '\'':;
                case '"':;
                case '?': break;
                default:
                    return false;
            }
        }
    }
    return res;
}

int main(){
    char* s = malloc(size*sizeof(char));
    FILE *f = fopen("input.txt","r");
    int commentscnt = 0;

    for (int i  = 1; !feof(f); ++i) {
        fgets(s,size,f);
        bool res = checkbrackets(s);
        printf(res ? "" : "Error: line %d brackets disbalance \n",i);
        res = checkescapesequence(s);
        printf(res ? "" : "Error: line %d unknown escape sequence \n",i);
        switch (checkcomments(s)){
            case 1: commentscnt = 1; break;
            case 2: commentscnt -= 1; break;
            default: break;
        }
    }
    printf(commentscnt ? "Error: comments disbalance \n" : "");
    fclose(f);
    return 0;
}