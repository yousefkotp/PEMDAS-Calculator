#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*
* Item: An item that is being pushed to or popped from the stack
* It may be float (to be used while evaluating the postfix)
* It may be char (to be used while converting infix to postfix)
*/
typedef union
{
    float fData;
    char  cData;
} Item;
/*
*
*/
typedef struct
{
    Item Item[50];
    int top;
} Stack;
/*
*
*/
Stack * initialize()
{
    Stack* s=malloc(sizeof(Stack));
    s->top = 0;
    return s;
}
/*
*
*/
int isEmpty(Stack *s)
{
    return s->top ==0 ? 1:0;
}
/*
*
*/
Item top(Stack *s)
{
    return s->Item[s->top -1];
}
/*
*
*/
Item pop(Stack *s)
{
    if(isEmpty(s) == 1){
        printf("popping failed, stack is empty\n");
        exit(0);
    }

    else{
        s->top--;
        return s->Item[s->top];
    }
}
/*
*
*/
void push(Stack *s, Item val)
{
    s->Item[s->top].fData = val.fData;
    s->Item[s->top].cData = val.cData;
    s->top++;
}



/*
* infixToPostfix: converts an expression in infix notation to
* to a postfix notation (Reverse-Polish Notation)
* ASSUME single-digit operands
* ASSUME ^*+-/ operators
* e.g., 22 + 31 --> 22 31 +
* e.g., ( 2 + 3 ) * 4 --> 2 3 + 4 *
*/

int priority(char c){
    switch(c)
    {
    case'(':
    case ')':
        return 2;
        break;
    case '*':
    case '/':
        return 1;
        break;
    case '+':
    case '-':
        return 0;
        break;
    }
}

void infixToPostfix(char* infix, char* postfix)
{
    Item f;
    Stack* s= initialize();
    char copyy[256];
    strcpy(copyy,infix);
    char temp[2]="\0";
    char temp2[2]="\0";
    char temp3[2]="\0";
    char str[2];
    char ch;
    char* token =strtok(copyy," ");

    while(token != NULL)
    {
        if(atof(token))
        {
            strcat(postfix,token);
            strcat(postfix," ");
        }


        else if (strcmp(token,")")==0)
        {
            while(top(s).cData != '(' && !isEmpty(s))
            {
                temp[0] = pop(s).cData;
                strcat(postfix,temp);
                strcat(postfix," ");
            }
        }
        else if(strcmp(token,"+")==0 || strcmp(token,"-")==0 ||strcmp(token,"*")==0 ||strcmp(token,"/")==0 )
        {

            strcpy(temp,token);
            f.cData =temp[0];
            if(isEmpty(s))
            {
                push(s,f);
            }
            else
            {
                while(priority(temp[0])<= priority(top(s).cData))
                {
                temp2[0] = pop(s).cData;
                strcat(postfix,temp2);
                strcat(postfix," ");

                }
                push(s,f);

            }

        }
        token=strtok(NULL," ");
    }
        while(!isEmpty(s))
        {
            temp3[0] = pop(s).cData;
            strcat(postfix,temp3);
            strcat(postfix," ");

        }
}

/*
* evaluatePostfix: Evaluates an expression in postfix notation
* (Reverse-Polish Notation)
*/

float evaluate(char x,float a,float b){
    if(x=='+')
        return a+b;
    if(x=='-')
        return a-b;
    if(x=='*')
        return a*b;
    if(x=='/')
        return a/b;
}

float evaluatePostfix(char* postfix)
{
    char copyy[256];
    strcpy(copyy,postfix);
    Stack* s=initialize();
    char* token = strtok(copyy," ");
    Item f;
    float a,b,result;
    while(token !=NULL)
    {
        if(atof(token))
        {
            f.fData = atof(token);
            push(s,f);
        }
        if(strcmp(token,"+") == 0 || strcmp(token,"-") == 0 || strcmp(token,"*") == 0 || strcmp(token,"/") == 0)
        {
            b=pop(s).fData;
            a=pop(s).fData;
            f.fData = evaluate(token[0],a,b);
            push(s,f);
        }



        token = strtok(NULL," ");
    }
    result = pop(s).fData;
    return result;
}

void replaceNewLineBySpace(char *s)
{
    char *s1 = s;
    while((s1 = strstr(s1, "\n")) != NULL)
        *s1 = ' ';
}


int main()
{
    char infixExpr[256] = "";
    char postfixExpr[256] = "";
    printf("Enter an expression you want to evaluate or Ctrl+Z to exit: ");
    while(fgets(infixExpr, 255, stdin) != NULL)
    {
        replaceNewLineBySpace(infixExpr);
        infixToPostfix(infixExpr, postfixExpr);
        printf("Postfix : %s\n", postfixExpr);
        float result = evaluatePostfix(postfixExpr);
        printf("Result: %.3f\n\n", result);
        printf("Enter an expression you want to evaluate or Ctrl+Z to exit: ");
    }
    return 0;
}





