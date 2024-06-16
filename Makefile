# Nama compiler
CC = gcc

# Compiler flags:
# -Wall: mengaktifkan semua pesan peringatan dari compiler
# -O2: level optimasi 2
CFLAGS = -Wall -O2

# Nama file eksekusi
TARGET = majority_minority_algorithm

# File source
SRCS = majority_minority_algorithm.c

# File object
OBJS = $(SRCS:.c=.o)

# Target default: membangun program
all: $(TARGET)

# Aturan untuk menghubungkan file object dan membuat file eksekusi
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

# Aturan untuk mengkompilasi file .c menjadi file .o
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Aturan untuk membersihkan direktori build
clean:
	rm -f $(OBJS) $(TARGET)

# Phony targets adalah target yang bukan file sebenarnya
.PHONY: all clean
