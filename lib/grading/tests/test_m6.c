/*
 * Copyright (c) 2019, ETH Zurich.
 * Copyright (c) 2022, The University of British Columbia.
 * All rights reserved.
 *
 * This file is distributed under the terms in the attached LICENSE file.
 * If you do not find this file, copies can be found by writing to:
 * ETH Zurich D-INFK, Universitaetstrasse 6, CH-8092 Zurich. Attn: Systems Group.
 */

///////////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                               //
//                          !! WARNING !!   !! WARNING !!   !! WARNING !!                        //
//                                                                                               //
//      This file is part of the grading library and will be overwritten before grading.         //
//                         You may edit this file for your own tests.                            //
//                                                                                               //
///////////////////////////////////////////////////////////////////////////////////////////////////

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include <aos/aos.h>
#include <aos/solution.h>
#include <aos/paging.h>
#include <proc_mgmt/proc_mgmt.h>

#include <grading/io.h>
#include <grading/state.h>
#include <grading/options.h>
#include <grading/tests.h>
#include "../include/grading/options_internal.h"

#define BINARY_NAME "alloc"


static void spawn_one_without_args(coreid_t core)
{
    errval_t err;

    grading_printf("spawn_one_without_args(%s, %d)\n", BINARY_NAME, core);

    domainid_t pid;
    err = proc_mgmt_spawn_with_cmdline(BINARY_NAME, core, &pid);
    if (err_is_fail(err)) {
        grading_test_fail("U1-1", "failed to load: %s\n", err_getstring(err));
        return;
    }
    // Heads up! When you have messaging support, then you may need to handle a
    // few messages here for the process to start up
    grading_printf("waiting 2 seconds to give the other domain chance to run...\n");
    // barrelfish_usleep(2000000);
}

errval_t grading_run_tests_urpc(void)
{
    if (grading_options.m6_subtest_run == 0) {
        return SYS_ERR_OK;
    }

    grading_printf("#################################################\n");
    grading_printf("# TESTS: Milestone 6 (URPC)                      \n");
    grading_printf("#################################################\n");

    spawn_one_without_args(0);
    spawn_one_without_args(1);

    grading_printf("#################################################\n");
    grading_printf("# DONE:  Milestone 6 (URPC)                      \n");
    grading_printf("#################################################\n");

    return SYS_ERR_OK;
}


bool grading_opts_handle_m6_tests(struct grading_options *opts, const char *arg)
{
    (void)arg;

    // enable the m6 tests
    opts->m6_subtest_run = 0x1;

    // TODO(optional): parsing options to selectively enable tests or configure them at runtime.

    return true;
}