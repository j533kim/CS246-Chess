CXX = g++
CXXFLAGS = -std=c++14 -Wall -Werror=vla -MMD
EXEC = chess
OBJECTS = main.o main_helper.o computer.o board.o textdisplay.o cell.o move.o nopiece.o piece.o king.o queen.o bishop.o rook.o knight.o pawn.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

state.o: state.h 
	${CXX} ${CXXFLAGS} state.h

-include ${DEPENDS}

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
.PHONY: clean
