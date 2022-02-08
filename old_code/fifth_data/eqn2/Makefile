SRC= src
UTIL = utils
BUILD= build
all: one two three four fifth

one: $(SRC)/calc_formulae.c $(UTIL)/calc_error.c
	gcc -O0 -Wall -o $(BUILD)/one $(SRC)/calc_formulae.c $(UTIL)/calc_error.c
two: $(SRC)/calc_formulae2.c $(UTIL)/calc_error.c
	gcc -O0 -Wall -o $(BUILD)/two $(SRC)/calc_formulae2.c $(UTIL)/calc_error.c
three: $(SRC)/calc_formulae3.c $(UTIL)/calc_error.c
	gcc -O0 -Wall -o $(BUILD)/three $(SRC)/calc_formulae3.c $(UTIL)/calc_error.c
four: $(SRC)/calc_formulae4.c $(UTIL)/calc_error.c
	gcc -O0 -Wall -o $(BUILD)/four $(SRC)/calc_formulae4.c $(UTIL)/calc_error.c
fifth: $(SRC)/calc_formulae5.c $(UTIL)/calc_error.c
	gcc -O0 -Wall -o $(BUILD)/fifth $(SRC)/calc_formulae5.c $(UTIL)/calc_error.c
