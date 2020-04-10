#Compiler and Linker
CC          := g++

#The Target Binary Program
TARGET      := main

#The Directories, Source, Includes, Objects, Binary and Resources
SRCDIR      := src
INCDIR      := inc
BUILDDIR    := obj
TARGETDIR   := .
TTARGETDIR  := testbin
RESDIR      := res
SRCEXT      := cpp
DEPEXT      := d
OBJEXT      := o

#Flags, Libraries and Includes
CFLAGS      := -Wall -O3 -g
LIB         := 
INC         := -I$(INCDIR) -I/usr/local/include
INCDEP      := -I$(INCDIR)

#---------------------------------------------------------------------------------
#DO NOT EDIT BELOW THIS LINE
#---------------------------------------------------------------------------------
SOURCES     := $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
OBJECTS     := $(filter-out $(BUILDDIR)/test%.o $(BUILDDIR)/main.o,$(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.$(OBJEXT))))

#default make
all: $(TARGET)

#linking
main: $(BUILDDIR)/main.o $(OBJECTS)
	$(CC) -o $(TARGETDIR)/main $(BUILDDIR)/main.o $(OBJECTS)

test1: $(BUILDDIR)/test/test1.o $(BUILDDIR)/Matrix_base.o $(BUILDDIR)/Matrix_functions.o $(BUILDDIR)/Matrix_basicoperations.o
	@mkdir -p $(TTARGETDIR)
	$(CC) -o $(TTARGETDIR)/$@ $^

test2: $(BUILDDIR)/test/test2.o $(BUILDDIR)/Matrix_base.o $(BUILDDIR)/Matrix_functions.o $(BUILDDIR)/Matrix_basicoperations.o $(BUILDDIR)/EquationSystem.o
	@mkdir -p $(TTARGETDIR)
	$(CC) -o $(TTARGETDIR)/$@ $^

test3: $(BUILDDIR)/test/test3.o $(BUILDDIR)/Matrix_base.o $(BUILDDIR)/Matrix_functions.o $(BUILDDIR)/Matrix_basicoperations.o $(BUILDDIR)/EquationSystem.o
	@mkdir -p $(TTARGETDIR)
	$(CC) -o $(TTARGETDIR)/$@ $^

test4: $(BUILDDIR)/test/test4.o $(BUILDDIR)/Matrix_base.o $(BUILDDIR)/Matrix_functions.o $(BUILDDIR)/Matrix_basicoperations.o $(BUILDDIR)/EquationSystem.o
	@mkdir -p $(TTARGETDIR)
	$(CC) -o $(TTARGETDIR)/$@ $^

test5: $(BUILDDIR)/test/test5.o $(BUILDDIR)/Matrix_base.o $(BUILDDIR)/Matrix_functions.o $(BUILDDIR)/Matrix_basicoperations.o
	@mkdir -p $(TTARGETDIR)
	$(CC) -o $(TTARGETDIR)/$@ $^

test6: $(BUILDDIR)/test/test6.o $(BUILDDIR)/NumInt.o
	@mkdir -p $(TTARGETDIR)
	$(CC) -o $(TTARGETDIR)/$@ $^


.PHONY: all clean
clean:
	rm -rf obj/
	rm test*
	rm main

#compiling
$(BUILDDIR)/%.$(OBJEXT): $(SRCDIR)/%.$(SRCEXT)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

$(BUILDDIR)/test/%.$(OBJEXT): $(SRCDIR)/test/%.$(SRCEXT)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<