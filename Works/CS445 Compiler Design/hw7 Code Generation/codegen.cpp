/* codegen.cpp
 * 
 * Miguel Villanueva
 * CS 445
 * May 9, 2021
 */

#include "codegen.h"
#include "semantic.h"
using namespace std;

// Globals
int toffset = 0;	// Temporary offset
bool inCall = false;	// Condition for parameters in CallK
int paramCount = 1;	// For counting number of parameters in CallK
TreeNode *id = NULL;	// For remembering an IdK node
bool inAssign = false;	// Condition for parameters in AssignK
bool inIntInt = false;  // Condition for constants in IntInt AssignK
bool onLHS = false;	// For tracking LHS
bool inIf = false;	// For id in IfK
bool inWhile = false;	// For id in WhileK
TreeNode *lhs = NULL;	// For remembering a LHS IdK node
stack<int> breakLoop;	// Stack for breaks
stack<int> startLoop;	// Stack for loop start
stack<bool> callStack;	// Stack for CallK parameters
bool inReturn1 = false;	// Condition for ReturnK
int parameters = 0;
bool inArray = false;

// Initialize Globals and Statics
void initGS(std::string s, void *ptr)
{
    TreeNode *node;
    node = (TreeNode *) ptr;
    if(node->subkind.decl == VarK)
    {
	if(node->isArray)
	{
	    emitRM((char *)"LDC", AC, node->size - 1, AC3, (char *)"Load size of array", node->attr.name);
	    emitRM((char *)"ST", AC, node->loc + 1, GP, (char *)"Save size of array", node->attr.name);
	}
	else if(node->child[0] != NULL && node->child[0]->subkind.exp == ConstantK)
	{
	    if(node->child[0]->expType == Integer)
		emitRM((char *)"LDC", AC, node->child[0]->attr.value, AC3, (char *)"Load integer constant");
	    else if(node->child[0]->expType == Boolean)
                emitRM((char *)"LDC", AC, node->child[0]->attr.value, AC3, (char *)"Load boolean constant");
	    else if(node->child[0]->expType == Char)
                emitRM((char *)"LDC", AC, node->child[0]->attr.cvalue, AC3, (char *)"Load char constant");
	    emitRM((char *)"ST", AC, node->loc, GP, (char *)"Store variable ga", node->attr.name); 
	}
    }
}

//  Traverses syntax tree, to emit TM code
void codegen(TreeNode *tree, SymbolTable *table)
{
    TreeNode *node;	// For global lookups	
    int remember;	// For remembering toffset and if location
    int rememberElse;	// For remembering else location

    while(tree != NULL)
    {
	if(tree->nodekind == DeclK)
	{
	    switch(tree->subkind.decl)
	    {
		case VarK:
		    if(tree->isArray && tree->mem == Local)
		    {
			emitRM((char *)"LDC", AC, tree->size - 1, AC3, (char *)"Load size of array", tree->attr.name);
            		emitRM((char *)"ST", AC, tree->loc + 1, FP, (char *)"Save size of array", tree->attr.name);
		    }

		    //  Traverse
                    codegen(tree->child[0], table);
		    if(tree->child[0] != NULL)
			emitRM((char *)"ST", AC, tree->loc, FP, (char *)"Store variable), tree->attr.name");
                    codegen(tree->child[1], table);
                    codegen(tree->child[2], table);
		    break;
		case FuncK:
		    tree->loc = emitSkip(0);
		    emitComment((char *)"");
    		    emitComment((char *)"** ** ** ** ** ** ** ** ** ** ** **");
		    emitComment((char *)"FUNCTION", tree->attr.name);
		    toffset = tree->size;
                    emitComment((char *)"TOFF set:", toffset);
		    emitRM((char *)"ST", AC, -1, FP, (char *)"Store return address");
		    if(tree->child[1] != NULL && tree->child[1]->subkind.stmt == CompoundK)
			tree->child[1]->compoundFlag = true;

    		    //  Traverse
		    codegen(tree->child[0], table);
                    codegen(tree->child[1], table);
                    codegen(tree->child[2], table);

		    toffset = tree->size;
                    emitComment((char *)"TOFF set:", toffset);
		    // Maybe something here
		    emitComment((char *)"END COMPOUND");
		    emitComment((char *)"Add standard closing in case there is no return statement");
		    emitRM((char *)"LDC", RT, 0, AC3, (char *)"Set return value to 0");
		    emitRM((char *)"LD", AC, -1, FP, (char *)"Load return address");
		    emitRM((char *)"LD", FP, 0, FP, (char *)"Adjust fp");
		    emitGoto(0, AC, (char *)"Return");
		    emitComment((char *)"END FUNCTION", tree->attr.name);
		    break;
		case ParamK:
		    //  Traverse
		    codegen(tree->child[0], table);
                    codegen(tree->child[1], table);
                    codegen(tree->child[2], table);
		    break;
		default:
		    printf("Unknown DeclNode kind");
		    break;
	    }
	}
	else if(tree->nodekind == StmtK)
	{
            switch(tree->subkind.stmt)
            {
		case IfK:
		    inIf = true;
		    emitComment((char *)"IF");
		    //  Traverse
		    codegen(tree->child[0], table);
		    remember = emitSkip(1);
		    emitComment((char *)"THEN");
                    codegen(tree->child[1], table);
		    if(tree->child[2] != NULL)
		    {
			emitComment((char *)"ELSE");
			rememberElse = emitSkip(1);
		    }
		    backPatchAJumpToHere((char *)"JZR", AC, remember, (char *)"Jump around the THEN if false [backpatch]");
                    codegen(tree->child[2], table);
		    if(tree->child[2] != NULL)
			backPatchAJumpToHere((char *)"JMP", PC, rememberElse, (char *)"Jump around the ELSE [backpatch]");
		    emitComment((char *)"END IF");
		    inIf = false;
		    break;
		case WhileK:
		    inWhile = true;
		    remember = toffset;
		    emitComment((char *)"WHILE");
		    startLoop.push(emitSkip(0));
		    //  Traverse
		    codegen(tree->child[0], table);
		    emitRM((char *)"JNZ", AC, 1, PC, (char *)"Jump to while part");
		    breakLoop.push(emitSkip(1));

		    emitComment((char *)"DO");
                    codegen(tree->child[1], table);
		    emitGotoAbs(startLoop.top(), (char *)"Go to beginning of loop");
		    backPatchAJumpToHere((char *)"JMP", PC, breakLoop.top(), (char *)"Jump past loop [backpatch]");

		    breakLoop.pop();
		    startLoop.pop();
		    emitComment((char *)"END WHILE");
		    inWhile = false;
		    break;
		case ForK:
		    //  Traverse
		    codegen(tree->child[0], table);
                    codegen(tree->child[1], table);
                    codegen(tree->child[2], table);
		    break;
		case CompoundK:
		    emitComment((char *)"COMPOUND");
		    toffset = tree->size;
		    emitComment((char *)"TOFF set:", toffset);

		    //  Traverse
		    codegen(tree->child[0], table);
		    emitComment((char *)"Compound Body");
                    codegen(tree->child[1], table);
                    codegen(tree->child[2], table);

		    if(!tree->compoundFlag)
		    {
			toffset = tree->size;
			emitComment((char *)"TOFF set:", toffset);
			emitComment((char *)"END COMPOUND");
		    }
		    break;
		case ReturnK:
		    inReturn1 = true;
		    emitComment((char *)"RETURN");

		    //  Traverse
		    codegen(tree->child[0], table);
		    if(tree->child[0] != NULL)
		    {
			/*if(tree->child[0]->subkind.exp == IdK)
			{
			    node = tree->child[0];
			    if(node->isArray)
                            {
                        	if(node->mem == Global)
                            	    emitRM((char *)"LDA", AC, node->loc, GP, (char *)"Load address of base array", node->attr.name);
                            	else if(node->mem == Local)
                                    emitRM((char *)"LDA", AC, node->loc, FP, (char *)"Load address of base array", node->attr.name);
                            	else if(node->mem == Parameter)
                                    emitRM((char *)"LD", AC, node->loc, FP, (char *)"Load address of base array", node->attr.name);
                            	emitRM((char *)"ST", AC, toffset, FP, (char *)"Push left side");
                            	toffset -= 1;
                            	emitComment((char *)"TOFF dec:", toffset);
                            }
                            else if(node->mem == Local || node->mem == Parameter)
                            	emitRM((char *)"LD", AC, node->loc, FP, (char *)"Load variable", node->attr.name);
                            else if(node->mem == Global || node->mem == LocalStatic)
                            	emitRM((char *)"LD", AC, node->loc, GP, (char *)"Load variable", node->attr.name);
			}*/
			emitRM((char *)"LDA", RT, 0, AC, (char *)"Copy result to return register");
		    }
                    codegen(tree->child[1], table);
                    codegen(tree->child[2], table);

		    emitRM((char *)"LD", AC, -1, FP, (char *)"Load return address");
                    emitRM((char *)"LD", FP, 0, FP, (char *)"Adjust fp");
                    emitGoto(0, AC, (char *)"Return");
		    inReturn1 = false;
		    break;
		case BreakK:
		    emitComment((char *)"BREAK");
		    emitGotoAbs(breakLoop.top(), (char *)"Break");
		    break;
		case RangeK:
		    //  Traverse
		    codegen(tree->child[0], table);
                    codegen(tree->child[1], table);
                    codegen(tree->child[2], table);
		    break;
		default:
                    printf("Unknown StmtNode kind");
                    break;
            }
	}
	else if(tree->nodekind == ExpK)
	{
            switch(tree->subkind.exp)
            {
		case OpK:
		    if(tree->arrayOp)
		    {
			inArray = true;
			if(tree->child[0]->subkind.exp = IdK)
			{
			    id = tree->child[0];
			    if(onLHS)
				lhs = tree->child[0];
			    if(inIntInt)
			    {
				if(id->mem == Global)
				    emitRM((char *)"LDA", AC, id->loc, GP, (char *)"Load address of base of array", id->attr.name);
				else if(id->mem == Local)
				    emitRM((char *)"LDA", AC, id->loc, FP, (char *)"Load address of base of array", id->attr.name);
				emitRM((char *)"ST", AC, toffset, FP, (char *)"Push left side");
				toffset -= 1;
                        	emitComment((char *)"TOFF dec:", toffset);
			    }
			}
		    }

		    //  Traverse
		    codegen(tree->child[0], table);
		    if(!tree->unary && !tree->arrayOp && !inAssign && !inWhile)
		    {
			emitRM((char *)"ST", AC, toffset, FP, (char *)"Push left side");
			toffset -= 1;
                    	emitComment((char *)"TOFF dec:", toffset);
		    }
		    else if(!tree->unary && !tree->arrayOp && (inAssign || inWhile))
		    {
			if(tree->child[0]->subkind.exp == IdK)
                        {
                            if(tree->child[0]->mem == Global)
                                emitRM((char *)"LD", AC, tree->child[0]->loc, GP, (char *)"Load variable",
                                        tree->child[0]->attr.name);
                            else if(tree->child[0]->mem == Local)
                                emitRM((char *)"LD", AC, tree->child[0]->loc, FP, (char *)"Load variable",
                                        tree->child[0]->attr.name);
                        }
                        emitRM((char *)"ST", AC, toffset, FP, (char *)"Push left side");
                        toffset -= 1;
                        emitComment((char *)"TOFF dec:", toffset);
		    }

                    codegen(tree->child[1], table);
		    if(tree->child[1] != NULL && !tree->arrayOp)
		    {
			toffset += 1;
                	emitComment((char *)"TOFF inc:", toffset);
			emitRM((char *)"LD", AC1, toffset, FP, (char *)"Pop left into ac1");
		    }
		    else if(tree->child[1] != NULL && tree->arrayOp && !inCall && !inIntInt && !inReturn1 && !inIf)
		    {
			if(tree->child[1]->subkind.exp == IdK)
			    emitRM((char *)"LD", AC, tree->child[1]->loc, FP, (char *)"Store variable", tree->child[1]->attr.name);
			emitRM((char *)"ST", AC, toffset, FP, (char *)"Push index");
			toffset--;
			emitComment((char *)"TOFF dec:", toffset);
		    }
		    else if(tree->child[1] != NULL && tree->arrayOp && !inCall && (inIntInt || inReturn1 || inIf))
		    {
			toffset += 1;
                        emitComment((char *)"TOFF inc:", toffset);
                        emitRM((char *)"LD", AC1, toffset, FP, (char *)"Pop left into ac1");
                        emitRO((char *)"SUB", AC, AC1, AC, (char *)"Compute location from index");
                        emitRM((char *)"LD", AC, GP, AC, (char *)"Load array element");
		    }
		    else if(tree->child[1] != NULL && tree->arrayOp && inCall && !inAssign)
		    {
			toffset += 1;
                        emitComment((char *)"TOFF inc:", toffset);
                        emitRM((char *)"LD", AC1, toffset, FP, (char *)"Pop left into ac1");
			emitRO((char *)"SUB", AC, AC1, AC, (char *)"Compute location from index");
			emitRM((char *)"LD", AC, GP, AC, (char *)"Load array element");

			if(parameters > 1)
			{
			    parameters--;
			    emitRM((char *)"ST", AC, toffset, FP, (char *)"Push parameter");
			}
		    }

		    if(tree->attr.op == 292)                                    // Negative (CHSIGN)
                        emitRO((char *)"NEG", AC, AC, AC, (char *)"Op unary -");
		    else if(tree->attr.op == 293)				// Size of
			emitRM((char *)"LD", AC, FP, AC, (char *)"Load array size");
		    else if(tree->attr.op == 275)				// Not
		    {
			emitRM((char *)"LDC", AC1, 1, AC3, (char *)"Load 1");
			emitRO((char *)"XOR", AC, AC, AC1, (char *)"Op XOR to get logical not");
		    }
		    else if(tree->attr.op == 273)				// And
			emitRO((char *)"AND", AC, AC1, AC, (char *)"Op AND");
		    else if(tree->attr.op == 274)				// Or
			emitRO((char *)"OR", AC, AC1, AC, (char *)"Op OR");
		    else if(strcmp(tree->attr.name, (char *)"?") == 0)          // Question Mark
                        emitRO((char *)"RND", AC, AC, AC3, (char *)"Op ?");
		    else if(strcmp(tree->attr.name, (char *)"==") == 0)         // ==
                        emitRO((char *)"TEQ", AC, AC1, AC, (char *)"Op ==");
		    else if(strcmp(tree->attr.name, (char *)">") == 0)         	// Greater Than
                        emitRO((char *)"TGT", AC, AC1, AC, (char *)"Op >");
		    else if(strcmp(tree->attr.name, (char *)"<") == 0)          // Less Than
                        emitRO((char *)"TLT", AC, AC1, AC, (char *)"Op <");
		    else if(strcmp(tree->attr.name, (char *)"!=") == 0)         // NEQ
                        emitRO((char *)"TNE", AC, AC1, AC, (char *)"Op !=");
		    else if(strcmp(tree->attr.name, (char *)">=") == 0)         // GEQ
                        emitRO((char *)"TGE", AC, AC1, AC, (char *)"Op >=");
		    else if(strcmp(tree->attr.name, (char *)"<=") == 0)         // LEQ
                        emitRO((char *)"TLE", AC, AC1, AC, (char *)"Op <=");
		    else if(strcmp(tree->attr.name, (char *)"*") == 0)		// Multiply
			emitRO((char *)"MUL", AC, AC1, AC, (char *)"Op *");
		    else if(strcmp(tree->attr.name, (char *)"/") == 0)          // Division
                        emitRO((char *)"DIV", AC, AC1, AC, (char *)"Op /");
		    else if(strcmp(tree->attr.name, (char *)"+") == 0)          // Add
                        emitRO((char *)"ADD", AC, AC1, AC, (char *)"Op +");
		    else if(strcmp(tree->attr.name, (char *)"-") == 0)          // Subtraction
                        emitRO((char *)"SUB", AC, AC1, AC, (char *)"Op -");
		    else if(strcmp(tree->attr.name, (char *)"%") == 0)          // Mod
                        emitRO((char *)"MOD", AC, AC1, AC, (char *)"Op %");
		    inArray = false;
		    break;
		case ConstantK:
		    if(tree->expType == Integer)
			emitRM((char *)"LDC", AC, tree->attr.value, AC3, (char *)"Load integer constant");
		    else if(tree->expType == Boolean)
			emitRM((char *)"LDC", AC, tree->attr.value, AC3, (char *)"Load boolean constant");
		    else if(tree->expType == Char)
			emitRM((char *)"LDC", AC, tree->attr.cvalue, AC3, (char *)"Load char constant");
		    
		    if(inCall && parameters > 1 && !inArray)
		    {
			parameters--;
			//if(tree != NULL && !tree->child[0]->isArray)
                        emitRM((char *)"ST", AC, toffset, FP, (char *)"Push parameter");
                    	//if(tree->child[0] == NULL || (tree->child[0] != NULL && !tree->child[0]->isArray))
                    	//{
                        //    toffset -= 1;
                        //    emitComment((char *)"TOFF dec:", toffset);
                    	//}
		    }
		    //if(inCall && parameters > 1 && inArray)
			//parameters--;
		    break;
		case IdK:
		    if((inCall && !inAssign) || inIf || inReturn1)
		    {
			if(tree->isArray)
			{
			    if(tree->mem == Global)
			        emitRM((char *)"LDA", AC, tree->loc, GP, (char *)"Load address of base array", tree->attr.name);
			    else if(tree->mem == Local)
                                emitRM((char *)"LDA", AC, tree->loc, FP, (char *)"Load address of base array", tree->attr.name);
			    else if(tree->mem == Parameter)
				emitRM((char *)"LD", AC, tree->loc, FP, (char *)"Load address of base array", tree->attr.name);
			    emitRM((char *)"ST", AC, toffset, FP, (char *)"Push left side");
			    if(inArray)
			    {
				toffset -= 1;
                    		emitComment((char *)"TOFF dec:", toffset);
			    }
			}
			else if(tree->mem == Local || tree->mem == Parameter)
			    emitRM((char *)"LD", AC, tree->loc, FP, (char *)"Load variable", tree->attr.name);
			else if(tree->mem == Global || tree->mem == LocalStatic)
			    emitRM((char *)"LD", AC, tree->loc, GP, (char *)"Load variable", tree->attr.name);
		    }
		    break;
		case AssignK:
		    inAssign = true;
		    if(!inCall)
		    	emitComment((char *)"EXPRESSION");

		    //  Traverse
		    onLHS = true;
		    codegen(tree->child[0], table);
		    onLHS = false;
		    if(tree->intInt)
			inIntInt = true;
                    codegen(tree->child[1], table);
		    inIntInt = false;
                    codegen(tree->child[2], table);

		    if(tree->unary)
                    {
                        if(tree->child[0]->mem == Global)
                            emitRM((char *)"LD", AC, tree->child[0]->loc, GP, (char *)"Load lhs variable", tree->child[0]->attr.name);
                        else if(tree->child[0]->mem == Local)
                            emitRM((char *)"LD", AC, tree->child[0]->loc, FP, (char *)"Load lhs variable", tree->child[0]->attr.name);
			else if(tree->child[0]->arrayOp)
			{
			    if(id->mem == Global)
				emitRM((char *)"LDA", AC2, id->loc, GP, (char *)"Load address of base of array", id->attr.name);
			    else if(id->mem == Local)
				emitRM((char *)"LDA", AC2, id->loc, FP, (char *)"Load address of base of array", id->attr.name);
			    else if(id->mem == Parameter)
				emitRM((char *)"LD", AC2, id->loc, FP, (char *)"Load address of base of array", id->attr.name);
                            emitRO((char *)"SUB", AC2, AC2, AC, (char *)"Compute offset of value");
			    if(id->mem == Global)
                        	emitRM((char *)"LD", AC, 0, AC2, (char *)"Load lhs variable", id->attr.name);
                            else if(id->mem == Local || id->mem == Parameter)
                        	emitRM((char *)"LD", AC, 0, AC2, (char *)"Load lhs variable", id->attr.name);
			}

                        if(strcmp(tree->attr.name, (char *)"++") == 0)
			{
			    if(tree->child[0]->arrayOp)
                                emitRM((char *)"LDA", AC, 1, AC, (char *)"increment value of", id->attr.name);
			    else if(!tree->child[0]->arrayOp)
                        	emitRM((char *)"LDA", AC, 1, AC, (char *)"increment value of", tree->child[0]->attr.name);
			}
                        if(strcmp(tree->attr.name, (char *)"--") == 0)
			{
			    if(tree->child[0]->arrayOp)
                                emitRM((char *)"LDA", AC, -1, AC, (char *)"decrement value of", id->attr.name);
			    else if(!tree->child[0]->arrayOp)
                        	emitRM((char *)"LDA", AC, -1, AC, (char *)"decrement value of", tree->child[0]->attr.name);
			}
                    }
		    else if(tree->intInt)
		    {
			if(tree->child[1]->mem == Global)
			    emitRM((char *)"LD", AC, tree->child[1]->loc, GP, (char *)"Load variable", tree->child[1]->attr.name);
			else if(tree->child[1]->mem == Local)
			    emitRM((char *)"LD", AC, tree->child[1]->loc, FP, (char *)"Load variable", tree->child[1]->attr.name);
			if(tree->child[0]->mem == Global)
			    emitRM((char *)"LD", AC1, tree->child[0]->loc, GP, (char *)"Load lhs variable", tree->child[0]->attr.name);
			else if(tree->child[0]->mem == Local)
			    emitRM((char *)"LD", AC1, tree->child[0]->loc, FP, (char *)"Load lhs variable", tree->child[0]->attr.name);

			if(tree->child[0]->arrayOp)
			{
			    toffset += 1;
                            emitComment((char *)"TOFF inc:", toffset);
                            emitRM((char *)"LD", AC1, toffset, FP, (char *)"Pop index");
                            if(lhs->mem == Global)
                        	emitRM((char *)"LDA", AC2, lhs->loc, GP, (char *)"Load address of base of array", lhs->attr.name);
                            else if(lhs->mem == Local)
                        	emitRM((char *)"LDA", AC2, lhs->loc, FP, (char *)"Load address of base of array", lhs->attr.name);
                            emitRO((char *)"SUB", AC2, AC2, AC1, (char *)"Compute offset of value");
			    if(lhs->mem == Global)
                                emitRM((char *)"LD", AC1, 0, AC2, (char *)"Load lhs variable", lhs->attr.name);
                            else if(lhs->mem == Local ||lhs->mem == Parameter)
                                emitRM((char *)"LD", AC1, 0, AC2, (char *)"Load lhs variable", lhs->attr.name);
			}

			if(strcmp(tree->attr.name, (char *)"+=") == 0)
			    emitRO((char *)"ADD", AC, AC1, AC, (char *)"Op +=");
			else if(strcmp(tree->attr.name, (char *)"-=") == 0)
                            emitRO((char *)"SUB", AC, AC1, AC, (char *)"Op -=");
			else if(strcmp(tree->attr.name, (char *)"*=") == 0)
                            emitRO((char *)"MUL", AC, AC1, AC, (char *)"Op *=");
			else if(strcmp(tree->attr.name, (char *)"/=") == 0)
                            emitRO((char *)"DIV", AC, AC1, AC, (char *)"Op /=");
		    }
		    else if(tree->equals && tree->child[1]->subkind.exp == IdK)
		    {
			if(tree->child[1]->mem == Local)
                            emitRM((char *)"LD", AC, tree->child[1]->loc, FP, (char *)"Load variable", tree->child[1]->attr.name);
                        else if(tree->child[1]->mem == Global || tree->child[1]->mem == LocalStatic)
                            emitRM((char *)"LD", AC, tree->child[1]->loc, GP, (char *)"Load variable", tree->child[1]->attr.name);
		    }

		    if(tree->child[0]->mem == Local || tree->child[0]->mem == Parameter)
			emitRM((char *)"ST", AC, tree->child[0]->loc, FP, (char *)"Store variable", tree->child[0]->attr.name);
		    else if(tree->child[0]->mem == Global || tree->child[0]->mem == LocalStatic)
			emitRM((char *)"ST", AC, tree->child[0]->loc, GP, (char *)"Store variable", tree->child[0]->attr.name);
		    else if(tree->child[0]->arrayOp && !tree->unary && !tree->intInt)
		    {
			toffset += 1;
                        emitComment((char *)"TOFF inc:", toffset);
			emitRM((char *)"LD", AC1, toffset, FP, (char *)"Pop index");
			if(id->mem == Global)
			    emitRM((char *)"LDA", AC2, id->loc, GP, (char *)"Load address of base of array", id->attr.name);
			else if(id->mem == Local)
			    emitRM((char *)"LDA", AC2, id->loc, FP, (char *)"Load address of base of array", id->attr.name);
			emitRO((char *)"SUB", AC2, AC2, AC1, (char *)"Compute offset of value");
			emitRM((char *)"ST", AC, GP, AC2, (char *)"Store variable", id->attr.name); 
		    }
		    else if(tree->child[0]->arrayOp && (tree->unary || tree->intInt))
		    {
			emitRM((char *)"ST", AC, 0, AC2, (char *)"Store variable", lhs->attr.name);
		    }
		    id = NULL;
		    lhs = NULL;
		    inAssign = false;

		    break;
		case CallK:
		    callStack.push(true);
		    inCall = true;
		    if(!inAssign && callStack.size() == 1)
			emitComment((char *)"EXPRESSION");
		    if(callStack.size() > 1)
			paramCount = 1;
		    emitComment((char *)"CALL", tree->attr.name);
		    emitRM((char *)"ST", FP, toffset, FP, (char *)"Store fp in ghost frame for", tree->attr.name);
		    remember = toffset;
		    toffset -= 1;
		    emitComment((char *)"TOFF dec:", toffset);
		    parameters = countParams(tree->child[0]);
		    if(tree->child[0] != NULL)
		    {
			toffset -= 1;
                        emitComment((char *)"TOFF dec:", toffset);
                        emitComment((char *)"Param", paramCount);
                        paramCount++;
                    }

		    //  Traverse
		    codegen(tree->child[0], table);
		    if(tree->child[0] != NULL && !tree->child[0]->isArray)
		    	emitRM((char *)"ST", AC, toffset, FP, (char *)"Push parameter");
		    if(tree->child[0] == NULL || (tree->child[0] != NULL && !tree->child[0]->isArray))
		    {
                 	toffset -= 1;
                	emitComment((char *)"TOFF dec:", toffset);
		    }
		    emitComment((char *)"Param end", tree->attr.name);
		    paramCount = 1;
		    inCall = false;
		    callStack.pop();

		    emitRM((char *)"LDA", FP, remember, FP, (char *)"Ghost frame becomes new active frame");
		    emitRM((char *)"LDA", AC, 1, PC, (char *)"Return address in ac");
		    node = (TreeNode *) table->lookupGlobal(tree->attr.name);
		    emitGotoAbs(node->loc, (char *)"CALL", tree->attr.name);
		    emitRM((char *)"LDA", AC, 0, RT, (char *)"Save the result in ac");

		    emitComment((char *)"Call end", tree->attr.name);
		    toffset = remember;
		    emitComment((char *)"TOFF set:", toffset);
		    break;
		default:
                    printf("Unknown ExpNode kind");
                    break;
            }
	}
	else
	{
	   printf("Unknown node kind\n");
	}
	if(inCall && tree->sibling != NULL)
        {
	    toffset -= 1;
            emitComment((char *)"TOFF dec:", toffset);
            emitComment((char *)"Param", paramCount);
            paramCount++;
	    /*tree = tree->sibling;
	    if(inCall && tree->sibling != NULL)
            {
            	if(tree != NULL && !tree->isArray)
                    emitRM((char *)"ST", AC, toffset, FP, (char *)"Push parameter");
            	if(tree == NULL || (tree != NULL && !tree->isArray))
            	{
                    toffset -= 1;
                    emitComment((char *)"TOFF dec:", toffset);
            	}
            }*/
        }
	//else
    	tree = tree->sibling;
    } /* END OF WHILE LOOP */
} /* END OF FUNCTION */


//  Traverses I/O Library tree, to emit TM code
void codegenIO(TreeNode *tree)
{
    while(tree != NULL)
    {
	if(tree->subkind.decl == FuncK)
	{
	    tree->loc = emitSkip(0);
	    emitIO(tree);
	}
	tree = tree->sibling;
    } /* END OF WHILE LOOP */
} /* END OF FUNCTION */

//  Emits TM code for a given I/O Library tree node
void emitIO(TreeNode *n)
{
    emitComment((char *)"");
    emitComment((char *)"** ** ** ** ** ** ** ** ** ** ** **");
    emitComment((char *)"FUNCTION", n->attr.name);

    //  Remember where this function is
    n->loc = emitSkip(0);

    //  Store return address
    //emitRM((char *)"ST", AC, RETURNOFFSET, FP, (char *)"Store return address");
    emitRM((char *)"ST", AC, -1, FP, (char *)"Store return address");

    //  Do the body of the IO function
    if(strcmp(n->attr.name, (char *)"input") == 0)
	emitRO((char *)"IN", RT, RT, RT, (char *)"Grab int input");
    else if(strcmp(n->attr.name, (char *)"inputb") == 0)
	emitRO((char *)"INB", RT, RT, RT, (char *)"Grab bool input");
    else if(strcmp(n->attr.name, (char *)"inputc") == 0)
	emitRO((char *)"INC", RT, RT, RT, (char *)"Grab char input");
    else if(strcmp(n->attr.name, (char *)"output") == 0)
    {
	emitRM((char *)"LD", AC, -2, FP, (char *)"Load parmater");
	emitRO((char *)"OUT", AC, AC, AC, (char *)"Output integer");
	//emitRM((char *)"LDC", RT, 0, 6, (char *)"Set return to 0");
    }
    else if(strcmp(n->attr.name, (char *)"outputb") == 0)
    {
        emitRM((char *)"LD", AC, -2, FP, (char *)"Load parmater");
        emitRO((char *)"OUTB", AC, AC, AC, (char *)"Output bool");
        //emitRM((char *)"LDC", RT, 0, 6, (char *)"Set return to 0");
    }
    else if(strcmp(n->attr.name, (char *)"outputc") == 0)
    {
        emitRM((char *)"LD", AC, -2, FP, (char *)"Load parmater");
        emitRO((char *)"OUTC", AC, AC, AC, (char *)"Output char");
        //emitRM((char *)"LDC", RT, 0, 6, (char *)"Set return to 0");
    }
    else if(strcmp(n->attr.name, (char *)"outnl") == 0)
	emitRO((char *)"OUTNL", AC, AC, AC, (char *)"Output a newline");
    else
    {
	emitComment((char *)"ERROR(LINKER): No support for special function");
	emitComment(n->attr.name);
    }

    //  Do return code for IO function
    //emitRM((char *)"LD", AC, RETURNOFFSET, FP, (char *)"Load return address");
    emitRM((char *)"LD", AC, -1, FP, (char *)"Load return address");
    //emitRM((char *)"LD", FP, OFPOFF, FP, (char *)"Adjust fp");
    emitRM((char *)"LD", FP, 0, FP, (char *)"Adjust fp");
    emitGoto(0, AC, (char *)"Return");

    emitComment((char *)"END FUNCTION", n->attr.name);
}
