#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dict.h"


void addtree(Treeptr* p, char *w, int code)    				/* Insert word w into tree p */
{ 
	int cond;
  	if (*p == NULL) {                              			/* If tree is empty */
    		*p = malloc(sizeof(Treenode));    			/* Allocate space for new node */
		(*p)->word = malloc((strlen(w)+1) * sizeof(char));	/* Allocate space to copy word */
    		strcpy((*p)->word, w);                 			/* Copy word w to tree node */
    		(*p)->code=code;
    		(*p)->left = NULL;            				/* Left subtree of new node is empty */
		(*p)->right = NULL;          				/* Right subtree of new node is empty*/ 
	}
 	else if ((cond = strcmp(w, (*p)->word)) < 0)			/* Does word w precede word of current node?  */
    		addtree(&(*p)->left, w,code);				/* If yes, insert it into left subtree */
  	else if (cond > 0)       					/* Does it follow word of current node?  */
    		addtree(&(*p)->right, w,code);				/* If yes, insert it into right subtree */
  							/* If it is the same with word of current node, do not insert it */
}

int treesearch(Treeptr p, char *w)			/* Check whether word w is in tree p*/
{ 
	int cond;
  	if (p == NULL)                  		/* If tree is empty*/
		return 0;                            	/* We did't find word*/
	if ((cond = strcmp(w, p->word)) == 0)		/* Word w is the same with word of current node*/
    		return 1;
  	else if (cond < 0)         			/* If w precedes word of current node*/
    		return treesearch(p->left, w);         	/* Search left suftree*/
  	else                                          	/* Otherwise*/
    		return treesearch(p->right, w);         /* search right subtree*/
}

int searchcode(Treeptr p, char *w)			/*check if the word is already in the tree*/
{
	int cond;
	if ((cond = strcmp(w, p->word)) == 0)		/*if the word is in the tree return word's code*/
		return p->code;
	else if (cond < 0)				
		return searchcode(p->left, w);
	else
		return searchcode(p->right, w);
}

void deletetree(Treeptr p)				/*delete tree when compression is not successful*/
{
	if ( p != NULL )
	{
		deletetree(p->right);
		deletetree(p->left);
		free(p->word);
		free(p);
	}
}
