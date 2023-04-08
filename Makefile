CC = g++
CFLAGS = -lsqlite3 -Iinclude
main_obj = obj/main.o
obj = obj/controller.o obj/model.o
run: build 
	./bin/main
build: mkdirs $(main_obj) $(obj)
	$(CC) $(main_obj) $(obj) -o bin/main $(CFLAGS)
mkdirs:
	mkdir -p obj bin
obj/%.o: src/%.cpp
	$(CC) -c $< -o $@ $(CFLAGS)
clean:
	rm bin/* obj/*