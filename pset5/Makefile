#
# Makefile
#
# Computer Science 50
# Problem Set 5
#


# compiler to use - используемый компилятор
CC = clang-3.5

# flags to pass compiler
# Флаги для передачи компилятора
CFLAGS = -ggdb3 -O0 -Qunused-arguments -std=c11 -Wall -Werror

# name for executable
# имя исполняемого файлаа
EXE = speller

# space-separated list of header files
# Список файлов заголовков, разделенных пробелами
HDRS = dictionary.h

# space-separated list of libraries, if any,
# each of which should be prefixed with -l
# Список разделенных пробелами библиотек, если таковые имеются,
# Каждый из которых должен иметь префикс -l
LIBS =

# space-separated list of source files
# Список исходных файлов, разделенных пробелами
SRCS = speller.c dictionary.c

# automatically generated list of object files
# Автоматически созданный список объектных файлов
OBJS = $(SRCS:.c=.o)


# default target
# Цель по умолчанию
$(EXE): $(OBJS) $(HDRS) Makefile
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(LIBS)

# dependencies - зависимости
$(OBJS): $(HDRS) Makefile

# housekeeping - уборка
clean:
	rm -f core $(EXE) *.o
