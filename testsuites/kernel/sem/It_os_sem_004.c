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
#include "osTest.h"
#include "It_os_sem.h"

static UINT32 Testcase(VOID)
{
    UINT32 ret;
    SemHandle semID = 0;

    ret = PRT_SemCreate(2, &semID); // 2, The semaphore count, number of available semaphores.
    ICUNIT_ASSERT_EQUAL(ret, OS_OK, ret);

    ret = PRT_SemPend(semID, OS_NO_WAIT);
    ICUNIT_GOTO_EQUAL(ret, OS_OK, ret, EXIT);

    ret = PRT_SemPend(semID, 0xF);
    ICUNIT_GOTO_EQUAL(ret, OS_OK, ret, EXIT);
    ret = PRT_SemPend(semID, OS_NO_WAIT);
    ICUNIT_GOTO_EQUAL(ret, OS_ERRNO_SEM_UNAVAILABLE, ret, EXIT);

    ret = PRT_SemPend(semID, 0xF);
    ICUNIT_TRACK_EQUAL(ret, OS_ERRNO_SEM_TIMEOUT, ret);

EXIT:
    ret = PRT_SemDelete(semID);
    ICUNIT_ASSERT_EQUAL(ret, OS_OK, ret);

    return OS_OK;
}

VOID ItOsSem004(void)
{
    TEST_ADD_CASE("ItOsSem004", Testcase, TEST_OS, TEST_SEM, TEST_LEVEL0, TEST_FUNCTION);
}

