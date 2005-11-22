#############################################################################
# Makefile for building: ktigcc
# Generated by qmake (1.07a) (Qt 3.3.4) on: Tue Nov 22 07:02:46 2005
# Project:  ktigcc.pro
# Template: app
# Command: $(QMAKE) -o Makefile ktigcc.pro
#############################################################################

####### Compiler, tools and options

CC       = gcc
CXX      = g++
LEX      = flex
YACC     = yacc
CFLAGS   = -pipe -Wall -W -g  -DQT_SHARED -DQT_NO_DEBUG -DQT_THREAD_SUPPORT
CXXFLAGS = -pipe -Wall -W -Os -g -Wno-non-virtual-dtor  -DQT_SHARED -DQT_NO_DEBUG -DQT_THREAD_SUPPORT
LEXFLAGS = 
YACCFLAGS= -d
INCPATH  = -I/usr/lib/qt-3.3/mkspecs/default -I. -I/usr/include/kde -I$(QTDIR)/include -I.ui/ -I. -I.moc/
LINK     = g++
LFLAGS   = 
LIBS     = $(SUBLIBS) -L$(QTDIR)/lib -L/usr/X11R6/lib -lktexteditor -lqassistantclient -L/usr/src/build/613981-i386/BUILD/qt-x11-free-3.3.4/lib -lmng -ljpeg -lpng -lz -lSM -lICE -ldl -lpthread -lqt-mt -lXext -lX11 -lm
AR       = ar cqs
RANLIB   = 
MOC      = $(QTDIR)/bin/moc
UIC      = $(QTDIR)/bin/uic
QMAKE    = qmake
TAR      = tar -cf
GZIP     = gzip -9f
COPY     = cp -f
COPY_FILE= $(COPY)
COPY_DIR = $(COPY) -r
INSTALL_FILE= $(COPY_FILE)
INSTALL_DIR = $(COPY_DIR)
DEL_FILE = rm -f
SYMLINK  = ln -sf
DEL_DIR  = rmdir
MOVE     = mv -f
CHK_DIR_EXISTS= test -d
MKDIR    = mkdir -p

####### Output directory

OBJECTS_DIR = .obj/

####### Files

HEADERS = 
SOURCES = ktigcc.cpp
OBJECTS = .obj/ktigcc.o \
		.obj/mainform.o \
		.obj/qmake_image_collection.o
FORMS = mainform.ui
UICDECLS = .ui/mainform.h
UICIMPLS = .ui/mainform.cpp
SRCMOC   = .moc/moc_mainform.cpp
OBJMOC = .obj/moc_mainform.o
DIST	   = ktigcc.pro
QMAKE_TARGET = ktigcc
DESTDIR  = 
TARGET   = ktigcc

first: all
####### Implicit rules

.SUFFIXES: .c .o .cpp .cc .cxx .C

.cpp.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $@ $<

.cc.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $@ $<

.cxx.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $@ $<

.C.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $@ $<

.c.o:
	$(CC) -c $(CFLAGS) $(INCPATH) -o $@ $<

####### Build rules

all: Makefile $(TARGET)

$(TARGET):  $(UICDECLS) $(OBJECTS) $(OBJMOC)  
	$(LINK) $(LFLAGS) -o $(TARGET) $(OBJECTS) $(OBJMOC) $(OBJCOMP) $(LIBS)

mocables: $(SRCMOC)
uicables: $(UICDECLS) $(UICIMPLS)

$(MOC): 
	( cd $(QTDIR)/src/moc && $(MAKE) )

Makefile: ktigcc.pro  /usr/lib/qt-3.3/mkspecs/default/qmake.conf /usr/lib/qt-3.3/lib/libqassistantclient.prl \
		/usr/lib/qt-3.3/lib/libqt-mt.prl
	$(QMAKE) -o Makefile ktigcc.pro
qmake: 
	@$(QMAKE) -o Makefile ktigcc.pro

dist: 
	@mkdir -p .obj/ktigcc && $(COPY_FILE) --parents $(SOURCES) $(HEADERS) $(FORMS) $(DIST) .obj/ktigcc/ && $(COPY_FILE) --parents images/00 images/01 images/02 images/03 images/04 images/05 images/06 images/07 images/08 images/09 images/10 images/11 images/12 images/13 images/14 images/15 images/16 images/17 images/18 images/19 images/20 images/21 images/22 images/23 images/24 images/25 images/26 images/27 images/tpr.png images/folder1.png images/folder2.png images/filec.png images/fileh.png images/fileo.png images/files.png images/filet.png images/filex.png .obj/ktigcc/ && $(COPY_FILE) --parents mainform.ui.h .obj/ktigcc/ && ( cd `dirname .obj/ktigcc` && $(TAR) ktigcc.tar ktigcc && $(GZIP) ktigcc.tar ) && $(MOVE) `dirname .obj/ktigcc`/ktigcc.tar.gz . && $(DEL_FILE) -r .obj/ktigcc

mocclean:
	-$(DEL_FILE) $(OBJMOC)
	-$(DEL_FILE) $(SRCMOC)

uiclean:
	-$(DEL_FILE) $(UICIMPLS) $(UICDECLS)

yaccclean:
lexclean:
clean: mocclean uiclean
	-$(DEL_FILE) $(OBJECTS)
		-$(DEL_FILE) .ui/qmake_image_collection.cpp
	-$(DEL_FILE) *~ core *.core


####### Sub-libraries

distclean: clean
	-$(DEL_FILE) $(TARGET) $(TARGET)


FORCE:

####### Compile

.obj/ktigcc.o: ktigcc.cpp .ui/mainform.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o .obj/ktigcc.o ktigcc.cpp

.ui/mainform.h: mainform.ui 
	$(UIC) mainform.ui -o .ui/mainform.h

.ui/mainform.cpp: .ui/mainform.h mainform.ui mainform.ui.h 
	$(UIC) mainform.ui -i mainform.h -o .ui/mainform.cpp

.obj/mainform.o: .ui/mainform.cpp mainform.ui.h \
		.ui/mainform.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o .obj/mainform.o .ui/mainform.cpp

.obj/moc_mainform.o: .moc/moc_mainform.cpp  .ui/mainform.h 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o .obj/moc_mainform.o .moc/moc_mainform.cpp

.moc/moc_mainform.cpp: $(MOC) .ui/mainform.h
	$(MOC) .ui/mainform.h -o .moc/moc_mainform.cpp

.obj/qmake_image_collection.o: .ui/qmake_image_collection.cpp
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o .obj/qmake_image_collection.o .ui/qmake_image_collection.cpp

.ui/qmake_image_collection.cpp: images/00 \
		images/01 \
		images/02 \
		images/03 \
		images/04 \
		images/05 \
		images/06 \
		images/07 \
		images/08 \
		images/09 \
		images/10 \
		images/11 \
		images/12 \
		images/13 \
		images/14 \
		images/15 \
		images/16 \
		images/17 \
		images/18 \
		images/19 \
		images/20 \
		images/21 \
		images/22 \
		images/23 \
		images/24 \
		images/25 \
		images/26 \
		images/27 \
		images/tpr.png \
		images/folder1.png \
		images/folder2.png \
		images/filec.png \
		images/fileh.png \
		images/fileo.png \
		images/files.png \
		images/filet.png \
		images/filex.png
	$(UIC)  -embed ktigcc images/00 images/01 images/02 images/03 images/04 images/05 images/06 images/07 images/08 images/09 images/10 images/11 images/12 images/13 images/14 images/15 images/16 images/17 images/18 images/19 images/20 images/21 images/22 images/23 images/24 images/25 images/26 images/27 images/tpr.png images/folder1.png images/folder2.png images/filec.png images/fileh.png images/fileo.png images/files.png images/filet.png images/filex.png -o .ui/qmake_image_collection.cpp

####### Install

install_syntaxfiles: all 
	@$(CHK_DIR_EXISTS) "$(INSTALL_ROOT)/usr/share/apps/katepart/syntax/" || $(MKDIR) "$(INSTALL_ROOT)/usr/share/apps/katepart/syntax/"
	-$(INSTALL_FILE) "gnuasm68k.xml" "$(INSTALL_ROOT)/usr/share/apps/katepart/syntax/"
	-$(INSTALL_FILE) "masm68k.xml" "$(INSTALL_ROOT)/usr/share/apps/katepart/syntax/"


uninstall_syntaxfiles: 
	-$(DEL_FILE) -r "$(INSTALL_ROOT)/usr/share/apps/katepart/syntax/gnuasm68k.xml"
	-$(DEL_FILE) -r "$(INSTALL_ROOT)/usr/share/apps/katepart/syntax/masm68k.xml"
	-$(DEL_DIR) "$(INSTALL_ROOT)/usr/share/apps/katepart/syntax/"


install_executable: all 
	@$(CHK_DIR_EXISTS) "$(INSTALL_ROOT)/usr/local/tigcc/bin/" || $(MKDIR) "$(INSTALL_ROOT)/usr/local/tigcc/bin/"
	-$(INSTALL_FILE) "ktigcc" "$(INSTALL_ROOT)/usr/local/tigcc/bin/"


uninstall_executable: 
	-$(DEL_FILE) -r "$(INSTALL_ROOT)/usr/local/tigcc/bin/ktigcc"
	-$(DEL_DIR) "$(INSTALL_ROOT)/usr/local/tigcc/bin/"


install: install_syntaxfiles install_executable  

uninstall: uninstall_syntaxfiles uninstall_executable  

