/*------------------------------------------------------------------------------
    JSON (JSON) Library Implementation in C with Assembly Language Support
    Libraries

    Copyright (C) 2025  J. McIntosh

    JSON is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    JSON is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along
    with JSON; if not, write to the Free Software Foundation, Inc.,
    51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
------------------------------------------------------------------------------*/
#ifndef UTIL_H
#define UTIL_H  1

#include <stddef.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
//------------------------------------------------------------------------------
//
void * memmove64 (void *, void const *, size_t);

//------------------------------------------------------------------------------
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
//
char * substring (char const *, size_t, size_t);

#endif
