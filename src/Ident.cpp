#define _CRT_SECURE_NO_WARNINGS
#include "../include/Ident.h"
#include <string.h>

Ident::Ident() { declare = false; assign = false; }
char   *Ident::get_name() { return name; }
void   Ident::put_name(const char *n){
	name = new char[strlen(n) + 1];
	strcpy(name, n);
}
bool         Ident::get_declare() { return declare; }
void         Ident::put_declare() { declare = true; }
type_of_token  Ident::get_type() { return type; }
void         Ident::put_type(type_of_token t) { type = t; }
bool         Ident::get_assign() { return assign; }
void         Ident::put_assign() { assign = true; }
Variable        Ident::get_value() { return value; }
void         Ident::put_value(Variable& v) { value = v; }
