An very interesting function for  the start address of a specific thread.It can be used for anti-injection because in most system processes share same system API address.

ListProcessThreads checks all thread in a specific process given by PID.

简单来说就是可以遍历某个进程中所有的线程的起始地址，然后就可以各种操作啦~

ListProcessThreads 会对一个指定PID内的线程进行各种操作，在这里会检查起始地址。
