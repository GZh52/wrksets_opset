
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "elemdata.h"
#include "printfnc.h"


void print_help()
{
    printf("\nUsage :  wrksets -p <union | intersection | " \
                  "difference> \"set A\" \"set B\" \n\n");
    return;
}


void print_element_by_chars(const char* element, const int N_chars, FILE* stream)
{
    int i = 0;
    
    if( element == NULL ) return;
    
    for( i = 0; i < N_chars; i++ )
    {
	fputc( *(element + i), stream );
    }
    return;
}


void print_twin_elements( tabl_elemts_of_set* tbl_elemts )
{
    int i = 0;
    int j = 0;
    int k = 0;
    int N = 0;
    
    int beg_elm = 0;
    int len_elm = 0;
    const char* elemt = NULL;
    
    N = tbl_elemts->total_numb;
    
    if( !N ) return;
    
    for( i = 0; i < N; i++ )
    {
	if( ((tbl_elemts->arr_elemts + i)->idx_prev_twin) == NO_ADJACENT_TWIN )
	{
	    printf("\n");
	    j = i;
	    beg_elm = (tbl_elemts->arr_elemts + j)->pos_begin;
	    elemt = tbl_elemts->str_of_set + beg_elm;
            len_elm = (tbl_elemts->arr_elemts + j)->quantity_symb;
	    
	    print_element_by_chars( elemt, len_elm, stdout);
	    printf(" : ");
/*	    
	    for( k = 0; k < len_elm; k++ )
	    {
                putchar( *(elemt + k) );
            }
            printf(" : ");
*/
	    
	    while( (tbl_elemts->arr_elemts + j)->idx_next_twin != NO_ADJACENT_TWIN )
	    {
		k = (tbl_elemts->arr_elemts + j)->idx_next_twin;
		j = k;
		beg_elm = (tbl_elemts->arr_elemts + j)->pos_begin;
	        elemt = tbl_elemts->str_of_set + beg_elm;
                len_elm = (tbl_elemts->arr_elemts + j)->quantity_symb;
		
		print_element_by_chars( elemt, len_elm, stdout);
	        printf(" ; ");

/*		 
		for( k = 0; k < len_elm; k++ )
		{
		    putchar( *(elemt + k) );
		}
		printf(" ; ");

*/
	    }
	}
    }
    printf("\n");
    return;
}
