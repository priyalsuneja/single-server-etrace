all:	rapl_cache_misses rapl_cm_0 rapl_cache_misses_old

rapl_cache_misses: rapl_cache_misses.c
	gcc -O0 -Wall -o rapl_cache_misses rapl_cache_misses.c -lpapi

rapl_cache_misses_old: rapl_cache_misses_old.c
	gcc -O0 -Wall -o rapl_cache_misses_old rapl_cache_misses_old.c -lpapi

rapl_cm_0: rapl_cm_0.c
	gcc -O0 -Wall -o rapl_cm_0 rapl_cm_0.c -lpapi

clean:
	rm -rf rapl_cache_misses rapl_cm_0 rapl_cache_misses_old

