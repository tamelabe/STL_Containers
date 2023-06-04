FLAGS=-ggdb -std=c++17 -Wall -Werror -Wextra -lstdc++
# Vector
VECTOR_TEST_SOURCE=s21_vector_test.cc
VECTOR_TEST_OUTPUT=s21_vector_test.o
# Array
ARRAY_TEST_SOURCE=s21_array_test.cc
ARRAY_TEST_OUTPUT=s21_array_test.o

all: array

array: clean check array_test leaks gcov_report

check:
	cp ../materials/linters/.clang-format . && clang-format *.cc *.h -i
	rm -f .clang-format
	cppcheck --std=c++17 --language=c++ --enable=all --suppress=missingIncludeSystem *.cc *.h

vector_test: $(VECTOR_TEST_SOURCE)
	@gcc $(FLAGS) --coverage $(VECTOR_TEST_SOURCE) -o $(VECTOR_TEST_OUTPUT) -lgtest
	@./$(VECTOR_TEST_OUTPUT)

array_test: $(ARRAY_TEST_SOURCE)
	@gcc $(FLAGS) --coverage $(ARRAY_TEST_SOURCE) -o $(ARRAY_TEST_OUTPUT) -lgtest
	@./$(ARRAY_TEST_OUTPUT)

leaks:
	leaks -atExit -- ./*.o

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
