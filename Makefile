NAME = allobobotests
SRCS_DIR = src/
INCLUDE = include/

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


CXX = g++
CFLAGS = -Wall
HEADERS = $(INCLUDE)*
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS) $(HEADERS)
	$(CXX) $(CFLAGS) -I$(INCLUDES) $(OBJS) -o $(NAME)
	@printf "make all"

# %.o: %.c
# 	@g++ $(CFLAGS) -I $(INCLUDES) -c $< -o $@

clean:
	@rm -f $(OBJS)
	@printf "cleaning"

fclean: clean
	@rm -f $(NAME)
	@printf "clean all"

re: fclean all