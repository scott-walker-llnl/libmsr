libmsr_test: libmsr_test.c 
	gcc -g -Wall -o libmsr_test libmsr_test.c -L../install/lib -lmsr -D_GNU_SOURCE

csr_test: csr_test.c 
	gcc -g -Wall -o csr_test csr_test.c -L../install/lib -lmsr -D_GNU_SOURCE

libmsr_mpi_test: libmsr_test.c 
	mpicc -Wall -DMPI -o libmsr_mpi_test libmsr_test.c -L ../lib -lmsr

mpi: mpi_test.c
	mpicc -Wall -o mpi_test mpi_test.c -L../lib -lPowThermTest -lmsr -lm

rzoz: 
	srun -p quad_sb -n 32 --auto-affinity=start=0,verbose,cpt=1 ./mpi_test | grep QQQ > QQQ

clean:
	rm -f mpi_test libmsr_test libmsr_powercap_test


