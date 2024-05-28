# Compilers Assignment 2

### Task 1
- Navigate to task_1_Lexical_Analysis
- Place the file to be tested in this folder
- Run -> lex BTC24ETH.l
- Run -> cc lex.yy.c
- Run -> ./a.out < <your_file_name>
- Get the output in terminal

### Task 2
- Navigate to task_2_Syntax_Analysis
- Place the file to be tested in this folder
- Run -> lex BTC24ETH.l
- Run -> bison -d --yacc BTC24ETH.y
- Run -> cc y.tab.c
- Run -> ./a.out < <your_file_name>
- Get the output in terminal

### Task 3
- Navigate to task_3
- Place the file to be tested in this folder
- Run -> yacc -d parser.y
- Run -> lex lexer.l
- Run -> gcc y.tab.c lex.yy.c -ll
- Run -> ./a.out <your_file_name>
- Run -> python3 draw.py
- Get the output in terminal and in .ps file

### Task 4
- Navigate to task_4
- Place the file to be tested in this folder
- Run -> yacc -d parser.y
- Run -> lex lexer.l
- Run -> gcc y.tab.c lex.yy.c -ll
- Run -> ./a.out <your_file_name>
- Get the output in terminal

### Task 5
- Navigate to task_5
- Place the file to be tested in this folder
- Run -> yacc -d parser.y
- Run -> lex lexer.l
- Run -> gcc y.tab.c lex.yy.c -ll
- Run -> ./a.out <your_file_name>
- Get the output in terminal

## For Task 5 while and for do loops are not implemented, additionally the evaluator cannot handle negative integers.
