BUILDDIR = build

#all: tlb_msr l2_msr l1_msr ins_msr ins l2 tlb l1 l1_populate l2_populate \
#        tlb_populate

#all: tlb_msr l1_msr l2_msr qs_msr mm_msr mm_signal

all: mm_signal

l1_msr: l1_msr.c utils.c msr.c
	gcc -O0 -Wall -o $(BUILDDIR)/l1_msr l1_msr.c utils.c msr.c -lm

l1: l1.c utils.c msr.c
	gcc -O0 -Wall -o $(BUILDDIR)/l1 l1.c utils.c msr.c -lm

l1_populate: l1_populate.c utils.c msr.c
	gcc -O0 -Wall -o $(BUILDDIR)/l1_populate l1_populate.c utils.c msr.c -lm

l2_msr: l2_msr.c utils.c msr.c
	gcc -O0 -g -Wall -o $(BUILDDIR)/l2_msr l2_msr.c utils.c msr.c -lm

l2: l2.c utils.c msr.c
	gcc -O0 -Wall -o $(BUILDDIR)/l2 l2.c utils.c msr.c -lm

l2_populate: l2_populate.c utils.c msr.c
	gcc -O0 -Wall -o $(BUILDDIR)/l2_populate l2_populate.c utils.c msr.c -lm

ins_msr: ins_msr.c msr.c utils.c
	gcc -O0 -Wall -o $(BUILDDIR)/ins_msr ins_msr.c utils.c msr.c -lm

qs_msr: qs_msr.c msr.c utils.c
	gcc -O0 -Wall -o $(BUILDDIR)/qs_msr qs_msr.c utils.c msr.c -lm

mm_msr: mm_msr.c msr.c utils.c
	gcc -O0 -g -Wall -o $(BUILDDIR)/mm_msr mm_msr.c utils.c msr.c -lm

mm_signal: mm_signal.c msr.c utils.c
	gcc -O0 -g -Wall -o $(BUILDDIR)/mm_signal mm_signal.c utils.c msr.c -lm

ins: ins.c  msr.c utils.c
	gcc -O0 -Wall -o $(BUILDDIR)/ins ins.c msr.c utils.c -lm

tlb_msr: tlb_msr.c utils.c msr.c
	gcc -O0 -Wall -o $(BUILDDIR)/tlb_msr tlb_msr.c utils.c msr.c -lm

tlb: tlb.c utils.c msr.c
	gcc -O0 -Wall -o $(BUILDDIR)/tlb tlb.c utils.c msr.c -lm

tlb_populate: tlb_populate.c utils.c msr.c
	gcc -O0 -Wall -o $(BUILDDIR)/tlb_populate tlb_populate.c utils.c msr.c -lm

clean:
	rm -rf $(BUILDDIR)/*
