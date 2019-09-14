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

	if (0x138b == *(uint16_t *) uc->uc_mcontext.gregs[REG_RIP]) {
		uc->uc_mcontext.gregs[REG_RDX] = 100000 + counter;
		uc->uc_mcontext.gregs[REG_RIP] += 2;
	} else if  (0x0004538b == *(uint32_t *) uc->uc_mcontext.gregs[REG_RIP] && 0x00ffffff) {
		uc->uc_mcontext.gregs[REG_RDX] = 100000 + 1000 + counter;
		uc->uc_mcontext.gregs[REG_RIP] += 3;
	} else if  (0x0008538b == *(uint32_t *) uc->uc_mcontext.gregs[REG_RIP] && 0x00ffffff) {
		uc->uc_mcontext.gregs[REG_RDX] = 100000 + 2000 + counter;
		uc->uc_mcontext.gregs[REG_RIP] += 3;
	} else if  (0x000c538b == *(uint32_t *) uc->uc_mcontext.gregs[REG_RIP] && 0x00ffffff) {
		uc->uc_mcontext.gregs[REG_RDX] = 100000 + 3000 + counter;
		uc->uc_mcontext.gregs[REG_RIP] += 3;
	} else if  (0x0000558b == *(uint32_t *) uc->uc_mcontext.gregs[REG_RIP] && 0x00ffffff) {
		uc->uc_mcontext.gregs[REG_RDX] = 100000 + counter;
		uc->uc_mcontext.gregs[REG_RIP] += 3;
	} else if  (0x0004558b == *(uint32_t *) uc->uc_mcontext.gregs[REG_RIP] && 0x00ffffff) {
		uc->uc_mcontext.gregs[REG_RDX] = 100000 + 1000 + counter;
		uc->uc_mcontext.gregs[REG_RIP] += 3;
	} else if  (0x0008558b == *(uint32_t *) uc->uc_mcontext.gregs[REG_RIP] && 0x00ffffff) {
		uc->uc_mcontext.gregs[REG_RDX] = 100000 + 2000 + counter;
		uc->uc_mcontext.gregs[REG_RIP] += 3;
	} else if  (0x000c558b == *(uint32_t *) uc->uc_mcontext.gregs[REG_RIP] && 0x00ffffff) {
		uc->uc_mcontext.gregs[REG_RDX] = 100000 + 3000 + counter;
		uc->uc_mcontext.gregs[REG_RIP] += 3;
	} else if  (0x0b8b == *(uint16_t *) uc->uc_mcontext.gregs[REG_RIP]) {
		uc->uc_mcontext.gregs[REG_RCX] = 100000 + counter;
		uc->uc_mcontext.gregs[REG_RIP] += 2;
	} else if  (0x00104d8b == *(uint32_t *) uc->uc_mcontext.gregs[REG_RIP] && 0x00ffffff) {
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
	sigemptyset(&act.sa_mask);
	sigaction(SIGSEGV, &act, NULL);
}
