FLAGS=-ggdb -std=c++17 -pedantic -Wall -Werror -Wextra -lstdc++

TEST_SOURCE=s21_vector_test.cc
TEST_OUTPUT=s21_vector_test.o

all: clean check test leaks
# all: clean check map_test leaks gcov_report 
# all: clean map_test

check:
	cp ../../materials/linters/.clang-format .
	find . -type f \( -name "*.cc" -o -name "*.h" \) -exec clang-format -i --style="Google" {} \;
	rm -f .clang-format
	cppcheck --check-config --std=c++17 --language=c++ --enable=all --suppress=missingIncludeSystem *.cc *.h

test: $(TEST_SOURCE)
	gcc $(FLAGS) --coverage $(TEST_SOURCE) -o $(TEST_OUTPUT) -lgtest
	@./$(TEST_OUTPUT)

leaks:
	leaks -atExit -- ./$(TEST_OUTPUT)

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
	@rm -rf *.dSYM
