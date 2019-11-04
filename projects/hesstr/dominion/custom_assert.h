#define ASSERT(expr) \
    if(expr) \
    {} \
    else \
    { \
        printf("Error, Assertion Failed:\n"); \
        printf(#expr); \
        printf(" on line %d", __LINE__); \
        printf(", in file %s\n", __FILE__); \
    }