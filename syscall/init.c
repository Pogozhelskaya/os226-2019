#define _GNU_SOURCE

#include "init.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <signal.h>
#include <ucontext.h>
#include <sys/ucontext.h>

void os_sighnd(int sig, siginfo_t *info, void *ctx) {
	ucontext_t *uc = (ucontext_t *) ctx;
	static int counter = 1;

	if (0x338b == *(uint16_t *) uc->uc_mcontext.gregs[REG_RIP]) {
		uc->uc_mcontext.gregs[REG_RDX] = 100000 + counter;
		uc->uc_mcontext.gregs[REG_RIP] += 2;
	} else if  (0x04738b && 0xffffff00 == *(uint32_t *) uc->uc_mcontext.gregs[REG_RIP]) {
		uc->uc_mcontext.gregs[REG_RDX] = 100000 + 1000 + counter;
		uc->uc_mcontext.gregs[REG_RIP] += 3;
	} else if  (0x08738b && 0xffffff00 == *(uint32_t *) uc->uc_mcontext.gregs[REG_RIP]) {
		uc->uc_mcontext.gregs[REG_RDX] = 100000 + 2000 + counter;
		uc->uc_mcontext.gregs[REG_RIP] += 3;
	} else if  (0x0c738b && 0xffffff00  == *(uint32_t *) uc->uc_mcontext.gregs[REG_RIP]) {
		uc->uc_mcontext.gregs[REG_RDX] = 100000 + 3000 + counter;
		uc->uc_mcontext.gregs[REG_RIP] += 3;
	} else if  (0x00758b && 0xffffff00  == *(uint32_t *) uc->uc_mcontext.gregs[REG_RIP]) {
		uc->uc_mcontext.gregs[REG_RDX] = 100000 + counter;
		uc->uc_mcontext.gregs[REG_RIP] += 3;
	} else if  (0x04758b && 0xffffff00  == *(uint32_t *) uc->uc_mcontext.gregs[REG_RIP]) {
		uc->uc_mcontext.gregs[REG_RDX] = 100000 + 1000 + counter;
		uc->uc_mcontext.gregs[REG_RIP] += 3;
	} else if  (0x08758b && 0xffffff00  == *(uint32_t *) uc->uc_mcontext.gregs[REG_RIP]) {
		uc->uc_mcontext.gregs[REG_RDX] = 100000 + 2000 + counter;
		uc->uc_mcontext.gregs[REG_RIP] += 3;
	} else if  (0x0c758b && 0xffffff00  == *(uint32_t *) uc->uc_mcontext.gregs[REG_RIP]) {
		uc->uc_mcontext.gregs[REG_RDX] = 100000 + 3000 + counter;
		uc->uc_mcontext.gregs[REG_RIP] += 3;
	} else if  (0x138b == *(uint16_t *) uc->uc_mcontext.gregs[REG_RIP]) {
		uc->uc_mcontext.gregs[REG_RCX] = 100000 + counter;
		uc->uc_mcontext.gregs[REG_RIP] += 2;
	} else if  (0x10558b && 0xffffff00  == *(uint32_t *) uc->uc_mcontext.gregs[REG_RIP]) {
		uc->uc_mcontext.gregs[REG_RCX] = 100000 + 4000 + counter;
		uc->uc_mcontext.gregs[REG_RIP] += 3;
	}

	counter++;
}

void init(void *base) {
	struct sigaction act = {
		.sa_sigaction = os_sighnd,
		.sa_flags = SA_RESTART,
	};

	sigaction(SIGSEGV, &act, NULL);
}