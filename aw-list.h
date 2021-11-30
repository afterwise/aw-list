
/*
   Copyright (c) 2014-2021 Malte Hildingsson, malte (at) afterwi.se

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

#if !_MSC_VER || _MSC_VER >= 1800
# include <stdbool.h>
#endif
#include <stddef.h>

#if __GNUC__
# define _list_alwaysinline inline __attribute__((always_inline))
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

#define list_object(link,type,member) \
	((type *) ((char *) (link) - offsetof(type, member)))

_list_alwaysinline bool list_empty(const struct list *list) {
	return list->next == list;
}

_list_alwaysinline bool list_singular(const struct list *list) {
	return list->next != list && list->next == list->prev;
}

_list_alwaysinline size_t list_count(const struct list *list) {
	struct list *it;
	size_t n = 0;
	for (it = list->next; it != list; it = it->next)
		++n;
	return n;
}

_list_alwaysinline struct list *list_begin(struct list *list) {
	return list->next;
}

_list_alwaysinline struct list *list_end(struct list *list) {
	return list;
}

_list_alwaysinline void list_add_front(struct list *list, struct list *link) {
	link->prev = list;
	link->next = list->next;
	list->prev->next = link;
	list->next = link;
}

_list_alwaysinline void list_add_back(struct list *list, struct list *link) {
	link->next = list;
	link->prev = list->prev;
	list->prev->next = link;
	list->prev = link;
}

_list_alwaysinline struct list *list_front(struct list *list) {
	return (list->next != list) ? list->next : NULL;
}

_list_alwaysinline struct list *list_back(struct list *list) {
	return (list->prev != list) ? list->prev : NULL;
}

_list_alwaysinline void list_remove(struct list *link) {
	link->next->prev = link->prev;
	link->prev->next = link->next;
}

_list_alwaysinline struct list *list_remove_front(struct list *list) {
	struct list *link = list->next;
	return (link != list) ? list_remove(link), link : NULL;
}

_list_alwaysinline struct list *list_remove_back(struct list *list) {
	struct list *link = list->prev;
	return (link != list) ? list_remove(link), link : NULL;
}

_list_alwaysinline void list_replace(struct list *old_link, struct list *new_link) {
	new_link->next = old_link->next;
	new_link->next->prev  = new_link;
	new_link->prev = old_link->prev;
	new_link->prev->next = new_link;
}

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* AW_LIST_H */

