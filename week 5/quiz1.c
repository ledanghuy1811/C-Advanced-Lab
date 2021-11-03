#include<stdio.h>
#include<stdlib.h>
#include"btree.h"

int main()
{
    char pd[]="phonebook.txt";
    // initialization
    btinit();
    BTA *book;
    // Open a b-tree file
    book=btopn(pd,0,0);
    if(book==NULL)
        book=btcrt(pd,0,0);
    // Close b-tree
    btcls(book);
    return 0;
}