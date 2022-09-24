/*
 * Copyright (c) 2022-2022 Huawei Technologies Co., Ltd. All rights reserved.
 *
 * UniProton is licensed under Mulan PSL v2.
 * You can use this software according to the terms and conditions of the Mulan PSL v2.
 * You may obtain a copy of Mulan PSL v2 at:
 *          http://license.coscl.org.cn/MulanPSL2
 * THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
 * EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
 * MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
 * See the Mulan PSL v2 for more details.
 * Create: 2022-09-21
 * Description: UniProton 信号量测试用例。
 */
#include "It_os_sem.h"

static UINT32 Testcase(VOID)
{
    UINT32 ret;

    ret = PRT_SemCreate(0, NULL);
    ICUNIT_ASSERT_EQUAL(ret, OS_ERRNO_SEM_PTR_NULL, ret);

    return OS_OK;
}

VOID ItOsSem002(void)
{
    TEST_ADD_CASE("ItOsSem002", Testcase, TEST_OS, TEST_SEM, TEST_LEVEL0, TEST_FUNCTION);
}

