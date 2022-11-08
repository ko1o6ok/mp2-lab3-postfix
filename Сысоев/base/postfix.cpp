#include "postfix.h"
#include <stdexcept>
using namespace std;
string TPostfix::ToPostfix()
{
    stack<char> my_stack;
  postfix = string("");
  bool PREV_WAS_A_NUMBER = false;
  string add_num;
    for (int i = 0;i<infix.length();i++) {
        char symbol = infix[i];
        switch (symbol) {
            case '0':
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':
            {
                add_num.push_back(symbol);
                PREV_WAS_A_NUMBER = true;
                if(i==infix.length()-1){
                    for (char& c:add_num) {
                        postfix.push_back(c);
                    }
                    postfix.push_back(' ');
                }
                //postfix.push_back(symbol);
                break;
            }
            case '(':
            {
                if(PREV_WAS_A_NUMBER){
                    for (char& c:add_num) {
                        postfix.push_back(c);
                    }
                    postfix.push_back(' ');
                    PREV_WAS_A_NUMBER = false;
                    add_num = "";
                }

                my_stack.push(symbol);
                break;
            }
            case ')':
            {
                if(PREV_WAS_A_NUMBER){
                    for (char& c:add_num) {
                        postfix.push_back(c);
                    }
                    postfix.push_back(' ');
                    PREV_WAS_A_NUMBER = false;
                    add_num = "";
                }
                while(!(my_stack.empty())&&(my_stack.top() != '(')){
                    postfix.push_back(my_stack.top());
                    //postfix.push_back(' ');
                    my_stack.pop();
                }
                my_stack.pop();
                break;
            }
            case '+':
            case '-':
            case '*':
            case '/':{
                if(PREV_WAS_A_NUMBER){
                    for (char& c:add_num) {
                        postfix.push_back(c);
                    }
                    postfix.push_back(' ');
                    PREV_WAS_A_NUMBER = false;
                    add_num = "";
                }
                if(!my_stack.empty())
                    while (!my_stack.empty()&&(Priority(my_stack.top()) >= Priority(symbol))) {
                        postfix.push_back(my_stack.top());

                        my_stack.pop();
                    }
                my_stack.push(symbol);break;}
            default:
                throw invalid_argument("I don't know this symbol!");
        }
    }
    while (!my_stack.empty()){
        postfix.push_back(my_stack.top());
        my_stack.pop();
        // ADDED
        unsigned long long l =  postfix.length();
        char c = postfix[l-1];
        int s = c - '0';
        if((c==postfix[l-4])&&((s>=10)||(s<0)))
            throw invalid_argument("Doubles are not allowed!");
    }
    return postfix;
}

double TPostfix::Calculate()
{
  string s = ToPostfix();
  stack<double> my_stack;
  int n_add = 0;
    for (char c:s) {
        switch (c) {
            case ' ':{
                my_stack.push(n_add);
                n_add = 0;
                break;
            }
            case '0':
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':{
                int ic = c-'0';
                n_add *= 10;
                n_add += ic;
                break;
            }
            case '+':{
                double a = my_stack.top();
                my_stack.pop();
                double b = my_stack.top();
                my_stack.pop();
                my_stack.push(a+b);
                break;
            }
            case '-':{
                double a = my_stack.top();
                my_stack.pop();
                double b = my_stack.top();
                my_stack.pop();
                my_stack.push(b-a);
                break;
            }
            case '*':{
                double a = my_stack.top();
                my_stack.pop();
                double b = my_stack.top();
                my_stack.pop();
                my_stack.push(a*b);
                break;
            }
            case '/':{
                double a = my_stack.top();
                my_stack.pop();
                double b = my_stack.top();
                my_stack.pop();
                if(a == 0)
                    throw invalid_argument("You are trying to divide by zero");
                my_stack.push(b/a);
                break;
            }
        }
    }
    return my_stack.top();
}

short TPostfix::Priority(char operation) {
    switch (operation) {
        case '(':
            return 0;
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
        default:
            return -1;
    }
}
