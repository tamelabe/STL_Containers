<<<<<<< HEAD
# FLAGS=-ggdb -std=c++17 -Wall -Werror -Wextra -lstdc++

MAP_TEST_SOURCE=./tests/s21_map_test.cc
MAP_TEST_OUTPUT=s21_map_test.o

# all: clean check map_test leaks gcov_report 
all: clean map_test

check:
	cp ../materials/linters/.clang-format . && clang-format *.cc *.h
	rm -f .clang-format
	cppcheck --std=c++17 --language=c++ --enable=all --suppress=missingIncludeSystem *.cc *.h

map_test: $(MAP_TEST_SOURCE)
	@g++ $(FLAGS) --coverage $(MAP_TEST_SOURCE) -o $(MAP_TEST_OUTPUT) -lgtest
	@./$(MAP_TEST_OUTPUT)

leaks:
	leaks -atExit -- ./$(MAP_TEST_OUTPUT)
=======
FLAGS=-ggdb -std=c++17 -Wall -Werror -Wextra -lstdc++

VECTOR_TEST_SOURCE=s21_vector_test.cc
VECTOR_TEST_OUTPUT=s21_vector_test.o

all: clean check vector_test leaks gcov_report 

check:
	cp ../materials/linters/.clang-format . && clang-format *.cc *.h -i
	rm -f .clang-format
	cppcheck --std=c++17 --language=c++ --enable=all --suppress=missingIncludeSystem *.cc *.h

vector_test: $(VECTOR_TEST_SOURCE)
	@gcc $(FLAGS) --coverage $(VECTOR_TEST_SOURCE) -o $(VECTOR_TEST_OUTPUT) -lgtest
	@./$(VECTOR_TEST_OUTPUT)

leaks:
	leaks -atExit -- ./$(VECTOR_TEST_OUTPUT)
>>>>>>> 73e64f099377aae28a8de04ffb82c78edd73658f

gcov_report:
	lcov -t "test" -o test.info -c -d ./
	lcov --remove test.info "/usr*" -o test.info
	genhtml -o report test.info
	open -a "Safari" ./report/index.html

clean:
	@rm -rf report
	@rm -rf *.gcda
	@rm -rf *.gcno
	@rm -rf *.info
	@rm -rf *.a
	@rm -rf *.o
<<<<<<< HEAD
	@rm -rf *.dSYM
=======
>>>>>>> 73e64f099377aae28a8de04ffb82c78edd73658f
