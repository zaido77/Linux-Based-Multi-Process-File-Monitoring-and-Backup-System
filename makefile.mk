
monitor: src/main.o src/scanner.o src/backup.o src/logger.o src/alerts_logger.o src/signal_handler.o
	gcc src/*.o -o monitor

src/main.o: src/main.c
	gcc -c src/main.c -o src/main.o

src/scanner.o: src/scanner.c
	gcc -c src/scanner.c -o src/scanner.o

src/backup.o: src/backup.c
	gcc -c src/backup.c -o src/backup.o

src/logger.o: src/logger.c
	gcc -c src/logger.c -o src/logger.o

src/alerts_logger.o: src/alerts_logger.c
	gcc -c src/alerts_logger.c -o src/alerts_logger.o

src/signal_handler.o: src/signal_handler.c
	gcc -c src/signal_handler.c -o src/signal_handler.o

