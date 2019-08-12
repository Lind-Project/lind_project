/**
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.
 * The ASF licenses this file to You under the Apache License, Version 2.0
 * (the "License"); you may not use this file except in compliance with
 * the License.  You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef _LUA_APR_H_
#define _LUA_APR_H_

#include "scoreboard.h"
#include "http_main.h"
#include "ap_mpm.h"
#include "apr_md5.h"
#include "apr_sha1.h"
#include "apr_poll.h"
#include "apr.h"
#include "apr_tables.h"
#include "apr_base64.h"


int ap_lua_init(lua_State *L, apr_pool_t * p);
req_table_t *ap_lua_check_apr_table(lua_State *L, int index);
void ap_lua_push_apr_table(lua_State *L, req_table_t *t);

#endif /* !_LUA_APR_H_ */
