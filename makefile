##########################################################################################
# Makefile to be used with the HAM SDK (www.ngine.de)
#
# Created using VisualHAM (www.console-dev.de)
#
##########################################################################################
include $(HAMDIR)/system/master.mak

#
# Set the name of your desired GBA image name here
#
PROGNAME=Demineur

#
# Set a list of files you want to compile
#
OFILES +=main.o			\
		mines.o			\
		view.o			\
		controls.o		\
		menu.o			\
		pause.o			\
		save.o			\
		selectionMenu.o	\
		keyboard.o		\
		font.o			\
		password.o		\
		load.o			\
		gameOver.o		\
		timers.o		\
		music.o			\
		settings.o		\
		flags.raw.o		\
		cases.raw.o		\
		mines.raw.o		\
		numbers.raw.o	\
		save.raw.o		\
		load.raw.o		\
		pseudo.raw.o	\
		font.raw.o		\
		game_over.raw.o	\
		password.raw.o	\
		continue.raw.o	\
		game_won.raw.o	\

#
# Set a list of libraries you want to link
#
ADD_LIBS +=

#
# Compile using Krawall software (set to yes or no) ?
# Also specify if Krawall is registered (yes or no)
#
USE_KRAWALL=yes
KRAWALL_IS_REGISTERED=no
KRAWALL_FILES=aqua.s3m adagio.s3m rois_mages.s3m

##########################################################################################
# Standard Makefile targets start here
##########################################################################################
all : $(PROGNAME).$(EXT) clean

#
# Most Makefile targets are predefined for you, suchas
# vba, clean ... in the following file
#
include $(HAMDIR)/system/standard-targets.mak

##########################################################################################
# Add custom makefile targets here
##########################################################################################
