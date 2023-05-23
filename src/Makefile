FLAGS=-Wall -Werror -Wextra -lstdc++ -std=c++17

VECTOR_TEST_SOURCE=s21_vector_test.cc
VECTOR_TEST_OUTPUT=s21_vector_test.o
VECTOR_SOURCE=s21_vector.cc
VECTOR_OUTPUT=s21_vector.a
VECTOR_O=s21_vector.o

# all: build check test leaks gcov_report 
all: clean check vector_test leaks gcov_report 

check:
	cp ../materials/linters/.clang-format . && clang-format *.cc *.h
	rm -f .clang-format
	cppcheck --std=c++17 --language=c++ --enable=all --suppress=missingIncludeSystem *.cc *.h

vector_test: $(VECTOR_TEST_SOURCE)
	@gcc $(FLAGS) --coverage $(VECTOR_TEST_SOURCE) -o $(VECTOR_TEST_OUTPUT) -lgtest
	@./$(VECTOR_TEST_OUTPUT)

leaks:
	leaks -atExit -- ./$(VECTOR_TEST_OUTPUT)

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
