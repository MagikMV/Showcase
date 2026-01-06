/* prodrules.h
 *
 * Miguel Villanueva 
 * CS 210
 */

#define OBJ       1000
#define OBJ_R1    1001  /* LCURLY RCURLY */
#define OBJ_R2    1002  /* LCURLY members RCURLY */
#define MEMS      2000 
#define MEMS_R1   2001  /* member */
#define MEMS_R2   2002  /* member COMMA members */
#define MEM       3000  
#define MEM_R1    3001  /* STRINGLIT COLON element */
#define ARY       4000
#define ARY_R1    4001  /* LBRACKET RBRACKET */
#define ARY_R2    4002  /* LBRACKET elements RBRACKET */
#define ELMS      5000 
#define ELMS_R1   5001  /* element */
#define ELMS_R2   5002  /* element COMMA elements */
#define ELM       6000
#define ELM_R1    6001  /* value */
#define VAL       7000
#define VAL_R1    7001  /* object */
#define VAL_R2    7003  /* array */
#define VAL_R3    7004  /* STRINGLIT */
#define VAL_R4    7005  /* NUMBER */
#define VAL_R5    7006  /* TRUE */
#define VAL_R6    7007  /* FALSE */
#define VAL_R7    7008  /* null */

