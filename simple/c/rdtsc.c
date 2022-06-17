#include <stdio.h>
#include <unistd.h>

typedef unsigned long long int hp_timing_t;

typedef hp_timing_t timing_t;
typedef unsigned long uint64_t;


# ifdef USE_RDTSCP
#  define HP_TIMING_NOW(Var) \
  (__extension__ ({				\
    unsigned int __aux;				\
    (Var) = __builtin_ia32_rdtscp (&__aux);	\
  }))
# else
#  define HP_TIMING_NOW(Var) ((Var) = __builtin_ia32_rdtsc ())
# endif

#define HP_TIMING_DIFF(Diff, Start, End)	((Diff) = (End) - (Start))
#define HP_TIMING_ACCUM_NT(Sum, Diff)		((Sum) += (Diff))

#define TIMING_NOW(var) HP_TIMING_NOW (var)
#define TIMING_DIFF(diff, start, end) HP_TIMING_DIFF ((diff), (start), (end))
#define TIMING_ACCUM(sum, diff) HP_TIMING_ACCUM_NT ((sum), (diff))

int main(){
    timing_t start, end;
    uint64_t cur;
    TIMING_NOW (start);
    sleep(1);
    TIMING_NOW (end);
    TIMING_DIFF (cur, start, end);
    printf("%lld \n",cur);
}