TARGET = morse

OBJS = morse.o

OPTS = -g

$(TARGET): $(OBJS)
	gcc $(OPTS) -o $@ $^

.c.o:
	gcc -c $(OPTS) $<

clean:
	rm $(TARGET) $(OBJS)
