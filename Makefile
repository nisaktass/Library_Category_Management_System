PROGRAM=kitap_sistemi
DOSYA=main.c	proje1.c
all:
	gcc	$(DOSYA)	-o	$(PROGRAM)
	./$(PROGRAM)
clean:
	rm	-f	$(PROGRAM)

