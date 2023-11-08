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
    unsigned long rsp;
    unsigned long rbp;
    unsigned long rip;
    unsigned long rbx;
    unsigned long r12;
    unsigned long r13;
    unsigned long r14;
    unsigned long r15;
};

struct task_struct {
    struct context *context;
    void (*func)();
};

struct task_struct *current;

void print_context( struct context *ctx)
{
    printf("rsp: %p\n", ctx->rsp);
    printf("rbp: %p\n", ctx->rbp);
    printf("rip: %p\n", ctx->rip);
    printf("rbx: %p\n", ctx->rbx);
    printf("r12: %p\n", ctx->r12);
    printf("r13: %p\n", ctx->r13);
    printf("r14: %p\n", ctx->r14);
    printf("r15: %p\n", ctx->r15);
}

void switch_to_task(struct task_struct *next)
{
    printf("switching to task\n");
    struct task_struct *prev = current;
    current = next;
    switch_to(prev->context, next->context);
}

void switch_to(struct context *from, struct context *to)
{
    if (from == to)
        return;
    if (from != NULL)
        save_context(from);
    restore_context(to);
}

void restore_context( struct context *context)
{
    printf("restoring context\n");


    __asm__ __volatile__(
        "pushq %%rbp\n\t"
        "pushq %%r15\n\t"
        "pushq %%r14\n\t"
        "pushq %%r13\n\t"
        "pushq %%r12\n\t"
        "pushq %%rbx\n\t"
        "pushq %%rbp\n\t"
        "movq %%rsp, %0\n\t"
        "movq %1, %%rsp\n\t"
        "popq %%rbp\n\t"
        "ret\n\t"
        :
        : "r"(context->rsp), "r"(context->rsp)
        :);
}

void save_context(struct context *ctx)
{
    // save registers
    asm volatile (
        "movq %%rsp, %0;"
        "movq %%rbp, %1;"
        "movq %%rbx, %2;"
        "movq %%r12, %3;"
        "movq %%r13, %4;"
        "movq %%r14, %5;"
        "movq %%r15, %6;"
        : "=m" (ctx->rsp), "=m" (ctx->rbp), "=m" (ctx->rbx), "=m" (ctx->r12),
          "=m" (ctx->r13), "=m" (ctx->r14), "=m" (ctx->r15)
        :
        : "memory"
    );
}

void func1() {
    // fill up some registers
    __asm__ __volatile__(
        "movq $0x1, %%rbx\n\t"
        "movq $0x2, %%r12\n\t"
        "movq $0x3, %%r13\n\t"
        "movq $0x4, %%r14\n\t"
        "movq $0x5, %%r15\n\t"
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
    struct context *context1 = (struct context *)malloc(sizeof(struct context));
    struct context *context2 = (struct context *)malloc(sizeof(struct context));
    struct context *context3 = (struct context *)malloc(sizeof(struct context));

    context1->rsp = (unsigned long)malloc(4096) + 4096;
    context2->rsp = (unsigned long)malloc(4096) + 4096;
    context3->rsp = (unsigned long)malloc(4096) + 4096;

    context1->rbp = context1->rsp;
    context2->rbp = context2->rsp;
    context3->rbp = context3->rsp;

    context1->rip = (unsigned long)func1;
    context2->rip = (unsigned long)func2;
    context3->rip = (unsigned long)func3;

    context1->rbx = 0;
    context2->rbx = 0;
    context3->rbx = 0;

    context1->r12 = 0;
    context2->r12 = 0;
    context3->r12 = 0;
    
    context1->r13 = 0;
    context2->r13 = 0;
    context3->r13 = 0;

    context1->r14 = 0;
    context2->r14 = 0;
    context3->r14 = 0;

    context1->r15 = 0;
    context2->r15 = 0;
    context3->r15 = 0;

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
    current->func();
    
    print_context(current->context);
    struct context *tmp = (struct context *)malloc(sizeof(struct context));
    save_context(tmp);
    print_context(tmp);

    //switch_to_task(task2);
    //current->func();
    //switch_to_task(task3);
    //current->func();
}