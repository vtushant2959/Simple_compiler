#include <iostream>
#include <cctype>
#include <vector>

using namespace std;

// Token types
enum TokenType { NUMBER, OPERATOR, END };

struct Token {
    TokenType type;
    double value;  // Stores numbers
    char op;       // Stores operators
};

// Function to tokenize input
vector<Token> tokenize(const string &input) {
    vector<Token> tokens;
    size_t i = 0;
    
    while (i < input.length()) {
        if (isdigit(input[i])) {  // If number
            double num = 0;
            while (i < input.length() && isdigit(input[i])) {
                num = num * 10 + (input[i] - '0');
                i++;
            }
            tokens.push_back({NUMBER, num, '\0'}); // Add number token
        } else if (input[i] == '+' || input[i] == '-' || input[i] == '*' || input[i] == '/') { 
            tokens.push_back({OPERATOR, 0, input[i]}); // Add operator token
            i++;
        } else {
            i++; // Ignore spaces
        }
    }
    
    tokens.push_back({END, 0, '\0'}); // End token
    return tokens;
}

// Parsing and evaluation
class Parser {
private:
    vector<Token> tokens;
    size_t pos = 0;

    Token getNextToken() {
        return tokens[pos++];
    }

    double factor() {  // Handles numbers
        Token token = getNextToken();
        return token.value;
    }

    double term() {  // Handles multiplication and division
        double result = factor();
        while (tokens[pos].type == OPERATOR && (tokens[pos].op == '*' || tokens[pos].op == '/')) {
            Token token = getNextToken();
            if (token.op == '*') result *= factor();
            else result /= factor();
        }
        return result;
    }

    double expression() {  // Handles addition and subtraction
        double result = term();
        while (tokens[pos].type == OPERATOR && (tokens[pos].op == '+' || tokens[pos].op == '-')) {
            Token token = getNextToken();
            if (token.op == '+') result += term();
            else result -= term();
        }
        return result;
    }

public:
    Parser(vector<Token> tok) : tokens(tok) {}

    double parse() {
        return expression();
    }
};

// Main function
int main() {
    string input;
    cout << "Enter an expression: ";
    getline(cin, input);  // Read user input
    
    vector<Token> tokens = tokenize(input);  // Tokenize input
    Parser parser(tokens);  // Parse the tokens
    
    cout << "Result: " << parser.parse() << endl;  // Output result
    
    return 0;
}

