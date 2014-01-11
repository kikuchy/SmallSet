echo "Compiling unit tests..."
clang -c set.c
clang++ -lgtest -std=c++11 -lpthread -o unit_test.o -c test.cpp
clang++ -lgtest -std=c++11 -lpthread -o unit_test unit_test.o set.o
echo "Running unit tests..."
./unit_test -v
result=$?
rm -r unit_test set.o unit_test.o
echo "Unit tests completed : $result"
exit $result
