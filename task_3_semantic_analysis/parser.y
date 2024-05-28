%{
    #include<stdio.h>
    #include<string.h>
    #include<stdlib.h>
    #include<ctype.h>

    extern char *yytext;
    extern int yylineno;
    void yyerror(const char *s);
    int yylex();
    int yywrap();

    struct node {
    struct node* children[20];
    char *token;
    };

    struct data_type {
        char* name;
        char* type;
        char* value;
        int line_number;
        int is_assigned;
    } symbol_table[40];

    struct node *head;
    int count = 0;
    int sem_error_count = 0;
    extern int line_number;
    char sem_errors[10][100];
    char reserved_arrays[100][100];
    int reserved_arrays_count = 0;
    char icg[500][100];
    int icg_count = 0;
    int temp_var = 0;
    int label = 0;
    int is_if = 0;
    int is_for = 0;
    int temp_label_1;
    int temp_label_2;

    int is_variable_present(char* name){
        for(int i = count - 1;i>=0;i--){
            if(strcmp(symbol_table[i].name,name)==0){
                return 1;
            }
        }
        return 0;
    }

    int is_variable_present_array(char* name){
        for(int i = 0;i<=reserved_arrays_count;i++){
            if(strcmp(reserved_arrays[i],name)==0){
                return 1;
            }
        }
        return 0;
    }

    void add_variable(char* name, char* type, int is_array, int start_index, int end_index) {
        if (is_variable_present(name) == 1 || is_variable_present_array(name) == 1) {
            sprintf(sem_errors[sem_error_count], "Line %d: Multiple declarations of \"%s\" not allowed\n", line_number + 1, name);
            sem_error_count++;
        } else {
            if (is_array) {
                for (int i = start_index; i <= end_index; i++) {
                    char array_instance[100];
                    sprintf(reserved_arrays[reserved_arrays_count],"%s",name);
                    reserved_arrays_count++;
                    sprintf(array_instance, "%s[%d]", name, i);
                    symbol_table[count].name = strdup(array_instance);
                    symbol_table[count].type = strdup(type);
                    symbol_table[count].line_number = line_number;
                    symbol_table[count].value = malloc(sizeof(char) * 100);
                    strcpy(symbol_table[count].value, "");
                    count++;
                }
            } else {
                symbol_table[count].name = strdup(name);
                symbol_table[count].type = strdup(type);
                symbol_table[count].line_number = line_number;
                symbol_table[count].value = malloc(sizeof(char) * 100);
                strcpy(symbol_table[count].value, "");
                count++;
            }
        }
    }

    void traverse_and_add(struct node* identifier_list_node, struct node* type_node) {
        if (strcmp(identifier_list_node->token, "identifier_list") == 0) {
            int child_index = 0;
            while (identifier_list_node->children[child_index] != NULL) {
                struct node* child_node = identifier_list_node->children[child_index];

                if (strcmp(child_node->token, "IDENTIFIER") == 0) {
                    if (strcmp(type_node->children[0]->token, "array_declaration") == 0) {
                        int start_index = atoi(type_node->children[0]->children[2]->children[0]->children[0]->token);
                        int end_index = atoi(type_node->children[0]->children[2]->children[2]->children[0]->token);
                        add_variable(child_node->children[0]->token, type_node->children[0]->children[5]->children[0]->token, 1, start_index, end_index);
                    } else {
                        add_variable(child_node->children[0]->token, type_node->children[0]->token, 0, 0, 0);
                    }
                } else if (strcmp(child_node->token, "identifier_list") == 0) {
                    traverse_and_add(child_node, type_node);
                }

                child_index += 2;
            }
        } else if (strcmp(identifier_list_node->token, "IDENTIFIER") == 0) {
            if (strcmp(type_node->children[0]->token, "array_declaration") == 0) {
                int start_index = atoi(type_node->children[0]->children[2]->children[0]->children[0]->token);
                int end_index = atoi(type_node->children[0]->children[2]->children[2]->children[0]->token);
                add_variable(identifier_list_node->children[0]->token, type_node->children[0]->children[5]->children[0]->token, 1, start_index, end_index);
            } else {
                add_variable(identifier_list_node->children[0]->token, type_node->children[0]->token, 0, 0, 0);
            }
        }
    }

    int check_type(int a, int b) {
        // valid additions
        if (a == 1 && b == 1) return 1;
        if (a == 2 && b == 2) return 2;
        if (a == 3 && b == 3) return 3;
        if (a == 4 && b == 4) return 4;
        if (a == 5 && b == 5) return 5;

        // adding int to real
        if (a == 1 && b == 2) return 2;
        if (a == 2 && b == 1) return 2;

        // invalid type mismatch
        char* type1 = "invalid";
        char* type2 = "invalid";

        switch (a) {
            case 1:
                type1 = "integer";
                break;
            case 2:
                type1 = "real";
                break;
            case 3:
                type1 = "char";
                break;
            case 4:
                type1 = "string";
                break;
            case 5:
                type1 = "boolean";
                break;
        }

        switch (b) {
            case 1:
                type2 = "integer";
                break;
            case 2:
                type2 = "real";
                break;
            case 3:
                type2 = "char";
                break;
            case 4:
                type2 = "string";
                break;
            case 5:
                type2 = "boolean";
                break;
        }

        sprintf(sem_errors[sem_error_count], "Line %d: Type mismatch: %s and %s\n", line_number + 1, type1, type2);
        sem_error_count++;
        return -1;
    }

    int check_assignment_type(int a, int b) {
        // valid additions
        if (a == 1 && b == 1) return 1;
        if (a == 2 && b == 2) return 2;
        if (a == 3 && b == 3) return 3;
        if (a == 4 && b == 4) return 4;
        if (a == 5 && b == 5) return 5;

        // only real can take in int value
        if (a == 2 && b == 1) return 2;

        // boolean values can be assigned to int and int to boolean
        if (a == 1 && b == 5) return 1;
        if (a==5 && b==1) return 5;

        // invalid type mismatch
        char* type1 = "invalid";
        char* type2 = "invalid";

        switch (a) {
            case 1:
                type1 = "integer";
                break;
            case 2:
                type1 = "real";
                break;
            case 3:
                type1 = "char";
                break;
            case 4:
                type1 = "string";
                break;
            case 5:
                type1 = "boolean";
                break;
        }

        switch (b) {
            case 1:
                type2 = "integer";
                break;
            case 2:
                type2 = "real";
                break;
            case 3:
                type2 = "char";
                break;
            case 4:
                type2 = "string";
                break;
            case 5:
                type2 = "boolean";
                break;
        }

        sprintf(sem_errors[sem_error_count], "Line %d: Assignment of %s to %s identifier\n", line_number + 1, type2, type1);
        sem_error_count++;
        return -1;
    }
    
    int check_condition_type(int a, int b) {
        // valid additions
        if (a == 1 && b == 1) return 1;
        if (a == 2 && b == 2) return 2;
        if (a == 3 && b == 3) return 3;
        if (a == 4 && b == 4) return 4;
        if (a == 5 && b == 5) return 5;

        // invalid type mismatch
        char* type1 = "invalid";
        char* type2 = "invalid";

        switch (a) {
            case 1:
                type1 = "integer";
                break;
            case 2:
                type1 = "real";
                break;
            case 3:
                type1 = "char";
                break;
            case 4:
                type1 = "string";
                break;
            case 5:
                type1 = "boolean";
                break;
        }

        switch (b) {
            case 1:
                type2 = "integer";
                break;
            case 2:
                type2 = "real";
                break;
            case 3:
                type2 = "char";
                break;
            case 4:
                type2 = "string";
                break;
            case 5:
                type2 = "boolean";
                break;
        }

        sprintf(sem_errors[sem_error_count], "Line %d: Type does not match for %s and %s identifier in Condition\n", line_number + 1, type2, type1);
        sem_error_count++;
        return -1;
    }

    void assign_variable(char* name,char* value){

    }

    int check_variable(char* name) {
        for (int i = 0; i < count; i++) {
            char *name_copy = strdup(symbol_table[i].name);
            char *bracket_position = strchr(name_copy, '[');
            if (bracket_position != NULL) {
                *bracket_position = '\0';
            }
            if (strcmp(name_copy, name) == 0) {
                return 1;
            }
        }

        return 0;
    }

    int set_type(char* name){
        for (int i = 0; i < count; i++) {
            char *name_copy = strdup(symbol_table[i].name);
            char *bracket_position = strchr(name_copy, '[');
            if (bracket_position != NULL) {
                *bracket_position = '\0';
            }
            if (strcmp(name_copy, name) == 0) {
                if (strcmp(symbol_table[i].type,"INTEGER") == 0) return 1;
                if (strcmp(symbol_table[i].type,"REAL") == 0) return 2;
                if (strcmp(symbol_table[i].type,"CHAR") == 0) return 3;
                if (strcmp(symbol_table[i].type,"STRING") == 0) return 4;
                if (strcmp(symbol_table[i].type,"BOOLEAN") == 0) return 5;
            }
        }
    return -1;
    }

    struct node* mknode(char *token) {	
	struct node *newnode = (struct node *)malloc(sizeof(struct node));
	char *newstr = (char *)malloc(strlen(token)+1);
	strcpy(newstr, token);
	newnode->token = newstr;
	return(newnode);
    }

%}
 
%union { 
    struct var_name { 
        char name[100]; 
        struct node* nd;
        int type;
        int t;
        int integer_val;
        char character_val;
        float real_val;
        int is_array;
        int is_assigned;
        char if_body[10];
        char else_body[10];
        int array_index;
    } nd_obj;
}
 
%token <nd_obj> T_AND T_OR T_NOT
%token <nd_obj> T_IF T_THEN T_ELSE
%token <nd_obj> T_WHILE T_DO T_FOR
%token <nd_obj> INTEGER REAL BOOLEAN STRING CHAR
%token <nd_obj> WRITE READ
%token <nd_obj> TO DOWNTO
%token <nd_obj> T_BEGIN T_END
%token <nd_obj> VAR CONST PROGRAM
%token <nd_obj> ARRAY OF
%token <nd_obj> T_IDENTIFIER T_INTEGER T_REAL T_STRING T_CHAR
%token <nd_obj> ASSIGNMENT COLON SEMICOLON COMMA DOT DOTDOT
%token <nd_obj> EQUAL NOTEQUAL LESSEQUAL LESS GREATEREQUAL GREATER
%token <nd_obj> LPAREN RPAREN LBRACKET RBRACKET
%token <nd_obj> PLUS MINUS MUL DIV MOD
 
%type<nd_obj> program variable_declaration_part statement_part compound_statement statement assignment_statement expression
%type<nd_obj> if_statement for_statement while_statement write_statement read_statement array_declaration write_params
%type<nd_obj> primary_expression constant additive_expression multiplicative_expression relational_expression logical_and_expression logical_or_expression identifier_or_array

%type<nd_obj> variable_declarations variable_declaration identifier_list type range statement_list identifier if_token else_statement

%start program

%%

program:
    PROGRAM identifier SEMICOLON
    variable_declaration_part
    statement_part
    DOT
    {
        $$.nd = mknode("program");

        $1.nd = mknode("PROGRAM");
        $1.nd->children[0] = mknode($1.name);

        $3.nd = mknode("SEMICOLON");
        $3.nd->children[0] = mknode($3.name);

        $6.nd = mknode("DOT");
        $6.nd->children[0] = mknode($6.name);

        $$.nd->children[0] = $1.nd;
        $$.nd->children[1] = $2.nd;
        $$.nd->children[2] = $3.nd;
        $$.nd->children[3] = $4.nd;
        $$.nd->children[4] = $5.nd;
        $$.nd->children[5] = $6.nd;
        head = $$.nd;
    }
;

variable_declaration_part:
    VAR variable_declarations
    {
        $$.nd = mknode("variable_declaration_part");

        $1.nd = mknode("VAR");
        $1.nd->children[0] = mknode($1.name);

        $$.nd->children[0] = $1.nd;
        $$.nd->children[1] = $2.nd;
    }
;

variable_declarations:
    variable_declaration SEMICOLON
    {
        $$.nd = mknode("variable_declarations");
        
        $2.nd = mknode("SEMICOLON");
        $2.nd->children[0] = mknode($2.name);

        $$.nd->children[0] = $1.nd;
        $$.nd->children[1] = $2.nd;
    }
    | 
    variable_declaration SEMICOLON variable_declarations
    {
        $$.nd = mknode("variable_declarations");
        
        $2.nd = mknode("SEMICOLON");
        $2.nd->children[0] = mknode($2.name);

        $$.nd->children[0] = $1.nd;
        $$.nd->children[1] = $2.nd;
        $$.nd->children[2] = $3.nd;
    }
;

variable_declaration: identifier_list COLON type
    {
        $$.nd = mknode("variable_declaration");
        $2.nd = mknode("COLON");
        $2.nd->children[0] = mknode($2.name);
        $$.nd->children[0] = $1.nd;
        $$.nd->children[1] = $2.nd;
        $$.nd->children[2] = $3.nd;

        traverse_and_add($1.nd,$3.nd);
    }
;

identifier_list:
    identifier
    {
        $$.nd = mknode("identifier_list");
        $$.nd->children[0] = $1.nd;

        sprintf(icg[icg_count++],"%s = NULL\n", $1.nd->children[0]->token);
    }
    |
    identifier COMMA identifier_list
    {
        $$.nd = mknode("identifier_list");

        $2.nd = mknode("COMMA");
        $2.nd->children[0] = mknode($2.name);

        $$.nd->children[0] = $1.nd;
        $$.nd->children[1] = $2.nd;
        $$.nd->children[2] = $3.nd;

        sprintf(icg[icg_count++],"%s = NULL\n", $1.nd->children[0]->token);
    }
;

type:
    INTEGER
    {
        $$.nd = mknode("type");

        $1.nd = mknode("INTEGER");
        $1.nd->children[0] = mknode($1.name);

        $$.nd->children[0] = $1.nd;
    }
    | 
    REAL
    {
        $$.nd = mknode("type");

        $1.nd = mknode("REAL");
        $1.nd->children[0] = mknode($1.name);

        $$.nd->children[0] = $1.nd;
    }
    | 
    BOOLEAN
    {
        $$.nd = mknode("type");

        $1.nd = mknode("BOOLEAN");
        $1.nd->children[0] = mknode($1.name);

        $$.nd->children[0] = $1.nd;
    }
    | 
    CHAR
    {
        $$.nd = mknode("type");

        $1.nd = mknode("CHAR");
        $1.nd->children[0] = mknode($1.name);

        $$.nd->children[0] = $1.nd;
    }
    | array_declaration
    {
        $$.nd = mknode("type");

        $$.nd->children[0] = $1.nd;
    }
;

array_declaration:
    ARRAY LBRACKET range RBRACKET OF type
    {
        $$.nd = mknode("array_declaration");

        $1.nd = mknode("ARRAY");
        $1.nd->children[0] = mknode($1.name);

        $2.nd = mknode("LBRACKET");
        $2.nd->children[0] = mknode($2.name);

        $4.nd = mknode("RBRACKET");
        $4.nd->children[0] = mknode($4.name);

        $5.nd = mknode("OF");
        $5.nd->children[0] = mknode($5.name);

        $$.nd->children[0] = $1.nd;
        $$.nd->children[1] = $2.nd;
        $$.nd->children[2] = $3.nd;
        $$.nd->children[3] = $4.nd;
        $$.nd->children[4] = $5.nd;
        $$.nd->children[5] = $6.nd;
    }
;

range:
    T_INTEGER DOTDOT T_INTEGER
    {
        $$.nd = mknode("range");

        $1.nd = mknode("INTEGER");
        $1.nd->children[0] = mknode($1.name);

        $2.nd = mknode("DOTDOT");
        $2.nd->children[0] = mknode($2.name);

        $3.nd = mknode("INTEGER");
        $3.nd->children[0] = mknode($3.name);

        $$.nd->children[0] = $1.nd;
        $$.nd->children[1] = $2.nd;
        $$.nd->children[2] = $3.nd;
    }
;

statement_part:
    compound_statement
    {
        $$.nd = mknode("statement_part");

        $$.nd->children[0] = $1.nd;
    }
;

compound_statement:
    T_BEGIN statement_list T_END
    {
        $$.nd = mknode("compound_statement");

        $1.nd = mknode("BEGIN");
        $1.nd->children[0] = mknode($1.name);

        $3.nd = mknode("END");
        $3.nd->children[0] = mknode($3.name);


        $$.nd->children[0] = $1.nd;
        $$.nd->children[1] = $2.nd;
        $$.nd->children[2] = $3.nd;

    }
;

statement_list:
    statement SEMICOLON statement_list
    {
        $$.nd = mknode("statement_list");

        $2.nd = mknode("SEMICOLON");
        $2.nd->children[0] = mknode($2.name);

        $$.nd->children[0] = $1.nd;
        $$.nd->children[1] = $2.nd;
        $$.nd->children[2] = $3.nd;
    }
    |
    statement SEMICOLON
    {
        $$.nd = mknode("statement_list");

        $2.nd = mknode("SEMICOLON");
        $2.nd->children[0] = mknode($2.name);

        $$.nd->children[0] = $1.nd;
        $$.nd->children[1] = $2.nd;
    }
;

statement:
    assignment_statement
    {
        $$.nd = mknode("statement");

        $$.nd->children[0] = $1.nd;
    }
    |
    if_statement
    {
        $$.nd = mknode("statement");

        $$.nd->children[0] = $1.nd;
    }
    | 
    for_statement
    {
        $$.nd = mknode("statement");

        $$.nd->children[0] = $1.nd;
    }
    | 
    while_statement
    {
        $$.nd = mknode("statement");

        $$.nd->children[0] = $1.nd;
    }
    |
    write_statement
    {
        $$.nd = mknode("statement");

        $$.nd->children[0] = $1.nd;
    }
    |
    read_statement
    {
        $$.nd = mknode("statement");

        $$.nd->children[0] = $1.nd;
    }
    |
    compound_statement
    {
        $$.nd = mknode("statement");

        $$.nd->children[0] = $1.nd;
    }
;

assignment_statement:
    identifier_or_array ASSIGNMENT expression
    {
        check_assignment_type($1.type,$3.type);

        $$.nd = mknode("assignment_statement");

        $2.nd = mknode("ASSIGNMENT");
        $2.nd->children[0] = mknode($2.name);

        $$.nd->children[0] = $1.nd;
        $$.nd->children[1] = $2.nd;
        $$.nd->children[2] = $3.nd;

        for (int i = 0; i < count; i++) {
            char *name_copy = strdup(symbol_table[i].name);
            char *bracket_position = strchr(name_copy, '[');
            if (bracket_position != NULL) {
                *bracket_position = '\0';
            }
            if (strcmp(name_copy, $1.nd->children[0]->children[0]->token) == 0) {
                if($3.type == 1){
                    sprintf(symbol_table[i].value, "%d", $3.integer_val);
                }
                if($3.type == 2){
                    sprintf(symbol_table[i].value, "%f", $3.real_val);
                }
                if($3.type == 3){
                    sprintf(symbol_table[i].value, "%c", $3.character_val);
                }
            }
        }

        if($1.is_array==0){
            sprintf(icg[icg_count++],"%s = t%d\n",$1.nd->children[0]->children[0]->token,$3.t);
        }
        else{
            if($1.type == 1){
                // int
                sprintf(icg[icg_count++],"t%d = 4 * %d\n",temp_var++,$1.array_index);
            }
            else if($1.type == 2){
                // real
                sprintf(icg[icg_count++],"t%d = 8 * %d\n",temp_var++,$1.array_index);
            }
            else if($1.type == 3){
                // char
                sprintf(icg[icg_count++],"t%d = 1 * %d\n",temp_var++,$1.array_index);
            }

            sprintf(icg[icg_count++], "t%d = &%s\n", temp_var++, $1.nd->children[0]->children[0]->token);
            sprintf(icg[icg_count++], "t%d = t%d + t%d\n", temp_var, temp_var - 2, temp_var - 1);
            sprintf(icg[icg_count++], "*t%d = t%d\n", temp_var, $3.t);
        }

        for (int i = 0; i < count; i++) {
            char *name_copy = strdup(symbol_table[i].name);
            char *bracket_position = strchr(name_copy, '[');
            if (bracket_position != NULL) {
                *bracket_position = '\0';
            }
            if (strcmp(name_copy, $1.nd->children[0]->children[0]->token) == 0) {
                symbol_table[i].is_assigned = 1;
            }
        }
    }
;

expression:
    logical_or_expression
    {
        $$.nd = mknode("expression");
        $$.type = $1.type;
        $$.nd->children[0] = $1.nd;

        $$.t = $1.t;

        $$.integer_val = $1.integer_val;
        $$.real_val = $1.real_val;
        $$.character_val = $1.character_val;
    }
;

logical_or_expression:
    logical_and_expression
    {
        $$.nd = mknode("logical_or_expression");
        $$.type = $1.type;
        $$.nd->children[0] = $1.nd;

        $$.t = $1.t;

        $$.integer_val = $1.integer_val;
        $$.real_val = $1.real_val;
        $$.character_val = $1.character_val;
    }
    | 
    logical_or_expression T_OR logical_and_expression
    {
        $$.nd = mknode("logical_or_expression");
        if($1.type != 5 || $3.type !=5){
            sprintf(sem_errors[sem_error_count++],"Line %d: Expected boolean type for OR statement \n",line_number+1);
        }
        $$.type = 5;
        $2.nd = mknode("OR");
        $2.nd->children[0] = mknode($2.name);

        $$.nd->children[0] = $1.nd;
        $$.nd->children[1] = $2.nd;
        $$.nd->children[2] = $3.nd;  

        if(is_if == 1) {
            sprintf(icg[icg_count++], "\nIF t%d OR t%d GOTO L%d ELSE GOTO L%d\n", $1.t, $3.t, label, label + 1);
            sprintf($$.if_body, "L%d", label++);
            sprintf($$.else_body, "L%d", label++);
        } 
        else if(is_for == 1) {
            
        }
        else {
            $$.t = temp_var++;
            sprintf(icg[icg_count++], "t%d = %d OR t%d\n", $$.t, $1.t, $3.t);
        }    
    }
;

logical_and_expression:
    relational_expression
    {
        $$.nd = mknode("logical_and_expression");
        $$.type = $1.type;
        $$.nd->children[0] = $1.nd;

        $$.t = $1.t;

        $$.integer_val = $1.integer_val;
        $$.real_val = $1.real_val;
        $$.character_val = $1.character_val;
    }
    | 
    logical_and_expression T_AND relational_expression
    {
        $$.nd = mknode("logical_and_expression");
        if($1.type != 5 || $3.type !=5){
            sprintf(sem_errors[sem_error_count++],"Line %d: Expected boolean type for AND statement \n",line_number+1);
        }
        $$.type = 5;
        $2.nd = mknode("AND");
        $2.nd->children[0] = mknode($2.name);

        $$.nd->children[0] = $1.nd;
        $$.nd->children[1] = $2.nd;
        $$.nd->children[2] = $3.nd; 

        if(is_if == 1) {
            sprintf(icg[icg_count++], "\nIF t%d AND t%d GOTO L%d ELSE GOTO L%d\n", $1.t, $3.t, label, label + 1);
            sprintf($$.if_body, "L%d", label++);
            sprintf($$.else_body, "L%d", label++);
        } 
        else if(is_for == 1) {
            
        }
        else {
            $$.t = temp_var++;
            sprintf(icg[icg_count++], "t%d = %d AND t%d\n", $$.t, $1.t, $3.t);
        } 
    }
;

relational_expression:
    additive_expression
    {
        $$.nd = mknode("relational_expression");
        $$.type = $1.type;
        $$.nd->children[0] = $1.nd;

        $$.t = $1.t;

        $$.integer_val = $1.integer_val;
        $$.real_val = $1.real_val;
        $$.character_val = $1.character_val;
    }
    | 
    relational_expression LESS additive_expression
    {
        $$.nd = mknode("relational_expression");
        $$.type = check_condition_type($1.type,$3.type);
        $$.type = 5;
        $2.nd = mknode("LESS");
        $2.nd->children[0] = mknode($2.name);

        $$.nd->children[0] = $1.nd;
        $$.nd->children[1] = $2.nd;
        $$.nd->children[2] = $3.nd; 

        if(is_if == 1){
            sprintf(icg[icg_count++], "\nIF t%d < t%d GOTO L%d ELSE GOTO L%d\n", $1.t, $3.t, label, label + 1);
            sprintf($$.if_body, "L%d", label++);
            sprintf($$.else_body, "L%d", label++);
        }
        else if(is_for == 1){

        }
        else {
            $$.t  = temp_var++;
            sprintf(icg[icg_count++],"t%d = t%d < t%d", $$.t, $1.t, $3.t);
        }
    }
    | 
    relational_expression LESSEQUAL additive_expression
    {
        $$.nd = mknode("relational_expression");
        $$.type = check_condition_type($1.type,$3.type);
        $$.type = 5;
        $2.nd = mknode("LESSEQUAL");
        $2.nd->children[0] = mknode($2.name);

        $$.nd->children[0] = $1.nd;
        $$.nd->children[1] = $2.nd;
        $$.nd->children[2] = $3.nd; 

        if(is_if == 1){
            sprintf(icg[icg_count++], "\nIF t%d <= t%d GOTO L%d ELSE GOTO L%d\n", $1.t, $3.t, label, label + 1);
            sprintf($$.if_body, "L%d", label++);
            sprintf($$.else_body, "L%d", label++);
        }
        else if(is_for == 1){

        }
        else {
            $$.t  = temp_var++;
            sprintf(icg[icg_count++],"t%d = t%d <= t%d", $$.t, $1.t, $3.t);
        }
    }
    | 
    relational_expression GREATER additive_expression
    {
        $$.nd = mknode("relational_expression");
        $$.type = check_condition_type($1.type,$3.type);
        $2.nd = mknode("GREATER");
        $$.type = 5;
        $2.nd->children[0] = mknode($2.name);

        $$.nd->children[0] = $1.nd;
        $$.nd->children[1] = $2.nd;
        $$.nd->children[2] = $3.nd; 

        if(is_if == 1){
            sprintf(icg[icg_count++], "\nIF t%d > t%d GOTO L%d ELSE GOTO L%d\n", $1.t, $3.t, label, label + 1);
            sprintf($$.if_body, "L%d", label++);
            sprintf($$.else_body, "L%d", label++);
        }
        else if(is_for == 1){

        }
        else {
            $$.t  = temp_var++;
            sprintf(icg[icg_count++],"t%d = t%d > t%d", $$.t, $1.t, $3.t);
        }
    }
    | 
    relational_expression GREATEREQUAL additive_expression
    {
        $$.nd = mknode("relational_expression");
        $$.type = check_condition_type($1.type,$3.type);
        $2.nd = mknode("GREATEREQUAL");
        $$.type = 5;
        $2.nd->children[0] = mknode($2.name);

        $$.nd->children[0] = $1.nd;
        $$.nd->children[1] = $2.nd;
        $$.nd->children[2] = $3.nd;

        if(is_if == 1){
            sprintf(icg[icg_count++], "\nIF t%d >= t%d GOTO L%d ELSE GOTO L%d\n", $1.t, $3.t, label, label + 1);
            sprintf($$.if_body, "L%d", label++);
            sprintf($$.else_body, "L%d", label++);
        }
        else if(is_for == 1){

        }
        else {
            $$.t  = temp_var++;
            sprintf(icg[icg_count++],"t%d = t%d >= t%d", $$.t, $1.t, $3.t);
        }
    }
    | 
    relational_expression EQUAL additive_expression
    {
        $$.nd = mknode("relational_expression");
        $$.type = check_condition_type($1.type,$3.type);
        $$.type = 5;
        $2.nd = mknode("EQUAL");
        $2.nd->children[0] = mknode($2.name);

        $$.nd->children[0] = $1.nd;
        $$.nd->children[1] = $2.nd;
        $$.nd->children[2] = $3.nd; 

        if(is_if == 1){
            sprintf(icg[icg_count++], "\nIF t%d == t%d GOTO L%d ELSE GOTO L%d\n", $1.t, $3.t, label, label + 1);
            sprintf($$.if_body, "L%d", label++);
            sprintf($$.else_body, "L%d", label++);
        }
        else if(is_for == 1){

        }
        else {
            $$.t  = temp_var++;
            sprintf(icg[icg_count++],"t%d = t%d == t%d", $$.t, $1.t, $3.t);
        }
    }
    | 
    relational_expression NOTEQUAL additive_expression
    {
        $$.nd = mknode("relational_expression");
        $$.type = check_condition_type($1.type,$3.type);
        $$.type = 5;
        $2.nd = mknode("NOTEQUAL");
        $2.nd->children[0] = mknode($2.name);

        $$.nd->children[0] = $1.nd;
        $$.nd->children[1] = $2.nd;
        $$.nd->children[2] = $3.nd; 

        if(is_if == 1){
            sprintf(icg[icg_count++], "\nIF t%d != t%d GOTO L%d ELSE GOTO L%d\n", $1.t, $3.t, label, label + 1);
            sprintf($$.if_body, "L%d", label++);
            sprintf($$.else_body, "L%d", label++);
        }
        else if(is_for == 1){

        }
        else {
            $$.t  = temp_var++;
            sprintf(icg[icg_count++],"t%d = t%d != t%d\n", $$.t, $1.t, $3.t);
        }
    }
;

additive_expression:
    multiplicative_expression
    {
        $$.nd = mknode("additive_expression");
        $$.type = $1.type;
        $$.nd->children[0] = $1.nd;

        $$.t = $1.t;

        $$.integer_val = $1.integer_val;
        $$.real_val = $1.real_val;
        $$.character_val = $1.character_val;
    }
    | 
    additive_expression PLUS multiplicative_expression
    {
        $$.nd = mknode("additive_expression");
        $$.type = check_type($1.type,$3.type);
        $2.nd = mknode("PLUS");
        $2.nd->children[0] = mknode($2.name);

        $$.nd->children[0] = $1.nd;
        $$.nd->children[1] = $2.nd;
        $$.nd->children[2] = $3.nd; 

        $$.t = temp_var++;
        sprintf(icg[icg_count++], "t%d = t%d + t%d\n", $$.t, $1.t, $3.t);
    }
    | 
    additive_expression MINUS multiplicative_expression
    {
        $$.nd = mknode("additive_expression");
        $$.type = check_type($1.type,$3.type);
        $2.nd = mknode("MINUS");
        $2.nd->children[0] = mknode($2.name);

        $$.nd->children[0] = $1.nd;
        $$.nd->children[1] = $2.nd;
        $$.nd->children[2] = $3.nd; 

        $$.t = temp_var++;
        sprintf(icg[icg_count++], "t%d = t%d - t%d\n", $$.t, $1.t, $3.t);
    }
;

multiplicative_expression:
    primary_expression
    {
        $$.nd = mknode("multiplicative_expression");
        $$.type = $1.type;
        $$.nd->children[0] = $1.nd;

        $$.t = $1.t;

        $$.integer_val = $1.integer_val;
        $$.real_val = $1.real_val;
        $$.character_val = $1.character_val;
    }
    | 
    multiplicative_expression MUL primary_expression
    {
        $$.nd = mknode("multiplicative_expression");
        $$.type = check_type($1.type,$3.type);
        $2.nd = mknode("MUL");
        $2.nd->children[0] = mknode($2.name);

        $$.nd->children[0] = $1.nd;
        $$.nd->children[1] = $2.nd;
        $$.nd->children[2] = $3.nd;

        $$.t = temp_var++;
        sprintf(icg[icg_count++], "t%d = t%d * t%d\n", $$.t, $1.t, $3.t);
    }
    | 
    multiplicative_expression DIV primary_expression
    {
        $$.nd = mknode("multiplicative_expression");
        $$.type = check_type($1.type,$3.type);
        $2.nd = mknode("DIV");
        $2.nd->children[0] = mknode($2.name);

        $$.nd->children[0] = $1.nd;
        $$.nd->children[1] = $2.nd;
        $$.nd->children[2] = $3.nd; 

        $$.t = temp_var++;
        sprintf(icg[icg_count++], "t%d = t%d / t%d\n", $$.t, $1.t, $3.t);
    }
    | 
    multiplicative_expression MOD primary_expression
    {
        $$.nd = mknode("multiplicative_expression");
        $$.type = check_type($1.type,$3.type);
        $2.nd = mknode("MOD");
        $2.nd->children[0] = mknode($2.name);

        $$.nd->children[0] = $1.nd;
        $$.nd->children[1] = $2.nd;
        $$.nd->children[2] = $3.nd; 

        $$.t = temp_var++;
        sprintf(icg[icg_count++], "t%d = t%d %% t%d\n", $$.t, $1.t, $3.t);

       
    }
;

primary_expression:
    identifier_or_array
    {
        $$.nd = mknode("primary_expression");
        $$.type = $1.type;
        $$.t = temp_var++;
        $$.nd->children[0] = $1.nd;
        if($1.is_array==0){
        sprintf(icg[icg_count++],"t%d = %s\n",$$.t,$1.nd->children[0]->children[0]->token);
        }
        else{
            char buffer[256];
            sprintf(buffer,"%s[0]",$1.nd->children[0]->children[0]->token);
            sprintf(icg[icg_count++],"t%d = %s\n",$$.t,buffer);
        }

        for (int i = 0; i < count; i++) {
            char *name_copy = strdup(symbol_table[i].name);
            char *bracket_position = strchr(name_copy, '[');
            if (bracket_position != NULL) {
                *bracket_position = '\0';
            }
            if (strcmp(name_copy, $1.nd->children[0]->children[0]->token) == 0) {
                if(symbol_table[i].is_assigned!=1){
                    sprintf(sem_errors[sem_error_count],"Line %d: Variable \"%s\" used before assignment\n",line_number+1,$1.nd->children[0]->children[0]->token);
                    sem_error_count++;
                    break;
                }
                else{
                    $$.is_assigned = 1;
                }
            }
        }

        $$.integer_val = $1.integer_val;
        $$.real_val = $1.real_val;
        $$.character_val = $1.character_val;

    }
    | 
    constant
    {
        $$.nd = mknode("primary_expression");
        $$.type = $1.type;
        $$.t = temp_var++;
        $$.nd->children[0] = $1.nd;
        sprintf(icg[icg_count++],"t%d = %s\n",$$.t,$1.nd->children[0]->token);
    }
    | 
    LPAREN expression RPAREN
    {
        $$.nd = mknode("primary_expression");
        $$.type = $2.type;
        $1.nd = mknode("LPAREN");
        $1.nd->children[0] = mknode($1.name);

        $3.nd = mknode("RPAREN");
        $3.nd->children[0] = mknode($3.name);

        $$.nd->children[0] = $1.nd;
        $$.nd->children[1] = $2.nd;
        $$.nd->children[2] = $3.nd; 

        $$.t = $2.t;

        $$.integer_val = $2.integer_val;
        $$.real_val = $2.real_val;
        $$.character_val = $2.character_val;
    }
;

identifier_or_array:
    identifier
    {
        // this checks for undeclared variables
        if(check_variable($1.nd->children[0]->token)==0){
            sprintf(sem_errors[sem_error_count],"Line %d: Variable \"%s\" not declared\n",line_number+1,$1.nd->children[0]->token);
            sem_error_count++;
        }
        $$.is_array = 0;
        $$.type = set_type($1.nd->children[0]->token);


        $$.nd = mknode("identifier_or_array");

        $$.nd->children[0] = $1.nd;

        for (int i = 0; i < count; i++) {
            char *name_copy = strdup(symbol_table[i].name);
            char *bracket_position = strchr(name_copy, '[');
            if (bracket_position != NULL) {
                *bracket_position = '\0';
            }
            if (strcmp(name_copy, $1.nd->children[0]->token) == 0) {
                if($$.type == 1){
                    $$.integer_val = atoi(symbol_table[i].value);
                }
            }
        }

    }
    | 
    identifier LBRACKET expression RBRACKET 
    {
        // this checks for undeclared array variables
        if(check_variable($1.nd->children[0]->token)==0){
            sprintf(sem_errors[sem_error_count],"Line %d: Array Variable \"%s\" not declared\n",line_number+1,$1.nd->children[0]->token);
            sem_error_count++;
        }
        $$.is_array = 1;
        $$.type = set_type($1.nd->children[0]->token);

        $$.array_index = $3.integer_val;

        $$.nd = mknode("identifier_or_array");

        $2.nd = mknode("LBRACKET");
        $2.nd->children[0] = mknode($2.name);

        $4.nd = mknode("RBRACKET");
        $4.nd->children[0] = mknode($4.name);

        $$.nd->children[0] = $1.nd;
        $$.nd->children[1] = $2.nd;
        $$.nd->children[2] = $3.nd; 
        $$.nd->children[3] = $4.nd; 

        if($3.type != 1){
            sprintf(sem_errors[sem_error_count++],"Line %d: Expected integer type in array \"%s\"\n",line_number+1,$1.nd->children[0]->token);
        }
    }
;

identifier:
    T_IDENTIFIER
    {
        $$.nd = mknode("IDENTIFIER");

        $$.nd->children[0] = mknode($1.name);
    }
;

constant:
    T_INTEGER
    {
        $$.nd = mknode("INTEGER_CONSTANT");
        $$.type = 1;
        $$.nd->children[0] = mknode($1.name);
        $$.is_assigned = 1;

        $$.integer_val = atoi($1.name);
    }
    | 
    T_REAL
    {
        $$.nd = mknode("REAL_CONSTANT");
        $$.type = 2;
        $$.nd->children[0] = mknode($1.name);
        $$.is_assigned = 1;

        $$.real_val = atof($1.name);
    }
    | 
    T_STRING
    {
        $$.nd = mknode("STRING_CONSTANT");
        $$.type = 3;
        $$.nd->children[0] = mknode($1.name);
        $$.is_assigned = 1;
    }
    | 
    T_CHAR
    {
        $$.nd = mknode("CHAR_CONSTANT");
        $$.type = 4;
        $$.nd->children[0] = mknode($1.name);
        $$.is_assigned = 1;

        $$.character_val = $1.name[0];
    }
;

if_token: T_IF 
{
    is_if = 1;
    $$.nd = mknode("IF");

    $1.nd = mknode($1.name);

    $$.nd->children[0] = $1.nd;
};

if_statement:
    if_token expression {sprintf(icg[icg_count++], "\nLABEL %s:\n", $2.if_body);} T_THEN compound_statement {sprintf(icg[icg_count++], "\nLABEL %s:\n", $2.else_body);} else_statement
    {
        $$.nd = mknode("if_statement");

        if($2.type != 5){
            sprintf(sem_errors[sem_error_count++],"Line %d: Expected bool type for condition in if statement\n",line_number+1);
        }

        $4.nd = mknode("THEN");
        $4.nd->children[0] = mknode($4.name);

        $$.nd->children[0] = $1.nd;
        $$.nd->children[1] = $2.nd;
        $$.nd->children[2] = $4.nd; 
        $$.nd->children[3] = $5.nd; 
        $$.nd->children[4] = $7.nd; 
        is_if = 0;
    }
;

else_statement: T_ELSE compound_statement
{
    $$.nd = mknode("else_statement");

    $1.nd = mknode("ELSE");
    $1.nd->children[0] = mknode($1.name);

    $$.nd->children[0] = $1.nd;
    $$.nd->children[1] = $2.nd;
}
|
{
    $$.nd = NULL;
}

for_statement:
    T_FOR identifier ASSIGNMENT expression TO expression T_DO
    {
        for (int i = 0; i < count; i++) {
            char *name_copy = strdup(symbol_table[i].name);
            char *bracket_position = strchr(name_copy, '[');
            if (bracket_position != NULL) {
                *bracket_position = '\0';
            }
            if (strcmp(name_copy, $2.nd->children[0]->token) == 0) {
                if($4.type == 1){
                    sprintf(symbol_table[i].value,"%d",$4.integer_val);
                }
                if($4.type == 2){
                    sprintf(symbol_table[i].value, "%f", $4.real_val);
                }
                if($4.type == 3){
                    sprintf(symbol_table[i].value, "%c", $4.character_val);
                }
            }
        }

        temp_label_1 = label++;
        temp_label_2 = label++;
        sprintf(icg[icg_count++],"%s = t%d\n",$2.nd->children[0]->token,$4.t);
        sprintf(icg[icg_count++], "\nLABEL L%d:\n", temp_label_1);
        sprintf(icg[icg_count++], "IF %s >= t%d GOTO L%d\n", $2.nd->children[0]->token, $6.t, temp_label_2);

      //  if($2.is_assigned != 1){
       //     sprintf(sem_errors[sem_error_count++],"Line %d: Identifier \"%s\" is not assigned any value\n",line_number+1,$2.nd->children[0]->token);
      //  }

      for (int i = 0; i < count; i++) {
            char *name_copy = strdup(symbol_table[i].name);
            char *bracket_position = strchr(name_copy, '[');
            if (bracket_position != NULL) {
                *bracket_position = '\0';
            }
            if (strcmp(name_copy, $2.nd->children[0]->token) == 0) {
                symbol_table[i].is_assigned = 1;
            }
        }
    }
    compound_statement
    {
        $$.nd = mknode("for_statement");

        $1.nd = mknode("FOR");
        $1.nd->children[0] = mknode($1.name);

        $3.nd = mknode("ASSIGNMENT");
        $3.nd->children[0] = mknode($3.name);

        $5.nd = mknode("TO");
        $5.nd->children[0] = mknode($5.name);

        $7.nd = mknode("DO");
        $7.nd->children[0] = mknode($7.name);

        $$.nd->children[0] = $1.nd;
        $$.nd->children[1] = $2.nd;
        $$.nd->children[2] = $3.nd; 
        $$.nd->children[3] = $4.nd;
        $$.nd->children[4] = $5.nd; 
        $$.nd->children[5] = $6.nd;
        $$.nd->children[6] = $7.nd; 
        $$.nd->children[7] = $9.nd;

        if($4.type != 1 || $6.type != 1){
            sprintf(sem_errors[sem_error_count++],"Line %d: Expected integer type for identifier \"%s\"\n",line_number+1,$2.nd->children[0]->token);
        }


        sprintf(icg[icg_count++], "%s = %s - 1\n",$2.nd->children[0]->token,$2.nd->children[0]->token);
        sprintf(icg[icg_count++], "GOTO L%d\n", temp_label_1);
        sprintf(icg[icg_count++], "\nLABEL L%d:\n", temp_label_2);
    }
    | 
    T_FOR identifier ASSIGNMENT expression DOWNTO expression T_DO
    {

        for (int i = 0; i < count; i++) {
            char *name_copy = strdup(symbol_table[i].name);
            char *bracket_position = strchr(name_copy, '[');
            if (bracket_position != NULL) {
                *bracket_position = '\0';
            }
            if (strcmp(name_copy, $2.nd->children[0]->token) == 0) {
                if($4.type == 1){
                    sprintf(symbol_table[i].value,"%d",$4.integer_val);
                }
                if($4.type == 2){
                    sprintf(symbol_table[i].value, "%f", $4.real_val);
                }
                if($4.type == 3){
                    sprintf(symbol_table[i].value, "%c", $4.character_val);
                }
            }
        }
        
        temp_label_1 = label++;
        temp_label_2 = label++;
        sprintf(icg[icg_count++],"%s = t%d\n",$2.nd->children[0]->token,$4.t);
        sprintf(icg[icg_count++], "\nLABEL L%d:\n", temp_label_1);
        sprintf(icg[icg_count++], "IF %s <= t%d GOTO L%d\n", $2.nd->children[0]->token, $6.t, temp_label_2);

        //if($2.is_assigned != 1){
        //    sprintf(sem_errors[sem_error_count++],"Line %d: Identifier \"%s\" is not assigned any value\n",line_number+1,$2.nd->children[0]->token);
       // }

       for (int i = 0; i < count; i++) {
            char *name_copy = strdup(symbol_table[i].name);
            char *bracket_position = strchr(name_copy, '[');
            if (bracket_position != NULL) {
                *bracket_position = '\0';
            }
            if (strcmp(name_copy, $2.nd->children[0]->token) == 0) {
                symbol_table[i].is_assigned = 1;
            }
        }
    }
    compound_statement
    {
        $$.nd = mknode("for_statement");

        $1.nd = mknode("FOR");
        $1.nd->children[0] = mknode($1.name);

        $3.nd = mknode("ASSIGNMENT");
        $3.nd->children[0] = mknode($3.name);

        $5.nd = mknode("DOWNTO");
        $5.nd->children[0] = mknode($5.name);

        $7.nd = mknode("DO");
        $7.nd->children[0] = mknode($5.name);

        $$.nd->children[0] = $1.nd;
        $$.nd->children[1] = $2.nd;
        $$.nd->children[2] = $3.nd; 
        $$.nd->children[3] = $4.nd;
        $$.nd->children[4] = $5.nd; 
        $$.nd->children[5] = $6.nd;
        $$.nd->children[6] = $7.nd; 
        $$.nd->children[7] = $9.nd;

        if($4.type != 1 || $6.type != 1){
            sprintf(sem_errors[sem_error_count++],"Line %d: Expected integer type for identifier \"%s\"\n",line_number+1,$2.nd->children[0]->token);
        }

        sprintf(icg[icg_count++], "%s = %s - 1\n",$2.nd->children[0]->token,$2.nd->children[0]->token);
        sprintf(icg[icg_count++], "GOTO L%d\n", temp_label_1);
        sprintf(icg[icg_count++], "\nLABEL L%d:\n", temp_label_2);
    }
;

while_statement:
    T_WHILE expression T_DO compound_statement
    {
        $$.nd = mknode("while_statement");

        $1.nd = mknode("WHILE");
        $1.nd->children[0] = mknode($1.name);

        $2.nd = mknode("DO");
        $2.nd->children[0] = mknode($2.name);

        $$.nd->children[0] = $1.nd;
        $$.nd->children[1] = $2.nd;
        $$.nd->children[2] = $3.nd;
        $$.nd->children[3] = $4.nd;
    }
;

write_statement:
    WRITE LPAREN write_params RPAREN
    {
        $$.nd = mknode("write_statement");

        $1.nd = mknode("WRITE");
        $1.nd->children[0] = mknode($1.name);

        $2.nd = mknode("LPAREN");
        $2.nd->children[0] = mknode($2.name);

        $4.nd = mknode("RPAREN");
        $4.nd->children[0] = mknode($4.name);

        $$.nd->children[0] = $1.nd;
        $$.nd->children[1] = $2.nd;
        $$.nd->children[2] = $3.nd;
        $$.nd->children[3] = $4.nd;
    }
;

write_params:
    T_STRING
    {
        $$.nd = mknode("write_params");

        $1.nd = mknode("STRING");
        $1.nd->children[0] = mknode($1.name);

        $$.nd->children[0] = $1.nd;
    }
    |
    identifier
    {
        $$.nd = mknode("write_params");

        $$.nd->children[0] = $1.nd;

        for (int i = 0; i < count; i++) {
            char *name_copy = strdup(symbol_table[i].name);
            char *bracket_position = strchr(name_copy, '[');
            if (bracket_position != NULL) {
                *bracket_position = '\0';
            }
            if (strcmp(name_copy, $1.nd->children[0]->token) == 0) {
                if(symbol_table[i].is_assigned!=1){
                    sprintf(sem_errors[sem_error_count],"Line %d: Variable \"%s\" used before assignment\n",line_number+1,$1.nd->children[0]->token);
                    sem_error_count++;
                    break;
                }
                else{
                    $$.is_assigned = 1;
                }
            }
        }
    }
    |
    write_params COMMA T_STRING
    {
        $$.nd = mknode("write_params");

        $2.nd = mknode("COMMA");
        $2.nd->children[0] = mknode($2.name);

        $3.nd = mknode("STRING");
        $3.nd->children[0] = mknode($3.name);

        $$.nd->children[0] = $1.nd;
        $$.nd->children[0] = $2.nd;
        $$.nd->children[0] = $3.nd;
    }
    | 
    write_params COMMA identifier
    {
        $$.nd = mknode("write_params");

        $2.nd = mknode("COMMA");
        $2.nd->children[0] = mknode($2.name);

        $$.nd->children[0] = $1.nd;
        $$.nd->children[0] = $2.nd;
        $$.nd->children[0] = $3.nd;

        for (int i = 0; i < count; i++) {
            char *name_copy = strdup(symbol_table[i].name);
            char *bracket_position = strchr(name_copy, '[');
            if (bracket_position != NULL) {
                *bracket_position = '\0';
            }
            if (strcmp(name_copy, $3.nd->children[0]->token) == 0) {
                if(symbol_table[i].is_assigned!=1){
                    sprintf(sem_errors[sem_error_count],"Line %d: Variable \"%s\" used before assignment\n",line_number+1,$3.nd->children[0]->token);
                    sem_error_count++;
                    break;
                }
                else{
                    $$.is_assigned = 1;
                }
            }
        }
    }
;

read_statement:
    READ LPAREN identifier_or_array RPAREN
    {
        $$.nd = mknode("read_statement");

        $1.nd = mknode("READ");
        $1.nd->children[0] = mknode($1.name);

        $2.nd = mknode("LPAREN");
        $2.nd->children[0] = mknode($2.name);

        $4.nd = mknode("RPAREN");
        $4.nd->children[0] = mknode($4.name);

        $$.nd->children[0] = $1.nd;
        $$.nd->children[1] = $2.nd;
        $$.nd->children[2] = $3.nd;
        $$.nd->children[3] = $4.nd;

        for (int i = 0; i < count; i++) {
            char *name_copy = strdup(symbol_table[i].name);
            char *bracket_position = strchr(name_copy, '[');
            if (bracket_position != NULL) {
                *bracket_position = '\0';
            }
            if (strcmp(name_copy, $3.nd->children[0]->children[0]->token) == 0) {
                symbol_table[i].is_assigned = 1;
            }
        }

    }
;

%%

extern FILE *yyin;
FILE* output;
void printtree(struct node* head, int n, int depth, int child){
	
	if(head==NULL){
		return;
	}
	fprintf(output,"{");
	
	/* fprintf(output,"%s=%d:%d=", head->token, depth, child); */
	fprintf(output,"%s", head->token);
	for(int i=0; i<20; i++){
		printtree(head->children[i], n+1, depth+1, i);
	}
	fprintf(output,"}");
}

int main(int argc, char* argv[]) {
    char* filename = argv[1];
    FILE *input_file = fopen(filename, "r");
    yyin = input_file;
    yyparse();
    fclose(input_file);


    printf("Semantic Analysis completed with %d errors\n\n",sem_error_count);
    if(sem_error_count>0){
        for(int i=0;i<sem_error_count;i++){
            printf("%d) %s\n",i+1,sem_errors[i]);
        }
    }

    output = fopen("output.txt","w+");
    printtree(head, 1, 0, 0);
    fclose(output);
}

void yyerror(const char* msg) {
    fprintf(stderr, "%s\n", msg);
    fprintf(stderr, "Syntax error at token: %s\n", yytext);
    fprintf(stderr, "Error occurred at line: %d\n", yylineno);
    exit(1);
}