# Locate the path to the Unity executable for building the package
ifeq ($(OS),Windows_NT)
	UNITY := C:/Program Files\Unity\Editor\Unity.exe
else
	ifeq ($(shell uname),Darwin)
		UNITY := /Applications/Unity/Unity.app/Contents/MacOS/Unity
	endif
endif
# Set default build arguments
UNITY += -nographics -batchmode -quit -force-free -logFile build/unity.log
SCAFFOLD=build/package
SCAFFOLD_SETTINGS=$(SCAFFOLD)/ProjectSettings/ProjectSettings.asset
LIBDIR=$(SCAFFOLD)/Assets/
SRC=src/checker.c src/checker.h src/Checkers.cs
LIBS=$(subst src,$(LIBDIR),$(SRC))

all: build/Checkers.unitypackage ## Build the package (default)

.PHONY: all clean help test

# Assemble a package which can be added to a Unity project. Requires a pro
# license to run on CI or without a TTY
# 	projectPath   = the path of the project which will be exported
# 	exportPackage = export the project in projectPath given a relative path to
#   	            the asset directory
build/Checkers.unitypackage: $(LIBS) $(SCAFFOLD_SETTINGS)
	$(UNITY) -projectPath=$(SCAFFOLD) -exportPackage Assets $@

build/test_runner: src/checker.c src/checker_test.c
	@mkdir -p build
	$(CC) -I deps $^ -o $@

# The scafford is the Unity project structure of the plugin
$(SCAFFOLD_SETTINGS):
	@mkdir -p build
	$(UNITY) -createProject $(SCAFFOLD)

# Copy the native plugin source into plugin directories
$(LIBDIR)/%: src/%
	@mkdir -p $(@D)
	install $< $(@D)

clean: ## Clean the build directory
	@rm -rf build

test: build/test_runner ## Run tests
	@./$<

help: ## Show help text
	@grep -E '^[a-zA-Z_-]+:.*?## .*$$' $(MAKEFILE_LIST) | sort | awk 'BEGIN {FS = ":.*?## "}; {printf "\033[36m%-30s\033[0m %s\n", $$1, $$2}'
