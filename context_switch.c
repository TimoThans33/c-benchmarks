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
    unsigned long sp;
    unsigned long tp;
    unsigned long ra;
    unsigned long pc;
    unsigned long a0;
    unsigned long a1;
    unsigned long a2;
    unsigned long a3;
};

struct task_struct {
    // Our PC Block
    struct context *context;
    void (*func)();
};

struct task_struct *current;

void print_context( struct context *ctx)
{
    printf("sp: %p\n", ctx->sp);
    printf("tp: %p\n", ctx->tp);
    printf("ra: %p\n", ctx->ra);
    printf("a0: %p\n", ctx->a0);
    printf("a1: %p\n", ctx->a1);
    printf("a2: %p\n", ctx->a2);
    printf("a3: %p\n", ctx->a3);
}

// void switch_to_task(struct task_struct *next)
// {
//     printf("switching to task\n");
//     struct task_struct *prev = current;
//     current = next;
//     switch_to(prev->context, next->context);
// }

// void switch_to(struct context *from, struct context *to)
// {
//     if (from == to)
//         return;
//     if (from != NULL)
//         save_context(from);
//     restore_context(to);
// }

// void restore_context( struct context *context)
// {
//     printf("restoring context\n");


//     __asm__ __volatile__(
//         "pushq %%rbp\n\t"
//         "pushq %%r15\n\t"
//         "pushq %%r14\n\t"
//         "pushq %%r13\n\t"
//         "pushq %%r12\n\t"
//         "pushq %%rbx\n\t"
//         "pushq %%rbp\n\t"
//         "movq %%rsp, %0\n\t"
//         "movq %1, %%rsp\n\t"
//         "popq %%rbp\n\t"
//         "ret\n\t"
//         :
//         : "r"(context->rsp), "r"(context->rsp)
//         :);
// }

void get_PC(struct context *ctx)
{
    // checkout a0 and get PC
    asm volatile (
        "sw a0, %0;"
        "auipc a0, 0;"
        "jalr zero, a0, 0;"
        "sw a0, %1;"
        : "=m" (ctx->a0), "=m" (ctx->pc) 
        :
        : "memory"
    );
}

void save_context(struct context *ctx)
{
    // store the program counter 
    // get_PC(ctx);
    // save registers
    asm volatile (
        "sw sp, %0;"
        "sw a1, %1;"
        "sw a2, %2;"
        "sw a3, %3;"
        "sw ra, %4;"
        : "=m" (ctx->a0), "=m" (ctx->a1), "=m" (ctx->a2), "=m" (ctx->a3), "=m" (ctx->ra)
        :
        : "memory"
    );
}

void func1() {
    // fill up some registers
    __asm__ __volatile__(
        "addi a0, a0, 0x04\n\t"
        "addi a1, a1, 0x08\n\t"
        "addi a2, a2, 0x0b\n\t"
        "addi a3, a3, 0x0f\n\t"
        :
        :);
    printf("func1: started\n");
}

void func2() {
    printf("func2: started\n");
}

void func3() {
    printf("func3: started\n");
}

int main() {
    // Create space on the stack for the register files
    struct context *context1 = (struct context *)malloc(sizeof(struct context));
    struct context *context2 = (struct context *)malloc(sizeof(struct context));
    struct context *context3 = (struct context *)malloc(sizeof(struct context));

    // Assign space for the task and return the stack pointer
    context1->sp = (unsigned long)malloc(4096) + 4096;
    context2->sp = (unsigned long)malloc(4096) + 4096;
    context3->sp = (unsigned long)malloc(4096) + 4096;

    context1->pc = 0;
    context2->pc = 0;
    context3->pc = 0;

    context1->a0 = 0;
    context2->a0 = 0;
    context3->a0 = 0;
    
    context1->a1 = 0;
    context2->a1 = 0;
    context3->a1 = 0;

    context1->a2 = 0;
    context2->a2 = 0;
    context3->a2 = 0;

    context1->a3 = 0;
    context2->a3 = 0;
    context3->a3 = 0;

    struct task_struct *task1 = (struct task_struct *)malloc(sizeof(struct task_struct));
    struct task_struct *task2 = (struct task_struct *)malloc(sizeof(struct task_struct));
    struct task_struct *task3 = (struct task_struct *)malloc(sizeof(struct task_struct));

    task1->context = context1;
    task2->context = context2;
    task3->context = context3;

    task1->func = func1;
    task2->func = func2;
    task3->func = func3;

    current = task1;
    print_context(current->context);
    current->func();
    struct context *tmp = (struct context *)malloc(sizeof(struct context));
    save_context(tmp);
    print_context(tmp);
    //switch_to_task(task2);
    //current->func();
    //switch_to_task(task3);
    //current->func();
}