CC=g++ -std=c++17 -ggdb3
GCOV=-fprofile-arcs -ftest-coverage
OS=$(shell uname)
TEXI2DVI=makeinfo --html
ifeq ($(OS), Linux)
  LIBS=-lgtest -lstdc++  -lpthread -lrt -lm
  OPEN=xdg-open
else
  LIBS=-lgtest -lstdc++ 
  OPEN=open
endif

all: clean clean_report dist gcov_report install dvi 

install: clean build
	@if [ -d ../install ]; then \
	rm -rf ../install/*; \
	else \
	mkdir ../install; \
	fi
	@-cp -R build/save build/script build/x_data build/3d build/settings.cfg ../install

uninstall:
	@rm -rf ../install

build:
	@-mkdir ./build
	@-cp -R model view controller x_data main.cpp *.pro settings.cfg save ./build
	@-cp -Ra view/script ./build
	#@-cp model/*.cpp model/*.h view/*.cpp view/*.h controller/*.cpp controller/*.h *.pro *.ui view/*.qrc ./build
	@-cd ./build; qmake 3d.pro
	@-make -C build
	@-cd build; rm -rf model view controller *.pro *.o *.cpp *.h *.ui Makefile

tests_build: clean model/model_test.cpp model/model_matrix.cpp model/model_parser.cpp model/model_observer.cpp
	$(CC)  model/model_test.cpp model/model_matrix.cpp model/model_parser.cpp $(LIBS)  -o test

tests: tests_build
	./test

test: tests

gcov_report: clean_report model/model_test.cpp model/model_matrix.cpp model/model_parser.cpp
	$(CC) --coverage model/model_test.cpp model/model_matrix.cpp model/model_parser.cpp  $(LIBS) -o gcov_report
	./gcov_report
	lcov --no-external -t "gcov_report" -o gcov_report.info -c -d .
	-genhtml -o report gcov_report.info
	$(OPEN) ./report/index.html

dvi:
	@$(TEXI2DVI) 3d.texi

dist: clean
	@mkdir ../3D_archive
	@mkdir ../3D_archive/src
	@cp -rf . ../3D_archive/src
	@cd ..; tar czvf 3D_archive.tgz 3D_archive/*
	@mkdir ../distrib
	@mv -t ../distrib ../3D_archive.tgz 
	@rm -rf ../3D_archive

clean:
	@rm -rf *.o *.a *.gcno *.gcda *.info *.dSYM test gcov_report *.out
	@rm -rf ./report ./build ./3d ../distrib

clean_report:
	@rm -rf *.gcno *.gcda *.info *.dSYM gcov_report
	@rm -rf ./report

check:
	@cp ../materials/linters/CPPLINT.cfg CPPLINT.cfg
	python3 ../materials/linters/cpplint.py --filter=-build/namespaces --extensions=cpp,h model/*.cpp model/*.h controller/*.cpp controller/*.h view/*.cpp view/*.h
	@rm -rf CPPLINT.cfg
	
cppcheck:
	@cppcheck --std=c++17 --language=c++ --enable=all --suppress=unusedFunction --suppress=unreadVariable \
	--suppress=unusedStructMember --suppress=unusedVariable --suppress=redundantInitialization \
	--suppress=variableScope --suppress=missingInclude --suppress=noCopyConstructor --suppress=noOperatorEq \
	--suppress=uninitMemberVar model/*.cpp model/*.h controller/*.cpp controller/*.h view/*.cpp view/*.h




