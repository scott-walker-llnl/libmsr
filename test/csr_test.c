#include "../include/csr_core.h"
#include "../include/csr_imc.h"
#include <sys/wait.h>
#include <stdlib.h>
#include <sched.h>
#include <unistd.h>
#include <stdio.h>

//#define MEMTEST

#ifdef MEMTEST
char * args[] = {"mg.B.1"};
const char path[] = "/g/g19/walker91/NPB3.3.1/NPB3.3-MPI/bin/mg.B.1";
#endif

int main()
{

    if (init_csr())
	{
		return -1;
	}
	init_imc_ctrs();
	// can be READ_BW, WRITE_BW, or ALL_BW
	mem_bw_on_ctr(0, ALL_BW);
	mem_pct_rw_on_ctr(1, 2);
#ifdef MEMTEST
	pid_t p = fork();
	int status = 0;
	if (p)
	{
		wait(&status);
	} else {
		execve(path, args, NULL);
		exit(1);
	}
#endif
#ifndef MEMTEST
	sleep(5);
#endif
	dump_mem_bw_from_ctr(0, stdout);
	dump_mem_pct_rw_from_ctr(1, 2, READ_PCT, stdout); 
	dump_mem_pct_rw_from_ctr(1, 2, WRITE_PCT, stdout); 

	mem_page_empty_on_ctr(1, 2, 0);
	mem_page_miss_on_ctr(2, 0);
#ifdef MEMTEST
	p = fork();
	status = 0;
	if (p)
	{
		wait(&status);
	} else {
		execve(path, args, NULL);
		exit(1);
	}
#endif
#ifndef MEMTEST
	sleep(5);
#endif
	dump_mem_page_empty_from_ctr(1, 2, 0, stdout);
	dump_mem_page_miss_from_ctr(2, 0, stdout);
    finalize_csr();
	return 0;
}
