#pragma once
#include "commonHeader.h"

uint64_t generate_nonce(void);
string generate_signature(string secret, string verb, string url, uint64_t nonce, string data);