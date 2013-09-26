/* -----------------------------
 operfunc.h
 -------------------------------
 Functions for operations over sets.
*/

#ifndef OPERFUNC_H
#define OPERFUNC_H


int search_twin_elemts_into_set( tabl_elemts_of_set* tbl_elemts );

int operation_union( tabl_elemts_of_set* tbl_A, tabl_elemts_of_set* tbl_B, FILE* stream );

int operation_intersection( tabl_elemts_of_set* tbl_A, tabl_elemts_of_set* tbl_B, FILE* stream );

int operation_difference( tabl_elemts_of_set* tbl_A, tabl_elemts_of_set* tbl_B, FILE* stream );


#endif  /* OPERFUNC_H */