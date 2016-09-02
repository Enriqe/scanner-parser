#include "Token.h"
#include <stdlib.h> //exit

class Parser {
public:
    parser(){

    }

    void parse(vector<Token> tokens) {
        parseF(tokens);
        cout << "The input is a well formed expression."  << endl;
    }

    bool match(vector<Token> tokens, Token expectedToken){
        if(!tokens.empty() && tokens[0].equalsToken(expectedToken)){
            //todo: check if .erase is best aproach
            tokens[0].erase;
            return true;
        }else{
            if(tokens.empty()){
                cout << "ERROR: Expecting" << expectedToken.getValue() << "; found nothing." << endl;
            } else{
                cout << "ERROR: Expecting" << expectedToken.getValue() << "; found " << tokens[0].getValue() << endl;
            }
            cout << "System will stop." << endl;
            exit(EXIT_FAILURE);
        }
        return false;
    }

    void parseF(vector<Token> tokens){
        switch(tokens[0].getType()) {
            case PARENTHESIS:
                match(tokens, Token(Type.PARENTHESIS, "("));
                match(tokens, Token(Type.OPERATOR, ""));
                parseF(tokens);
                parseF(tokens);
                match(tokens, Token(Type.PARENTHESIS, ")"));
                break;
            case INTEGER:
                match(tokens, Token(Type.INTEGER, ""));
                break;
            case DOUBLE:
                match(tokens, Token(Type.DOUBLE, ""));
                break;
            case VARIABLE:
                match(tokens, Token(Type.VARIABLE, ""));
                break;
            case PARAM_SEPARAT0R:
                match(tokens, Token(Type.PARAM_SEPARAT0R, ""));
                break;
            case EOI:
                match(tokens, Token(Type.EOI, ""));
                break;
            case FUNCTION:
                match(tokens, Token(Type.FUNCTION, ""));
                break;
            default:
                cout << "ERROR: UNEXPECTED: " << tokens[0] << endl;
                cout << "System will stop." << endl;
                exit(EXIT_FAILURE);
        }
    }


}