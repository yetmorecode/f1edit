NAME=f1edit
OBJS=$NAME.obj

$NAME.exe: $(OBJS)
	wlink @<< 
		name $@ 	
		system dos32a
		file {
			..\..\pdcurses\dos\pdcurses.lib 
			$<
		}
		option quiet
<<

$NAME.obj: $NAME.c
	wpp386 -zq -bt=dos32a $< -i=..\..\pdcurses

clean: .SYMBOLIC
	del *.obj
	del $NAME.exe
