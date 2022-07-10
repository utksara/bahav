#include "parser.cpp"

int main(){
    string test1 = "a*b + c";
    string test2 = "a*(b + c)";
    string test3 = "a * (b + c)";
    string test4 = "(a +b )* (b + c)";

    lexer(test1);
    lexer(test2);
    lexer(test3);
    lexer(test4);

    return 0;
}