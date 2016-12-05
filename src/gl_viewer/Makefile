#########################
# Makefile
# Author: Peiyu Liao
# Date: 2016.11.30
#########################

SRCS = main.cpp
OBJS = $(SRCS:.c = .o)
PROG = proj
CC = gcc
CFFLAGS = -g

$(PROG): $(OBJS)
	$(CC) $(CFFLAGS) -o $@ $^ -lGL -lGLU -lglut
