BUILDDIR = build

all:	rapl_l1 rapl_lst rapl_ins rapl_l2

rapl_l1: rapl_l1.c
	gcc -O0 -Wall -o $(BUILDDIR)/rapl_l1 rapl_l1.c -lpapi

rapl_l2: rapl_l2.c
	gcc -O0 -Wall -o $(BUILDDIR)/rapl_l2 rapl_l2.c -lpapi

rapl_lst: rapl_lst.c
	gcc -O0 -Wall -o $(BUILDDIR)/rapl_lst rapl_lst.c -lpapi

rapl_ins: rapl_ins.c
	gcc -O0 -Wall -o $(BUILDDIR)/rapl_ins rapl_ins.c -lpapi

clean:
	rm -rf $(BUILDDIR)/*
