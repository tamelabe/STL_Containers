FLAGS=-ggdb -std=c++17 -Wall -Werror -Wextra -lstdc++
# STACK
stack_TEST_SOURCE=s21_stack_test.cc
stack_TEST_OUTPUT=s21_stack_test.o

all: stack

stack: clean check stack_test leaks gcov_report


check:
	cp ../../materials/linters/.clang-format . && clang-format --style="Google" *.cc *.h -n
	rm -f .clang-format

stack_test: $(stack_TEST_SOURCE)
	@gcc $(FLAGS) --coverage $(stack_TEST_SOURCE) -o $(stack_TEST_OUTPUT) -lgtest
	@./$(stack_TEST_OUTPUT)

leaks:
	leaks -atExit -- ./*.o

gcov_report:
	lcov -t "test" -o s21_test.info -c -d ./ --no-external
	genhtml ./s21_test.info --output-directory ./report/
	open ./report/index.html

clean:
	@rm -rf report
	@rm -rf *.gcda
	@rm -rf *.gcno
	@rm -rf *.info
	@rm -rf *.gch
	@rm -rf *.dSYM
	@rm -rf ../*.idea
	@rm -rf ../.run
	@rm -rf ../*.dSYM
	@rm -rf ./report
	@rm -rf *.a
	@rm -rf *.o
