BUILDDIR = build
INCLUDE = ../../includes

all: tlb_signal l1_signal l2_signal qs_signal mm_signal redis

#all: mm_signal

l1_signal: l1_signal.c $(INCLUDE)/utils.c $(INCLUDE)/msr.c
	gcc -O0 -Wall -o $(BUILDDIR)/l1_signal l1_signal.c $(INCLUDE)/utils.c $(INCLUDE)/msr.c -lm

l2_signal: l2_signal.c $(INCLUDE)/utils.c $(INCLUDE)/msr.c
	gcc -O0 -g -Wall -o $(BUILDDIR)/l2_signal l2_signal.c $(INCLUDE)/utils.c $(INCLUDE)/msr.c -lm

qs_signal: qs_signal.c $(INCLUDE)/msr.c $(INCLUDE)/utils.c
	gcc -O0 -Wall -o $(BUILDDIR)/qs_signal qs_signal.c $(INCLUDE)/utils.c $(INCLUDE)/msr.c -lm

mm_signal: mm_signal.c $(INCLUDE)/msr.c $(INCLUDE)/utils.c
	gcc -O0 -g -Wall -o $(BUILDDIR)/mm_signal mm_signal.c $(INCLUDE)/utils.c $(INCLUDE)/msr.c -lm

tlb_signal: tlb_signal.c $(INCLUDE)/utils.c $(INCLUDE)/msr.c
	gcc -O0 -Wall -o $(BUILDDIR)/tlb_signal tlb_signal.c $(INCLUDE)/utils.c $(INCLUDE)/msr.c -lm

redis: redis.c $(INCLUDE)/utils.c $(INCLUDE)/msr.c $(INCLUDE)/hiredis/hiredis.c
	gcc -O0 -Wall -o $(BUILDDIR)/redis redis.c $(INCLUDE)/utils.c $(INCLUDE)/msr.c -lm

clean:
	rm -rf $(BUILDDIR)/*
