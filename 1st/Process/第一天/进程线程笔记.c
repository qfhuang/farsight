�����̣߳�3�죩:
1��	�������ۣ����̴������ػ����̡��ļ���
2��	���̼�ͨ��IPC�������ܵ��������ܵ����źš������ڴ桢�ź�����
3��	�߳����ۡ��̲߳����������̼߳��ͬ���ͻ��⣨POSIX�ź����� ��������


һ���������ۣ�
������ϵͳ������Դ����С��λ���߳���ϵͳִ�е���С��λ��
���̿��ƿ飨PCB����struct  task_struct �ṹ�壨���Ǵ�˵�н��̵�ʬ�壩���ں�������ṹ��������һ��������Ϣ������̵�״̬������pid�ȵȣ� 
·����vi /usr/src/linux-headers-3.2.0-29-generic-pae/include/linux/sched.h

���̵��ص㣺
 	��̬��-?������һ�����еĹ��̣�״̬���ϵ��л�
 	������--?������̿���ͬʱִ�С�
 	������---?ÿ�����̷�������ݿռ䶼�Ƕ����ģ��������̲���ֱ�ӷ��ʡ�
 	�첽��---?һ�����������еĹ����У�����Ԥ�ϵ��յ������������Ӱ�죨���źţ�
pid��
pid_t getpid(void)��//��õ�ǰ���̵�PID
pit_t getppid(void)��//��õ�ǰ���̸����̵�PID

���̹ؼ��֣�
���̻���
   ���̻�����ָ�������ɽ��̶�Ҫʹ��ĳһ������Դʱ���κ�ʱ���������һ������ʹ�ã�����Ҫ ʹ�ø���Դ�Ľ��̱���ȴ���ֱ��ֻ����Ը���ͷ��˸���Դ
����ͬ��
  һ�鲢�����̰�һ����˳��ִ�еĹ��̳�Ϊ���̼��ͬ��������ͬ����ϵ��һ�鲢�����̳�Ϊ�������̣��������̼以�෢�͵��źų�Ϊ��Ϣ���¼���
�ٽ���Դ
   ����ϵͳ�н��Դ�ֻ����һ�����̷��ʵ���Դ��Ϊ�ٽ���Դ
�ٽ���
   �����з����ٽ���Դ���Ƕγ�������Ϊ�ٽ�����Ϊʵ�ֶ��ٽ���Դ�Ļ�����ʣ�Ӧ��֤����̻���ؽ�����Ե��ٽ�����
����
   �������������Դ���γ�һ�ֽ��֣������������ã���Щ���̽���Զ������ǰ�ƽ���
fork����һ���ӽ��̣��ӽ��̼�����ȫ���������̵���Դ�����˴���Σ�

Exec�����飺
һ������£����ӽ����е��øú���������֮����execִ�еĺ����Ĵ��롢���ݡ���ջ�Ḳ�ǵ��ӽ����дӸ����̼̳й�������Դ��ʹ�ӽ���ִ���µ�����
�޸�PATH��������
export PATH=$PATH:��������Ŀ¼�ľ���·��

int main(void)
{
    char *arg[] = {"ls", "-al", NULL};
    char *env[] = {"USR = zhangsan", NULL};

	execl("/bin/ls", "ls", "-al", NULL);
	execl("/home/farsight/lesson/1_day/mycp", "./mycp", "1.c", "2.c", NULL);
    execv("/bin/ls", arg);
    execle("/bin/ls", "ls", "-al", env);
    execve("/bin/ls", arg, env);

    execlp("ls", "ls", "-al", NULL);//ϵͳ���Զ��Ĵ�path·�����ҿ�ִ���ļ�

    execvp("ls" ,arg);

    return 0;
}

system("touch 123");
system("rm 123");
system("clear");

#define EXIT_SUCCESS 0
#define EXIT_FAILED  1

exit(int status)��
	��һ���������κεط�����exit�������˳��������̣�����status�ǽ��̽���ʱ���������̵�״̬��Ϣ����ϵͳ�Ѿ�Ĭ����
0(����)��1����������������״̬��������ֵ���ӽ��̺͸�����֮�����Լ����
	exit�ڽ���ʱ�����Զ����I/O��������������do_exit()�˳����̡�



pid_t wait(int *status)

wait��
	wait����һ�㶼�Ǹ����������ã��������ӽ�����ʬ����ʱ�����̻�һֱ������ֱ����һ���ӽ��̽���Ϊֹ.
	
	waitpid(-1, &status, 0);//��wait(&status)�ȼ�

	waitһ��ֻ�ܸ�һ���ӽ�����ʬ������ж���ӽ��̣����ж�ε���
	wait(NULL);


//===============================

//waitpid���Ը�ָ��pid�Ľ�����ʬ
pid_t waitpid(pid_t pid, int *status, int options)
options:
	WNOHONG:���ӽ���û���˳�,��ֱ�ӷ���
	0:��waitһ��,�ӽ���û���˳�,������


�¶����̣�
	��һ�����̵ĸ�������ǰ��ȥʱ���ý��̾ͱ�Ϊ�¶����̣����ᱻinit����(pid = 1)����,����֮����init������ʬ�����Թ¶�����
ʱһ�ַǳ���ȫ�Ľ��̣����ÿ�����ʬ�����⡣

��ʬ����:
	һ�����̽���֮��,��������˳�״̬��Ϣû�б����,��ô�ں��е�strut task_struct��һֱ
�ᱻ����,ֱ���н������������˳�״̬��Ϣ.



������ģ�ͣ� 

//��ģ�Ϳ��Ա��⸸���̻���̫���ʱ�������ӽ�����ʬ��Ӱ�츸���̵�Ч�ʡ�
int main(void)
{
	pid_t pid;

	pid = fork();
	if(pid < 0)
	{
		perror("fork");
		exit(1);
	}
	if(pid == 0) //�ӽ���
	{
		pid = fork();
		if(pid < 0)
		{
			perror("fork");
			exit(1);
		}
		if(pid == 0)//���ӽ���,���ӽ��̽����󣬸ý��̳�Ϊ�¶����̣���init��������
		{
			//���ӽ������Լ�������
			//do something

			exit(0); //���ӽ�����������֮���˳�
		}
		if(pid > 0)
			exit(0);//�ӽ��̽���
		
	}
	wait(NULL);//Ϊ�ӽ�����ʬ

	//������
	{
		//���������������Լ�������
		//do something
	}

	return 0;
}

�ػ����̣��ֳƾ�����̣���Daemon���̣�һ��������̨������̣��ڿ���ʱ�������ػ�ʱ������

//==============�ػ����̴�������==================
    //�����źŵ�Ӱ��
    signal(SIGHUP, SIG_IGN);
    signal(SIGTSTP, SIG_IGN);
    //��һ��fork��Ϊ�ӽ��̵���setsid��׼��
    pid = fork();
    if(pid > 0)
	exit(0);
    //����setsid()�������µĻỰ��
    setsid();
    
    //�ڶ���fork
    pid = fork();
    if(pid > 0)
	exit(0);
    
    //����setpgrp(),�����µĽ�����
    setpgrp();

    //�ر����дӸ����̼̳й������ļ�������
    max_fd = sysconf(_SC_OPEN_MAX);
    for (i = 0; i < max_fd;i++)
	close(i);
    //����umask��Ӱ��
    umask(0);
    //�ı���̵�ǰ����Ŀ¼
    chdir("/");
    //����׼I/O�����ض���
	fd = open("/dev/null",O_RDWR);
    dup(fd);
    dup(fd);

//===============�ܵ�====================
�����ܵ�û�о����·������ֻ�������ļ���������
�����ܵ���·�����������ļ�ϵͳ,ע��ܵ��Ķ��˺�д�˱���ͬʱ�򿪣��������ܽ�������ͨ�š�
1��ʹ��mkfifo�����ܵ���
2��ʹ��open�򿪹ܵ���
3��ʹ��read/write��д�ܵ���
4��ʹ��close�رչܵ�


//=====================�ź�===============================
�źŵ��е���Դ:
1.��Ӳ��������(�δ���:SIGSEGV)
2.�������������(����Ϊ��:SIGFPE)
3.���жϰ�������(ctrl+c:SIGINT,ctrl+\:SIGQUIT)
4.������������(�ܵ�:SIGPIPE,����:SIGALRM)
5.���������̷���(kill�����kill����)

�յ��ź�֮����ô����:
1.���Ը��ź�,SIGKILL��SIGSTOP���ܱ�����
2.����ϵͳĬ�ϵķ�ʽȥ����
3.�����û�ָ���ķ�ʽȥ����.��ͨ��signal����ע�ᣩ��ע�⣺SIGKILL��SIGSTOP���ܱ�ע��ͺ���


�����������ں��н���ϵͳ���ã������ʱ�յ��źţ��������ȥ�����źţ�Ȼ���ٷ����ں˼���ϵͳ���á�
ϵͳ���������źţ�SIGUSR1��SIGUSR2��û������ĺ��壬�û����Ը����Լ�����Ҫȥ����ע�ᡣ��ʹ���������ź�֮ǰ������
ע��(signal)��

alarm(int sec):
	alarm(5):����ǰ���̶�ʱ��5����֮�󣬵�ǰ���̻��ܵ�SIGALRM�źţ�Ĭ����ֹ��ǰ���̡�
	����ֵ��������һ������ʣ���������alarm(0)ȡ����һ�����ӡ�
	alarm����ʵ��read��write�Ķ�ʱ������
pause: ����������ǰ���̣�ֱ���ܵ�����һ���ź�Ϊֹ����������ʵ�ֶ������֮���ͬ��,ע��ʹ���ź�ʵ�ֽ��̼��ͬ����һ��
��ȱ�ݣ���Ϊpause���յ��κ��źţ������������ʱ������������źţ��ﲻ��Ԥ�ڵ�Ҫ��
sleep�������ý���˯�ߣ���˯�߹����У�ֻҪ�յ��źžͻ�������

�ӽ��̻�̳и����̶��źŵĴ���ʽ��
��ʹ���ն˰����������ź�ʱ���������źŻᷢ�����������е�ǰ̨����.

//================�����ڴ�===============================
key_t ftok(const char *pathname, int proj_id);
ftok�����������stat������ȥpathname��st_dev��st_ino�����һ��24λ����������Ϊkey��ǰ24λ����proj_id��hou8λ��Ϊ
key�ĺ�8λ��

//�ں������½ṹ��������һ��IPC�����Ȩ�ޡ�
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
//�ں������½ṹ�������������ڴ����Ϣ��
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

�ڶԹ����ڴ�д����ʱ���Ὣ֮ǰ�Ѿ��е�����ȫ�����ǣ����Ϊ���飩.


//===========================�ź���===================================
�ź�����(system V�ź���)����ʾ��Դ�Ŀ�������ע���ź�����������Դ����Ϊ��ֵ�ź����Ͷ�ֵ�ź������������ڽ��̺��̡߳�
һ������£���ʹ�ö�ֵ�ź�����
POSIX�ź���:ֻ�������̡߳�

P����:�����Դ���ź�����ֵ��1�����ź�����ֵΪ0ʱ������p�����Ľ�������
V�������ͷ���Դ���ź�����ֵ��1������ʧ�ܡ�
PV����ʱԭ�Ӳ����������̲��ܱ���ϣ�Ҫô�ɹ���Ҫôʧ�ܡ�
SEM_UNDO:��һ�����̽���ʱ���᳷�����ź����Ĳ�����

int semctl(int semid, int semnum, int cmd, ...);
	1����ɶ��ź������ĳ�ʼ��(�����ź���:cmd = SETVAL, ����ź���ͬʱ��ʼ����cmd = SETALL)
	2����ȡ�ź�����ֵ(cmd = GETVAL)
	3��ɾ���ź�������cmd = IPC_RMID��

//��Ҫ�û��Լ�����
union semun {
      int              val;    /* Value for SETVAL */
      struct semid_ds *buf;    /* Buffer for IPC_STAT, IPC_SET */
      unsigned short  *array;  /* Array for GETALL, SETALL */
      struct seminfo  *__buf;  /* Buffer for IPC_INFO
                                           (Linux-specific) */
};

//���ź���sem��ֵ��ʼ��Ϊ1
union semun sem_p;
sem_p.val = 1;
semctl(semid, 0, SETVAL, sem_p);


int semop ( int semid, struct sembuf  *opsptr,  size_t  nops);

//==================PV����=====================
//ʵ��sem�ź�����p����
struct sembuf buf;
buf.sem_num = 0;//�±�
buf.sem_op = -1;
buf.sem_flg = 0;

semop(semid, &buf, 1);

//ʵ��sem�ź�����V����
struct sembuf buf;
buf.sem_num = 0;//�±�
buf.sem_op = 1;
buf.sem_flg = 0;

semop(semid, &buf, 1);
//�ź��������������ź���,�Ե�һ���ź�������V����,�Եڶ�������P����
struct sembuf buf[2];

buf[0].sem_num = 0;
buf[0].sem_op = 1;
buf[0].sem_flg = 0;

buf[1].sem_num = 1;
buf[1].sem_op = -1;
buf[1].sem_flg = 0;

semop(semid, buf,  2);


int semctl(int semid, int semnum,  int cmd��/*union semun arg*/);
//�ź��������������ź���,�ֱ������ź�����ʼ��Ϊ100��200
 unsigned short val_buf[2];
 union semun  un;

val_buf[0] = 100;
val_buf[1] = 200;

un.array = val_buf;
semctl(semid, 0,  SETALL, un);

//��ȡ�ź�����ֵ,ͨ������ֵ
val = semctl(semid, 0,  GETVAL);

//ɾ���ź�����
semctl(semid, 0,  IPC_RMID);


//���̺��̵߳�����
1.������ϵͳ������Դ����С��λ,�߳���ϵͳ���ȵ���С��λ
2.һ�����̿��Դ�������߳�,����Щ�̹߳�����̵���Դ.
3.�̱߳��������ڽ��̶�����,���ܶ�������.
4.�̺߳ͽ��̵�ִ��˳��ȷ��,�ھ���CPUʱ,�������.

//=====================�̵߳�����===================

pthread_attr_t attr;//�߳���������
//���߳����Խ��г�ʼ��
pthread_attr_init(&attr);
//���������Լ��뵽�̵߳�������(�߳�Ĭ���ǿ���������:PTHREAD_CREATE_JOINABLE)
pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
//���������߳�
pthread_create(&tid, &attr, func, NULL);
//���һ���߳�Ϊ�����߳�,����̲���Ҫ����pthread_joinΪ���߳���ʬ,���򽫻����

int pthread_detach(pthread_t thread);//�ú������Խ�һ���������е��߳���Ϊ�����߳�.


��(��) ��������:
     if  (�ź�����ֵ����0) {   ������Դ������������У�
                                                �ź�����ֵ��һ��}
     else {   ������Դ������������} 


V(��) ��������:
     if  (û�������ڵȴ�����Դ) {   �ź�����ֵ��һ��}
     else {   ���ѵ�һ���ȴ������������������}
     


#include <semaphore.h>
int  sem_init(sem_t *sem,  int pshared,  unsigned int value); 
int sem_wait(sem_t *sem);   //  P����
int sem_post(sem_t *sem);  // V���� 
int sem_trywait(sem_t *sem);//��������ʽ��p������p����ʧ�ܷ��ء�
int sem_getvalue(sem_t *sem,  int *svalue);


��������
	���ܣ�1��ʹ������̿��Ի�����ʹ�����Դ
		  2������һ����Ҫ�Ĵ��룬ʹ��δ�����ִ�й����У����ᱻ��ϡ�( ���еĴ��Ͳ�ѯϵͳ��

	
����������
���ͣ�
pthread_cond_t cond;
pthread_mutex_t mutex;//������������

 //�Ի������������������г�ʼ��
pthread_mutex_init(&mutex, NULL);
pthread_cond_init(&cond, NULL);
 

 pthread_mutex_lock(&m);
 while(global != 100)
 {
     pthread_cond_wait(&cond, &mutex);
 }
 
   //xxxxxxxx�ٽ���xxxxxxxxx
pthread_mutex_unlock(&m);


//��ȴ��������̷߳����ź�
pthread_cond_signal(&cond);// 
pthread_cond_broadcat(&cond);//�㲥ʽ����