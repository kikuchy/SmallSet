echo "Compiling unit tests..."
clang -c set.c
clang++ -lgtest -std=c++11 -pthread -g -Wall -Wextra -o unit_test.o -c test.cpp
clang++ -std=c++11 -g -Wall -Wextra -o unit_test set.o unit_test.o -lgtest -pthread
echo "Running unit tests..."
./unit_test -v
result=$?
rm -r unit_test set.o unit_test.o
echo "Unit tests completed : $result"
exit $result
