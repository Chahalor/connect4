DIR_MODULE_AI		:= AI
DIR_INTERFACE_AI	:= $(DIR_MODULE_AI)
DIR_INTERNAL_AI	:= $(DIR_MODULE_AI)/_internal

SRC_INTERFACE_AI	:= AI.c 
SRC_INTERNAL_AI	:= _ai.c 

OBJ_AI			:= $(addprefix $(DIR_OBJ)/$(DIR_INTERFACE_AI)/, $(SRC_INTERFACE_AI:.c=.o))
OBJ_AI			+= $(addprefix $(DIR_OBJ)/$(DIR_INTERNAL_AI)/, $(SRC_INTERNAL_AI:.c=.o))

$(DIR_OBJ)/$(DIR_MODULE_AI)/%.o: $(DIR_SRC)/$(DIR_MODULE_AI)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(DEBUGFLAGS) $(INCLUDE_ALL) -I$(DIR_SRC)/$(DIR_MODULE_AI)/_internal -c $< -o $@
