#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

struct line {
    char* str ;
    unsigned int len ;
};

void swap(struct line* a ,struct line* b );

int size_file(FILE* ptr_file); //размер файла

int add_null(char *ptr_str, int size);  // добавляем \0 в конец каждоц строки вместо \n

void add_struct(struct line *strings, char *ptr_str, int str_len); // заполняем структуру

void my_qsort(struct line* str, int left, int right, int comp(char *str_1, char *str_2)) ;

int main()
{
    FILE *ptr_file ;
    char *ptr_str;
    int size = 0;
    int str_len = 0 ;

    ptr_file = fopen("file.txt", "r");
    assert(ptr_file != 0);
    size = size_file(ptr_file);
    //printf("%d\n", size) ;

    ptr_str = (char*)calloc(size, size * sizeof(char));

    size_t result = fread(ptr_str, sizeof(char), size + 1, ptr_file);
    fclose(ptr_file) ;

    str_len = add_null(ptr_str, size) ; // кол-во строк
    //printf("\n%d", str_len) ;

    struct line *strings = (struct line*)calloc(str_len, str_len * sizeof(struct line));
    assert(strings != 0);

    add_struct(strings, ptr_str, str_len);

    /*for (int i = 0 ; i < str_len ; ++i) {
        printf("%s %d\n", (strings + i) -> str, (strings + i) -> len);
    }*/
    //printf("\n");

    my_qsort(strings, 0, str_len-1, strcmp);

    for (int i = 0 ; i < str_len ; ++i) {
        printf("%s\n", (strings + i) -> str);
    }

    free(ptr_str) ;
    return 0;

}

int size_file(FILE* ptr_file) {
    int size = NULL;
    fseek(ptr_file , 0 , SEEK_END );
    size = ftell(ptr_file);
    fseek(ptr_file , 0 , SEEK_SET);
    return size ;
}

int add_null(char *ptr_str, int size) {
    int str_len = 0;
    char *nul = 0;
    char *begin_line;
    begin_line = ptr_str;
    while(strchr(ptr_str, '\n') != NULL) {
        nul = strchr(ptr_str,'\n') ;
        *nul = '\0' ;
        ptr_str = nul + 2 ; // так как /n/r
        ++str_len ; //количество строк
    }
    ptr_str = begin_line;
    ptr_str[size - 1 + 1] = '\0' ; // в последнюю стоку добавляем \0
    ++str_len ;
    return str_len ;
}

void add_struct(struct line *strings, char *ptr_str, int str_len) {
    char *begin = 0, *end = 0;
    int size_string = 0; //??
    for (int i = 0 ; i < str_len ; ++i) {
        begin = ptr_str;
        end = strchr(ptr_str, '\0');
        size_string = end - begin ;
        (strings + i) -> str = begin ;
        (strings + i) -> len = size_string ;
        ptr_str = end + 1 ;
    }
}


void swap(struct line *a ,struct line *b ) {
    struct line tmp = *a ;
    *a = *b;
    *b = tmp;
}

void my_qsort(struct line *strings, int left, int right, int comp(char *str_1, char *str_2)) {
    int i = left;
    int j = right;
    struct line pivot =strings[(left + right) / 2];
    while(i <= j) {
        while(comp(strings[i].str, pivot.str) < 0) {
                ++i;
        }
        while(comp(strings[j].str, pivot.str) > 0) {
            --j;
        }
        if(i <= j) {
            swap(&strings[i], &strings[j]) ;
            ++i;
            --j;
        }
    }
    if(left < j) {
    my_qsort(strings, left, j, strcmp) ;
    }
    if(right > i) {
    my_qsort(strings, i, right, strcmp) ;
    }
}
