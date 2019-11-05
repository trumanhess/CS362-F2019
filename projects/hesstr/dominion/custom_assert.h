#define ASSERT(expr) \
    if(expr) \
    {} \
    else \
    { \
        printf("\n\tError, Assertion Failed:\n"); \
        printf("\t"); \
        printf(#expr); \
        printf(" on line %d", __LINE__); \
        printf(", in file %s\n", __FILE__); \
    }