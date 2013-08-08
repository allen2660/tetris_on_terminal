#COMAKE2 edit-mode: -*- Makefile -*-
####################64Bit Mode####################
ifeq ($(shell uname -m),x86_64)
CC=gcc
CXX=g++
CXXFLAGS=-g \
  -pipe \
  -W \
  -Wall \
  -fPIC
CFLAGS=-g \
  -pipe \
  -W \
  -Wall \
  -fPIC
CPPFLAGS=-D_GNU_SOURCE \
  -D__STDC_LIMIT_MACROS \
  -DVERSION=\"1.9.8.7\"
INCPATH=-I. \
  -I./include \
  -I./output \
  -I./output/include
DEP_INCPATH=-I../../../lib2-64/ullib \
  -I../../../lib2-64/ullib/include \
  -I../../../lib2-64/ullib/output \
  -I../../../lib2-64/ullib/output/include

#============ CCP vars ============
CCHECK=@ccheck.py
CCHECK_FLAGS=
PCLINT=@pclint
PCLINT_FLAGS=
CCP=@ccp.py
CCP_FLAGS=


#COMAKE UUID
COMAKE_MD5=87bfb56563cb4f2f9a72ec1e6a0de8de  COMAKE


.PHONY:all
all:comake2_makefile_check tetris test_kbutil test_KBListener 
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mall[0m']"
	@echo "make all done"

.PHONY:comake2_makefile_check
comake2_makefile_check:
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mcomake2_makefile_check[0m']"
	#in case of error, update 'Makefile' by 'comake2'
	@echo "$(COMAKE_MD5)">comake2.md5
	@md5sum -c --status comake2.md5
	@rm -f comake2.md5

.PHONY:ccpclean
ccpclean:
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mccpclean[0m']"
	@echo "make ccpclean done"

.PHONY:clean
clean:ccpclean
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mclean[0m']"
	rm -rf tetris
	rm -rf ./output/bin/tetris
	rm -rf test_kbutil
	rm -rf ./output/bin/test_kbutil
	rm -rf test_KBListener
	rm -rf ./output/bin/test_KBListener
	rm -rf tetris_main.o
	rm -rf tetris_Shape.o
	rm -rf tetris_Container.o
	rm -rf tetris_kb_util.o
	rm -rf test_kbutil_kb_util.o
	rm -rf test_kbutil_test_kb_util.o
	rm -rf test_KBListener_kb_util.o
	rm -rf test_KBListener_test_KBListener.o

.PHONY:dist
dist:
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mdist[0m']"
	tar czvf output.tar.gz output
	@echo "make dist done"

.PHONY:distclean
distclean:clean
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mdistclean[0m']"
	rm -f output.tar.gz
	@echo "make distclean done"

.PHONY:love
love:
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mlove[0m']"
	@echo "make love done"

tetris:tetris_main.o \
  tetris_Shape.o \
  tetris_Container.o \
  tetris_kb_util.o
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mtetris[0m']"
	$(CXX) tetris_main.o \
  tetris_Shape.o \
  tetris_Container.o \
  tetris_kb_util.o -Xlinker "-("  ../../../lib2-64/ullib/lib/libullib.a -lpthread \
  -lcrypto \
  -lrt -Xlinker "-)" -o tetris
	mkdir -p ./output/bin
	cp -f --link tetris ./output/bin

test_kbutil:test_kbutil_kb_util.o \
  test_kbutil_test_kb_util.o
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mtest_kbutil[0m']"
	$(CXX) test_kbutil_kb_util.o \
  test_kbutil_test_kb_util.o -Xlinker "-("  ../../../lib2-64/ullib/lib/libullib.a -lpthread \
  -lcrypto \
  -lrt -Xlinker "-)" -o test_kbutil
	mkdir -p ./output/bin
	cp -f --link test_kbutil ./output/bin

test_KBListener:test_KBListener_kb_util.o \
  test_KBListener_test_KBListener.o
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mtest_KBListener[0m']"
	$(CXX) test_KBListener_kb_util.o \
  test_KBListener_test_KBListener.o -Xlinker "-("  ../../../lib2-64/ullib/lib/libullib.a -lpthread \
  -lcrypto \
  -lrt -Xlinker "-)" -o test_KBListener
	mkdir -p ./output/bin
	cp -f --link test_KBListener ./output/bin

tetris_main.o:main.cpp \
  Container.h \
  Point.h \
  Shape.h \
  ShapeFactory.h \
  KBListener.h \
  kb_util.h
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mtetris_main.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o tetris_main.o main.cpp

tetris_Shape.o:Shape.cpp \
  Shape.h \
  Point.h
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mtetris_Shape.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o tetris_Shape.o Shape.cpp

tetris_Container.o:Container.cpp \
  Container.h \
  Point.h \
  Shape.h
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mtetris_Container.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o tetris_Container.o Container.cpp

tetris_kb_util.o:kb_util.cpp \
  kb_util.h
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mtetris_kb_util.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o tetris_kb_util.o kb_util.cpp

test_kbutil_kb_util.o:kb_util.cpp \
  kb_util.h
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mtest_kbutil_kb_util.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o test_kbutil_kb_util.o kb_util.cpp

test_kbutil_test_kb_util.o:test_kb_util.cpp \
  kb_util.h
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mtest_kbutil_test_kb_util.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o test_kbutil_test_kb_util.o test_kb_util.cpp

test_KBListener_kb_util.o:kb_util.cpp \
  kb_util.h
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mtest_KBListener_kb_util.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o test_KBListener_kb_util.o kb_util.cpp

test_KBListener_test_KBListener.o:test_KBListener.cpp \
  KBListener.h \
  kb_util.h
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mtest_KBListener_test_KBListener.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o test_KBListener_test_KBListener.o test_KBListener.cpp

endif #ifeq ($(shell uname -m),x86_64)


