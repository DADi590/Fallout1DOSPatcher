// Copyright 2022 DADi590
//
// Licensed to the Apache Software Foundation (ASF) under one
// or more contributor license agreements.  See the NOTICE file
// distributed with this work for additional information
// regarding copyright ownership.  The ASF licenses this file
// to you under the Apache License, Version 2.0 (the
// "License"); you may not use this file except in compliance
// with the License.  You may obtain a copy of the License at
//
//   http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing,
// software distributed under the License is distributed on an
// "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
// KIND, either express or implied.  See the License for the
// specific language governing permissions and limitations
// under the License.

#include "../GameAddrs/CStdFuncs.h"
#include "../Utils/General.h"
#include "../Utils/GlobalEXEAddrs.h"
#include "../Utils/GlobalVars.h"
#include "../Utils/BlockAddrUtils.h"
#include "stdio.h"
#include <stdint.h>

uint32_t ret_addr = 0;

char const fmt_strln[] = "%s"NL;

__declspec(naked) int printf(char const *format, ...) {
	(void) format; // To ignore the unused parameter warning
	__asm {
			// Pointer correction (only on the first argument though - aside from not knowing how many others, one could be
			// just an int and I can't add the address to an int)
			// Below, I'm using ESP and not just [format] because Watcom thought it would be a good idea to use EBP to get
			// to the parameter, even though I have no instruction here that messes with EBP to equal it to ESP. So I'm
			// doing it manually. esp+4 because on ESP, is the return address, not the parameters, which are put on the stack
			// before the return address (the last one to be put).
			mov     eax, [esp+4]
			call    getRealBlockAddrData
			mov     [esp+4], eax

			push    edi

			mov     edi, [esp+4] // Return address
			lea     eax, [ret_addr]
			add     eax, SN_DATA_SEC_BLOCK_ADDR
			mov     [eax], edi

			pop     edi
			add     esp, 4 // Remove the return address from the stack (so the stack can be what it was before calling printf())

			// Now we call printf_() with the arguments passed to printf() and nothing else on the stack - it's like we had
			// jumped to printf_() and not called a wrapper at all.
			mov     eax, SN_CODE_SEC_EXE_ADDR
			add     eax, F_printf_
			call    eax

			lea     esp, [esp-4] // Get space on the stack to put the return address back on
			push    edi
			lea     edi, [ret_addr]
			lea     edi, [edi+SN_DATA_SEC_BLOCK_ADDR]
			mov     edi, [edi]
			mov     [esp+4], edi // Store the return address on the stack again

			lea     edi, [ret_addr]
			lea     edi, [edi+SN_DATA_SEC_BLOCK_ADDR]
			mov     dword ptr [edi], 0 // Empty ret_addr just in case I ever use it elsewhere and check its value(?)

			pop     edi

			ret
	}
}

__declspec(naked) int sprintf(char *s, char const *format, ...) {
	(void) s; // To ignore the unused parameter warning
	(void) format; // To ignore the unused parameter warning
	__asm {
			// For explanations of how this function works, check printf()

			// Pointer correction
			mov     eax, [esp+4]
			call    getRealBlockAddrData
			mov     [esp+4], eax
			mov     eax, [esp+8]
			call    getRealBlockAddrData
			mov     [esp+8], eax

			push    edi

			mov     edi, [esp+4] // Return address
			lea     eax, [ret_addr]
			add     eax, SN_DATA_SEC_BLOCK_ADDR
			mov     [eax], edi

			pop     edi
			add     esp, 4 // Remove the return address from the stack

			mov     eax, SN_CODE_SEC_EXE_ADDR
			add     eax, F_sprintf_
			call    eax

			lea     esp, [esp-4] // Get space on the stack to put the return address back on
			push    edi
			lea     edi, [ret_addr]
			lea     edi, [edi+SN_DATA_SEC_BLOCK_ADDR]
			mov     edi, [edi]
			mov     [esp+4], edi // Store the return address on the stack again

			lea     edi, [ret_addr]
			lea     edi, [edi+SN_DATA_SEC_BLOCK_ADDR]
			mov     dword ptr [edi], 0 // Empty ret_addr just in case I ever use it elsewhere and check its value(?)

			pop     edi

			ret
	}
}

__declspec(naked) int sscanf(char *s, char const *format, ...) {
	(void) s; // To ignore the unused parameter warning
	(void) format; // To ignore the unused parameter warning
	__asm {
			// For explanations of how this function works, check printf()

			// Pointer correction
			mov     eax, [esp+4]
			call    getRealBlockAddrData
			mov     [esp+4], eax
			mov     eax, [esp+8]
			call    getRealBlockAddrData
			mov     [esp+8], eax

			push    edi

			mov     edi, [esp+4] // Return address
			lea     eax, [ret_addr]
			add     eax, SN_DATA_SEC_BLOCK_ADDR
			mov     [eax], edi

			pop     edi
			add     esp, 4 // Remove the return address from the stack

			mov     eax, SN_CODE_SEC_EXE_ADDR
			add     eax, F_sscanf_
			call    eax

			lea     esp, [esp-4] // Get space on the stack to put the return address back on
			push    edi
			lea     edi, [ret_addr]
			lea     edi, [edi+SN_DATA_SEC_BLOCK_ADDR]
			mov     edi, [edi]
			mov     [esp+4], edi // Store the return address on the stack again

			lea     edi, [ret_addr]
			lea     edi, [edi+SN_DATA_SEC_BLOCK_ADDR]
			mov     dword ptr [edi], 0 // Empty ret_addr just in case I ever use it elsewhere and check its value(?)

			pop     edi

			ret
	}
}

// ////////////////////////////////////////////////////////////////////////////////
// Non-standard functions

int printlnStr(char const *string) {
	int ret_var = 0;

	// Pointer correction
	string = getRealBlockAddrData(string);

	__asm {
			pusha

			push    dword ptr [string]

			lea     eax, [fmt_strln]
			add     eax, SN_DATA_SEC_BLOCK_ADDR
			push    eax

			call    printf

			add     esp, 8

			mov     [ret_var], eax

			popa
	}

	return ret_var;
}
