#include <iostream>
#include <stdlib.h> //exit
#include "Parser.h"
#include "Token.h"
#include "Scanner.h"


using namespace std;

int main(){
    string str;
    Scanner scanner;
    Parser parser;
    vector<Token> tokens;
    str = "(  *  (+ 2 (* $a 10)) 3)";
    cout << str << endl;
    if(!scanner.scan(string)){
        exit(EXIT_FAILURE);
    }
    tokens = scanner.getTokens();
    for(Token t : tokens) {
        cout << t << endl;
    }
    parser.parse(tokens);
}