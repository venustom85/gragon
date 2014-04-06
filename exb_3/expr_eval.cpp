/*
   数学表达式，只含 + - * / 四类运算，数字为非负整数，包含小括号。
  */
#include "common/test_string.h" 
#include <ctype.h>
#include <cstdlib>
#include <vector>
#include <stack>
using namespace std;

namespace exb_3_expr_eval {

bool g_invalid_input = false;

enum token_types
{
    U = -1, // unknown
    D = 0,  // operand
    R = 1   // operator
};

struct token
{
    token_types type;
    union {
        char op;
        int  num;
    } value;
};

void skip_space(const char * str, int & p)
{
    while (str[p] != 0 && isspace(str[p])) {
        ++p;
    }
}

int read_number(const char * str, int & p)
{
    char buf[10];
    int i = 0;
    while (i < 9 && str[p+i] != 0 && isdigit(str[p+i])) {
        buf[i] = str[p+i];
        ++i;
    }
    buf[i] = 0;
    p += i;

    return atoi(buf);
}

int read_operator(const char * str, int & p)
{
    char ch = str[p++];
    switch (ch) {
        case '+':
        case '-':
        case '*':
        case '/':
        case '(':
        case ')':
            return ch;
        default :
            return -1;
    }
}

void read_token(const char * str, int & p, token & tk)
{
    skip_space(str, p);
    if (str[p] == 0) {
        tk.type = R;
        tk.value.op = '#';
    } else if (isdigit(str[p])) {
        tk.type = D;
        tk.value.num = read_number(str, p);
    } else {
        int ch = read_operator(str, p);
        if (ch == -1) {
            tk.type = U;
        } else {
            tk.type = R;
            tk.value.op = (char)ch;
        }
    }
}

int op_index[127] = {0};

struct op_index_initializer
{
    op_index_initializer()
    {
        op_index['+'] = 0;
        op_index['-'] = 1;
        op_index['*'] = 2;
        op_index['/'] = 3;
        op_index['('] = 4;
        op_index[')'] = 5;
        op_index['#'] = 6;
    }
} _oii;

int op_table[7][7] = {
    //        +  -  *  /  (  )  #
    /* + */ { 1, 1,-1,-1,-1, 1, 1},
    /* - */ { 1, 1,-1,-1,-1, 1, 1},
    /* * */ { 1, 1, 1, 1,-1, 1, 1},
    /* / */ { 1, 1, 1, 1,-1, 1, 1},
    /* ( */ {-1,-1,-1,-1,-1, 0,-2},
    /* ) */ {-2,-2,-2,-2,-2,-2,-2},
    /* # */ {-1,-1,-1,-1,-1,-2, 0},
};

int op_compare(int c1, int c2)
{
    return op_table[op_index[c1]][op_index[c2]];
}

double expression_eval(const char * expr)
{
    vector<token> rpn;

    stack<token> op_stk;
    token start_token;
    start_token.type = R;
    start_token.value.op = '#';
    op_stk.push(start_token);

    token tk;
    int i = 0;
    read_token(expr, i, tk);
    while (!op_stk.empty()) {
        if (tk.type == D) {
            rpn.push_back(tk);
            read_token(expr, i, tk);
        } else if (tk.type == R) {
            int top = op_stk.top().value.op;
            int c = op_compare(top, tk.value.op);
            if (c == -1) {
                token t;
                t.type = R;
                t.value.op = tk.value.op;
                op_stk.push(t);
                read_token(expr, i, tk);
            } else if (c == 1) { 
                rpn.push_back(op_stk.top());
                op_stk.pop();
            } else if (c == 0) {
                op_stk.pop();
                read_token(expr, i, tk);
            } else {
                cerr << "ERROR format of expression " << expr << endl;
                return -1;
            }
        }
    }

    stack<double> e_stk;
    for (vector<token>::iterator i = rpn.begin(); i != rpn.end(); ++i) {
        if (i->type == D) {
            e_stk.push(i->value.num);
        } else {
            if (e_stk.size() < 2) {
                cerr << "ERROR format of expression " << expr << endl;
                return -1;
            }
            double a2 = e_stk.top();
            e_stk.pop();
            double a1 = e_stk.top();
            e_stk.pop();

            double b = 0;
            switch (i->value.op) {
                case '+': b = a1 + a2; break;
                case '-': b = a1 - a2; break;
                case '*': b = a1 * a2; break;
                case '/': b = a1 / a2; break;
            }
            e_stk.push(b);
        }
    }

    return e_stk.top();
}

CLASS_STRING_RUNNER;

void Runner::exec(string * obj)
{
    string * str = obj;
    cout << "expr: " << (*str) << endl;
    
    double result = expression_eval(str->c_str());
    cout << "result: " << result << endl;
}

int g_main(int argc, char ** argv)
{
    Runner r;
    return r.run(argc, argv);
}

} // namespace exb_3_expr_eval

