//$file${qxk::xthread2.c} vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
//
// Model: dpp_mpu.qm
// File:  ${qxk::xthread2.c}
//
// This code has been generated by QM 5.3.0 <www.state-machine.com/qm>.
// DO NOT EDIT THIS FILE MANUALLY. All your changes will be lost.
//
// SPDX-License-Identifier: GPL-3.0-or-later
//
// This generated code is open source software: you can redistribute it under
// the terms of the GNU General Public License as published by the Free
// Software Foundation.
//
// This code is distributed in the hope that it will be useful, but WITHOUT
// ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
// FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
// more details.
//
// NOTE:
// Alternatively, this generated code may be distributed under the terms
// of Quantum Leaps commercial licenses, which expressly supersede the GNU
// General Public License and are specifically designed for licensees
// interested in retaining the proprietary status of their code.
//
// Contact information:
// <www.state-machine.com/licensing>
// <info@state-machine.com>
//
//$endhead${qxk::xthread2.c} ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
#include "qpc.h"               // QP/C real-time embedded framework
#include "dpp.h"               // DPP Application interface
#include "bsp.h"               // Board Support Package

//----------------------------------------------------------------------------
Q_DEFINE_THIS_FILE

//----------------------------------------------------------------------------
//$declare${XThreads::XThread2} vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv

//${XThreads::XThread2} ......................................................
typedef struct {
// protected:
    QXThread super;

// private:

    // NOTE: data needed by this thread should be members of
    // the thread class. That way they are in the memory region
    // accessible from this thread.
    uint8_t foo;
} XThread2;

// private:
static void XThread2_run(QXThread * const thr);
//$enddecl${XThreads::XThread2} ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
//$skip${QP_VERSION} vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
// Check for the minimum required QP version
#if (QP_VERSION < 730U) || (QP_VERSION != ((QP_RELEASE^4294967295U) % 0x3E8U))
#error qpc version 7.3.0 or higher required
#endif
//$endskip${QP_VERSION} ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

//$define${Shared-TH::XThread2_ctor} vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv

//${Shared-TH::XThread2_ctor} ................................................
void XThread2_ctor(
    uint8_t * const sto,
    uint32_t const size,
    void const * const mpu)
{
    Q_REQUIRE(sizeof(XThread2) <= size);

    XThread2 *me = (XThread2 *)sto;
    QXThread_ctor(&me->super, &XThread2_run, 0U);
    me->super.super.thread = mpu;
}
//$enddef${Shared-TH::XThread2_ctor} ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
//$define${XThreads::XThread2} vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv

//${XThreads::XThread2} ......................................................

//${XThreads::XThread2::run} .................................................
static void XThread2_run(QXThread * const thr) {
    QS_OBJ_DICTIONARY(TH_XThread2);
    QS_OBJ_DICTIONARY(&TH_XThread2->timeEvt);
    QS_OBJ_DICTIONARY(&TH_sema);
    QS_OBJ_DICTIONARY(&TH_mutex);

    // downcast the generic thr pointer to the specific thread
    //XThread2 *me = (XThread2 *)thr;

    // initialize the semaphore before using it
    // NOTE: Here the semaphore is initialized in the highest-priority thread
    // that uses it. Alternatively, the semaphore can be initialized
    // before any thread runs.
    QXSemaphore_init(&TH_sema,
                0U,  // count==0 (signaling semaphore)
                1U); // max_count==1 (binary semaphore)

    // initialize the mutex before using it
    // NOTE: Here the mutex is initialized in the highest-priority thread
    // that uses it. Alternatively, the mutex can be initialized
    // before any thread runs.
    QXMutex_init(&TH_mutex, N_PHILO + 6U); // priority-ceiling mutex
    //QXMutex_init(&TH_mutex, 0U); // alternatively: priority-ceiling NOT used

    for (;;) {
        // wait on a semaphore (BLOCK indefinitely)
        QXSemaphore_wait(&TH_sema, QXTHREAD_NO_TIMEOUT);

        QXMutex_lock(&TH_mutex, QXTHREAD_NO_TIMEOUT); // lock the mutex
        QXThread_delay(5U);  // wait more (BLOCK)
        QXMutex_unlock(&TH_mutex);
    }
}
//$enddef${XThreads::XThread2} ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
