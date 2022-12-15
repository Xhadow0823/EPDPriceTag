// 本檔案包含所有action
// #define NUMARGS(...) (sizeof((unsigned int){__VA_ARGS__})\/sizeof(unsigned int))

typedef unsigned int (*action0)(void);
typedef unsigned int (*action1)(unsigned int);
typedef unsigned int (*action2)(unsigned int, unsigned int);
typedef unsigned int (*action3)(unsigned int, unsigned int, unsigned int);
typedef unsigned int (*action4)(unsigned int, unsigned int, unsigned int, unsigned int);
#define ACTION_N(n) action##n
#define N_PARAM0(paramArr) ()
#define N_PARAM1(paramArr) (paramArr[0])
#define N_PARAM2(paramArr) (paramArr[0], paramArr[1])
#define N_PARAM3(paramArr) (paramArr[0], paramArr[1], paramArr[2])
#define N_PARAM4(paramArr) (paramArr[0], paramArr[1], paramArr[2], paramArr[3])
#define N_PARAM(n, paramArr) N_PARAM##n(paramArr)
#define callAction(n, action, paramArr) ({ \
    unsigned int ret = (unsigned int)0; \
    switch(n){ \
        case 0: \
        ret = ((ACTION_N(0))action)N_PARAM(0, paramArr); \
        break; \
        case 1: \
        ret = ((ACTION_N(1))action)N_PARAM(1, paramArr); \
        break; \
        case 2: \
        ret = ((ACTION_N(2))action)N_PARAM(2, paramArr); \
        break; \
        case 3: \
        ret = ((ACTION_N(3))action)N_PARAM(3, paramArr); \
        break; \
        case 4: \
        ret = ((ACTION_N(4))action)N_PARAM(4, paramArr); \
        break; \
    } \
    ret; \
})

// =============== for condition ===============
#define GET_CONDITION_VAR(n) ( \
    n==10?a:( \
        n==11?b:( \
            n==12?c:( \
                n==13?d:( \
                    n==14?e:f )))))

#define SET_CONDITION_VAR(n, v) ( \
    n==10?(a=v):( \
        n==11?(b=v):( \
            n==12?(c=v):( \
                n==13?(d=v):( \
                    n==14?(e=v):(1?(f=v):0))))))
unsigned int a, b, c, d, e, f;
// =============== for condition ===============



unsigned int getFruitSayBeachReturn87(unsigned int fruit) {
    printf("Fruit = %d\n", fruit);
    printf("Beach\n");
    return (unsigned int)87;
}

unsigned int sayBeachReturn87(void) {
    a = 102;
    b = 101;
    printf("Beach\n");
    return (unsigned int)87;
}

void* actionTable[] = { getFruitSayBeachReturn87, sayBeachReturn87 };