
ROOT = ./..
PWD = .
INCLUDE_JSON = -I ${PWD}/cpp_modules/dist/ ${PWD}/cpp_modules/dist/*.cpp
INCLUDE_PRIMEORDEAL = -I ${PWD}/cpp_modules/primeordeal/  ${PWD}/cpp_modules/primeordeal/*.cpp
INCLUDE_UTILS = -I ${PWD}/cpp_modules/  ${PWD}/cpp_modules/*.cpp

.PHONY : clean
clean:
	rm ./*o
	
main:
	g++ -std=c++11 main.cpp $(INCLUDE_JSON) $(INCLUDE_PRIMEORDEAL) $(INCLUDE_UTILS) processes.cpp -o ${ROOT}/cpp_bins/main

.PHONY : calculations
calculations:
	g++ calculations.cpp -o calculations
	${ROOT}/cpp_bins/calculations

.PHONY : test
test:
	g++ test.cpp calculations.cpp -o test
	${ROOT}/cpp_bins/test

.PHONY : beehive_tests
beehive_tests:
	node ./../module_tests.js

.PHONY : basicbuild
basicbuild:
	g++ -std=c++17 basicmath.cpp -o ${ROOT}/cpp_bins/basic 

.PHONY : basictest
basictest:basicbuild
	${ROOT}/cpp_bins/basic square 2
	${ROOT}/cpp_bins/basic log10 100000
	${ROOT}/cpp_bins/basic cube 3

.PHONY : maintests
maintests: main
	${ROOT}/cpp_bins/main float "1011.1"
	${ROOT}/cpp_bins/main line center "500,500" angle "0.52" length "400"  

.PHONY : maintestsonly
maintestsonly:
	${ROOT}/cpp_bins/main line center "500,500" angle "0.52" length "400" 
	${ROOT}/cpp_bins/main curve center "500,500" movement "100, 100, 100, 100"

.PHONY :  all 
all:  main basictest maintests
