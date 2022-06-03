DIR := $(abspath $(dir $(lastword $(MAKEFILE_LIST))))
CFLAGS := -std=c++2a -I$(DIR)
BUILD := $(DIR)/build
BIN := $(BUILD)/memory
DEP := $(BUILD)/dep

SRC := $(shell find $(DIR) -type f -name '*.cpp')
OBJ := $(foreach obj,$(notdir $(SRC:%.cpp=%.o)),$(BUILD)/$(obj))

.PHONY: all
all: $(BUILD) $(DEP) $(BIN)

$(DEP): $(OBJ:%.o=%.d)
	cat $^ > $@

ifneq ($(realpath $(DEP)),)
include $(DEP)
endif

$(OBJ:%.o=%.d): %.d: %.o
	g++ -g $(CFLAGS) -MM -MF $@ -c $(DIR)/$(patsubst %.d,%.cpp,$(notdir $@)) $(LDFLAGS)
	sed -i -r 's?^$(notdir $(@:%.d=%.o)):?$(@:%.d=%.o):?' $@

$(BIN): $(OBJ)
	g++ -g -Wall $(CFLAGS) -o $@ $^ $(LDFLAGS)

$(OBJ): $(BUILD)/%.o: $(DIR)/%.cpp
	g++ -g $(CFLAGS) -o $@ -c $<

$(BUILD):
	mkdir -p $@

.PHONY: clean
clean:
	@rm -rf $(BUILD)
