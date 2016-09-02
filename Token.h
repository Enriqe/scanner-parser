#include <string>
#include <boost/algorithm/string.hpp> //case insensitive comparison
#include <sstream>

class Token {
private:
    enum Type {
        INTEGER,
        DOUBLE,
        VARIABLE,
        PARAM_SEPARATOR,
        PARENTHESIS,
        FUNCTION,
        EOI
    };

    Type type;
    string value;

public: 
    Token(Type t, string val){
        type = t;
        value = val;
    }

    Type getType(){
        return type;
    }

    string getValue(){
        return value;
    }

    bool equalsToken(Token token){
        if(token.value.length() > 0){
            return (type == token.type && boost::iequals(value, token.value));
        }else{
            return (type == token.type);
        }
    }

    string toString() {
        stingstream ss;
        string ans;
        ss << "<" << type << "," << value << ">";
        return ans;
    }


}