#ifndef IDENT_H
#define IDENT_H
#include "Variable.h"
#include "TokenType.h"

class Ident
{
	char			*name;
	bool		    declare;
	type_of_token	type;
	bool			assign;
	Variable		value;
public:
	Ident();
	char*           get_name();
	void			put_name(const char *n);
	bool			get_declare();
	void			put_declare();
	type_of_token	get_type();
	void			put_type(type_of_token t);
	bool			get_assign();
	void			put_assign() ;
	Variable		get_value() ;
	void			put_value(Variable& v);
};

#endif