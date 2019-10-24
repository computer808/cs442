all: lex compilation

lex:
	lex lex1.l

compilation:
	gcc lex.yy.c -o lex IOManager/IOMngr.c symbolTable/symTab.c -I symbolTable/ -I IOManager/ -Wno-implicit-function-declaration

clean:
	rm lex.yy.c && rm lex