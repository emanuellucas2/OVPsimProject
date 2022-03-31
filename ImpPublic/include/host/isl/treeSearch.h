/*
 *
 * Copyright (c) 2005-2021 Imperas Software Ltd., www.imperas.com
 *
 * The contents of this file are provided under the Software License Agreement
 * that you accepted before downloading this file.
 *
 * This header forms part of the Software but may be included and used unaltered
 * in derivative works.
 *
 * For more information, please visit www.OVPworld.org or www.imperas.com
 */

#ifndef _TREESEARCH_H
#define    _TREESEARCH_H

/* The treeSearch routines are very interesting. They make many
   assumptions about the compiler.  It assumes that the first field
   in node must be the "key" field, which points to the datum.
   Everything depends on that.  */
/* For treeSearch */
typedef enum
{
  VISIT_preorder,
  VISIT_postorder,
  VISIT_endorder,
  VISIT_leaf
}
VISIT;

#ifndef __COMPAR_FN_T
# define __COMPAR_FN_T
typedef int (*__compar_fn_t) (const void *, const void *);
#endif

#ifndef __ACTION_FN_T
# define __ACTION_FN_T
typedef void (*__action_fn_t) (const void *__nodep, VISIT __value,
                   int __level, void *userData);
#endif

/* Callback type for function to free a tree node.  If the keys are atomic
   data this function should do nothing.  */
#ifndef __FREE_FN_T
# define __FREE_FN_T
typedef void (*__free_fn_t) (void *__nodep, void *__userData);
#endif



/* Search for an entry matching the given KEY in the tree pointed to
   by *ROOTP and insert a new element if not found using  a memory pool.
   memPoolHead is the address of a pointer (provided by caller)
   to the first free element  */
extern void *treeSearchMPool (const void *__key, void **__rootp,
              __compar_fn_t __compar, void **memPoolHead);

/* same as treeSearchMPool but with no memory pool */
#define treeSearch(_K, _R, _C) treeSearchMPool((_K), (_R), (_C), NULL)

/* Search for an entry matching the given KEY in the tree pointed to
   by *ROOTP.  If no matching entry is available return NULL.  */
extern void *treeFind (const void *__key, void *const *__rootp,
            __compar_fn_t __compar);

/* Remove the element matching KEY from the tree pointed to by *ROOTP
   using  a memory pool. memPoolHead is the address of a pointer (provided
   by caller) to the first free element  */
extern void *treeDeleteMPool (const void *__restrict __key,
              void **__restrict __rootp,
              __compar_fn_t __compar, void **memPoolHead);

/* same as treeDeleteMPool but with no memory pool */
#define treeDelete(_K, _R, _C) treeDeleteMPool((_K), (_R), (_C), NULL)

/* Walk through the whole tree and call the ACTION callback for every node
   or leaf.  */
extern void treeWalk (const void *__root, __action_fn_t __action, void *userData);

/* Destroy the whole tree, call FREEFCT for each node or leaf.
   Also destroy the memory pool. memPoolHead is the address
   of a pointer (provided by caller) to the first free element */
extern void treeDestroyMPool (void *__root, __free_fn_t __freefct, void *memPoolHead, void *userData);

/* same as treeDestroyMPool but with no memory pool or userData */
#define treeDestroy(_R, _F, _U) treeDestroyMPool((_R), (_F), NULL, (_U))

#endif /* _TREESEARCH_H */
