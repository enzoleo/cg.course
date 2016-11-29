#########################
# Makefile
# Author: Peiyu Liao
# Date: 2016.11.25
#########################

SRCS = main.cpp stanford_bunny.cpp
OBJS = $(SRCS:.c = .o)
PROG = proj
CC = gcc
CFFLAGS = -g

$(PROG): $(OBJS)
	$(CC) $(CFFLAGS) -o $@ $^ -lGL -lGLU -lglut

$(OBJS): stanford_bunny.h
