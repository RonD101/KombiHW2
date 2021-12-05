#include "tokens.hpp"
#include <stdio.h>
#include <string>
#include <cstring>
#include <iostream>

using std::string;

void showToken(const char* name, string lex = yytext) {
    std::cout << yylineno << " " << name << " " << lex << std::endl;
}

bool is_valid_hexa(char first, char second) {
    return first >= 48 && first <= 55 && isxdigit(second);
}

bool is_odd_number_of_slash(const char* str) {
    int cnt = 0;
    for(int i = strlen(str) - 2; i >= 1; i--) {
        if(str[i] == '\\')
            cnt++;
        else
            break;
    }
    return ((cnt % 2) == 1);
}

static string analyze_string(const char* str) {
    int len = strlen(str);
    string new_str;
    if (is_odd_number_of_slash(str)) {
        printf("Error unclosed string\n");
        exit(0);
    }

    for (int i = 1; i < len - 1; i++) {
        if (str[i] == '\\') {
            if (str[i+1] == '\\')
                new_str.push_back('\\');
            else if (str[i+1] == '"')
                new_str.push_back('"');
            else if (str[i+1] == 'n')
                new_str.push_back('\n');
            else if (str[i+1] == 'r')
                new_str.push_back('\r');
            else if (str[i+1] == 't')
                new_str.push_back('\t');
            else if (str[i+1] == '0')
                new_str.push_back('\0');
            else if (str[i+1] == 'x') {
                if (i < len - 4) { // i+4 == len -1
                    if (is_valid_hexa(str[i + 2], str[i + 3])) {
                        char a = tolower(str[i + 2]);
                        char b = tolower(str[i + 3]);
                        int a_digit_value = a >= 'a' ? (a - 'a' + 10) : a - '0';
                        int b_digit_value = b >= 'a' ? (b - 'a' + 10) : b - '0';
                        int value = a_digit_value * 0x10 + b_digit_value;
                        new_str.push_back(value);
                        i += 2;
                    }
                    else {
                        printf("Error undefined escape sequence x%c%c\n", str[i + 2], str[i + 3]);
                        exit(0);
                    }
                } else {
                    printf("Error undefined escape sequence x");
                    if (i == len - 4)
                        printf("%c", str[i+2]);
                    printf("\n");
                    exit(0);
                }
            } else {
                printf("Error undefined escape sequence %c\n", str[i + 1]);
                exit(0);
            }
            i++;
        }
        else
            new_str.push_back(str[i]);
    }
    return new_str;
}

int main() {
	int token;
	while ((token = yylex())) {
      if (token == VOID)
          showToken("VOID");
      else if (token == INT)
          showToken("INT");
      else if (token == BYTE)
          showToken("BYTE");
      else if (token == B)
          showToken("B");
      else if (token == BOOL)
          showToken("BOOL");
      else if (token == AND)
          showToken("AND");
      else if (token == OR)
          showToken("OR");
      else if (token == NOT)
          showToken("NOT");
      else if (token == TRUE)
          showToken("TRUE");
      else if (token == FALSE)
          showToken("FALSE");
      else if (token == RETURN)
          showToken("RETURN");
      else if (token == IF)
          showToken("IF");
      else if (token == ELSE)
          showToken("ELSE");
      else if (token == WHILE)
          showToken("WHILE");
      else if (token == BREAK)
          showToken("BREAK");
      else if (token == CONTINUE)
          showToken("CONTINUE");
      else if (token == SC)
          showToken("SC");
      else if (token == COMMA)
          showToken("COMMA");
      else if (token == LPAREN)
          showToken("LPAREN");
      else if (token == RPAREN)
          showToken("RPAREN");
      else if (token == LBRACE)
          showToken("LBRACE");
      else if (token == RBRACE)
          showToken("RBRACE");
      else if (token == ASSIGN)
          showToken("ASSIGN");
      else if (token == RELOP)
          showToken("RELOP");
      else if (token == ID)
          showToken("ID");
      else if (token == BINOP)
          showToken("BINOP");
      else if (token == NUM)
          showToken("NUM");
      else if (token == STRING)
          showToken("STRING", analyze_string(yytext));
      else if (token == COMMENT)
          showToken("COMMENT", "//");
      else if (token == UNCLOSED){
          printf("Error unclosed string\n");
          exit(0);
      }
      else if (token == UNDEF){
          printf("Error %c\n", *yytext);
          exit(0);
      }
	}
	return 0;
}
