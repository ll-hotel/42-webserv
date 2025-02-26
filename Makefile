MAKEFLAGS := --no-print-directory

Q := @

RM := rm -fv
CXX := c++

MODULES :=
MODULES += config
MODULES += http_response
MODULES += httpRequest
MODULES += socket
MODULES += webserv
MODULES += logger

OBJ_DIR := .obj
SRC_DIR := src
INC_DIR := include

CPPFLAGS := -MMD -MP
CXXFLAGS := -Wall -Wextra -Werror
CXXFLAGS += -Wpedantic
CXXFLAGS += -std=c++98
CXXFLAGS += -I$(INC_DIR)

SRCS :=
SRCS += main.cpp

include $(patsubst %,$(SRC_DIR)/%/.srcs.mk,$(MODULES))

OBJS := $(patsubst %.cpp,$(OBJ_DIR)/%.o,$(SRCS))
DEPS := $(patsubst %.o,%.d,$(OBJS))

NAME := webserv

.PHONY: all
all: $(NAME)

.PHONY: fsan
fsan: CXXFLAGS += -fsanitize=leak,address
fsan: all

.PHONY: format
format:
	find . -regex '.*\.[ch]pp' -exec clang-format -i '{}' \;

$(NAME): $(OBJS)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -o $@ $(OBJS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
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
