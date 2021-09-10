# you can set this to 1 to see all commands that are being run
VERBOSE ?= 0

ifeq ($(VERBOSE),1)
export Q :=
export VERBOSE := 1
else
export Q := @
export VERBOSE := 0
endif

# trivial change

# This skeleton is built for CMake's Ninja generator
export CMAKE_GENERATOR=Ninja

OPTIONS ?= -DCMAKE_BUILD_TYPE=Debug -DENABLE_COVERAGE=Yes

all: default



BUILDRESULTS ?= buildresults
CONFIGURED_BUILD_DEP = $(BUILDRESULTS)/build.ninja

$(CONFIGURED_BUILD_DEP):
	$(Q)cmake -B $(BUILDRESULTS) $(OPTIONS) $(INTERNAL_OPTIONS)

.PHONY: default
default: | $(CONFIGURED_BUILD_DEP)
	$(Q)ninja -C $(BUILDRESULTS)


.PHONY: clean
clean:
	$(Q) if [ -d "$(BUILDRESULTS)" ]; then ninja -C $(BUILDRESULTS) clean; fi

.PHONY: pristine
pristine:
	$(Q) rm -rf $(BUILDRESULTS)


CALL_NINJA_TARGETS := cppcheck cppcheck-xml test docs complexity
CALL_NINJA_TARGETS += complexity-xml complexity-full tidy format format-patch
CALL_NINJA_TARGETS += qkl-unittests-xml coverage-xml coverage-html coverage

define CALL_NINJA
.PHONY: $(1)
$(1): | $(CONFIGURED_BUILD_DEP)
	$(Q) ninja -C $(BUILDRESULTS) $(1)
endef

$(foreach call_ninja_tgt, $(CALL_NINJA_TARGETS), $(eval $(call CALL_NINJA, $(call_ninja_tgt) )))
