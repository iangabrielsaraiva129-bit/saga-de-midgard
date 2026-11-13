SRC = src/main.c src/util.c src/interface.c src/personagem.c src/combate.c src/fases.c

jogo: $(SRC)
	gcc -std=c99 -Wall -Wextra -o jogo $(SRC) -lm

clean:
	rm -f jogo jogo.exe
