/* -----------------------------
 elemdata.h
 -------------------------------
 Basic type for indexing elements of set.
 Elements stores in command line.
*/

#ifndef ELEMDATA_H
#define ELEMDATA_H

#define NO_TWIN_INFO -2
#define NO_ADJACENT_TWIN -1

typedef struct some_elemt_in_str
{
    int pos_begin;
    int quantity_symb;
    int idx_prev_twin;
    int idx_next_twin;
    
} some_elemt_in_str;


typedef struct tabl_elemts_of_set
{
    int total_numb;
    const char* str_of_set;
    some_elemt_in_str* arr_elemts;

} tabl_elemts_of_set;    

#endif  /* ELEMDATA_H */