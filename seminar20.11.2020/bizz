#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h> 
#include <unistd.h>
#include <assert.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#define TEST 0
                                                                    

enum errors {
    NO_INPUT = -1,
    ARGS_OVERFLOW = -2,
    NOFILE = -100,
    READ_SIZE = -4,
    ARGS_UNDERFLOW = -5,
    BAD_ALLOC = -6,
};
int check_input(int argc, char** argv) {
    if (argc == 1) {
        return NO_INPUT;
    } else if (argc == 2) {
        return ARGS_UNDERFLOW;
    } else if (argc > 3) {
        return ARGS_OVERFLOW;
    }

    return 0;
}
void dump(int error_type) {
    switch(error_type) {

        case NO_INPUT:
        fprintf(stderr, "bizz_buzz error: at least 1 argument expected\n");
        exit(NO_INPUT);
        break;

        case ARGS_OVERFLOW:
        fprintf(stderr, "bizz_buzz error: too many arguments passed\n");
        exit(ARGS_OVERFLOW);
        break;
        case EISDIR:
        fprintf(stderr, "bizz_buzz error: trying to open a directory\n");
        exit(EISDIR);
        break;
        case ENOENT:
        fprintf(stderr, "bizz_buzz error: input file does not exist\n");
        exit(ENOENT);
        break;

        case ARGS_UNDERFLOW:
        fprintf(stderr, "bizz_buzz error: output file does not exist\n");
        exit(ARGS_UNDERFLOW);
        break;

        case BAD_ALLOC:
        fprintf(stderr, "bizz_buzz error: could not allocate memory\n");
        exit(BAD_ALLOC);
        break;
        case 0:
        break;
        default:
        fprintf(stderr, "bizz_buzz error: unexpected error\n");
    }
}
char* replace_str(char* buf, char* pos, const char* str, unsigned* buf_size, unsigned insert_sz, unsigned offset) {
    unsigned pos_offset = pos - buf; 
    char* remaining = pos + offset; 
    int rem_len = strlen(remaining);
    char* copy_remaining = (char*) calloc(rem_len, sizeof(char));
    strcpy(copy_remaining, remaining);
    *buf_size = *buf_size + insert_sz + offset + 1; // increasing buffer size, may become bigger than required but not a huge issue
    int rem_size = strlen(copy_remaining);
    
    char* new_buf = realloc(buf, *buf_size);  
    strcpy(new_buf + pos_offset, str);
    strcat(new_buf, copy_remaining);
    
    free(copy_remaining);
    return new_buf;
}
unsigned count_digits(long number) {
    unsigned count = 0;
    while (number != 0) {
        number /= 10;
        ++count;
    }
    return count;
}
void test_replace(char* buf, const char* str, int* buf_size, unsigned insert_sz) {
    replace_str(buf, buf + 3, str, (unsigned*) buf_size, insert_sz, 0);
}
char* parse_numbers(char* buf, unsigned* size) {
    const char bizz[] ="bizz";
    const char buzz[]="buzz";
    const char bizz_buzz[] = "bizzbuzz";
    char* p = buf;
    char** endptr = (char**) calloc(1, sizeof(char*)); // careful
    if (endptr == NULL){
    }
    assert(endptr);

    long number= 0;
    unsigned buf_offset= 0;

    while(*p) { // while there are charachters in buffer
        number = strtol(p, endptr, 10);
        unsigned digits = 0;
        if (number > 0) {

            digits = count_digits(number);
            if (number % 15 == 0) {
                p = *endptr - digits; // moving to the location preceeding string
                buf = replace_str(buf, p, bizz_buzz, size, sizeof("bizzbuzz"), digits);
            } else if (number % 3 == 0) {
                p = *endptr - digits;      
                buf = replace_str(buf, p, bizz, size, sizeof("bizz"), digits);
            } else if (number % 5 == 0) {
                p = *endptr - digits;
                buf = replace_str(buf, p, buzz, size, sizeof("buzz"), digits);            
            }
    p = buf + buf_offset; 
        }
        strtol(p, endptr, 10); 
        if (number > 0) { 
            p = *endptr;
            buf_offset = p - buf; 
        } else {
            p++; /
            buf_offset++; 
        }
    }
    return buf;
}
void print_buf(char* buf, unsigned n_bytes) {
    int res = write(STDOUT_FILENO, buf, n_bytes);
}
int handle_input(int argc, char** argv) {

    int fd_1 = open(argv[1], O_RDONLY);
    int fd_2 = NOFILE;
    fd_2 = open(argv[2], O_WRONLY);
    if (errno == ENOENT) {
        fprintf(stdout, "bizz_buzz warning: output file not specified, creating new output file\n");
        fd_2 = open(argv[2], O_WRONLY | O_CREAT, S_IRWXU);
    }
    struct stat input;
    fstat(fd_1, &input);
    int input_size = input.st_size;
    char* buf = (char*) calloc(input_size, sizeof(char));
    int n_read = read(fd_1, buf, input_size);
    buf[input_size] = '\0';
    assert(n_read == input_size);
    unsigned buf_size = (unsigned) n_read;
    char* new_buf = parse_numbers(buf, &buf_size);
    int new_size = strlen(new_buf);
    int n_write = write(fd_2, new_buf, new_size); // writing whole file

    close(fd_1);
    close(fd_2);
    return 0;
}

int main(int argc, char** argv) {
    int result = check_input(argc ,argv);
    dump(result);
    handle_input(argc, argv);
    return 0;
}
