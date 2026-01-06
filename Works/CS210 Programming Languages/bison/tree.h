/* tree.h 
 *
 * Miguel Villanueva
 * CS 210
 */

struct node
{
    int symbol;
    union
    {
	struct leaf
	{
	    char *lexeme;
	    int val;
	} t;
	struct nonleaf
	{
	    int production_rule;
	    struct node *child[9];
	} nt;			
    } u;
};

struct node *treenode(int symbol);
struct node *alcleaf(int symbol, char *lexeme);
struct node *alcnary(int symbol, int prodrule, int nkids, ...);
void printTree(struct node *np);
