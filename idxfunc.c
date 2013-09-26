#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "elemdata.h"
#include "idxfunc.h"


int get_element( const tabl_elemts_of_set* tbl_elemts, int idx_elmt,
                                     char* val_elmt, const size_t size_val_el )
{
    int i = 0;
    int j = 0;
    
    int tot_numb_elm = 0;
    
    int beg_elm = 0;
    int end_elm = 0;
    int quant_symb = 0;
    int size_buf = 0;

    
    if( tbl_elemts == NULL ) return -1;
    
    tot_numb_elm = tbl_elemts->total_numb;
    if( tot_numb_elm == 0 ) return 0;
    
    if( (tbl_elemts->str_of_set) == NULL ) return -2;
    
    if( idx_elmt > (tot_numb_elm - 1) ) return -3;
    if( val_elmt == NULL ) return -4;   
    
    if( size_val_el == 0 ) return -5;
            
    beg_elm = ((tbl_elemts->arr_elemts) + idx_elmt)->pos_begin;
    quant_symb = ((tbl_elemts->arr_elemts) + idx_elmt)->quantity_symb;
    end_elm = beg_elm + quant_symb;
    size_buf = size_val_el - 1;
    
    j = 0;
    
    for( i = beg_elm; i < end_elm; i++ )
    {
        if( j < size_buf )
        {
            *(val_elmt + j++) = *((tbl_elemts->str_of_set) + i);
        }
    }
    
    *(val_elmt + j) = 0;
    
    return 0;
}



int parse_elmt_of_set( const tabl_elemts_of_set* tbl_elemts,
                                                     const char separator )
{
    int i, j;
    int len_str = 0;
    int count_elem = 0;
    const char* str = NULL;
    char current = 0;
        
    enum { CHARS_OF_SEPARATOR, CHARS_OF_ELEM } state = CHARS_OF_SEPARATOR;
    
    
    if( tbl_elemts == NULL ) return -1;
    
    if( (tbl_elemts->total_numb) == 0 ) return -2;
    
    len_str = strlen( tbl_elemts->str_of_set );
    
    str = tbl_elemts->str_of_set;
    
    for( i = 0; i < len_str; i++ )
    {
        current = *(str + i);
        switch( state )
        {
            case CHARS_OF_SEPARATOR :
            {
                if( current != separator )
                {
                    state = CHARS_OF_ELEM;
                    ((tbl_elemts->arr_elemts) + count_elem)->pos_begin = i;
                    j = 1;
                }
                break;
            }
            case CHARS_OF_ELEM :
            {
                if( current == separator )
                {
                    state = CHARS_OF_SEPARATOR;                 
                    ((tbl_elemts->arr_elemts) + count_elem)->quantity_symb = j;
                    count_elem++;
                }
                else
                {
                    j++;
                }
                break;
            }    
        } /* END of switch */
    } /*END of for*/
    
    if( state == CHARS_OF_ELEM )
    {
        ((tbl_elemts->arr_elemts) + count_elem)->quantity_symb = j;
        count_elem++;
    }  

    return count_elem;
}



int calc_total_numb_of_elemts( const char* const str_of_set,
                                                         const char separator )
{
    int i;
    int len_str;
    int tot_numb_of_elemts = 0;
    char current = 0;
    
    enum { CHARS_OF_SEPARATOR, CHARS_OF_ELEM } state = CHARS_OF_SEPARATOR;
    
    len_str = strlen( str_of_set );
    for( i = 0; i < len_str; i++ )
    {
        current = *(str_of_set + i);
        switch( state )
        {
            case CHARS_OF_SEPARATOR :
            {
                if( current != separator )
                {
                    state = CHARS_OF_ELEM;
                }
                break;
            }
            case CHARS_OF_ELEM :
            {
                if( current == separator )
                {
                    state = CHARS_OF_SEPARATOR;
                    tot_numb_of_elemts++;
                }
                break;
            }    
        } /* END of switch */
    } /*END of for*/
    
    if( state == CHARS_OF_ELEM )   tot_numb_of_elemts++;

    return tot_numb_of_elemts;
}
