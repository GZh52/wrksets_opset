/* -----------------------------
 idxfunc.h
 -------------------------------
 Basic functions for indexing elements of set.
 Elements stores in command line.
*/

#ifndef IDXFUNC_H
#define IDXFUNC_H


int get_element( const tabl_elemts_of_set* tbl_elemts, int idx_elmt,
                                    char* val_elmt, const size_t size_val_el );


int parse_elmt_of_set( const tabl_elemts_of_set* tbl_elemts,
                                             const char separator );


int calc_total_numb_of_elemts( const char* const str_of_set,
                                                 const char separator );


#endif  /* IDXFUNC_H */