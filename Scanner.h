#include "Token.h"
#include <stringstream>

class Scanner{
private:
    int ERROR = 9999;
    int transMatrix[][];
    vector<Token> tokens;
    enum Type {
        INTEGER,
        DOUBLE,
        VARIABLE,
        PARAM_SEPARATOR,
        PARENTHESIS,
        FUNCTION,
        EOI
    };
public:
    Scanner(){
        transMatrix[6][7] = {
            {0, 1, 2, 4, 5, ERROR, ERROR},
            {100, 1, ERROR, 100, 100, ERROR, ERROR},
            {ERROR, ERROR, ERROR, ERROR, ERROR, 3, ERROR},
            {101, 3, -1, 101, 101, 3, ERROR},
            {102, 102, 102, 102, 102, 102, ERROR},
            {103, 103, 103, 103, ERROR, ERROR, ERROR}
        };
    }

    int filterChar(char c){
        switch(c){
                        case ' ':
            case '\t':
                return 0;
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
                return 1;
            case '$':
                return 2;
            case '(':
            case ')':
                return 3;
            case '+':
            case '-':
            case '*':
            case '/':
                return 4;
            case 'a':
            case 'b':
            case 'c':
            case 'd':
            case 'e':
            case 'f':
            case 'g':
            case 'h':
            case 'i':
            case 'j':
            case 'k':
            case 'l':
            case 'm':
            case 'n':
            case 'o':
            case 'p':
            case 'q':
            case 'r':
            case 's':
            case 't':
            case 'u':
            case 'v':
            case 'w':
            case 'x':
            case 'y':
            case 'z':
            case 'A':
            case 'B':
            case 'C':
            case 'D':
            case 'E':
            case 'F':
            case 'G':
            case 'H':
            case 'I':
            case 'J':
            case 'K':
            case 'L':
            case 'M':
            case 'N':
            case 'O':
            case 'P':
            case 'Q':
            case 'R':
            case 'S':
            case 'T':
            case 'U':
            case 'V':
            case 'W':
            case 'X':
            case 'Y':
            case 'Z':
                return 5;
            default:
                /*
                 * Illigal character.
                 */
                return 6;
        }
    }

    vector<Token> getTokens() {
        return tokens;
    }

    bool scan(string str){
        char c;
        int state, index;
        stringstream value;
        state = 0;
        index = 0;
        str = str + " ";
        while(index < str.length()){
            do{
                c = str[index++];
                state = transMatrix[state][filterChar(c)];
                if(state > 0 && state < 100){
                    value << c;
                }
            } while(index < str.length() && state < 100);

            switch(state) {
                case 0:
                    return true;
                case 9999:
                    value << c;
                    cout << "LEXICAL ERROR: the string " << value.str() << " is not a valid elem in the language.";
                    return false;
                case 100: //todo: import type n update transMatrix
                    tokens.push_back(Token(Type.INTEGER), value.str());
                    break;
                case 101:
                    tokens.push_back(Token(Type.DOUBLE), value.str());
                    break;
                case 102:
                    tokens.push_back(Token(Type.VARIABLE), value.str());
                    break;
                case 103:
                    tokens.push_back(Token(Type.PARAM_SEPARATOR), value.str());
                    break;
                case 104:
                    tokens.push_back(Token(Type.PARENTHESIS), value.str());
                    break;
                case 105:
                    tokens.push_back(Token(Type.FUNCTION), value.str());
                    break;
                case 106:
                    tokens.push_back(Token(Type.EOI), value.str());
                    break;
            }
            index--;
            state = 0;
        }
        return true;
    }

};