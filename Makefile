MAKEFLAGS := --no-print-directory

Q := @

RM := rm -fv
CXX := c++

CPPFLAGS := -MMD -MP
CXXFLAGS := -Wall -Wextra
CXXFLAGS := -Werror
CXXFLAGS += -std=c++98
CXXFLAGS += -Iinclude

MODULES := worker config
OBJ_DIR := .obj
SRC_DIR := src

SRCS :=
SRCS += main.cpp

include $(patsubst %,$(SRC_DIR)/%/.srcs.mk,$(MODULES))

OBJS := $(patsubst %.cpp,$(OBJ_DIR)/%.o,$(SRCS))
DEPS := $(patsubst %.o,%.d,$(OBJS))

NAME := webserv

.PHONY: all
all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -o $@ $(OBJS)

$(OBJ_DIR)/%.o:: $(SRC_DIR)/%.cpp
	$(Q)mkdir -p $(dir $@)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -o $@ -c $<

.PHONY: clean
clean:
	$(Q)$(RM) -r $(OBJ_DIR)

.PHONY: fclean
fclean: clean
	$(Q)$(RM) $(NAME)

.PHONY: re
re: fclean
	$(Q)$(MAKE) $(NAME)

-include $(DEPS)
