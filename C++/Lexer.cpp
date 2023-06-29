///VERY SIMPLE IMPLEMENTATION

#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <vector>
#include <string>
#include <cstring>
#include <fstream>

//Enumerators for the Token [negatives are tokens, 0 -> 255 are correpsonding ascii characters]
enum Token {
    // Special Symbols:
    Tok_ss_Parenthesis = -1,
    Tok_ss_Braces = -2,
    Tok_ss_Comma = -3,
    Tok_ss_Semicolon = -4,

    // Operators:
    Tok_op_Arithmetic = -5,
    Tok_op_Relational = -6,
    Tok_op_Logical = -7,
    Tok_op_assign = -8,

    //Management:
    Tok_man_EOF = -9,
    Tok_man_Identifier = -10,
    Tok_man_Number = -11,

    //Reserved Words:
    Tok_res_Def = -12,
    Tok_res_Return = -13,
};

//Scans the source file, and returns a buffer as a vector.
std::vector<char> Scanner() {
    //fstream
    std::ifstream fin("main.turbo");
    std::ofstream fout("main.out");

    //Go through the src file and scan
    char in_char; //The character being inputted
    std::vector<char> buffer; //Character buffer as a vertex, in which the lexer can peak at upcoming characters

    while (fin.get(in_char)) {
        buffer.push_back(in_char);
    }

    // for (int i = 0; i < buffer.size(); ++i) {
    //     int ascii_val = buffer[i];
    //     fout << buffer[i] <<  "(" << ascii_val << ")" << std::endl;
    // }

    // std::cout << "There are " << buffer.size() << " elements in the buffer" << std::endl;
    return buffer;
}
//TODO: VALIDATE ANALYZER:

/* Psuedocode:

    Analyzer(buffer, prev_tokens, prev_pos):
        Create tokens = prev_tokens
        Create pos = prev_pos

        Create lastChar <-- Character that was just peaked and consumed
        Create token_string <--String to be checked for token

        If (Nothing is present or at the end of the buffer):
            add a EOF token
            return the vector

        otherwise:
            Skip whitespaces

            Check for Identifiers and reserved words

            Check for Numbers

            Ignore comments

            Recurse Case --> Analyze(buffer, tokens, pos) <-- Call will check if the end is reached and will update tokens
*/


//Analyzes the character vector from the Scanner
std::vector<int> Analyzer(std::vector<char> buffer, std::vector<int> prev_tokens, int prev_pos) {
    std::cout << prev_pos << std::endl;

    std::vector<int> tokens = prev_tokens;
    int pos = prev_pos;

    char lastChar = ' ';
    std::string token_string; 
    double num_double_val;

    //Base Case: Either there are no elements in the buffer, or the end of the buffer has been reached:
    if (buffer.size() == 0 || prev_pos >= buffer.size() - 1) {
        std::cout << std::endl << "..Lexing Complete!" << std::endl;
        tokens.push_back(Tok_man_EOF);
        return tokens;
    }

    //Skip whitespaces
    while (isspace(lastChar)) {
        lastChar = buffer[pos++];
    }

    //Checking for comments
    if (lastChar == '/') {
        token_string = lastChar;
        token_string += buffer[pos++];
        std::cout << "Comment?: " << token_string << std::endl;
        if (token_string == "//") { //Peaks at next character to deduce
            std::cout << "Comment detected" << std::endl;
            //Comment till the end of the line
            do {
                pos++;
                lastChar = buffer[pos];
            } while (lastChar != EOF && lastChar != '\n' && lastChar != '\r');

            if (lastChar != EOF) {
                return Analyzer(buffer, tokens, pos);
            }
        }
    }

    //Checks for identifiers and reserved words
    if (isalpha(lastChar)) {
        token_string = lastChar;
        std::cout << "Token String Being Generated" << std::endl;
        while (isalnum(lastChar = buffer[pos++])) {
            token_string += lastChar;
        }

        std::cout << "Possible Token: " << token_string << std::endl << std::endl;
        //Check for reserved words:
        if (token_string == "def")
            tokens.push_back(Tok_res_Def);

        else if (token_string == "return")
            tokens.push_back(Tok_res_Return);
        //.... Keep adding for more reserved words

        //If not matching any of the above reserved words, it must be an identifier.
        else 
            tokens.push_back(Tok_man_Identifier);

        return Analyzer(buffer, tokens, pos);
    }

    //Checking for numbers
    if (isdigit(lastChar) || lastChar == '.') {
        std::string num_str_val;

        do {
            num_str_val += lastChar;
            lastChar = buffer[pos++];
        } while (isdigit(lastChar) || lastChar == '.');

        num_double_val = strtod(num_str_val.c_str(), 0);
        std::cout << "Possible Token: " << num_double_val << std::endl;
        tokens.push_back(Tok_man_Number);

        return Analyzer(buffer, tokens, pos);
    }

    

    if(lastChar == EOF) {
        tokens.push_back(Tok_man_EOF);
        return tokens;
    }

    return Analyzer(buffer, tokens, pos);
}

int main() {
    std::vector<int> blank_tokens;
    auto t = Analyzer(Scanner(), blank_tokens, 0);

    if (t[0] == 255) {
        std::cout << "something went wrong" << std::endl;
    }    
    std::cout << "Number of tokens in the vector: " << t.size() << std::endl;

    for (int i = 0; i < t.size(); ++i) {
        std::cout << "Token type: " << t[i] << std::endl;
    }

    return 0;
}
