#!/usr/bin/env python
import threading

'''
Hint:
    lock = threading.Lock()
    lock.acquire()
    lock.release()
'''

t1 = 0
t2 = 0
t3 = 0

def Task(num):
    # hint
    for i in range(3):
        print(num)
    # hint

def thread_init():
    global t1
    global t2
    global t3
    
    # hint
    t1 = threading.Thread(target = Task, args = ('1'))
    t2 = threading.Thread(target = Task, args = ('2'))
    t3 = threading.Thread(target = Task, args = ('3'))

def init():
    thread_init()
    t1.start()
    t2.start()
    t3.start()
    t1.join()
    t2.join()
    t3.join()

if __name__ == "__main__":
    for i in range(3):
        init()
