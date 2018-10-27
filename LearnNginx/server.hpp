void startServer();
void startWorker(int workerId,int serverSock);
void handleNewConnection(int kqueuefd,int serverSock);
char* handleReadFromClient(int workerId,struct kevent event);
void handleWriteToClient(int workerId,struct kevent event, char* msg);