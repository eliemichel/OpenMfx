/*
 * Copyright 2019-2022 Elie Michel
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#pragma once

/**
 * Make a class move only (disable default copy but not default move semantics)
 * Example:
 *   class Foo {
 * public:
 *     Foo();
 *     MOVE_ONLY(Foo)
 *   }
 */
#define MOVE_ONLY(T) \
T(const T &) = delete; \
T &operator=(const T &) = delete; \
T(T&&) = default; \
T &operator=(T&&) = default;

/**
 * A simple logging macro that is only defined in debug mode
 */
#ifndef NDEBUG
#include <cstdio>
#  define LOG printf
#else
#  define LOG(...)
#endif

