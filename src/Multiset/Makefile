FLAGS=-ggdb -std=c++17 -Wall -Werror -Wextra -lstdc++

SET_TEST_SOURCE=s21_multiset_test.cc
SET_TEST_OUTPUT=s21_multiset_test.o

all: clean check multiset_test leaks

check:
	cp ../../materials/linters/.clang-format . && clang-format -n *.cc *.h
	# rm -f .clang-format
	cppcheck --check-config --std=c++17 --language=c++ --enable=all --suppress=missingIncludeSystem *.cc *.h

multiset_test: $(SET_TEST_SOURCE)
	@g++ $(FLAGS) --coverage $(SET_TEST_SOURCE) -o $(SET_TEST_OUTPUT) -lgtest --coverage
	@./$(SET_TEST_OUTPUT)

leaks:
	leaks -atExit -- ./$(SET_TEST_OUTPUT)

gcov_report:
	lcov -t "test" -o test.info -c -d ./ --no-external --ignore-errors mismatch
	genhtml test.info -o report test.info
	open -a "Safari" ./report/index.html

clean:
	@rm -rf report
	@rm -rf *.gcda
	@rm -rf *.gcno
	@rm -rf *.info
	@rm -rf *.a
	@rm -rf *.o
	@rm -rf *.dSYM
