CC = gcc
CFLAGS = -Wall -std=c99

TARGET = FinancialDataAnalyzer.exe

SRCDIR = src
SRC = src/main.c src/query_interface.c src/analytics.c src/data_structures.c

INC = -I$(SRCDIR)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(INC) $(SRC) -o $(TARGET)

clean:
	rm -f $(TARGET)
