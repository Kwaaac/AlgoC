#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct _link {
    int data;
    struct _link *next;
} link;

link *create_link(int elt) {
    link *lnk = (link *) malloc(sizeof(link));
    assert(lnk != NULL);
    lnk->data = elt;
    lnk->next = NULL;
    return lnk;
}

link *insert_first(link *lst, int elt) {
    link *lnk = create_link(elt);
    lnk->next = lst;
    return lnk;
}

link *one_to_n(int n) {
    int i;
    link *lst = NULL;

    for (i = n + 1; i > 1; i--, lst = insert_first(lst, i)) {}

    return lst;
}

link *insert_last(link *lst, int elt) {
    link *ptr;
    link *lnk = create_link(elt);

    if (lst == NULL) {
        return lnk;
    }

    for (ptr = lst; ptr->next != NULL; ptr = ptr->next) {}

    ptr->next = lnk;
    return lst;
}

link *one_to_n_last(int n) {
    int i;
    link *lst = NULL;

    for (i = 0; i < n; i++, lst = insert_last(lst, i)) {}

    return lst;
}


link *one_to_n_last2(int n, int start, int skip) {
    int i;
    link *lst = NULL;

    for (i = start; i < n; i += skip, lst = insert_last(lst, i)) {}

    return lst;
}

link *reverse(link *lst) {
    link *ptr;
    link *new_link = NULL;

    for (ptr = lst; ptr != NULL; ptr = ptr->next) {
        new_link = insert_first(new_link, ptr->data);
    }
    return new_link;
}

void display_link(link *lst) {
    if (lst == NULL) {
        return;
    }
    printf("%d ", lst->data);
    display_link(lst->next);
}

link *remove_link(link *lst, int elt) {
    link *ptr;

    if (lst == NULL) {
        return NULL;
    }

    if (lst->data == elt) {
        ptr = lst;
        lst = lst->next;
        free(ptr);
        return lst;
    }

    lst->next = remove_link(lst->next, elt);
    return lst;
}

/*
 * Exercice 1:
 *     Tableau | simple | double
 * a)   O(1)   |  O(1)  | O(1)
 * b)   O(1)   |  O(n)  | O(1)
 * c)   O(n)   |  O(n)  | O(1)
 * d)   O(n)   |  O(1)  | O(1)
 * e)   O(n)   |  O(n)  | O(1)
 * f) O(log(n) |  O(n)  | O(n)
 *
 */

link *copy(link *lst) {
    link *copy, *ptr, *ptr_copy, *ptr_pred;

    if (lst == NULL) {
        return lst;
    }

    for (ptr = lst->next, copy = create_link(lst->data), ptr_pred = copy;
         ptr != NULL;
         ptr = ptr->next, ptr_pred = ptr_copy) {

        ptr_copy = create_link(ptr->data);
        ptr_pred->next = ptr_copy;
    }

    return copy;
}

link *merge(link *lst1, link *lst2) {
    if (lst1 != NULL || lst2 != NULL || lst1->data <= lst2->data) {
        return lst1;
    }

    link *ptr1 = lst1, *ptr2 = lst2, *tmp;

    while(ptr2 != NULL){
        while(ptr1->next != NULL && ptr1->next->data < ptr2->data){
            ptr1 = ptr1->next;
        }
        tmp = ptr2->next;
        ptr2->next = ptr1->next;
        ptr1->next = ptr2;
        ptr2 = tmp;
    }

    return lst1;
}

link *merge_rec(link * lst1, link *lst2){
    if(lst2 == NULL){
        return lst1;
    }
    if(lst1 == NULL){
        return lst2;
    }
    if(lst1->data < lst2->data){
        lst1->next = merge_rec(lst1->next, lst2);
        return lst1;
    } else {
        lst2->next = merge_rec(lst1, lst2->next);
        return lst2;
    }
}

link *merge_sort(link *lst){

}

int main() {

    link *ptr = remove_link(remove_link(one_to_n_last2(5, 0, 1), 4), 3);
    link *ptr2 = one_to_n_last2(10, 2, 2);
    display_link(ptr);
    printf("\n");
    display_link(ptr2);
    printf("\n");
    return 0;
}
