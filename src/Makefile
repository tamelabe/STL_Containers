.PHONY : clean check stack_test

CC = gcc
CPPFLAGS = -ggdb -lstdc++ -std=c++17 -pedantic -Wall -Werror -Wextra -lstdc++
TEST_FLAGS = --coverage -lgtest
LINUX_FLAGS = -lrt -lpthread -lm -lsubunit
VG_FLAGS = CK_FORK=no valgrind --trace-children=yes --track-fds=yes --track-origins=yes --leak-check=full --show-leak-kinds=all --verbose --log-file=RESULT_VALGRIND.txt

#TESTS
LIST_TEST_SOURCE=./List/s21_list_test.cc
STACK_TEST_SOURCE=./Stack/s21_stack_test.cc
QUEUE_TEST_SOURCE=./Queue/s21_queue_test.cc


all: clean check tests leaks gcov_report

check:
	cp ../materials/linters/.clang-format .
	find . -type f \( -name "*.cc" -o -name "*.h" \) -exec clang-format -n --style="Google" {} \;
	rm -f .clang-format

tests_compile:
	$(CC) $(CPPFLAGS)  $(LIST_TEST_SOURCE) -o list.o $(TEST_FLAGS)
	$(CC) $(CPPFLAGS)  $(STACK_TEST_SOURCE) -o stack.o $(TEST_FLAGS)
	$(CC) $(CPPFLAGS)  $(QUEUE_TEST_SOURCE) -o queue.o $(TEST_FLAGS)
	./list.o && ./stack.o && ./queue.o

leaks:
	leaks -atExit -- ./list.o
	leaks -atExit -- ./stack.o
	leaks -atExit -- ./queue.o

leaks_valgrind:
	$(VG) ./leaks_report

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
