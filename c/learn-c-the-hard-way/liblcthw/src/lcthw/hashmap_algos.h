#ifndef _lcthw_hashmap_algos_h_
#define _lcthw_hashmap_algos_h_

#include <stdint.h>

uint32_t Hashmap_fnv1a_hash(void* data);
uint32_t Hashmap_adler32_hash(void* data);
uint32_t Hashmap_djb_hash(void* data);

#endif
