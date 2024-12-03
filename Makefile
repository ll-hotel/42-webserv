NAME := webserv

CXX := c++
CPPFLAGS := -MMD -MP
CXXFLAGS := -Wall -Wextra -Werror -std=c++98

SRC_DIR := src
SRCS := main.cpp
OBJ_DIR := .build
OBJS := $(patsubst %,$(OBJ_DIR)/%.o,$(SRCS))
DEPS := $(patsubst %.o,%.d,$(OBJS))

.PHONY: all
all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -o $@ $(OBJS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%
	@mkdir -p $(dir $@)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -o $@ -c $<

clean:
	$(RM) -r $(OBJ_DIR)

fclean: clean
	$(RM) $(NAME)

re: fclean
	@$(MAKE) --no-print-directory $(NAME)

-include $(DEPS)
