#ifndef SCANNER
#define SCANNER
#include "TokenType.h"
#include "Token.h"
#include "TableIdent.h"


class Scanner
{
	enum         state { H, IDENT, NUMB, COM, ALE, DELIM, NEQ, Z };
	static char       * TW[];
	static type_of_token  words[];
	static char       * TD[];
	static type_of_token  dlms[];
	state        CS;
	FILE       * fp;
	Table_ident* TID;
	char         c;
	char         buf[80];
	int          buf_top;
	void         clear();
	void         add();
	int          look(const char *buf, char **list);
	void         gc();
public:
	Scanner(const char * program);
	Token    get_token();
	Table_ident* getTID();
};

#endif
