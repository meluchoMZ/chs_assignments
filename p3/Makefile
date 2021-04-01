x64:
	g++ -I. -I$SYSTEMC_HOME/include -L. -L$SYSTEMC_HOME/lib-linux64 -Wl,-rpath=$SYSTEMC_HOME/lib-linux64 -o p3 practicaFSM_Secuencia.cpp secuencia.cpp -lsystemc -lm -g

x86:
	g++ -I. -I$SYSTEMC_HOME/include -L. -L$SYSTEMC_HOME/lib-linux -Wl,-rpath=$SYSTEMC_HOME/lib-linux -o p3 practicaFSM_Secuencia.cpp secuencia.cpp -lsystemc -lm -g

clean:
	rm p3
