/*
 * Copyright 2019 The OpenSSL Project Authors. All Rights Reserved.
 * Copyright (c) 2019, Oracle and/or its affiliates.  All rights reserved.
 *
 * Licensed under the Apache License 2.0 (the "License").  You may not use
 * this file except in compliance with the License.  You can obtain a copy
 * in the file LICENSE in the source distribution or at
 * https://www.openssl.org/source/license.html
 */

#ifndef HEADER_SPARSE_ARRAY_H
# define HEADER_SPARSE_ARRAY_H

# include <openssl/e_os2.h>

# ifdef __cplusplus
extern "C" {
# endif

# define SPARSE_ARRAY_OF(type) struct sparse_array_st_ ## type

# define DEFINE_SPARSE_ARRAY_OF_INTERNAL(type, ctype) \
    SPARSE_ARRAY_OF(type); \
    static ossl_unused ossl_inline SPARSE_ARRAY_OF(type) * \
        ossl_sa_##type##_new(void) \
    { \
        return (SPARSE_ARRAY_OF(type) *)OPENSSL_SA_new(); \
    } \
    static ossl_unused ossl_inline void ossl_sa_##type##_free(SPARSE_ARRAY_OF(type) *sa) \
    { \
        OPENSSL_SA_free((OPENSSL_SA *)sa); \
    } \
    static ossl_unused ossl_inline void ossl_sa_##type##_free_leaves(SPARSE_ARRAY_OF(type) *sa) \
    { \
        OPENSSL_SA_free_leaves((OPENSSL_SA *)sa); \
    } \
    static ossl_unused ossl_inline size_t ossl_sa_##type##_num(const SPARSE_ARRAY_OF(type) *sa) \
    { \
        return OPENSSL_SA_num((OPENSSL_SA *)sa); \
    } \
    static ossl_unused ossl_inline void ossl_sa_##type##_doall(const SPARSE_ARRAY_OF(type) *sa, \
                                                   void (*leaf)(ossl_uintmax_t, \
                                                                type *)) \
    { \
        OPENSSL_SA_doall((OPENSSL_SA *)sa, (void (*)(ossl_uintmax_t, void *))leaf); \
    } \
    static ossl_unused ossl_inline \
    void ossl_sa_##type##_doall_arg(const SPARSE_ARRAY_OF(type) *sa, \
                                    void (*leaf)(ossl_uintmax_t, type *, void *), \
                                    void *arg) \
    { \
        OPENSSL_SA_doall_arg((OPENSSL_SA *)sa, (void (*)(ossl_uintmax_t, void *, \
                                                void *))leaf, \
                             arg); \
    } \
    static ossl_unused ossl_inline ctype *ossl_sa_##type##_get(const SPARSE_ARRAY_OF(type) *sa, \
                                                  ossl_uintmax_t n) \
    { \
        return (type *)OPENSSL_SA_get((OPENSSL_SA *)sa, n); \
    } \
    static ossl_unused ossl_inline int ossl_sa_##type##_set(SPARSE_ARRAY_OF(type) *sa, \
                                                ossl_uintmax_t n, ctype *val) \
    { \
        return OPENSSL_SA_set((OPENSSL_SA *)sa, n, (void *)val); \
    } \
    SPARSE_ARRAY_OF(type)

# define DEFINE_SPARSE_ARRAY_OF(type) \
    DEFINE_SPARSE_ARRAY_OF_INTERNAL(type, type)
# define DEFINE_SPARSE_ARRAY_OF_CONST(type) \
    DEFINE_SPARSE_ARRAY_OF_INTERNAL(type, const type)

typedef struct sparse_array_st OPENSSL_SA;
OPENSSL_SA *OPENSSL_SA_new(void);
void OPENSSL_SA_free(OPENSSL_SA *sa);
void OPENSSL_SA_free_leaves(OPENSSL_SA *sa);
size_t OPENSSL_SA_num(const OPENSSL_SA *sa);
void OPENSSL_SA_doall(const OPENSSL_SA *sa,
                      void (*leaf)(ossl_uintmax_t, void *));
void OPENSSL_SA_doall_arg(const OPENSSL_SA *sa,
                          void (*leaf)(ossl_uintmax_t, void *, void *), void *);
void *OPENSSL_SA_get(const OPENSSL_SA *sa, ossl_uintmax_t n);
int OPENSSL_SA_set(OPENSSL_SA *sa, ossl_uintmax_t n, void *val);

# ifdef  __cplusplus
}
# endif
#endif
