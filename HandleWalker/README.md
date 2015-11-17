HandlerWalker checks kernel objects in other processes.It works like a reader who can read handler hold by other processes,duplicate them into itself then check whether the handler is what we need.It is very complicated and unstable cause undocumented function and unpredictable handlers list (sometimes it will return ~100000 handlers and most of them are fake)

HandlerWalker被设计用做一个非常复杂的句柄扫描器，这个功能常见于各大监视系统。要注意的是这个东西本身的复杂性注定低效率和不稳定的一面。大量的使用文档中没有的函数，以及不可预知的句柄表会降低程序的性能。
然而它却可以有效的对各种注入和dump起作用，当然绕过的方法也是有的。
