NAME = allobobotests
SRCS_DIR = src/
INCLUDE = include/
HEADERS = $(INCLUDE)*
GOOGLE_TEST_INCLUDE = /Users/domitilleprevost/googletest/googletest/include/
GOOGLE_MOCK_INCLUDE = /Users/domitilleprevost/googletest/googlemock/include/

GOOGLE_TEST_LIB = gtest
GOOGLE_TEST_MOCK = gmock

LD_FLAGS = -L/usr/local/lib -l$(GOOGLE_TEST_LIB) -l$(GOOGLE_TEST_MOCK) -lpthread

CXX = g++
CFLAGS = -std=c++14 -I$(GOOGLE_TEST_INCLUDE) -I$(GOOGLE_MOCK_INCLUDE)


SRCS =	$(SRCS_DIR)Algorithm.cpp			\
		$(SRCS_DIR)Appointment.cpp		    \
		$(SRCS_DIR)Genetic.cpp				\
		$(SRCS_DIR)Inputs.cpp			    \
		$(SRCS_DIR)Nurse.cpp				\
		$(SRCS_DIR)Patient.cpp			    \
		$(SRCS_DIR)Point.cpp				\
		$(SRCS_DIR)Solution.cpp				\
		$(SRCS_DIR)Time.cpp					\
		$(SRCS_DIR)TimeInterval.cpp			\
		$(SRCS_DIR)Treatment.cpp			\
		$(SRCS_DIR)TreatmentType.cpp		\
		$(SRCS_DIR)Utils.cpp				\
		$(SRCS_DIR)WebServer.cpp			\
		$(SRCS_DIR)GluttonBreadth.cpp       \
		$(SRCS_DIR)GluttonDepth.cpp         \

SRCS_TEST  = 	unitTests/main_test.cpp           	\
    			unitTests/test_solution.cpp			\
#    			unitTests/test_genetic.cpp			\
#    			unitTests/test_inputs.cpp			\

OBJS = $(SRCS:.cpp=.o)
OBJS_TEST = $(SRCS_TEST:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJS) $(HEADERS)
	@printf "make all \n"
	$(CXX) $(OBJS) main.cpp -o $(NAME)

test: $(OBJS) $(OBJS_TEST) $(HEADERS)
	@printf "make test \n"
	$(CXX) $(OBJS) $(OBJS_TEST) -o test $(LD_FLAGS)

%.o: %.cpp
	$(CXX) $(CFLAGS) -c $< -o $@

clean:
	@rm -f $(OBJS) $(OBJS_TEST) main.o
	@printf "cleaning \n"

fclean: clean
	@rm -f $(NAME)
	@printf "clean all \n"

re: fclean all

