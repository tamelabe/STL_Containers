# FLAGS=-ggdb -std=c++17 -Wall -Werror -Wextra -lstdc++

TREE_TEST_SOURCE=s21_tree_test.cc
TREE_TEST_OUTPUT=s21_tree_test.o

# all: clean check tree_test leaks gcov_report 
all: clean check tree_test

check:
	cp ../materials/linters/.clang-format . && clang-format *.cc *.h -i
	rm -f .clang-format
	cppcheck --std=c++17 --language=c++ --enable=all --suppress=missingIncludeSystem *.cc *.h

tree_test: $(TREE_TEST_SOURCE)
	# @gcc $(FLAGS) --coverage $(TREE_TEST_SOURCE) -o $(TREE_TEST_OUTPUT) -lgtest
	@g++ --coverage $(TREE_TEST_SOURCE) -o $(TREE_TEST_OUTPUT) -lgtest
	@./$(TREE_TEST_OUTPUT)

leaks:
	leaks -atExit -- ./$(TREE_TEST_OUTPUT)

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