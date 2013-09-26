
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "elemdata.h"
#include "printfnc.h"
#include "operfunc.h"



int search_twin_elemts_into_set( tabl_elemts_of_set* tbl_elemts )
{
    int i = 0;    
    int j = 0;
    int N = 0;
    int res = 0;
    
    int len_elm_1 = 0;
    int len_elm_2 = 0;
    int beg_elm_1 = 0;
    int beg_elm_2 = 0;
    int adjac_twin = 0;
    
    const char* elemt_1 = NULL;
    const char* elemt_2 = NULL;
    
    N = tbl_elemts->total_numb;
    
    if( N == 0 ) return 0;
    
/*    tbl_elemts->arr_elemts->idx_prev_twin = NO_ADJACENT_TWIN; */
    
/*    elemt_1 = tbl_elemts->str_of_set;
    len_elm_1 = tbl_elemts->arr_elemts->quantity_symb; */
        
    for( i = 0; i < N; i++ )
    {
/* Если элемент не имеет двойников (idx_next_twin и idx_prev_twin равны)*/
        if( ((tbl_elemts->arr_elemts + i)->idx_prev_twin) ==
	    ((tbl_elemts->arr_elemts + i)->idx_next_twin)
	  )
	{
	    adjac_twin = i;
	    (tbl_elemts->arr_elemts + i)->idx_prev_twin = NO_ADJACENT_TWIN;
	    (tbl_elemts->arr_elemts + i)->idx_next_twin = NO_ADJACENT_TWIN;
	    
	    beg_elm_1 = (tbl_elemts->arr_elemts + i)->pos_begin;
	    elemt_1 = tbl_elemts->str_of_set + beg_elm_1;
            len_elm_1 = (tbl_elemts->arr_elemts + i)->quantity_symb;
	
	    for( j = (i + 1); j < N; j++ )
	    {
		len_elm_2 = (tbl_elemts->arr_elemts + j)->quantity_symb;
	
	        if( len_elm_1 == len_elm_2 )
	        {
	            beg_elm_2 = (tbl_elemts->arr_elemts + j)->pos_begin;
	            elemt_2 = tbl_elemts->str_of_set + beg_elm_2;
	    
	            res = strncmp( elemt_1, elemt_2, len_elm_1 );
	            if( !res )
	            {
		        (tbl_elemts->arr_elemts + j)->idx_prev_twin = adjac_twin;
			(tbl_elemts->arr_elemts + j)->idx_next_twin = NO_ADJACENT_TWIN;
			(tbl_elemts->arr_elemts + adjac_twin)->idx_next_twin = j;
			adjac_twin = j;
	            }
	    
	        }
	    }
	}
    }
    
    return 0;
}



int operation_union( tabl_elemts_of_set* tbl_A, tabl_elemts_of_set* tbl_B, FILE* stream )
{
    int i = 0;
    int j = 0;
    
    int N = 0;
    int M = 0;
    
    const char* elemt_A = NULL;
    const char* elemt_B = NULL;
    
    int beg_elem_A = 0;
    int beg_elem_B = 0;
    
    int len_elem_A = 0;
    int len_elem_B = 0;
    
    int res = 0;
    
    
    N = tbl_A->total_numb;
    M = tbl_B->total_numb;
    
    fputc('\n', stream);
    
    if( !N )
    {
	fputc('\"', stream);
	for( i = 0; i < M; i++ )
	{
	    beg_elem_B = (tbl_B->arr_elemts + i)->pos_begin;
	    len_elem_B = (tbl_B->arr_elemts + i)->quantity_symb;
	    elemt_B = tbl_B->str_of_set + beg_elem_B;
	    
	    print_element_by_chars( elemt_B, len_elem_B, stream);
	    fputc(' ', stream);
	}
	fputc('\"', stream);
	fputc('\n', stream);
	return 0;
    }
    
    if( !M )
    {
	fputc('\"', stream);
	for( i = 0; i < N; i++ )
	{
	    beg_elem_A = (tbl_A->arr_elemts + i)->pos_begin;
	    len_elem_A = (tbl_A->arr_elemts + i)->quantity_symb;
	    elemt_A = tbl_A->str_of_set + beg_elem_A;
	    
	    print_element_by_chars( elemt_A, len_elem_A, stream);
	    fputc(' ', stream);
	}
	fputc('\"', stream);
	fputc('\n', stream);
	return 0;
    }
    
/* Если поиска двойников ещё не было - ищем их */    
    if( (tbl_A->arr_elemts->idx_prev_twin) != NO_ADJACENT_TWIN )
    {
	res = search_twin_elemts_into_set( tbl_A );
    }
    if( (tbl_B->arr_elemts->idx_prev_twin) != NO_ADJACENT_TWIN )
    {
	res = search_twin_elemts_into_set( tbl_B );
    }
    
    fputc('\"', stream);

/* Выводим в результат все элементы А, убирая повторный вывод двойников */
    for( i = 0; i < N; i++ )
    {
/* Если в множестве А встретился первый слева двойник или уникальный элемент */
        if( ((tbl_A->arr_elemts + i)->idx_prev_twin) == NO_ADJACENT_TWIN )
	{
	    beg_elem_A = (tbl_A->arr_elemts + i)->pos_begin;
	    len_elem_A = (tbl_A->arr_elemts + i)->quantity_symb;
	    elemt_A = tbl_A->str_of_set + beg_elem_A;
/* Выводим элемент в результирующее множество */
            print_element_by_chars( elemt_A, len_elem_A, stream);
	    fputc(' ', stream);
	}
    }    
/* Добавляем в результат те элементы из В, которые не равны ни одному эл-ту из А */
/* Двойников повторно не выводим*/
/* Если А и В отсортированы и без двойников - они логично объединятся одно за другим*/
    for( i = 0; i < M; i++ )
    {
/* Если в множестве B встретился первый слева двойник или уникальный элемент */
        if( ((tbl_B->arr_elemts + i)->idx_prev_twin) == NO_ADJACENT_TWIN )
	{
	    beg_elem_B = (tbl_B->arr_elemts + i)->pos_begin;
	    len_elem_B = (tbl_B->arr_elemts + i)->quantity_symb;
	    elemt_B = tbl_B->str_of_set + beg_elem_B;
/* Проходим по множеству A */
            for( j = 0; j < N; j++ )
	    {
/* Если в множестве A встретился первый слева двойник или уникальный элемент */		
		if( ((tbl_A->arr_elemts + j)->idx_prev_twin) == NO_ADJACENT_TWIN )
		{
		    beg_elem_A = (tbl_A->arr_elemts + j)->pos_begin;
	            len_elem_A = (tbl_A->arr_elemts + j)->quantity_symb;
	            elemt_A = tbl_A->str_of_set + beg_elem_A;
/* Если длины элементов равны - проверяем, равны-ли сами элементы ?*/
	            if( len_elem_A == len_elem_B )
	            {
		        res = strncmp( elemt_A, elemt_B, len_elem_A );
/* Если элементы из А и из В равны - то НЕ все элементы из А не равны эл-ту из В */
			if( !res )
			{
			    break;
			}
		    }
		} /* END if A->idx_prev_twin*/
	    } /* END for j*/
/* Если ВСЕ элементы из А НЕ равны элементу из В - выводим его */	    
	    if( j == N )
	    {
		print_element_by_chars( elemt_B, len_elem_B, stream);
	        fputc(' ', stream);
	    }
	} /* END if B->idx_prev_twin */
    } /* END for i*/
    
    fputc('\"', stream);
    fputc('\n', stream);
    
    return 0;
}



int operation_intersection( tabl_elemts_of_set* tbl_A, tabl_elemts_of_set* tbl_B, FILE* stream )
{
    int i = 0;
    int j = 0;
    
    int N = 0;
    int M = 0;
    
    const char* elemt_A = NULL;
    const char* elemt_B = NULL;
    
    int beg_elem_A = 0;
    int beg_elem_B = 0;
    
    int len_elem_A = 0;
    int len_elem_B = 0;
    
    int res = 0;
    
    
    N = tbl_A->total_numb;
    M = tbl_B->total_numb;
    
    fputc('\n', stream);

/* Если одно из множеств пустое - результат тоже пустой */    
    if( (!N) || (!M) )
    {
	fputc('\"', stream);
	fputc('\"', stream);
	fputc('\n', stream);
	return 0;
    }
    
/* Если поиска двойников ещё не было - ищем их */    
    if( (tbl_A->arr_elemts->idx_prev_twin) != NO_ADJACENT_TWIN )
    {
	res = search_twin_elemts_into_set( tbl_A );
    }
    if( (tbl_B->arr_elemts->idx_prev_twin) != NO_ADJACENT_TWIN )
    {
	res = search_twin_elemts_into_set( tbl_B );
    }
    
    fputc('\"', stream);

/* Для всех элементов из А без их повторений */
    for( i = 0; i < N; i++ )
    {
/* Если в множестве A встретился первый слева двойник или уникальный элемент */
        if( ((tbl_A->arr_elemts + i)->idx_prev_twin) == NO_ADJACENT_TWIN )
	{
	    beg_elem_A = (tbl_A->arr_elemts + i)->pos_begin;
	    len_elem_A = (tbl_A->arr_elemts + i)->quantity_symb;
	    elemt_A = tbl_A->str_of_set + beg_elem_A;
/* Проходим по всем элементам из B без их повторений*/
            for( j = 0; j < M; j++ )
	    {
/* Если в множестве B встретился первый слева двойник или уникальный элемент */		
		if( ((tbl_B->arr_elemts + j)->idx_prev_twin) == NO_ADJACENT_TWIN )
		{
		    beg_elem_B = (tbl_B->arr_elemts + j)->pos_begin;
	            len_elem_B = (tbl_B->arr_elemts + j)->quantity_symb;
	            elemt_B = tbl_B->str_of_set + beg_elem_B;
/* Если длины элементов равны - проверяем, равны-ли сами элементы ?*/
	            if( len_elem_A == len_elem_B )
	            {
		        res = strncmp( elemt_A, elemt_B, len_elem_A );
/* Если элементы из А и из В равны, - выводим любой элемент (например из А) */
			if( !res )
			{
			    print_element_by_chars( elemt_A, len_elem_A, stream);
	                    fputc(' ', stream);
/* Прекращаем дальнейший поиск по B*/
/* Элемент из A уже выведен в результат - переходим к следующему эл-ту из A */
                            j = N;
			}
		    }
		} /* END if B->idx_prev_twin*/
	    } /* END for j*/
	} /* END if A->idx_prev_twin */
    } /* END for i*/
    
    fputc('\"', stream);
    fputc('\n', stream);
    
    return 0;
}



int operation_difference( tabl_elemts_of_set* tbl_A, tabl_elemts_of_set* tbl_B, FILE* stream )
{
    int i = 0;
    int j = 0;
    
    int N = 0;
    int M = 0;
    
    const char* elemt_A = NULL;
    const char* elemt_B = NULL;
    
    int beg_elem_A = 0;
    int beg_elem_B = 0;
    
    int len_elem_A = 0;
    int len_elem_B = 0;
    
    int res = 0;
    
    
    N = tbl_A->total_numb;
    M = tbl_B->total_numb;
    
    fputc('\n', stream);

/* Если одно из множеств пустое - результат тоже пустой */    
    if( (!N) || (!M) )
    {
	fputc('\"', stream);
	fputc('\"', stream);
	fputc('\n', stream);
	return 0;
    }
    
/* Если поиска двойников ещё не было - ищем их */    
    if( (tbl_A->arr_elemts->idx_prev_twin) != NO_ADJACENT_TWIN )
    {
	res = search_twin_elemts_into_set( tbl_A );
    }
    if( (tbl_B->arr_elemts->idx_prev_twin) != NO_ADJACENT_TWIN )
    {
	res = search_twin_elemts_into_set( tbl_B );
    }
    
    fputc('\"', stream);

/* Для всех элементов из А без их повторений */
    for( i = 0; i < N; i++ )
    {
/* Если в множестве A встретился первый слева двойник или уникальный элемент */
        if( ((tbl_A->arr_elemts + i)->idx_prev_twin) == NO_ADJACENT_TWIN )
	{
	    beg_elem_A = (tbl_A->arr_elemts + i)->pos_begin;
	    len_elem_A = (tbl_A->arr_elemts + i)->quantity_symb;
	    elemt_A = tbl_A->str_of_set + beg_elem_A;
/* Проходим по всем элементам из B без их повторений*/
            for( j = 0; j < M; j++ )
	    {
/* Если в множестве B встретился первый слева двойник или уникальный элемент */		
		if( ((tbl_B->arr_elemts + j)->idx_prev_twin) == NO_ADJACENT_TWIN )
		{
		    beg_elem_B = (tbl_B->arr_elemts + j)->pos_begin;
	            len_elem_B = (tbl_B->arr_elemts + j)->quantity_symb;
	            elemt_B = tbl_B->str_of_set + beg_elem_B;
/* Если длины элементов равны - проверяем, равны-ли сами элементы ?*/
	            if( len_elem_A == len_elem_B )
	            {
		        res = strncmp( elemt_A, elemt_B, len_elem_A );
/* Если элементы из А и из В равны, - прерываем цикл, элемент из А не выводим */
			if( !res )
			{
			    break;
			}
		    }
		} /* END if B->idx_prev_twin*/
	    } /* END for j*/
/* Если ВСЕ элементы из B НЕ равны элементу из A - выводим его */	    
	    if( j == M )
	    {
		print_element_by_chars( elemt_A, len_elem_A, stream);
	        fputc(' ', stream);
	    }
	} /* END if A->idx_prev_twin */
    } /* END for i*/
    
    fputc('\"', stream);
    fputc('\n', stream);
    
    return 0;
}