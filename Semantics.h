/* Semantics.h
   The action and supporting routines for performing semantics processing.
*/

/* Semantic Records */
struct IdList {
  struct SymEntry * TheEntry;
  struct IdList * Next;
};

struct ExprRes {
  int Reg;
  struct InstrSeq * Instrs;
};

struct ExprResList {
	struct ExprRes *Expr;
	struct ExprResList * Next;
};

//Branch expression
struct BExprRes {
  char * Label;
  struct InstrSeq * Instrs;
};


/* Semantics Actions */

//Loading Integer Load Immediate into a temp register.
extern struct ExprRes *  doIntLit(char * digits);

//Loading Data from data segment and variable name into a temp register.
extern struct ExprRes *  doRval(char * name);

//Stores data from a register into a variable in the data segment (represented by name).
extern struct InstrSeq *  doAssign(char * name,  struct ExprRes * Res1);
extern struct ExprRes *  doAdd(struct ExprRes * Res1,  struct ExprRes * Res2);
extern struct ExprRes * doSub(struct ExprRes * Res1, struct ExprRes * Res2);
extern struct ExprRes * doDiv(struct ExprRes * Res1, struct ExprRes * Res2);
extern struct ExprRes *  doMult(struct ExprRes * Res1,  struct ExprRes * Res2);
extern struct InstrSeq *  doPrint(struct ExprRes * Expr);
extern struct BExprRes * doBExpr (struct ExprRes * Res1,  struct ExprRes * Res2);
extern struct InstrSeq * doIf(struct BExprRes *bRes, struct InstrSeq * seq);

extern void	Finish(struct InstrSeq *Code);
