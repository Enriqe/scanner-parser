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
        transMatrix[17][16] = {
            {0     , 1     , 5     , ERR   , ERR   , 20    , 22    , 24    , 8    , ERR  , 16   , ERR  , 12   , ERR  , ERR  , ERR },
            {102   , 1     , ERR   , 3     , ERR   , ERR   , ERR   , 102   , ERR  , ERR  , ERR  , ERR  , ERR  , ERR  , ERR  , ERR },
            {104   , 3     , ERR   , ERR   , ERR   , ERR   , ERR   , 104   , ERR  , ERR  , ERR  , ERR  , ERR  , ERR  , ERR  , ERR },
            {ERR   , ERR   , ERR   , ERR   , 6     , ERR   , ERR   , ERR   , 6    , 6    , 6    , 6    , 6    , 6    , 6    , 6   },
            {107   , 6     , ERR   , ERR   , 6     , ERR   , ERR   , 107   , 6    , 6    , 6    , 6    , 6    , 6    , 6    , 6   },
            {ERR   , ERR   , ERR   , ERR   , ERR   , ERR   , ERR   , ERR   , ERR  , 9    , ERR  , ERR  , ERR  , ERR  , ERR  , ERR },
            {ERR   , ERR   , ERR   , ERR   , ERR   , ERR   , ERR   , ERR   , ERR  , ERR  , 10   , 10   , ERR  , ERR  , ERR  , ERR },
            {111   , ERR   , ERR   , ERR   , ERR   , ERR   , ERR   , 111   , ERR  , ERR  , ERR  , ERR  , ERR  , ERR  , ERR  , ERR },
            {ERR   , ERR   , ERR   , ERR   , ERR   , ERR   , ERR   , ERR   , ERR  , ERR  , ERR  , ERR  , ERR  , 13   , ERR  , ERR },
            {ERR   , ERR   , ERR   , ERR   , ERR   , ERR   , ERR   , ERR   , ERR  , ERR  , ERR  , ERR  , ERR  , ERR  , 14   , ERR },
            {115   , ERR   , ERR   , ERR   , ERR   , 115   , ERR   , 115   , ERR  , ERR  , ERR  , ERR  , ERR  , ERR  , ERR  , ERR },
            {ERR   , ERR   , ERR   , ERR   , ERR   , ERR   , ERR   , ERR   , ERR  , 17   , ERR  , ERR  , ERR  , ERR  , ERR  , ERR },
            {ERR   , ERR   , ERR   , ERR   , ERR   , ERR   , ERR   , ERR   , ERR  , ERR  , ERR  , ERR  , ERR  , ERR  , ERR  , 18  },
            {119   , ERR   , ERR   , ERR   , ERR   , 119   , ERR   , ERR   , ERR  , ERR  , ERR  , ERR  , ERR  , ERR  , ERR  , ERR },
            {121   , 121   , 121   , ERR   , ERR   , 121   , 121   , 121   , 121  , ERR  , 121  , ERR  , 121  , ERR  , ERR  , ERR },
            {123   , ERR   , ERR   , ERR   , ERR   , ERR   , ERR   , 123   , ERR  , ERR  , ERR  , ERR  , ERR  , ERR  , ERR  , ERR },
            {125   , 125   , 125   , ERR   , ERR   , 125   , 125   , ERR   , 125  , ERR  , ERR  , ERR  , 125  , ERR  , ERR  , ERR }
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
            case '.':
                return 3;
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
                return 4;
            case '(':
                return 5;
            case ')';
                return 6;
            case ',';
                return 7;
            case 'S'
                return 8;
            case 'U'
                return 9;
            case 'M'
                return 10;
            case 'B'
                return 11;
            case 'D'
                return 12;
            case 'I'
                return 13;
            case 'V'
                return 14;
            case 'L'
                return 15;
            default:
                /*
                 * Illegal character.
                 */
                 return 16;
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