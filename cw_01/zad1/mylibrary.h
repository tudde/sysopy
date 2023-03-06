#ifndef MYLIBRARY_H_   /* Include guard */
#define MYLIBRARY_H_



typedef struct{
    char** ptrArray;
    int size;
    int taken;
} MemArray;

MemArray create_MemArray(int size); /* An example function declaration */

void run_wc(MemArray* mainArray, char* filename);

char* value_at(MemArray mainArray, int idx);

void remove_at(MemArray mainArray, int idx);

void free_array(MemArray mainArray);


#endif // MYLIBRARY_H_
