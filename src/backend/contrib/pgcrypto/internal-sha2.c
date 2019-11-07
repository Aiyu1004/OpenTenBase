/*
 * Tencent is pleased to support the open source community by making TBase available.  
 * 
 * Copyright (C) 2019 THL A29 Limited, a Tencent company.  All rights reserved.
 * 
 * TBase is licensed under the BSD 3-Clause License, except for the third-party component listed below. 
 * 
 * A copy of the BSD 3-Clause License is included in this file.
 * 
 * Other dependencies and licenses:
 * 
 * Open Source Software Licensed Under the PostgreSQL License: 
 * --------------------------------------------------------------------
 * 1. Postgres-XL XL9_5_STABLE
 * Portions Copyright (c) 2015-2016, 2ndQuadrant Ltd
 * Portions Copyright (c) 2012-2015, TransLattice, Inc.
 * Portions Copyright (c) 2010-2017, Postgres-XC Development Group
 * Portions Copyright (c) 1996-2015, The PostgreSQL Global Development Group
 * Portions Copyright (c) 1994, The Regents of the University of California
 * 
 * Terms of the PostgreSQL License: 
 * --------------------------------------------------------------------
 * Permission to use, copy, modify, and distribute this software and its
 * documentation for any purpose, without fee, and without a written agreement
 * is hereby granted, provided that the above copyright notice and this
 * paragraph and the following two paragraphs appear in all copies.
 * 
 * IN NO EVENT SHALL THE UNIVERSITY OF CALIFORNIA BE LIABLE TO ANY PARTY FOR
 * DIRECT, INDIRECT, SPECIAL, INCIDENTAL, OR CONSEQUENTIAL DAMAGES, INCLUDING
 * LOST PROFITS, ARISING OUT OF THE USE OF THIS SOFTWARE AND ITS
 * DOCUMENTATION, EVEN IF THE UNIVERSITY OF CALIFORNIA HAS BEEN ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 * 
 * THE UNIVERSITY OF CALIFORNIA SPECIFICALLY DISCLAIMS ANY WARRANTIES,
 * INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY
 * AND FITNESS FOR A PARTICULAR PURPOSE.  THE SOFTWARE PROVIDED HEREUNDER IS
 * ON AN "AS IS" BASIS, AND THE UNIVERSITY OF CALIFORNIA HAS NO OBLIGATIONS TO
 * PROVIDE MAINTENANCE, SUPPORT, UPDATES, ENHANCEMENTS, OR MODIFICATIONS.
 * 
 * 
 * Terms of the BSD 3-Clause License:
 * --------------------------------------------------------------------
 * Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:
 * 
 * 1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
 * 
 * 2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation 
 * and/or other materials provided with the distribution.
 * 
 * 3. Neither the name of THL A29 Limited nor the names of its contributors may be used to endorse or promote products derived from this software without 
 * specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, 
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS 
 * BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE 
 * GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT 
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH 
 * DAMAGE.
 * 
 */
/*
 * internal.c
 *        Wrapper for builtin functions
 *
 * Copyright (c) 2001 Marko Kreen
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *      notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *      notice, this list of conditions and the following disclaimer in the
 *      documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 * contrib/pgcrypto/internal-sha2.c
 */

#include "postgres.h"

#include <time.h>

#include "contrib/pgcrypto/px.h"
#include "contrib/pgcrypto/sha2.h"

void        init_sha224(PX_MD *h);
void        init_sha256(PX_MD *h);
void        init_sha384(PX_MD *h);
void        init_sha512(PX_MD *h);

/* SHA224 */

static unsigned
int_sha224_len(PX_MD *h)
{
    return SHA224_DIGEST_LENGTH;
}

static unsigned
int_sha224_block_len(PX_MD *h)
{
    return SHA224_BLOCK_LENGTH;
}

static void
int_sha224_update(PX_MD *h, const uint8 *data, unsigned dlen)
{
    SHA224_CTX *ctx = (SHA224_CTX *) h->p.ptr;

    SHA224_Update(ctx, data, dlen);
}

static void
int_sha224_reset(PX_MD *h)
{
    SHA224_CTX *ctx = (SHA224_CTX *) h->p.ptr;

    SHA224_Init(ctx);
}

static void
int_sha224_finish(PX_MD *h, uint8 *dst)
{
    SHA224_CTX *ctx = (SHA224_CTX *) h->p.ptr;

    SHA224_Final(dst, ctx);
}

static void
int_sha224_free(PX_MD *h)
{
    SHA224_CTX *ctx = (SHA224_CTX *) h->p.ptr;

    crypt_memset(ctx, 0, sizeof(*ctx));
    crypt_free(ctx);
    crypt_free(h);
}

/* SHA256 */

static unsigned
int_sha256_len(PX_MD *h)
{
    return SHA256_DIGEST_LENGTH;
}

static unsigned
int_sha256_block_len(PX_MD *h)
{
    return SHA256_BLOCK_LENGTH;
}

static void
int_sha256_update(PX_MD *h, const uint8 *data, unsigned dlen)
{
    SHA256_CTX *ctx = (SHA256_CTX *) h->p.ptr;

    SHA256_Update(ctx, data, dlen);
}

static void
int_sha256_reset(PX_MD *h)
{
    SHA256_CTX *ctx = (SHA256_CTX *) h->p.ptr;

    SHA256_Init(ctx);
}

static void
int_sha256_finish(PX_MD *h, uint8 *dst)
{
    SHA256_CTX *ctx = (SHA256_CTX *) h->p.ptr;

    SHA256_Final(dst, ctx);
}

static void
int_sha256_free(PX_MD *h)
{
    SHA256_CTX *ctx = (SHA256_CTX *) h->p.ptr;

    crypt_memset(ctx, 0, sizeof(*ctx));
    crypt_free(ctx);
    crypt_free(h);
}

/* SHA384 */

static unsigned
int_sha384_len(PX_MD *h)
{
    return SHA384_DIGEST_LENGTH;
}

static unsigned
int_sha384_block_len(PX_MD *h)
{
    return SHA384_BLOCK_LENGTH;
}

static void
int_sha384_update(PX_MD *h, const uint8 *data, unsigned dlen)
{
    SHA384_CTX *ctx = (SHA384_CTX *) h->p.ptr;

    SHA384_Update(ctx, data, dlen);
}

static void
int_sha384_reset(PX_MD *h)
{
    SHA384_CTX *ctx = (SHA384_CTX *) h->p.ptr;

    SHA384_Init(ctx);
}

static void
int_sha384_finish(PX_MD *h, uint8 *dst)
{
    SHA384_CTX *ctx = (SHA384_CTX *) h->p.ptr;

    SHA384_Final(dst, ctx);
}

static void
int_sha384_free(PX_MD *h)
{
    SHA384_CTX *ctx = (SHA384_CTX *) h->p.ptr;

    crypt_memset(ctx, 0, sizeof(*ctx));
    crypt_free(ctx);
    crypt_free(h);
}

/* SHA512 */

static unsigned
int_sha512_len(PX_MD *h)
{
    return SHA512_DIGEST_LENGTH;
}

static unsigned
int_sha512_block_len(PX_MD *h)
{
    return SHA512_BLOCK_LENGTH;
}

static void
int_sha512_update(PX_MD *h, const uint8 *data, unsigned dlen)
{
    SHA512_CTX *ctx = (SHA512_CTX *) h->p.ptr;

    SHA512_Update(ctx, data, dlen);
}

static void
int_sha512_reset(PX_MD *h)
{
    SHA512_CTX *ctx = (SHA512_CTX *) h->p.ptr;

    SHA512_Init(ctx);
}

static void
int_sha512_finish(PX_MD *h, uint8 *dst)
{
    SHA512_CTX *ctx = (SHA512_CTX *) h->p.ptr;

    SHA512_Final(dst, ctx);
}

static void
int_sha512_free(PX_MD *h)
{
    SHA512_CTX *ctx = (SHA512_CTX *) h->p.ptr;

    crypt_memset(ctx, 0, sizeof(*ctx));
    crypt_free(ctx);
    crypt_free(h);
}

/* init functions */

void
init_sha224(PX_MD *md)
{
    SHA224_CTX *ctx;

    ctx = crypt_alloc(sizeof(*ctx));
    memset(ctx, 0, sizeof(*ctx));

    md->p.ptr = ctx;

    md->result_size = int_sha224_len;
    md->block_size = int_sha224_block_len;
    md->reset = int_sha224_reset;
    md->update = int_sha224_update;
    md->finish = int_sha224_finish;
    md->free = int_sha224_free;

    md->reset(md);
}

void
init_sha256(PX_MD *md)
{
    SHA256_CTX *ctx;

    ctx = crypt_alloc(sizeof(*ctx));
    memset(ctx, 0, sizeof(*ctx));

    md->p.ptr = ctx;

    md->result_size = int_sha256_len;
    md->block_size = int_sha256_block_len;
    md->reset = int_sha256_reset;
    md->update = int_sha256_update;
    md->finish = int_sha256_finish;
    md->free = int_sha256_free;

    md->reset(md);
}

void
init_sha384(PX_MD *md)
{
    SHA384_CTX *ctx;

    ctx = crypt_alloc(sizeof(*ctx));
    memset(ctx, 0, sizeof(*ctx));

    md->p.ptr = ctx;

    md->result_size = int_sha384_len;
    md->block_size = int_sha384_block_len;
    md->reset = int_sha384_reset;
    md->update = int_sha384_update;
    md->finish = int_sha384_finish;
    md->free = int_sha384_free;

    md->reset(md);
}

void
init_sha512(PX_MD *md)
{
    SHA512_CTX *ctx;

    ctx = crypt_alloc(sizeof(*ctx));
    memset(ctx, 0, sizeof(*ctx));

    md->p.ptr = ctx;

    md->result_size = int_sha512_len;
    md->block_size = int_sha512_block_len;
    md->reset = int_sha512_reset;
    md->update = int_sha512_update;
    md->finish = int_sha512_finish;
    md->free = int_sha512_free;

    md->reset(md);
}
