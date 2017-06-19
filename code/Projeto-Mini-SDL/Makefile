CEU_DIR     = /opt/reativos/ceu
CEU_SDL_DIR = /opt/reativos/ceu-sdl

game:
	    ceu --pre --pre-args="-I$(CEU_DIR)/include -I$(CEU_SDL_DIR)/include" \
	              --pre-input=src/game.ceu                                   \
	        --ceu --ceu-err-unused=pass --ceu-err-uninitialized=pass         \
	        --env --env-types=$(CEU_DIR)/env/types.h                         \
	              --env-threads=$(CEU_DIR)/env/threads.h                     \
	              --env-main=$(CEU_DIR)/env/main.c                           \
	        --cc --cc-args="-lm -llua5.3 -lpthread -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf -lSDL2_gfx '-Wl,-rpath,$ORIGIN/lib'" \
	             --cc-output=/tmp/game.ceu;                                  \
		/tmp/game.ceu;	                                                 \
