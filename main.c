/* -----------------------------
 * main.c for wrksets project
 * -----------------------------
 * 
 * Формат вызова
 * wrksets -p <union | intersection | difference> "set A" "set B"
 * ПОРЯДОК СЛЕДОВАНИЯ АРГУМЕНТОВ ВАЖЕН !
 * разделители элементов множеств - пробелы
*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "elemdata.h"
#include "idxfunc.h"
#include "printfnc.h"
#include "operfunc.h"




int main( int argc, char* argv[], char* envp[] )
{
    int i = 0;
    int j = 0;
/*    int result = 0; */
    
    char buf[128];
    
    int res = 0;
/*    int k = 0; */

    struct tabl_elemts_of_set* tbl_elem_A = NULL;
    struct tabl_elemts_of_set* tbl_elem_B = NULL;
    
    
    if( argc != 5 )
    {
        print_help();
        return EXIT_FAILURE;
    }

#ifdef MY_DEBUG    
    for( i = 0; i < argc; i++)
    {
        printf("\n argc = %d , i = %d , argv[i] = %s ", argc, i, *(argv +i) );
    }
   
    res = calc_total_numb_of_elemts( *(argv+3), ' ' );
    printf("\n\nTotal number of elements of set A = %d \n", res);
    
    res = calc_total_numb_of_elemts( *(argv+4), ' ' );
    printf("Total number of elements of set B = %d \n", res);
#endif    

    tbl_elem_A = (tabl_elemts_of_set*) malloc( sizeof(tabl_elemts_of_set) );
    if( tbl_elem_A == NULL )
    {
        perror("\n ERROR : Bad memory allocation (phase 1) for primary set ! \n ");
        return EXIT_FAILURE;
    }
    
    tbl_elem_A->total_numb = calc_total_numb_of_elemts( *(argv+3), ' ' );
    tbl_elem_A->str_of_set = *(argv+3);
    tbl_elem_A->arr_elemts = NULL;
    tbl_elem_A->arr_elemts = (some_elemt_in_str*) calloc(
                                                          (tbl_elem_A->total_numb),
                                                           sizeof(some_elemt_in_str) );
    if( (tbl_elem_A->arr_elemts) == NULL )
    {
        free( tbl_elem_A );
        perror("\n ERROR : Bad memory allocation (phase 2) for primary set ! \n ");
        return EXIT_FAILURE;
    }
/*    
    tbl_elem_A->arr_elemts->idx_prev_twin = NO_ADJACENT_TWIN;
    tbl_elem_A->arr_elemts->idx_next_twin = NO_ADJACENT_TWIN;
*/    
    
    tbl_elem_B = (tabl_elemts_of_set*) malloc( sizeof(tabl_elemts_of_set) );
    if( tbl_elem_B == NULL )
    {
        free( (void*) (tbl_elem_A->arr_elemts) );
        free( tbl_elem_A );
        perror("\n ERROR : Bad memory allocation (phase 1) for secondary set ! \n ");
        return EXIT_FAILURE;
    }
    
    tbl_elem_B->total_numb = calc_total_numb_of_elemts( *(argv+4), ' ' );
    tbl_elem_B->str_of_set = *(argv+4);
    tbl_elem_B->arr_elemts = NULL;
    tbl_elem_B->arr_elemts = (some_elemt_in_str*) calloc(
                                                         (tbl_elem_B->total_numb),
                                                           sizeof(some_elemt_in_str) );
    if( (tbl_elem_B->arr_elemts) == NULL )
    {
        free( tbl_elem_B );
        free( (void*) (tbl_elem_A->arr_elemts) );
        free( tbl_elem_A );
        perror("\n ERROR : Bad memory allocation (phase 2) for secondary set ! \n ");
        return EXIT_FAILURE;
    }
/*    
    tbl_elem_B->arr_elemts->idx_prev_twin = NO_ADJACENT_TWIN;
    tbl_elem_B->arr_elemts->idx_next_twin = NO_ADJACENT_TWIN;
*/
/* ================ Test for set A ====================== */  
    res = parse_elmt_of_set( tbl_elem_A, ' ' );

#ifdef MY_DEBUG    
    printf("\nparse_elmt_of_set  for set A return : %d \n", res);
#endif
    
    res = tbl_elem_A->total_numb;
    buf[0] = 0;
   
    printf("\n Elements of set A : \n");
    for( i = 0 ; i < res; i++)
    {
        j = get_element( tbl_elem_A, i, buf, 128 );
        if( j == 0 )
        {
            printf("\nElement N %d = %s", i, buf);
        }
    }

    res = search_twin_elemts_into_set( tbl_elem_A );
    printf("\n\nList of Twin elements for each element into set A:\n");
    print_twin_elements( tbl_elem_A );
    

/* ================ Test for set B ====================== */    
    res = parse_elmt_of_set( tbl_elem_B, ' ' );

#ifdef MY_DEBUG    
    printf("\n\nparse_elmt_of_set  for set B return : %d \n", res);
#endif
    
    res = tbl_elem_B->total_numb;
    buf[0] = 0;
   
    printf("\n Elements of set B : \n");
    for( i = 0 ; i < res; i++)
    {
        j = get_element( tbl_elem_B, i, buf, 128 );
        if( j == 0 )
        {
            printf("\nElement N %d = %s", i, buf);
        }
    }
    
    res = search_twin_elemts_into_set( tbl_elem_B );
    printf("\n\nList of Twin elements for each element into set B:\n");
    print_twin_elements( tbl_elem_B );
    
/* ============ */
    printf("\n A union B = \n");
    
    res = operation_union( tbl_elem_A, tbl_elem_B, stdout );
    
    printf("\n A intersection B = \n");
    
    res = operation_intersection( tbl_elem_A, tbl_elem_B, stdout );
    
    printf("\n A difference B = \n");
    
    res = operation_difference( tbl_elem_A, tbl_elem_B, stdout );

/* ==============*/


    free( (void*) (tbl_elem_B->arr_elemts) );
    free( tbl_elem_B );
    
    free( (void*) (tbl_elem_A->arr_elemts) );
    free( tbl_elem_A );
    
    printf("\n\n");
            
    return EXIT_SUCCESS;
}