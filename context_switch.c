/**
 * @file context_switch.c
 * @author your name (you@domain.com)
 * @brief context switch in RISC-V
 * @version 0.1
 * @date 2023-11-06
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <stdio.h>
#include <stdlib.h>

struct context {
    // Our register
    unsigned long ra;
    unsigned long sp;
    unsigned long gp;
    unsigned long tp;

    unsigned long t0, t1, t2;

    unsigned long s0, s1;

    unsigned long a0, a1, a2, a3, a4, a5, a6, a7;
    unsigned long s2, s3, s4, s5, s6, s7, s8, s9, s10, s11;
    unsigned long t3, t4, t5, t6;

    // floating point registers
    double f0, f1, f2, f3, f4, f5, f6, f7;
    double f8, f9;
    double f10, f11;
    double f12, f13, f14, f15, f16, f17;
    double f18, f19, f20, f21, f22, f23, f24, f25, f26, f27;
    double f28, f29, f30, f31;
};

struct task_struct {
    // Our PC Block
    struct context *context;
    void (*func)();
    // Cancelation flag
    int cancel;
    int cancel_successful;
};

struct task_struct *current;

void thread_cancel(struct task_struct *ts)
{
    
}

// all functions should periodically check if the task should be canceled
int thread_testcancel(struct task_struct *ts) {
    if (ts->cancel==1) { ts->cancel_successful; }
    return ts->cancel;
}

unsigned long read_cycles(void)
{
    unsigned long cycles;
    asm volatile ("rdcycle %0" : "=r" (cycles));
    return cycles;
}

void print_context( struct context *ctx)
{
    printf("ra: %p\n", ctx->ra);
    printf("sp: %p\n", ctx->sp);
    printf("gp: %p\n", ctx->gp);
    printf("tp: %p\n", ctx->tp);

    printf("t0: %p\n", ctx->t0);
    printf("t1: %p\n", ctx->t1);
    printf("t2: %p\n", ctx->t2);

    printf("s0: %p\n", ctx->s0);
    printf("s1: %p\n", ctx->s1);

    printf("a0: %p\n", ctx->a0);
    printf("a1: %p\n", ctx->a1);
    printf("a2: %p\n", ctx->a2);
    printf("a3: %p\n", ctx->a3);
    printf("a4: %p\n", ctx->a4);
    printf("a5: %p\n", ctx->a5);
    printf("a6: %p\n", ctx->a6);
    printf("a7: %p\n", ctx->a7);

    printf("s2: %p\n", ctx->s2);
    printf("s3: %p\n", ctx->s3);
    printf("s4: %p\n", ctx->s4);
    printf("s5: %p\n", ctx->s5);
    printf("s6: %p\n", ctx->s6);
    printf("s7: %p\n", ctx->s7);
    printf("s8: %p\n", ctx->s8);
    printf("s9: %p\n", ctx->s9);
    printf("s10: %p\n", ctx->s10);
    printf("s11: %p\n", ctx->s11);

    printf("t3: %p\n", ctx->t3);
    printf("t4: %p\n", ctx->t4);
    printf("t5: %p\n", ctx->t5);
    printf("t6: %p\n", ctx->t6);

    printf("f0: %p\n", ctx->f0);
    printf("f1: %p\n", ctx->f1);
    printf("f2: %p\n", ctx->f2);
    printf("f3: %p\n", ctx->f3);
    printf("f4: %p\n", ctx->f4);
    printf("f5: %p\n", ctx->f5);
    printf("f6: %p\n", ctx->f6);
    printf("f7: %p\n", ctx->f7);

    printf("fs0: %p\n", ctx->f8);
    printf("fs1: %p\n", ctx->f9);

    printf("fa0: %p\n", ctx->f10);
    printf("fa1: %p\n", ctx->f11);
    
    printf("fa2: %p\n", ctx->f12);
    printf("fa3: %p\n", ctx->f13);
    printf("fa4: %p\n", ctx->f14);
    printf("fa5: %p\n", ctx->f15);
    printf("fa6: %p\n", ctx->f16);
    printf("fa7: %p\n", ctx->f17);

    printf("fs2: %p\n", ctx->f18);
    printf("fs3: %p\n", ctx->f19);
    printf("fs4: %p\n", ctx->f20);
    printf("fs5: %p\n", ctx->f21);
    printf("fs6: %p\n", ctx->f22);
    printf("fs7: %p\n", ctx->f23);
    printf("fs8: %p\n", ctx->f24);
    printf("fs9: %p\n", ctx->f25);
    printf("fs10: %p\n", ctx->f26);
    printf("fs11: %p\n", ctx->f27);
    
    printf("ft8: %p\n", ctx->f28);
    printf("ft9: %p\n", ctx->f29);
    printf("ft10: %p\n", ctx->f30);
    printf("ft11: %p\n", ctx->f31);
}


void restore_context( struct context *context)
{
    unsigned long start = read_cycles();
    __asm__ __volatile__(
        "lw t0, %0;"
        "lw t1, %1;"
        "lw t2, %2;"
        
        "lw a0, %3;"
        "lw a1, %4;"
        "lw a2, %5;"
        "lw a3, %6;"
        "lw a4, %7;"

        "lw s2, %8;"
        "lw s3, %9;"
        "lw s4, %10;"
        "lw s5, %11;"
        "lw s6, %12;"
        "lw s7, %13;"
        "lw s8, %14;"
        
        "lw t3, %15;"
        "lw t4, %16;"
        "lw t5, %17;"
        "lw t6, %18;"

        "flw f0, %19;"
        "flw f1, %20;"
        :
        : "m"(context->ra), "m"(context->sp), "m"(context->gp), "m"(context->tp), "m"(context->t0), "m"(context->t1), "m"(context->t2), "m"(context->s0), "m"(context->s1), "m"(context->s2), "m"(context->a0), "m"(context->a1), "m"(context->a2), "m"(context->a3), "m"(context->a4), "m"(context->s2), "m"(context->s3), "m"(context->s4), "m"(context->s5), "m"(context->s6), "m"(context->s7), "m"(context->s8), "m"(context->t3), "m"(context->t4), "m"(context->t5), "m"(context->t6), "m"(context->f0), "m"(context->f1)
        : "t0", "t1", "t2", "s0", "s1", 
            "a0", "a1", "a2", "a3", "a4",
            "s2", "s3", "s4", "s5", "s6", "s7", "s8",
            "t3", "t4", "t5", "t6",
            "f0", "f1");

    __asm__ __volatile__(
        "flw f2, %0;"
        "flw f3, %1;"
        "flw f4, %2;"
        "flw f5, %3;"
        "flw f6, %4;"
        "flw f7, %5;" 
        "flw f8, %6;"
        "flw f9, %7;" 
        "flw f10, %8;"
        "flw f11, %9;" 
        "flw f12, %10;"
        "flw f13, %11;"
        "flw f14, %12;"
        "flw f15, %13;"
        "flw f16, %14;"
        "flw f17, %15;"
        "flw f18, %16;"
        "flw f19, %17;"
        "flw f20, %18;"
        "flw f21, %19;"
        "flw f22, %20;"
        "flw f23, %21;"
        "flw f24, %22;"
        "flw f25, %23;"
        :
        : "m"(context->f2), "m"(context->f3), "m"(context->f4), "m"(context->f5), "m"(context->f6), "m"(context->f7), "m"(context->f8), "m"(context->f8), "m"(context->f9), "m"(context->f10),"m"(context->f11), "m"(context->f12), "m"(context->f13), "m"(context->f14), "m"(context->f15), "m"(context->f16), "m"(context->f17), "m"(context->f18), "m"(context->f19), "m"(context->f20), "m"(context->f21), "m"(context->f22), "m"(context->f23), "m"(context->f24), "m"(context->f25)
        : "f2", "f3", "f4", "f5", "f6", "f7",
            "f8", "f9", "f10", "f11", "f12", "f13", "f14", "f15", "f16", "f17",
            "f18", "f19", "f20", "f21", "f22", "f23", "f24", "f25");
    printf("total cycles context restore: %ld", read_cycles()-start);
    printf("\n");
}

void save_context(struct context *context)
{
    unsigned long start = read_cycles();
    __asm__ __volatile__(
        "sw t0, %0;"
        "sw t1, %1;"
        "sw t2, %2;"
        "sw a0, %3;"
        "sw a1, %4;"
        "sw a2, %5;"
        "sw a3, %6;"
        "sw a4, %7;"
        "sw s2, %8;"
        "sw s3, %9;"
        "sw s4, %10;"
        "sw s5, %11;"
        "sw s6, %12;"
        "sw s7, %13;"
        "sw s8, %14;"
        "sw t3, %15;"
        "sw t4, %16;"
        "sw t5, %17;"
        "sw t6, %18;"
        "fsw f0, %19;"
        "fsw f1, %20;"
        : "=m"(context->ra), "=m"(context->sp), "=m"(context->gp), "=m"(context->tp), "=m"(context->t0), "=m"(context->t1), "=m"(context->t2), "=m"(context->s0), "=m"(context->s1), "=m"(context->s2), "=m"(context->a0), "=m"(context->a1), "=m"(context->a2), "=m"(context->a3), "=m"(context->a4), "=m"(context->s2), "=m"(context->s3), "=m"(context->s4), "=m"(context->s5), "=m"(context->s6), "=m"(context->s7), "=m"(context->s8), "=m"(context->t3), "=m"(context->t4), "=m"(context->t5), "=m"(context->t6), "=m"(context->f0), "=m"(context->f1)
        :
        : "memory");

    __asm__ __volatile__(
        "fsw f2, %0;"
        "fsw f3, %1;"
        "fsw f4, %2;"
        "fsw f5, %3;"
        "fsw f6, %4;"
        "fsw f7, %5;"
        "fsw f8, %6;"
        "fsw f9, %7;"
        "fsw f10, %8;"
        "fsw f11, %9;"
        "fsw f12, %10;"
        "fsw f13, %11;"
        "fsw f14, %12;"
        "fsw f15, %13;"
        "fsw f16, %14;"
        "fsw f17, %15;"
        "fsw f18, %16;"
        "fsw f19, %17;"
        "fsw f20, %18;"
        "fsw f21, %19;"
        "fsw f22, %20;"
        "fsw f23, %21;"
        "fsw f24, %22;"
        "fsw f25, %23;"
        : "=m"(context->f2), "=m"(context->f3), "=m"(context->f4), "=m"(context->f5), "=m"(context->f6), "=m"(context->f7), "=m"(context->f8), "=m"(context->f8), "=m"(context->f9), "=m"(context->f10),"=m"(context->f11), "=m"(context->f12), "=m"(context->f13), "=m"(context->f14), "=m"(context->f15), "=m"(context->f16), "=m"(context->f17), "=m"(context->f18), "=m"(context->f19), "=m"(context->f20), "=m"(context->f21), "=m"(context->f22), "=m"(context->f23), "=m"(context->f24), "=m"(context->f25)
        : 
        : "memory");
    printf("total cycles context save: %ld", read_cycles()-start);
    printf("\n");
}

void func1() {
    // threader function
    int a = 10;
    int b = 20;
    int result;

    __asm__ volatile (
        "add %0, %1, %2"   // Add a and b, store the result in 'result'
        : "=r" (result)    // Output operands
        : "r" (a), "r" (b) // Input operands
    );

    printf("The result in func 1 is %d\n", result);
}

void func2() {
    int a = 1;
    int b = 1;
    int result;
    int i;

    for (i = 0; i < 1000; i++) {
        __asm__ volatile (
            "add %0, %1, %2"   // Add a and b, store the result in 'result'
            : "=r" (result)    // Output operands
            : "r" (a), "r" (b) // Input operands
        );
    }
    printf("The result in func 2 is %d\n", result);
}

void func3() {
    printf("func3: started\n");
}

int main() {
    // Create space on the stack for the register files
    struct context *context1 = (struct context *)calloc(1, sizeof(struct context ));
    struct context *context2 = (struct context *)calloc(1, sizeof(struct context ));
    struct context *context3 = (struct context *)calloc(1, sizeof(struct context ));
    // Create space on the stack for the PCB (program control block)
    struct task_struct *task1 = (struct task_struct *)malloc(sizeof(struct task_struct));
    struct task_struct *task2 = (struct task_struct *)malloc(sizeof(struct task_struct));
    struct task_struct *task3 = (struct task_struct *)malloc(sizeof(struct task_struct));
    // Link all the register files to a task
    task1->context = context1;
    task2->context = context2;
    task3->context = context3;
    // Link the function point to the task
    task1->func = func1;
    task2->func = func2;
    task3->func = func3;
    // Simulate a simple scheduler
    for (int i; i<10; i++)
    {
        // Set current task and print status
        current = task1;
        restore_context(current->context);
        print_context(current->context);
        // Execute function
        current->func();
        // Tell task to stop (it should automatically store it's context, right?)
        save_context(current->context);
        print_context(current->context);
        // Execute new task
        current = task2;
        restore_context(current->context);
        print_context(current->context);
        current->func();
        save_context(current->context);
        print_context(current->context);
    }
}