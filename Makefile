# you can set this to 1 to see all commands that are being run
VERBOSE ?= 0

ifeq ($(VERBOSE),1)
export Q :=
export VERBOSE := 1
else
export Q := @
export VERBOSE := 0
endif

# This skeleton is built for CMake's Ninja generator
export CMAKE_GENERATOR=Ninja

OPTIONS := -DCMAKE_BUILD_TYPE=Debug

all: default



BUILDRESULTS ?= buildresults
CONFIGURED_BUILD_DEP = $(BUILDRESULTS)/build.ninja

CONFIGURED_BUILD_DEP:
	$(Q)cmake -B $(BUILDRESULTS) $(OPTIONS) $(INTERNAL_OPTIONS)

.PHONY: default
default: | CONFIGURED_BUILD_DEP
	$(Q)ninja -C $(BUILDRESULTS)


.PHONY: clean
clean:
	$(Q) if [ -d "$(BUILDRESULTS)" ]; then ninja -C $(BUILDRESULTS) clean; fi

.PHONY: distclean
distclean:
	$(Q) rm -rf $(BUILDRESULTS)