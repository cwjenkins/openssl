/*
 * Copyright 2001-2019 The OpenSSL Project Authors. All Rights Reserved.
 *
 * Licensed under the Apache License 2.0 (the "License").  You may not use
 * this file except in compliance with the License.  You can obtain a copy
 * in the file LICENSE in the source distribution or at
 * https://www.openssl.org/source/license.html
 */

/*-
 * Fujitsu SPARC64 X support for AES GCM.
 * This file is included by cipher_gcm_hw.c
 */

static int t4_aes_gcm_initkey(PROV_GCM_CTX *ctx, const unsigned char *key,
                              size_t keylen)
{
    ctr128_f ctr;
    PROV_AES_GCM_CTX *actx = (PROV_AES_GCM_CTX *)ctx;
    AES_KEY *ks = &actx->ks.ks;


    switch (keylen) {
    case 16:
        ctr = (ctr128_f)aes128_t4_ctr32_encrypt;
        break;
    case 24:
        ctr = (ctr128_f)aes192_t4_ctr32_encrypt;
        break;
    case 32:
        ctr = (ctr128_f)aes256_t4_ctr32_encrypt;
        break;
    default:
        return 0;
    }

    SET_KEY_CTR_FN(ks, aes_t4_set_encrypt_key, aes_t4_encrypt, ctr);
    return 1;
}

static const PROV_GCM_HW t4_aes_gcm = {
    t4_aes_gcm_initkey,
    gcm_setiv,
    gcm_aad_update,
    gcm_cipher_update,
    gcm_cipher_final,
    gcm_one_shot
};
const PROV_GCM_HW *PROV_AES_HW_gcm(size_t keybits)
{
    return SPARC_AES_CAPABLE ? &t4_aes_gcm : &aes_gcm;
}
