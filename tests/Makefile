all:	rapl_cache_misses rapl_cm_0 rapl_cache_misses_old rapl_sleep rapl_temp

rapl_cache_misses: rapl_cache_misses.c
	gcc -O0 -Wall -o rapl_cache_misses rapl_cache_misses.c -lpapi

rapl_cache_misses_old: rapl_cache_misses_old.c
	gcc -O0 -Wall -o rapl_cache_misses_old rapl_cache_misses_old.c -lpapi

rapl_cm_0: rapl_cm_0.c
	gcc -O0 -Wall -o rapl_cm_0 rapl_cm_0.c -lpapi


rapl_temp: rapl_temp.c
	gcc -O0 -Wall -o rapl_temp rapl_temp.c -lpapi

rapl_sleep: rapl_sleep.c
	gcc -O0 -Wall -o rapl_sleep rapl_sleep.c -lpapi

clean:
	rm -rf rapl_cache_misses rapl_cm_0 rapl_cache_misses_old

