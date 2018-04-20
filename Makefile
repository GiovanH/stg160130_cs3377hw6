#Seth Giovanetti
#stg160130

#=========Variable block=========
PROJECTNAME = hw6
TAREXCLUDE = --exclude scratch --exclude .git

#Variables
EXE = hw6
SRCS = draw.cc binio.cc main.cc

#C implicit rules
CXX = g++
CXXFLAGS = -Wall
CPPFLAGS = -I/scratch/perkins/include -Wall

#Linker Flags
LDFLAGS = -L/scratch/perkins/lib
LDLIBS = -lcdk -lncurses

#Nonphony:
#The executable requires all its object files
$(EXE): $(SRCS:.cc=.o)
	$(CXX) -o $(EXE) $(SRCS:.cc=.o) $(LDFLAGS) $(LDLIBS)  

#=========Phony block=========
#The main target is the executable
.PHONY: all
all: $(EXE)

#Clean
.PHONY: clean
clean:
	rm -f $(SRCS:.cc=.o) \
	*.d *~ *#\
	log.log

#More phony meta stuff
.PHONY: do
do: all
	@echo I have standards.
	-./$(EXE) 

.PHONY: deliverables
deliverables: all
#	./$(EXE) > output.txt
	make backup

#Backup target
.PHONY: backup
backup:	clean
	@mkdir -p ~/backups; chmod 700 ~/backups
	@$(eval CURDIRNAME := $(shell basename `pwd`))
	@$(eval MKBKUPNAME := ~/backups/$(PROJECTNAME)-$(shell date +'%Y-%m-%d_%H.%M.%S').tar.gz)
	-tar zcf $(MKBKUPNAME) ../$(CURDIRNAME) $(TAREXCLUDE) >/dev/null 2>/dev/null
	tar -tf $(MKBKUPNAME)

#Non-phony methods

#Makefile: Generate .d files
#Makefile: $(SRCS:.cc=.d) $(CSRCS:.c=.d)

#Pattern for .d files. Magically adds files to the left hand side.
#%.d:%.cc
#	@echo Updating .d Dependency File for $<
#	@set -e; rm -f $@; \
#	$(CXX) -MM $(CPPFLAGS) $< > $@.$$$$; \
#	sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
	rm -f $@.$$$$
#Pattern for .d files. Magically adds files to the left hand side.
#%.d:%.c
#	@echo Updating .d Dependency File for $<
#	@set -e; rm -f $@; \
#	$(CXX) -MM $(CPPFLAGS) $< > $@.$$$$; \
#	sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
	rm -f $@.$$$$


#========Notes on make syntax=========
# <target>: [dependency]*
# (\t	<command>)*

#Override implicit rule for .o
#%.o:%.cc
#	$(CXX) -c $(CXXFLAGS) $(CPPFLAGS) -O $< -o $@

#Override implicit rule for .c files to force G++
#%.o:%.c
#	$(CXX) -c $(CXXFLAGS) $(CPPFLAGS) -O $< -o $@


# Include the dependency files
#-include $(SRCS:.cc=.d) 
#-include $(CSRCS:.c=.d)
