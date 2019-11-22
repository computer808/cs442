all: yacc lex compilation

yacc:
	yacc -d ExprEval.y

lex:
	lex lex1.l


compilation:
	gcc main.c -o driver y.tab.c IOManager/IOMngr.c symbolTable/symTab.c Semantics.c CodeGen.c -I symbolTable/ -I IOManager/ -Wno-implicit-function-declaration

clean:
	rm lex.yy.c && rm y.tab.c && rm driver