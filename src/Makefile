FLAGS=-Wall -Werror -Wextra -lstdc++ -std=c++17

VECTOR_TEST_SOURCE=s21_Vector_test.cc
VECTOR_TEST_OUTPUT=s21_Vector_test.o
VECTOR_SOURCE=s21_Vector.cc
VECTOR_OUTPUT=s21_Vector.a
VECTOR_O=s21_Vector.o

# main: main.cc
# 	@gcc main.cc -o main.o -lstdc++

# all: build check test leaks gcov_report 
all: build test

build: $(VECTOR_OUTPUT)

rebuild: clean build

$(VECTOR_OUTPUT):
	gcc $(FLAGS) -c $(VECTOR_SOURCE)
	@ar rc $(VECTOR_OUTPUT) $(VECTOR_O)
	@ranlib $(VECTOR_OUTPUT)

check:
	cp ../materials/linters/.clang-format . && clang-format *.cc *.h
	rm -f .clang-format
	cppcheck --std=c++17 --language=c++ --enable=all --suppress=missingIncludeSystem *.cc *.h

test: $(VECTOR_TEST_SOURCE)
	@gcc $(FLAGS) --coverage $(VECTOR_TEST_SOURCE) $(VECTOR_SOURCE) $(VECTOR_OUTPUT) -o $(VECTOR_TEST_OUTPUT) -lgtest
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
