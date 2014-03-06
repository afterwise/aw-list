
/*
   Copyright (c) 2014 Malte Hildingsson, malte (at) afterwi.se

   Permission is hereby granted, free of charge, to any person obtaining a copy
   of this software and associated documentation files (the "Software"), to deal
   in the Software without restriction, including without limitation the rights
   to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
   copies of the Software, and to permit persons to whom the Software is
   furnished to do so, subject to the following conditions:

   The above copyright notice and this permission notice shall be included in
   all copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
   AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
   OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
   THE SOFTWARE.
 */

#ifndef AW_LIST_H
#define AW_LIST_H

#include <stdbool.h>
#include <stddef.h>

#if __GNUC__
# define _list_alwaysinline inline __attribute__((always_inline, nodebug))
#elif _MSC_VER
# define _list_alwaysinline __forceinline
#endif

#ifdef __cplusplus
extern "C" {
#endif

struct list {
	struct list *prev;
	struct list *next;
};

_list_alwaysinline void list_init(struct list *list) {
	list->prev = list;
	list->next = list;
}

_list_alwaysinline bool list_empty(const struct list *list) {
	return list->next == list;
}

_list_alwaysinline bool list_singular(const struct list *list) {
	return list->next != list && list->next == list->prev;
}

_list_alwaysinline int list_count(const struct list *list) {
	struct list *it;
	int n = 0;

	for (it = list->next; it != list; it = it->next)
		++n;

	return n;
}

_list_alwaysinline void list_add_front(struct list *list, struct list *elem) {
	elem->prev = list;
	elem->next = list->next;
	list->prev->next = elem;
	list->next = elem;
}

_list_alwaysinline void list_add_back(struct list *list, struct list *elem) {
	elem->next = list;
	elem->prev = list->prev;
	list->prev->next = elem;
	list->prev = elem;
}

_list_alwaysinline void *list_front(struct list *list) {
	return (list->next != list) ? list->next : NULL;
}

_list_alwaysinline void *list_back(struct list *list) {
	return (list->next != list) ? list->prev : NULL;
}

_list_alwaysinline void list_remove(struct list *elem) {
	elem->next->prev = elem->prev;
	elem->prev->next = elem->next;
}

_list_alwaysinline void list_replace(struct list *old_elem, struct list *new_elem) {
	new_elem->next = old_elem->next;
	new_elem->next->prev  = new_elem;
	new_elem->prev = old_elem->prev;
	new_elem->prev->next = new_elem;
}

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* AW_LIST_H */

