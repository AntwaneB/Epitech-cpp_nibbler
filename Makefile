##
## Makefile for monlongserpent in /home/buchse_a/Projects/
##
## Made by Antoine Buchser
## Login   <buchse_a@epitech.net>
##
## Started on  Fri Feb  6 11:34:26 2015 Antoine Buchser
## Last update Wed Feb 11 13:40:14 2015 Antoine Buchser
##

CC		  =  g++

NAME		  =  nibbler

RM		  =  rm -f
MKDIR		  =  mkdir -p

SRCS_DIR	  =  src
SRCS		  =  main.cpp \
		     App.cpp \
		     Position.cpp \
		     AEntity.cpp \
		     Block.cpp \
		     Snake.cpp \
		     Clock.cpp \
		     Config.cpp \
		     IGraphics.cpp \
		     EventHandler.cpp \
		     Level.cpp \
		     Food.cpp \
		     pugixml.cpp

OBJS_DIR	  =  obj
OBJS		  =  $(SRCS:%.cpp=$(OBJS_DIR)/%.o)

INCS_DIR	  =  inc
INCS		  =  Exception.hpp \
		     App.hpp \
		     Position.hpp \
		     AEntity.hpp \
		     Block.hpp \
		     Snake.hpp \
		     Clock.hpp \
		     Config.hpp \
		     IGraphics.hpp \
		     Event.hpp \
		     EventHandler.hpp \
		     Level.hpp \
		     Food.hpp \
		     pugiconfig.hpp \
		     pugixml.hpp

LIBS_DIR	  =  libs

COMMON_SRCS	  =  IGraphics.cpp \
		     Position.cpp \
		     Config.cpp
COMMON_OBJS	  =  $(COMMON_SRCS:%.cpp=$(OBJS_DIR)/%.o)
LIB_NCURSE_NAME	  =  lib_nibbler_ncurses.so
LIB_NCURSE_DIR	  =  $(LIBS_DIR)/ncurses
LIB_NCURSE_SRCS	  =  NcursesGraphics.cpp
LIB_NCURSE_OBJS	  =  $(LIB_NCURSE_SRCS:%.cpp=$(OBJS_DIR)/$(LIB_NCURSE_DIR)/%.o)

LIB_SDL_NAME	  =  lib_nibbler_sdl.so
LIB_SDL_DIR	  =  $(LIBS_DIR)/sdl
LIB_SDL_SRCS	  =  SDLGraphics.cpp
LIB_SDL_OBJS	  =  $(LIB_SDL_SRCS:%.cpp=$(OBJS_DIR)/$(LIB_SDL_DIR)/%.o)

LIB_OPENGL2D_NAME	  =  lib_nibbler_opengl2D.so
LIB_OPENGL2D_DIR	  =  $(LIBS_DIR)/opengl2D
LIB_OPENGL2D_SRCS	  =  OpenGL2DGraphics.cpp
LIB_OPENGL2D_OBJS	  =  $(LIB_OPENGL2D_SRCS:%.cpp=$(OBJS_DIR)/$(LIB_OPENGL2D_DIR)/%.o)

LIB_OPENGL3D_NAME	  =  lib_nibbler_opengl3D.so
LIB_OPENGL3D_DIR	  =  $(LIBS_DIR)/opengl3D
LIB_OPENGL3D_SRCS	  =  OpenGL3DGraphics.cpp
LIB_OPENGL3D_OBJS	  =  $(LIB_OPENGL3D_SRCS:%.cpp=$(OBJS_DIR)/$(LIB_OPENGL3D_DIR)/%.o)

DEPS		  =  $(patsubst %,$(INCS_DIR)/%,$(INCS))

CFLAGS		  += -I./inc -ldl
CFLAGS		  += -std=c++11 -Wall -Wextra -W -Werror -fPIC

CFLAGS		  += -g


#######################
## COMPILATION RULES ##
#######################

all:		     $(NAME) $(LIB_NCURSE_NAME) $(LIB_SDL_NAME) $(LIB_OPENGL2D_NAME) $(LIB_OPENGL3D_NAME)

## Compiling core
$(NAME):	     $(OBJS)
		     $(CC) $(OBJS) $(CFLAGS) -o $(NAME)

$(OBJS_DIR)/%.o:     $(SRCS_DIR)/%.cpp $(DEPS)
		     @$(MKDIR) $(OBJS_DIR)
		     $(CC) $(CFLAGS) -c -o $@ $<
## END Compiling core

## Compiling Ncurses Graphical module
$(LIB_NCURSE_NAME):  $(LIB_NCURSE_OBJS)
		     $(CC) $(LIB_NCURSE_OBJS) $(COMMON_OBJS) $(CFLAGS) -lncurses -shared -o $(LIB_NCURSE_NAME)

$(OBJS_DIR)/$(LIB_NCURSE_DIR)/%.o:  $(LIB_NCURSE_DIR)/%.cpp
				    @$(MKDIR) $(OBJS_DIR)/$(LIB_NCURSE_DIR)
				    $(CC) $(CFLAGS) -lncurses -c -o $@ $<
## END Compiling Ncurses Graphical module

## Compiling SDL Graphical module
$(LIB_SDL_NAME):  $(LIB_SDL_OBJS)
		     $(CC) $(LIB_SDL_OBJS) $(COMMON_OBJS) $(CFLAGS) -lSDL -lSDL_image -lSDL_ttf -lSDL_mixer -lX11 -shared -o $(LIB_SDL_NAME)

$(OBJS_DIR)/$(LIB_SDL_DIR)/%.o:  $(LIB_SDL_DIR)/%.cpp
				    @$(MKDIR) $(OBJS_DIR)/$(LIB_SDL_DIR)
				    $(CC) $(CFLAGS) -lSDL -lSDL_image -lSDL_ttf -lSDL_mixer -lX11 -c -o $@ $<
## END Compiling SDL Graphical module

## Compiling OpenGL2D Graphical module
$(LIB_OPENGL2D_NAME):  $(LIB_OPENGL2D_OBJS)
		     $(CC) $(LIB_OPENGL2D_OBJS) $(COMMON_OBJS) $(CFLAGS) -lSDL -lSDL_image -lSDL_ttf -lSDL_mixer -lX11 -shared -o $(LIB_OPENGL2D_NAME)

$(OBJS_DIR)/$(LIB_OPENGL2D_DIR)/%.o:  $(LIB_OPENGL2D_DIR)/%.cpp
				    @$(MKDIR) $(OBJS_DIR)/$(LIB_OPENGL2D_DIR)
				    $(CC) $(CFLAGS) -lSDL -lSDL_image -lSDL_ttf -lSDL_mixer -lX11 -c -o $@ $<
## END Compiling OpenGL2D Graphical module

## Compiling OpenGL3D Graphical module
$(LIB_OPENGL3D_NAME):  $(LIB_OPENGL3D_OBJS)
		     $(CC) $(LIB_OPENGL3D_OBJS) $(COMMON_OBJS) $(CFLAGS) -lSDL -lSDL_image -lSDL_ttf -lSDL_mixer -lX11 -shared -o $(LIB_OPENGL3D_NAME)

$(OBJS_DIR)/$(LIB_OPENGL3D_DIR)/%.o:  $(LIB_OPENGL3D_DIR)/%.cpp
				    @$(MKDIR) $(OBJS_DIR)/$(LIB_OPENGL3D_DIR)
				    $(CC) $(CFLAGS) -lSDL -lSDL_image -lSDL_ttf -lSDL_mixer -lX11 -c -o $@ $<
## END Compiling OpenGL3D Graphical module


################
## MISC RULES ##
################

clean:
		     $(RM) -r $(OBJS_DIR)

fclean:		     clean
		     $(RM) $(NAME)
		     $(RM) $(LIB_NCURSE_NAME)
		     $(RM) $(LIB_SDL_NAME)
		     $(RM) $(LIB_OPENGL2D_NAME)
		     $(RM) $(LIB_OPENGL3D_NAME)

re:		     fclean all

.PHONY: re fclean clean all
