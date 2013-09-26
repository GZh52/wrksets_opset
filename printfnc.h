/* -----------------------------
 printfnc.h
 -------------------------------

*/

#ifndef PRINTFNC_H
#define PRINTFNC_H


void print_help();

void print_element_by_chars(const char* element, const int N_chars, FILE* stream);

void print_twin_elements( tabl_elemts_of_set* tbl_elemts );


#endif  /* PRINTFNC_H */