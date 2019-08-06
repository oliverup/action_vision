PROJECT_NAME            = Monochrom_am_Ofen

PROJECT_DIR             = ../..
VIMBASDK_DIR			= $(PROJECT_DIR)/../Vimba_2_1
MAKE_INCLUDE_DIR        = $(CURDIR)/$(VIMBASDK_DIR)/VimbaCPP/Examples/Build/Make

include $(MAKE_INCLUDE_DIR)/Common.mk

CONFIG_DIR          = $(ARCH)_$(WORDSIZE)bit
BIN_FILE            = $(PROJECT_NAME)
BIN_DIR             = binary/$(CONFIG_DIR)
OBJ_DIR             = object/$(CONFIG_DIR)
BIN_PATH            = $(BIN_DIR)/$(BIN_FILE)

all: $(BIN_PATH)

include $(MAKE_INCLUDE_DIR)/VimbaCPP.mk

SOURCE_DIR          = $(PROJECT_DIR)/Source
INCLUDE_DIRS        = -I$(SOURCE_DIR) \
                      -I$(VIMBASDK_DIR)/VimbaCPP/Include \

LIBS                = $(VIMBACPP_LIBS)

DEFINES             =

CFLAGS              = $(COMMON_CFLAGS) \
                      $(VIMBACPP_CFLAGS)

OBJ_FILES           = $(OBJ_DIR)/find_ROI.o \
                      $(OBJ_DIR)/main.o 

DEPENDENCIES        = VimbaCPP

$(OBJ_DIR)/%.o: $(SOURCE_DIR)/%.cpp $(OBJ_DIR)
	$(CXX) -c $(INCLUDE_DIRS) $(DEFINES) $(CFLAGS) -o $@ $< -std=c++11

$(BIN_PATH): $(DEPENDENCIES) $(OBJ_FILES) $(BIN_DIR)
	$(CXX) $(ARCH_CFLAGS) -o $(BIN_PATH) $(OBJ_FILES) $(LIBS) -lyaml-cpp -lopencv_imgcodecs -lopencv_imgproc -lopencv_core -lopencv_highgui -Wl,-rpath,'$$ORIGIN'

clean:
	$(RM) binary -r -f
	$(RM) object -r -f

$(OBJ_DIR):
	$(MKDIR) -p $(OBJ_DIR)

$(BIN_DIR):
	$(MKDIR) -p $(BIN_DIR)
