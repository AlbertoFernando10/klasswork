CXXFLAGS += -Wall -Wextra -Weffc++ -std=c++14 -MMD

UNIT_TESTS = pe-vector-tests
OBJS = main.o
DEPS = $(OBJS:%.o=%.d)

$(UNIT_TESTS): $(OBJS)
        $(CXX) -o $@ $^

clean:
        -@$(RM) $(UNIT_TESTS)
        -$(DEPS)
        @$(RM) $(OBJS)

-include main.d