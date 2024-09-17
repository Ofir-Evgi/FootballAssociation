#ifndef __MACROS__
#define __MACROS__

#define CHECK_RETURN_INT(ptr) {if(!ptr) return 0;}
#define CHECK_RETURN_NULL(ptr) {if(!ptr){ return NULL;}}
#define MINUS(x,y) (x)-(y)
#define PRINT_HORIZONTAL_LINE(num) \
     { \
        for (int i = 0; i < num; i++) { \
            printf("-"); \
        } \
        printf("\n"); \
    }

//NEEDS TO REMEMBER TO USE ANOTHER MACRO 

#endif