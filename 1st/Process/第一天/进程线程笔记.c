进程线程（3天）:
1、	进程理论，进程创建、守护进程、文件锁
2、	进程间通信IPC（无名管道、有名管道、信号、共享内存、信号量）
3、	线程理论、线程操作函数、线程间的同步和互斥（POSIX信号量， 互斥锁）


一、进程理论：
进程是系统分配资源的最小单位，线程是系统执行的最小单位。
进程控制块（PCB）：struct  task_struct 结构体（就是传说中进程的尸体），内核用这个结构体来描述一个进程信息（如进程的状态、进程pid等等） 
路径：vi /usr/src/linux-headers-3.2.0-29-generic-pae/include/linux/sched.h

进程的特点：
 	动态性-?进程是一个运行的过程，状态不断的切换
 	并发性--?多个进程可以同时执行。
 	独立性---?每个进程分配的内容空间都是独立的，其他进程不能直接访问。
 	异步性---?一个进程在运行的过程中，不可预料的收到其他的情况的影响（如信号）
pid：
pid_t getpid(void)；//获得当前进程的PID
pit_t getppid(void)；//获得当前进程父进程的PID

进程关键字：
进程互斥
   进程互斥是指当有若干进程都要使用某一共享资源时，任何时候最多允许一个进程使用，其他要 使用该资源的进程必须等待，直到只用自愿者释放了该资源
进程同步
  一组并发进程按一定的顺序执行的过程称为进程间的同步。具有同步关系的一组并发进程称为合作进程，合作进程间互相发送的信号称为消息或事件。
临界资源
   操作系统中将以此只允许一个进程访问的资源称为临界资源
临界区
   进程中访问临界资源的那段程序代码称为临界区。为实现对临界资源的互斥访问，应保证诸进程互斥地进入各自的临界区。
死锁
   多个进程因竞争资源而形成一种僵局，若无外力作用，这些进程将永远不能向前推进。
fork创建一个子进程，子进程几乎完全拷贝父进程的资源（除了代码段）

Exec函数组：
一般情况下，在子进程中调用该函数，调用之后，有exec执行的函数的代码、数据、堆栈会覆盖掉子进程中从父进程继承过来的资源。使子进程执行新的任务。
修改PATH环境变量
export PATH=$PATH:程序所在目录的绝对路径

int main(void)
{
    char *arg[] = {"ls", "-al", NULL};
    char *env[] = {"USR = zhangsan", NULL};

	execl("/bin/ls", "ls", "-al", NULL);
	execl("/home/farsight/lesson/1_day/mycp", "./mycp", "1.c", "2.c", NULL);
    execv("/bin/ls", arg);
    execle("/bin/ls", "ls", "-al", env);
    execve("/bin/ls", arg, env);

    execlp("ls", "ls", "-al", NULL);//系统对自动的从path路径中找可执行文件

    execvp("ls" ,arg);

    return 0;
}

system("touch 123");
system("rm 123");
system("clear");

#define EXIT_SUCCESS 0
#define EXIT_FAILED  1

exit(int status)：
	在一个进程中任何地方调用exit，都是退出整个进程，参数status是进程结束时，给父进程的状态信息，在系统已经默认了
0(正常)和1（非正常）这两个状态。其他的值有子进程和父进程之间进行约定。
	exit在结束时，会自动清空I/O缓冲区，最后调用do_exit()退出进程。



pid_t wait(int *status)

wait：
	wait函数一般都是父进程来调用，用来给子进程收尸，这时父进程会一直阻塞，直到有一个子进程结束为止.
	
	waitpid(-1, &status, 0);//和wait(&status)等价

	wait一次只能给一个子进程收尸，如果有多个子进程，则有多次调用
	wait(NULL);


//===============================

//waitpid可以给指定pid的进程收尸
pid_t waitpid(pid_t pid, int *status, int options)
options:
	WNOHONG:当子进程没有退出,则直接返回
	0:和wait一样,子进程没有退出,则阻塞


孤儿进程：
	当一个进程的父进程提前死去时，该进程就变为孤儿进程，它会被init进程(pid = 1)收养,死掉之后又init进程收尸，所以孤儿进程
时一种非常安全的进程，不用考虑收尸的问题。

僵尸进程:
	一个进程结束之后,如果它的退出状态信息没有被获得,那么内核中的strut task_struct就一直
会被保留,直到有进程来获得这个退出状态信息.



服务器模型： 

//该模型可以避免父进程花费太多的时间来给子进程收尸，影响父进程的效率。
int main(void)
{
	pid_t pid;

	pid = fork();
	if(pid < 0)
	{
		perror("fork");
		exit(1);
	}
	if(pid == 0) //子进程
	{
		pid = fork();
		if(pid < 0)
		{
			perror("fork");
			exit(1);
		}
		if(pid == 0)//孙子进程,当子进程结束后，该进程成为孤儿进程，有init进程收养
		{
			//孙子进程做自己的事情
			//do something

			exit(0); //孙子进程做完事情之后退出
		}
		if(pid > 0)
			exit(0);//子进程结束
		
	}
	wait(NULL);//为子进程收尸

	//父进程
	{
		//父进程在这里做自己的事情
		//do something
	}

	return 0;
}

守护进程：又称精灵进程，或Daemon进程，一般用作后台服务进程，在开机时启动，关机时结束。

//==============守护进程创建步骤==================
    //忽略信号的影响
    signal(SIGHUP, SIG_IGN);
    signal(SIGTSTP, SIG_IGN);
    //第一次fork，为子进程调用setsid做准备
    pid = fork();
    if(pid > 0)
	exit(0);
    //调用setsid()，创建新的会话；
    setsid();
    
    //第二次fork
    pid = fork();
    if(pid > 0)
	exit(0);
    
    //调用setpgrp(),创建新的进程组
    setpgrp();

    //关闭所有从父进程继承过来的文件描述符
    max_fd = sysconf(_SC_OPEN_MAX);
    for (i = 0; i < max_fd;i++)
	close(i);
    //消除umask的影响
    umask(0);
    //改变进程当前工作目录
    chdir("/");
    //将标准I/O进行重定向
	fd = open("/dev/null",O_RDWR);
    dup(fd);
    dup(fd);

//===============管道====================
无名管道没有具体的路径名，只有两个文件描述符；
有名管道有路径名，基于文件系统,注意管道的读端和写端必须同时打开，这样才能进行数据通信。
1、使用mkfifo创建管道；
2、使用open打开管道；
3、使用read/write读写管道；
4、使用close关闭管道


//=====================信号===============================
信号的有的来源:
1.由硬件检测产生(段错误:SIGSEGV)
2.有算数运算产生(除数为零:SIGFPE)
3.由中断按键产生(ctrl+c:SIGINT,ctrl+\:SIGQUIT)
4.由软件本身产生(管道:SIGPIPE,闹钟:SIGALRM)
5.由其他进程发送(kill命令或kill函数)

收到信号之后怎么处理:
1.忽略该信号,SIGKILL及SIGSTOP不能被忽略
2.按照系统默认的方式去处理
3.按照用户指定的方式去处理.（通过signal函数注册）：注意：SIGKILL和SIGSTOP不能被注册和忽略


当进程正在内核中进行系统调用，如果这时收到信号，则会优先去处理信号，然后再返回内核继续系统调用。
系统中有两个信号：SIGUSR1和SIGUSR2，没有特殊的含义，用户可以根据自己的需要去定义注册。在使用这两个信号之前，必须
注册(signal)。

alarm(int sec):
	alarm(5):给当前进程定时，5秒钟之后，当前进程会受到SIGALRM信号，默认终止当前进程。
	返回值：返回上一个闹钟剩余的秒数，alarm(0)取消上一个闹钟。
	alarm可以实现read或write的定时阻塞。
pause: 可以阻塞当前进程，直到受到任意一个信号为止，可以用来实现多个进程之间的同步,注意使用信号实现进程间的同步有一定
的缺陷，因为pause在收到任何信号，都会继续，有时候会接受意外的信号，达不到预期的要求。
sleep：可以让进程睡眠，在睡眠过程中，只要收到信号就会醒来。

子进程会继承父进程对信号的处理方式。
当使用终端按键给程序发信号时，产生的信号会发给程序中所有的前台进程.

//================共享内存===============================
key_t ftok(const char *pathname, int proj_id);
ftok函数将会调用stat函数后去pathname的st_dev和st_ino，组成一个24位的整数，作为key的前24位，将proj_id的hou8位作为
key的后8位。

//内核用以下结构体来描述一个IPC对象的权限。
struct kern_ipc_perm
{
        spinlock_t      lock;
        int             deleted;
        int             id;
        key_t           key;
        uid_t           uid;
        gid_t           gid;
        uid_t           cuid;
        gid_t           cgid;
        mode_t          mode;
        unsigned long   seq;
        void            *security;
};
//内核用以下结构体来描述共享内存的信息。
struct shmid_ds {
        struct ipc_perm         shm_perm;       /* operation perms */
        int                     shm_segsz;      /* size of segment (bytes) */
        __kernel_time_t         shm_atime;      /* last attach time */
        __kernel_time_t         shm_dtime;      /* last detach time */
        __kernel_time_t         shm_ctime;      /* last change time */
        __kernel_ipc_pid_t      shm_cpid;       /* pid of creator */
        __kernel_ipc_pid_t      shm_lpid;       /* pid of last operator */
        unsigned short          shm_nattch;     /* no. of current attaches */
        unsigned short          shm_unused;     /* compatibility */
        void                    *shm_unused2;   /* ditto - used by DIPC */
        void                    *shm_unused3;   /* unused */
};

在对共享内存写数据时，会将之前已经有的内容全部覆盖（理解为数组）.


//===========================信号量===================================
信号量集(system V信号量)：表示资源的可用量，注意信号量本身不是资源。分为二值信号量和多值信号量，可以用于进程和线程。
一般情况下，都使用二值信号量。
POSIX信号量:只能用于线程。

P操作:获得资源，信号量的值减1；当信号量的值为0时，进行p操作的进程阻塞
V操作：释放资源，信号量的值加1；不会失败。
PV操作时原子操作，即过程不能被打断，要么成功，要么失败。
SEM_UNDO:当一个进程结束时，会撤销对信号量的操作。

int semctl(int semid, int semnum, int cmd, ...);
	1、完成对信号量集的初始化(单个信号量:cmd = SETVAL, 多个信号量同时初始化：cmd = SETALL)
	2、获取信号量的值(cmd = GETVAL)
	3、删除信号量集（cmd = IPC_RMID）

//需要用户自己定义
union semun {
      int              val;    /* Value for SETVAL */
      struct semid_ds *buf;    /* Buffer for IPC_STAT, IPC_SET */
      unsigned short  *array;  /* Array for GETALL, SETALL */
      struct seminfo  *__buf;  /* Buffer for IPC_INFO
                                           (Linux-specific) */
};

//将信号量sem的值初始化为1
union semun sem_p;
sem_p.val = 1;
semctl(semid, 0, SETVAL, sem_p);


int semop ( int semid, struct sembuf  *opsptr,  size_t  nops);

//==================PV操作=====================
//实现sem信号量的p操作
struct sembuf buf;
buf.sem_num = 0;//下标
buf.sem_op = -1;
buf.sem_flg = 0;

semop(semid, &buf, 1);

//实现sem信号量的V操作
struct sembuf buf;
buf.sem_num = 0;//下标
buf.sem_op = 1;
buf.sem_flg = 0;

semop(semid, &buf, 1);
//信号量集中有两个信号量,对第一个信号量进行V操作,对第二个进行P操作
struct sembuf buf[2];

buf[0].sem_num = 0;
buf[0].sem_op = 1;
buf[0].sem_flg = 0;

buf[1].sem_num = 1;
buf[1].sem_op = -1;
buf[1].sem_flg = 0;

semop(semid, buf,  2);


int semctl(int semid, int semnum,  int cmd…/*union semun arg*/);
//信号量集中有两个信号量,分别将两个信号量初始化为100和200
 unsigned short val_buf[2];
 union semun  un;

val_buf[0] = 100;
val_buf[1] = 200;

un.array = val_buf;
semctl(semid, 0,  SETALL, un);

//获取信号量的值,通过返回值
val = semctl(semid, 0,  GETVAL);

//删除信号量集
semctl(semid, 0,  IPC_RMID);


//进程和线程的区别
1.进程是系统分配资源的最小单位,线程是系统调度的最小单位
2.一个进程可以创建多个线程,而这些线程共享进程的资源.
3.线程必须依赖于进程而存在,不能独立运行.
4.线程和进程的执行顺序不确定,在竞争CPU时,机会均等.

//=====================线程的属性===================

pthread_attr_t attr;//线程属性类型
//对线程属性进行初始化
pthread_attr_init(&attr);
//将分离属性加入到线程的属性中(线程默认是可联合属性:PTHREAD_CREATE_JOINABLE)
pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
//创建分离线程
pthread_create(&tid, &attr, func, NULL);
//如果一个线程为分离线程,则进程不需要调用pthread_join为该线程收尸,否则将会出错

int pthread_detach(pthread_t thread);//该函数可以将一个正在运行的线程设为分离线程.


Ｐ(Ｓ) 含义如下:
     if  (信号量的值大于0) {   申请资源的任务继续运行；
                                                信号量的值减一；}
     else {   申请资源的任务阻塞；} 


V(Ｓ) 含义如下:
     if  (没有任务在等待该资源) {   信号量的值加一；}
     else {   唤醒第一个等待的任务，让其继续运行}
     


#include <semaphore.h>
int  sem_init(sem_t *sem,  int pshared,  unsigned int value); 
int sem_wait(sem_t *sem);   //  P操作
int sem_post(sem_t *sem);  // V操作 
int sem_trywait(sem_t *sem);//非阻塞方式的p操作，p操作失败返回。
int sem_getvalue(sem_t *sem,  int *svalue);


互斥锁：
	功能：1、使多个进程可以互斥访问共享资源
		  2、保护一段重要的代码，使这段代码在执行过程中，不会被打断。( 银行的存款和查询系统）

	
条件变量：
类型：
pthread_cond_t cond;
pthread_mutex_t mutex;//条件变量类型

 //对互斥锁和条件变量进行初始化
pthread_mutex_init(&mutex, NULL);
pthread_cond_init(&cond, NULL);
 

 pthread_mutex_lock(&m);
 while(global != 100)
 {
     pthread_cond_wait(&cond, &mutex);
 }
 
   //xxxxxxxx临界区xxxxxxxxx
pthread_mutex_unlock(&m);


//向等待条件的线程发送信号
pthread_cond_signal(&cond);// 
pthread_cond_broadcat(&cond);//广播式发送