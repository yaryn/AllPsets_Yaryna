# compiler to use
# -> визначає змінну на ім’я CC яка показує що make має використовувати clang для компіляції
CC = clang

# flags to pass compiler -> визначає змінну CFLAGS, яка визначає прапори, які має використати clang
CFLAGS = -ggdb3 -O0 -Qunused-arguments -std=c11 -Wall -Werror

# name for executable -> зміннa EXE вміщає ім’я нашої програми
EXE = speller

# space-separated list of header files -> HDRS, значення якої – список заголовних файлів використовуваних speller-ом, розділений пробілами
HDRS = dictionary.h

# space-separated list of libraries, if any,
# each of which should be prefixed with -l
# LIBS, значення якої – розділений пробілами список заголовних бібліотек, 
# кожній з яких має передувати -l (Пригадайте використання -lcs50 раніше.) 
# Швидше за все вам не буде потрібна жодна бібліотека для цього завдання, 
# але ми включили цю опцію про всяк випадок
LIBS =

# space-separated list of source files ->змінну SRCS значення якої – розділений пробілами список С-файлів, які є реалізацією перевірки правопису
SRCS = speller.c dictionary.c

# automatically generated list of object files ->OBJS, значення те саме, що і SRCS, за винятком того, що розширення файлів не .c, а .o
OBJS = $(SRCS:.c=.o)


# default target ->  визначає «ціль», використовуючи змінні, що ми визначили вище, яка визначає як make буде компілювати програму
$(EXE): $(OBJS) $(HDRS) Makefile
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(LIBS)

# dependencies 
# -> рядок визначає, що наші .o файли залежать від dictionary.h і Makefile, 
# тому зміни будь-якого з них приведуть до рекомпіляції .o файлів при наступному запуску make
$(OBJS): $(HDRS) Makefile

# housekeeping -> код визначає іншу ціль для очищення директорії
clean:
	rm -f core $(EXE) *.o
