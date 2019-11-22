%{
#include "y.tab.h"

#define YY_INPUT(buf,result,max_size) \
	{ int c = get_source_char(); \
          result = (c == EOF) ? YY_NULL : (buf[0] = c, 1); \
        }

%}


letter [A-Za-z]
digit [0-9]

%%
if								{return IF;}
int								{return Int;}
print							{return Write;}
{letter}({letter}|{digit})*		{return Ident;}
{digit}{digit}*					{return IntLit;}
\=\=							{return EQ;}
\=								{return '=';}
\+								{return '+';}
\*								{return '*';}
\;								{return ';';}
\{								{return '{';}
\}								{return '}';}
\(								{return '(';}
\)								{return ')';}

[ ]								{}
\t								{}
\r								{}
\n								{}

.								{write_indicator(get_current_column());
				   					write_message("Illegal Character in lex");}

%%

	
int yywrap () {
}
			

