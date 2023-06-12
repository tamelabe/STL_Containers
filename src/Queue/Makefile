FLAGS=-ggdb -std=c++17 -Wall -Werror -Wextra -lstdc++
# STACK
queue_TEST_SOURCE=s21_queue_test.cc
queue_TEST_OUTPUT=s21_queue_test.o

all: queue

queue: clean check queue_test leaks gcov_report


check:
	cp ../../materials/linters/.clang-format . && clang-format --style="Google" *.cc *.h -n
	rm -f .clang-format

queue_test: $(queue_TEST_SOURCE)
	@gcc $(FLAGS) --coverage $(queue_TEST_SOURCE) -o $(queue_TEST_OUTPUT) -lgtest
	@./$(queue_TEST_OUTPUT)

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
