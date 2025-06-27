#ifndef UTIL_H
#define UTIL_H

#include <errno.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>

//------------------------------------------------------------------------------
#define minimum(X, Y) ((X < Y) ? X : Y)
#define maximum(X, Y) ((X > Y) ? X : Y)
#define addr_of(P) ((void *)&P)
#define deref(P) (*((void **)P))
//------------------------------------------------------------------------------
// FUNCTION: MMOVE
// memory move using quadword (64-bits)
// 2023-11-24
// J. McIntosh
//
// WARNING: THIS ROUTINE DOES NOT HANDLE THE OVERLAPPING SOURCE-DESTINATION
//          SENARIO.
//
void * memmove64 (void *, void const *, size_t);
//------------------------------------------------------------------------------
// STRUCTURE: LIST
// 2023-12-31
// J. McIntosh
//
typedef struct list list_t;

struct list {
  size_t      o_size;
  size_t      s_size;
  void      * iter;
  void      * next;
#define   blkend    next
  void      * bufend;
  void      * buffer;
};

#define list_alloc() (calloc(1, sizeof(list_t)))
#define list_free(P) (free(P))

int list_add (list_t *, void const *);

void * list_at (list_t *, size_t const);

void * list_begin (list_t *);

size_t list_count (list_t const *);

void * list_curr (list_t *);

int list_delete (list_t *, void const *,
    int (*find_cb) (void const *, void const *),
    void (*delete_cb) (void *));

void * list_end (list_t *);

void * list_find (list_t const *, void const *,
    int (*find_cb) (void const *, void const *));

int list_init (list_t *, size_t const);

void * list_next (list_t *);

size_t list_object_size (list_t *);

void * list_pred (list_t *);

void * list_prev (list_t *);

void list_remove (list_t *, void const *, void (*delete_cb) (void *));

size_t list_slot_size (list_t *);

void list_sort (list_t *,
    int (*sort_cb) (void const *, void const *));

void * list_succ (list_t *);

void list_term (list_t *);

//------------------------------------------------------------------------------
// STRUCTURE: LIFO
// 2025-02-22
// J. McIntosh
//
typedef struct lifo lifo_t;

struct lifo {
  void *      head;
  void *      end;
  void *      buffer;
};

#define lifo_alloc() (calloc(1, sizeof(lifo_t)))
#define lifo_free(P) (free(P), P = NULL)

int lifo_empty (lifo_t *);
int lifo_full (lifo_t *);
int lifo_init (lifo_t *, size_t const);
void * lifo_pop (lifo_t *);
void * lifo_push (lifo_t *, void const *);
void lifo_term (lifo_t *);
void * lifo_top (lifo_t *);

//------------------------------------------------------------------------------
// STRUCTURE: QUEUE
// 2024-03-11
// J. McIntosh
//
typedef struct queue queue_t;

struct queue {
  size_t      o_size;
  size_t      s_size;
  void *      head;
  void *      tail;
  void *      bufend;
  void *      buffer;
};

#define queue_alloc() (calloc(1, sizeof(queue_t)))
#define queue_free(P) (free(P), P = NULL)

int queue_empty (queue_t *);
int queue_full (queue_t *);
void * queue_init (queue_t *, size_t const, size_t const);
int queue_deque (queue_t *, void *);
int queue_enque (queue_t *, void const *);
void queue_term (queue_t *);
//------------------------------------------------------------------------------
// STRUCTURE: STACK
// 2024-10-17
// J. McIntosh
//
typedef struct stack t_stack;

struct stack {
  size_t      o_size;
  size_t      s_size;
  void *      head;
  void *      end;
  void *      buffer;
};

#define stack_alloc() (calloc(1, sizeof(t_stack)))
#define stack_free(P) (free(P), P = NULL)

int stack_empty (t_stack *);
int stack_full (t_stack *);
void * stack_init (t_stack *, size_t const, size_t const);
int stack_pop (t_stack *, void *);
int stack_push (t_stack *, void const *);
void stack_term (t_stack *);
//------------------------------------------------------------------------------
// FUNCTION: SUBSTRING
// 2024-01-20
// J. McIntosh
//
char * substring (char const *, size_t, size_t);
//------------------------------------------------------------------------------
// FUNCTION: STRUPPER
// 2024-01-20
// J. McIntosh
//
char * strupper (char *);
//------------------------------------------------------------------------------
// FUNCTION: GET_ERRNO
// 2024-02-25
// J. McIntosh
//
int get_errno (void);
//------------------------------------------------------------------------------
// FUNCTION: CLR_ERRNO
// 2024-02-25
// J. McIntosh
//
void clr_errno (void);
#endif
