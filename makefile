CPPFLAGS = -g
all: a.out
	./a.out
a.out: objects/account.o objects/askfm_user.o objects/helperFunctions.o objects/login.o objects/question.o objects/signup.o objects/systemBase.o objects/systemFlow.o objects/askme.o
	g++ objects/account.o objects/askfm_user.o objects/helperFunctions.o objects/login.o objects/question.o objects/signup.o objects/systemBase.o objects/systemFlow.o objects/askme.o

objects/account.o: Sources/account.cpp
	g++ Sources/account.cpp -c $(CPPFLAGS) -o objects/account.o
objects/askfm_user.o: Sources/askfm_user.cpp
	g++ Sources/askfm_user.cpp -c $(CPPFLAGS) -o objects/askfm_user.o
objects/helperFunctions.o: Sources/helperFunctions.cpp
	g++ Sources/helperFunctions.cpp -c $(CPPFLAGS) -o objects/helperFunctions.o
objects/login.o: Sources/login.cpp
	g++ Sources/login.cpp -c $(CPPFLAGS) -o objects/login.o
objects/question.o: Sources/question.cpp
	g++ Sources/question.cpp -c $(CPPFLAGS) -o objects/question.o
objects/signup.o: Sources/signup.cpp
	g++ Sources/signup.cpp -c $(CPPFLAGS) -o objects/signup.o
objects/systemBase.o: Sources/systemBase.cpp
	g++ Sources/systemBase.cpp -c $(CPPFLAGS) -o objects/systemBase.o 
objects/systemFlow.o: Sources/systemFlow.cpp
	g++	Sources/systemFlow.cpp -c $(CPPFLAGS) -o objects/systemFlow.o
objects/askme.o: Sources/askme.cpp
	g++ Sources/askme.cpp -c $(CPPFLAGS) -o objects/askme.o
