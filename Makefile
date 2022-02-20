PROJECT			= gnome-phone-companion
TARGET			= $(DIR_BIN)/$(PROJECT)
CC				= g++
DIR_BASE		= src
DIR_SRC			= $(DIR_BASE) $(DIR_BASE)/server $(DIR_BASE)/tools $(DIR_BASE)/widgets $(DIR_BASE)/widgets/tabs $(DIR_BASE)/resources
DIR_BIN 		= bin
DIR_OBJ	 		= $(DIR_BIN)/obj
DIR_RESOURCES	= src/resources
RESOURCES_XML	= $(DIR_RESOURCES)/app.gresource.xml
RESOURCES_C		= $(DIR_RESOURCES)/resources.c
RESOURCES_O		= $(DIR_OBJ)/resources.o
UI_GTK4			= $(DIR_RESOURCES)/$(PROJECT).ui	
DEPFLAGS		= -MP -MD
COMP_RES		= /usr/lib/x86_64-linux-gnu/glib-2.0/glib-compile-resources

FILES_SRC		:= $(shell find $(DIR_BASE)/ -type f -name '*.cpp')
#FILES_TPP		:= $(shell find $(DIR_BASE)/ -type f -name '*.tpp')
#FILES_ALL		:= $(FILES_SRC) $(FILES_TPP)
#FILES_DEP		:= $(foreach h,$(shell find $(DIR_BASE)/ -type f -name '*.h') $(shell find $(DIR_SRC)/ -type f -name '*.tpp'),-include ./$(h))
FILES_OBJ		:= $(addprefix $(DIR_OBJ)/, $(notdir $(patsubst $(DIR_BASE)/%.cpp, %.o, $(FILES_SRC)))) $(RESOURCES_O)

CFLAGS			= `pkg-config --cflags --libs gtkmm-4.0`

all: createdirs $(TARGET)

debug: addg all

$(TARGET): $(FILES_OBJ)
	$(CC) $(CFLAGS) $(FILES_DEP) $^ -o $@

$(RESOURCES_O): $(RESOURCES_C)
	$(CC) -c $(CFLAGS) $< -o $@

$(RESOURCES_C): $(DIR_BASE)/ui/mainWindow.ui
	glib-compile-resources $(RESOURCES_XML) --target=$(RESOURCES_C) --generate-source

$(DIR_OBJ)/%.o: $(DIR_BASE)/%.cpp
	$(CC) -c $(CFLAGS) $< -o $@

$(DIR_OBJ)/%.o: $(DIR_BASE)/server/%.cpp
	$(CC) -c $(CFLAGS) $< -o $@

$(DIR_OBJ)/%.o: $(DIR_BASE)/widgets/%.cpp
	$(CC) -c $(CFLAGS) $< -o $@

$(DIR_OBJ)/%.o: $(DIR_BASE)/widgets/tabs/%.cpp
	$(CC) -c $(CFLAGS) $< -o $@

$(DIR_OBJ)/%.o: $(DIR_BASE)/tools/%.cpp
	$(CC) -c $(CFLAGS) $< -o $@

$(DIR_OBJ)/%.o: $(DIR_BASE)/resources/%.cpp
	$(CC) -c $(CFLAGS) $< -o $@

createdirs:
	@mkdir -p $(DIR_BIN)	
	@mkdir -p $(DIR_OBJ)

clean:
	rm -Rf $(DIR_BIN)

test:
	@echo "==========================================="
	@echo "DIR_SRC:"
	@echo $(DIR_SRC)
	@echo "==========================================="
	@echo "FILES_SRC:"
	@echo $(FILES_SRC)
	@echo "==========================================="
	@echo "FILES_OBJ:"
	@echo $(FILES_OBJ)
	@echo "==========================================="
	@echo "FILES_DEP:"
	@echo $(FILES_DEP)
	@echo "==========================================="

addg:
	$(eval CFLAGS = -g $(CFLAGS))
