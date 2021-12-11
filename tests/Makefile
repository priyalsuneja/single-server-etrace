BUILDDIR = build

all:	rapl_l1 rapl_ins rapl_l2 rapl_fp rapl_tlb

rapl_l1: rapl_l1.c utils.c
	gcc -O0 -Wall -o $(BUILDDIR)/rapl_l1 rapl_l1.c utils.c -lpapi

rapl_l2: rapl_l2.c utils.c
	gcc -O0 -Wall -o $(BUILDDIR)/rapl_l2 rapl_l2.c utils.c -lpapi

rapl_ins: rapl_ins.c
	gcc -O0 -Wall -o $(BUILDDIR)/rapl_ins rapl_ins.c -lpapi

rapl_fp: rapl_fp.c
	gcc -O0 -Wall -o $(BUILDDIR)/rapl_fp rapl_fp.c -lpapi

rapl_tlb: rapl_tlb.c utils.c
	gcc -O0 -Wall -o $(BUILDDIR)/rapl_tlb rapl_tlb.c utils.c -lpapi

clean:
	rm -rf $(BUILDDIR)/*
