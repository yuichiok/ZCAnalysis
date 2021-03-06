# Make file for ZCAnalysis

CC=g++
CFLAGS=-c -Wall
ROOTFLAGS=`root-config --cflags --glibs --libs`

all : NtupleProcessor ControlPlotMaker EffPlotAndCalc CombineBCLTemplates
	make -f NtupleProcessor/makefile
	make -f ControlPlotMaker/makefile
	make -C EffPlotAndCalc

# EffPlotAndCalc :
# 	$(CC) EffPlotAndCalc.cpp -o EffPlotAndCalc.exe $(ROOTFLAGS) -lboost_program_options

CombineBCLTemplates :
	$(CC) CombineBCLTemplates.cpp -o CombineBCLTemplates.exe $(ROOTFLAGS) -lboost_program_options

clean :
	make clean -f NtupleProcessor/makefile
	make clean -f ControlPlotMaker/makefile
	make clean - EffPlotAndCalc
