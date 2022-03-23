NAME=f1edit.exe
OBJS=f1edit.obj

$NAME: $(OBJS)
	wlink @<< 
		name $@ 	
		system dos32a
		file {
			..\..\pdcurses\dos\pdcurses.lib 
			$<
		}
		option quiet
<<

f1edit.obj: f1edit.c
	wpp386 -zq -bt=dos32a $< -i=..\..\pdcurses

clean: .SYMBOLIC
	del *.obj
	del lxedit.exe
