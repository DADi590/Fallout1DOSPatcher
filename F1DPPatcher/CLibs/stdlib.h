// Copyright 2022 Edw590
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

#ifndef F1DPPATCHER_STDLIB_H
#define F1DPPATCHER_STDLIB_H


#include <stddef.h>

#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1

__declspec(noreturn) void exit(int status);
char *itoa(int value, char *str, int base);
void free(void * ptr);
void *malloc(size_t size);
int abs(int i);



#endif //F1DPPATCHER_STDLIB_H
