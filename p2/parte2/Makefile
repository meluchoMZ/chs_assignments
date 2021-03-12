x64:
	g++ -I. -I$SYSTEMC_HOME/include -L. -L$SYSTEMC_HOME/lib-linux64 -Wl,-rpath=$SYSTEMC_HOME/lib-linux64 -o p2 practicaCA.cpp duplicar.cpp diferencia.cpp -lsystemc -lm -g

x86:
	g++ -I. -I$SYSTEMC_HOME/include -L. -L$SYSTEMC_HOME/lib-linux -Wl,-rpath=$SYSTEMC_HOME/lib-linux -o p2 practicaCA.cpp duplicar.cpp diferencia.cpp -lsystemc -lm -g

clean:
	rm p2
