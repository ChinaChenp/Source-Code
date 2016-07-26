#include <threadpool/TP_ThreadPool.h>
#include <iostream>
#include <vector>
#include <unistd.h>
using namespace std;

class CMyTask : public CTP_Task {
public:
    CMyTask() {m_data = 0;}
    virtual ~CMyTask() {}

    int handle(int threadid) {
        //cout << "threadId:" << threadid << endl;
        //cout << "data:" << ++m_data << endl;
        m_data = threadid;
	    sleep((threadid%2) * 3);

        return 0;
    }

    int getData(){return m_data;}

private:
    int m_data;
};

#if EXECUTE_ALL_TASKS
int main() {
    int maxThreads = 10;
    int maxQueueSize = 10;
    CTP_ThreadPool* threadPool = new CTP_ThreadPool(maxThreads, maxQueueSize);

    vector<CMyTask*> tasks;
    for(int i = 0; i < 10; ++i) {
        CMyTask* task = new CMyTask();
        if(threadPool->execute(task) == 0 ) {
            tasks.push_back(task);
        } else {
            delete task;
        }
    }

    cout << "use execute one tasks" << endl;
    for(size_t i = 0; i < tasks.size(); ++i) {
        cout << "result: " <<tasks[i]->getResult() << endl;
        cout << "data:" << tasks[i]->getData() << endl;
        delete tasks[i];
    }

    delete threadPool;

    return 0;
}

#else
int main() {
    int maxThreads = 10;
    int maxQueueSize = 10;
    CTP_ThreadPool* threadPool = new CTP_ThreadPool(maxThreads, maxQueueSize);

    vector<CTP_Task*> tasks;
    for(int i = 0; i < 10; ++i) {
        CTP_Task* task = dynamic_cast<CTP_Task* >(new CMyTask);
        if(task != NULL) {
            tasks.push_back(task);
        } else {
            delete task;
        }
    }
    int work_size = threadPool->execute(tasks);

    cout << "use execute all tasks" << endl;
    for(size_t i = 0; i < work_size; ++i) {
        CMyTask * t = dynamic_cast<CMyTask *> (tasks[i]);
        cout << "result: " <<t->getResult() << endl;
        cout << "data:" << t->getData() << endl;
        delete t;
    }

    delete threadPool;

    return 0;

}

#endif

