#*********************************************************************
#**     Make file to build an example program using g++ complier    **
#*********************************************************************


#--------------------------------------------------------------------#
# 1 Prepare the environment for making the executable
#
#    1.1 Set directory information
#---------------------------------------------------------------------#
QHULLDISK_INCDIR = ../implementation/header
QHULLDISK_SRCDIR = ../implementation/cpp
QHULLDISK_OBJDIR = object
#---------------------------------------------------------------------#
#    1.2 Set compiler flags
#---------------------------------------------------------------------#
CXX = g++
CXXFLAGS = -c -Wall -Wextra -pedantic -std=c++14 -O3  
INCLUDE_DIR = -I$(QHULLDISK_INCDIR)

#---------------------------------------------------------------------#
#    1.3 Set source files
#---------------------------------------------------------------------#
APP_SRC = TestDriverForQuickhullDisk.cpp
QHULLDISK_SRCS = \
                 Circle2D.cpp \
                 CircularArc2D.cpp \
                 CircularDisk2D.cpp \
                 ConvexHullOfDisks.cpp \
                 FileIOForConvexHullOfDisks.cpp \
                 GeometricFunction2D.cpp \
                 Line2D.cpp \
                 Point2D.cpp \
                 QuickhullDisk.cpp \
                 RelativeOperator.cpp \
                 TimeStatistics.cpp 
SRCS = $(APP_SRC) $(QHULLDISK_SRCS)
QHULLDISK_SRCS_FULLPATH = $(addprefix $(QHULLDISK_SRCDIR)/, $(QHULLDISK_SRCS))
#---------------------------------------------------------------------#
#    1.4 Set object files
#---------------------------------------------------------------------#
OBJS = $(SRCS:.cpp=.o)
OBJS_FULL_PATH = $(addprefix $(QHULLDISK_OBJDIR)/, $(OBJS))

#---------------------------------------------------------------------#
#    1.5 Define dependency
#---------------------------------------------------------------------#
DEPENDENCY = TestDriverForQuickhullDisk.dep.mk

#---------------------------------------------------------------------#
# 2 Make the excutable !!!
#---------------------------------------------------------------------#
TARGET = RunQuickhullDisk

VPATH = $(QHULLDISK_SRCDIR)


$(QHULLDISK_OBJDIR)/%.o: %.cpp | $(QHULLDISK_OBJDIR)
	$(CXX) $(CXXFLAGS) -c $(INCLUDE_DIR) $< -o $@ 


all: $(TARGET)


$(TARGET): $(OBJS_FULL_PATH)
	$(CXX) -o $@ $(OBJS_FULL_PATH)


$(QHULLDISK_OBJDIR):
	mkdir -p $@

.PHONY: clean
clean:
	rm -f $(TARGET)
	rm -f $(OBJS_FULL_PATH)

.PHONY: dep	
dep:
	g++ -MM $(INCLUDE_DIR) $(QHULLDISK_SRCS_FULLPATH) $(APP_SRC) > $(DEPENDENCY)


ifeq "$(DEPENDENCY)" "$(findstring $(DEPENDENCY),$(wildcard *.mk))"
-include $(DEPENDENCY)
else
 $(warning "[ Can't find dependency file: $(DEPENDENCY). Please "make dep" ]")
endif

