CFLAGS = -lsqlite3 -Iinclude -lssl -lcrypto
TESTFLAGS = -lsqlite3 -lgtest -lgtest_main -lssl -Iinclude -lcrypto
COVFLAGS = -fprofile-arcs -ftest-coverage
CC = g++
main_obj = obj/main.o
obj = obj/controller.o obj/model.o
test_obj = obj/test.o
run: build
	./bin/main
report: test
	lcov -c --directory obj --output-file coverage.info; genhtml coverage.info -o cov; rm coverage.info; firefox cov/index.html
test: build_test
	./bin/test_main
build_test: dirs $(test_obj) $(obj)
	$(CC) $(COVFLAGS) $(obj) $(test_obj) -o bin/test_main  $(TESTFLAGS)
build: dirs $(obj) $(main_obj)
	$(CC) $(COVFLAGS) $(main_obj) $(obj) -o bin/main $(CFLAGS)
dirs:
	mkdir -p obj bin
obj/%.o: test/%.cc
	$(CC) $(COVFLAGS) -c $< -o $@ $(TESTFLAGS)
obj/%.o: src/%.cpp
	$(CC) $(COVFLAGS) -c $< -o $@ $(CFLAGS)
clean:
	rm bin/* obj/*; rm -r cov