# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yskrypny <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/09/20 13:16:20 by yskrypny          #+#    #+#              #
#    Updated: 2018/01/27 20:42:44 by yskrypny         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#all rule

#Colors tags

GREENTAG:="\033[1;32m"
YELLOWTAG:="\033[1;33m"
REDTAG:="\033[1;31m"
CENDTAG:="\033[0;0m"
#-----------

#Binary name
NAME = ft_gkrellm
#Compiler
CC = clang++
#Compiler flags
CFLAGS = -Wall -Wextra -Werror
LIBFLAGS = `pkg-config --cflags --libs gtk+-3.0` -lncurses
LDFLAGS = rcs
#Project structure directories
IDIR = src/ src/display_modules/ src/monitor_modules/
ODIR = obj
SDIR = src
#All project sources list (norminette demand)
SRCS = src/main.cpp\
    src/monitor_modules/MonitorCpu.cpp \
    src/monitor_modules/MonitorDateTime.cpp \
    src/monitor_modules/MonitorDisk.cpp \
    src/monitor_modules/MonitorHostUser.cpp \
    src/monitor_modules/AMonitorModule.cpp \
    src/monitor_modules/MonitorNetwork.cpp \
    src/monitor_modules/MonitorOsInfo.cpp \
    src/monitor_modules/MonitorRam.cpp \
    src/display_modules/AMonitorDisplay.cpp \
    src/display_modules/DisplayNcurses.cpp \
    src/display_modules/DisplayGtk.cpp \
#Creating objects path
OBJS := $(patsubst %.c,$(ODIR)%.o,$(SRCS))

#Compiling object files
$(ODIR)/%.o:$(SDIR)/%.c
	@mkdir -p $(dir $@)
	@echo $(YELLOWTAG)"|\c"
	@$(CC) $(CFLAGS) -I $(IDIR) -I $(LIDIR) -c $< -o $@

#Linking binary, adding libs etc.
$(NAME):$(OBJS)
	@echo $(GREENTAG)"Linking project..."
	@$(CC) -o $@ $^ $(CFLAGS) $(LIBFLAGS) $(LBFLAGS) -pg
	@echo "Done."$(CENDTAG)

#defining order and checking that obj dir exists
$(OBJS): | $(ODIR)
#creating obj dir if not exist
$(ODIR):
	@mkdir -p $(ODIR)

all: $(NAME)

#clean rule
clean:
	@echo $(YELLOWTAG)"Cleaning project..."
	@rm -rf $(ODIR)
	@echo "Done."$(CENDTAG)
#full clean rule
fclean: clean
	@rm -rf $(NAME)
	@echo $(REDTAG)"Project deleted."$(CENDTAG)
#norminette rule
norm:
	@norminette $(SDIR)/*.c
	@norminette $(IDIR)/*.h
#re rule
re: clean all
#phony defend
.PHONY: all clean fclean re norm
