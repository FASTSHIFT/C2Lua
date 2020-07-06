#ifndef __TEST_H
#define __TEST_H

/*stdint.h*/
#include <stdint.h>

#define __Sizeof(arr) (sizeof(arr)/sizeof(arr[0]))
#define MAX(a,b) ((a)>(b)?(a):(b))

extern int value;

char* CFunction(int a,float b,const char* c);
uint32_t millis();
double getsum(float n1, float n2);
char *getStr(void);

typedef struct{ int a; int b;} struct_t;
enum {A, B};


unsigned long gpio_set(uint8_t pin, bool val);
const char * UserInput();
void Nop();
double* testFunc(float* n1, int* n2, const char* str);

#endif
