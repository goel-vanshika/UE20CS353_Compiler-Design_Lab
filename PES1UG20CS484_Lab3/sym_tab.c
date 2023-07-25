#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sym_tab.h"

table *init_table()
{
    /*
        allocate space for table pointer structure eg (t_name)* t
        initialise head variable eg t->head
        return structure
    */
    table *t = (table *)malloc(sizeof(table));
    t->head = NULL;
    return t;
}

symbol *init_symbol(char *name, int size, int type, int lineno, int scope) // allocates space for items in the list
{
    /*
        allocate space for entry pointer structure eg (s_name)* s
        initialise all struct variables(name, value, type, scope, length, line number)
        return structure
    */
    symbol *s = (symbol *)malloc(sizeof(symbol));
    s->name = name;
    s->size = size;
    s->type = type;
    s->val = "~";
    s->line = lineno;
    s->scope = scope;
    s->next = NULL;
    return s;
}

void insert_symbol(char* name, int size, int type, int lineno,int scope)	
/*
 arguments can be the structure s_name already allocated before this function call
 or the variables to be sent to allocate_space_for_table_entry for initialisation
*/

/*
        check if table is empty or not using the struct table pointer
        else traverse to the end of the table and insert the entry
*/
{
    symbol* s = init_symbol(name, size, type, lineno,scope);
    if (t->head == NULL)
    {
        t->head = s;
    }
    else
    {
        symbol *temp = t->head;
        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = s;
    }
    return;
}
int check_sym_tab(char *name) // return a value like integer for checking
{
    /*
        check if table is empty and return a value like 0
        else traverse the table
        if entry is found return a value like 1
        if not return a value like 0
    */

    symbol *temp = t->head;
    if (temp == NULL)
    {
        return 0;
    }
    while (temp != NULL)
    {
        if (strcmp(temp->name, name) == 0)
        {
            return 1;
        }
        temp = temp->next;
    }
    return 0;
}

int insert_val(char *name, char *value, int type)
{
    /*
        if value is default value return back
        check if table is empty
        else traverse the table and find the name
        insert value into the entry structure
    */

    symbol *temp = t->head;
    if (strcmp(value, "~") == 0)
    {
        return 0;
    }
    if (temp == NULL)
    {
        return 0;
    }
    while (temp != NULL)
    {
        if (strcmp(temp->name, name) == 0)
        {
            temp->val = value;
            temp->type = type;
            return 1;
        }
        temp = temp->next;
    }
    return 0;
}

void display_sym_tab()
{
    /*
        traverse through table and print every entry
        with its struct variables
    */

    printf("Name\tSize\tType\tLineno\tScope\tValue\n");
    symbol *temp = t->head;
    while (temp != NULL)
    {
        printf("%s\t%d\t%d\t%d\t%d\t%s\n", temp->name, temp->size, temp->type, temp->line, temp->scope, temp->val);
        temp = temp->next;
    }
}

char* retrieve_val(char* name)	//retrieves value from symbol table
{
	char* val="~";
	if(t->head == NULL)
	{
		return val;
	}
	symbol* temp = t->head;
	while(temp!=NULL)		//find variable name and insert
	{
		if(strcmp(temp->name,name)==0)
		{
			val=temp->val;
			return val;
		}	
		temp = temp->next;
	}
	return val;
}

int retrieve_type(char* name)	//retrieves type from symbol table
{
	int type=-1;
	if(t->head == NULL)
	{
		return type;
	}
	symbol* temp = t->head;
	while(temp!=NULL)		//find variable name and insert
	{
		if(strcmp(temp->name,name)==0)
		{
			type=temp->type;
			return type;
		}	
		temp = temp->next;
	}
	return type;
}

int type_check(char* value)		//checks the type from the value string
{
	char *s=strchr(value,'\"');	
	if(s!=NULL)
		return 1; 
	char *f=strchr(value,'.');	
	if(f!=NULL)
		return 3;
	return 2;			
}

int size(int type)
{
	if(type==3)
		return 4;
	if(type==4)
		return 8;
	return type;
}

