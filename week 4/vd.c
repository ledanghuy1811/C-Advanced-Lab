#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"jval.h"
#include"jrb.h"

void print(JRB a);

int main()
{
    JRB PhoneBook=make_jrb();
    jrb_insert_str(PhoneBook,"Huy",new_jval_l(1905));
    jrb_insert_str(PhoneBook,"Hang",new_jval_l(1811));
    jrb_insert_str(PhoneBook,"Anh",new_jval_l(1234));
    print(PhoneBook);
    JRB temp=jrb_find_str(PhoneBook,"Heuy");
    if(temp==NULL)
        printf("1\n");
    return 0;
}

void print(JRB a)
{
    JRB temp;
    jrb_traverse(temp,a)
    {
        printf("%s\t%ld\n",jval_s(temp->key),jval_l(temp->val));
    }
}