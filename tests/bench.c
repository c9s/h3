/*
 * bench.c
 * Copyright (C) 2014 c9s <c9s@c9smba.local>
 *
 * Distributed under terms of the MIT license.
 */
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <sys/time.h>
#include <stdarg.h>     /* va_list, va_start, va_arg, va_end */
#include "bench.h"

unsigned long unixtime() {
    struct timeval tp;
    if (gettimeofday((struct timeval *) &tp, (NUL)) == 0) {
        return tp.tv_sec;
    }
    return 0;
}

double microtime() {
    struct timeval tp;
    long sec = 0L;
    double msec = 0.0;
    if (gettimeofday((struct timeval *) &tp, (NUL)) == 0) {
        msec = (double) (tp.tv_usec / MICRO_IN_SEC);
        sec = tp.tv_sec;
        if (msec >= 1.0)
            msec -= (long) msec;
        return sec + msec;
    }
    return 0;
}

void bench_start(bench *b) {
    b->start = microtime();
}

void bench_stop(bench *b) {
    b->end = microtime();
}

double bench_iteration_speed(bench *b) {
    return (b->N * b->R) / (b->end - b->start);
}

double bench_duration(bench *b) {
    return (b->end - b->start);
}

void bench_print_summary(bench *b) {
    printf("%ld runs, ", b->R);
    printf("%ld iterations each run, ", b->N);
    printf("finished in %lf seconds\n", bench_duration(b) );
    printf("%.2f i/sec\n", bench_iteration_speed(b) );
}

/**
 * Combine multiple benchmark result into one measure entry.
 *
 * bench_append_csv("benchmark.csv", 3, &b1, &b2)
 */
void bench_append_csv(char *filename, int countOfB, ...) {
    FILE *fp = fopen(filename, "a+");
    if(!fp) {
        return;
    }

    unsigned long ts = unixtime();
    fprintf(fp, "%ld", ts);


    int i;
    bench * b;
    va_list vl;
    va_start(vl,countOfB);
    for (i=0 ; i < countOfB ; i++) {
        b = va_arg(vl, bench*);
        fprintf(fp, ",%.2f", bench_iteration_speed(b) );
    }
    va_end(vl);

    fprintf(fp, "\n");
    fclose(fp);
}



int main()
{
    MEASURE(tree_compile)
    // r3_tree_compile(n, NULL);
    END_MEASURE(tree_compile)

    BENCHMARK(str_dispatch)
    // r3_tree_matchl(n , "/qux/bar/corge", strlen("/qux/bar/corge"), NULL);
    END_BENCHMARK(str_dispatch)
    BENCHMARK_SUMMARY(str_dispatch);

    BENCHMARK(pcre_dispatch)
    // r3_tree_matchl(tree2, "/post/2014/12", strlen("/post/2014/12"), NULL);
    END_BENCHMARK(pcre_dispatch)
    BENCHMARK_SUMMARY(pcre_dispatch);

    BENCHMARK_RECORD_CSV("bench_str.csv", 4, BR(str_dispatch), BR(pcre_dispatch), BR(tree_compile), BR(str_match_entry) );
    return 0;
}
