课程名称：文件编程

课程安排：
==============================================================================
第一天：标准IO 文件IO
第二天：目录操作 库的制作和使用

参考书籍： Stevens 《UNIX advanced environment programming》/unix高级环境编程
  第三、四，五章




==============================================================================
LINUX中
1. LINUX几乎将所有的东西看成是文件（网络稍微特殊点）
2. 应用实现策略，驱动实现机制


对文件进行操作的方式：
------------------------------------------------------------------------------
1.标准IO(标准C库函数)：不依赖于系统，建立在系统调用的基础上，带缓冲
2.文件IO(系统调用)：依赖于系统，不同的系统有差异
	IO： In/Out,输入/输出,对文件进行读写

系统调用和库函数的差别
------------------------------------------------------------------------------
LINUX系统中大概有200多个不到300个系统调用函数
库函数可以有很多。 比如数学库，浮点库（不需要系统调用）
系统调用与库函数的比较
    所有的操作系统都提供多种服务的入口点，通过这些入口点，程序向内核请求服务
    从执行者的角度来看，系统调用和库函数之间有重大的区别，但从用户的角度来看，其区别并不非常的重要。
    应用程序可以调用系统调用或者库函数，库函数则会调用系统调用来完成其功能，库函数并不必须需要系统调用，比如数学库，浮点库
   系统调用通常提供一个访问系统的最小界面，而库函数通常提供比较复杂的功能。


标准IO与文件IO最大差别：
------------------------------------------------------------------------------
  标准IO 有缓冲，文件IO无缓冲 
  

标准IO基本概念：
------------------------------------------------------------------------------
  标准IO，由库在内存中开辟一个缓冲区，读写的时候是对缓冲区操作，以提高系统的效能

  1.缓冲区分三种类型：一般缓冲区的最佳大小：1024 或者是 4096
    全缓冲：
    行缓冲：
       当在输入和输出中遇到新行符(‘\n’)时，进行I/O操作
       printf();  
    不带缓冲:

  2.改变缓冲的特性：
   2.1. setbuf()和setvbuf()可以更改缓冲的类型 //FIXME!!!
   2.2.使用fflush()强制刷新    
     形式：   int fflush(FILE *stream);
 
  
  3.文件指针：
    把“文件”概念（相关的特性）把它抽象出来放到一个结构体里面 FILE *, 文件指针
	
	FILE 结构体： /usr/include/libio.h   
    struct _IO_FILE {
      /*读写文件指针位置*/
      char* _IO_read_ptr;   /* Current read pointer */
 		  char* _IO_read_end;   /* End of get area. */
 		  char* _IO_read_base;  /* Start of putback+get area. */ 
      //...
       int _fileno;  //文件IO关联
       
   };      
  
  4.流：
    是一个描述FILE *指针的一个形象的概念
    
    
  5.每个进程在创建的时候，会自动打开3个标准终端：
  ------------------------------------------------------------------------------------------------  
	 描述	          		文件指针（FILE *）    文件描述符（int）  文件描述符对应的宏（int）   	
	1.标准输入(行缓冲)            stdin                   0	               STDIN_FILENO                 
	2.标准输出(行缓冲)	          stdout                  1	               STDOUT_FILENO	            
	3.标准错误输出（无缓冲）	  stderr                  2	               STDERR_FILENO	            
														 
	  
  
    
 6.标准IO的库函数
 --------------------------------------------------------------------------------------------------
 6.1.fopen() //按照指定方式打开一个流
   形式：
    FILE *fopen(const char *path, const char *mode);
      引深： man手册查阅方法
      主要特性： r(read),w(write),a(add), b(binary)
       附加特性： + (增加读写的另外特性)
         操作ASCII的文件： r+, w+, a+ 
         操作二进制：rb+, wb+ ab+
	
	
	freopen()//重定位流
	FILE *freopen(const char *path, const char *mode, FILE *stream);
	---------------------------------------------------------------
	例子：freopen("1.txt", "w+", stdout);//将stdout重定位到文件1.txt
		思考：如何再定位回来？

  
   附：errno: 错误号 /usr/include/asm-generic/errno-base.h

		全局错误码errno：每个进程或线程独有自己独立一个errno，它记录的是上一次出现错误的原因（错误号）
		#include <errno.h>
		 EACCES          Permission denied (POSIX.1) //权限不允许
		 EAGAIN          Resource temporarily unavailable  //资源临时不可用    
		 EBUSY           Device or resource busy   //设备忙
		 EEXIST          File exists      //文件已经存在
		 EINTR           Interrupted function call, // 被“中断”打断
	  相关函数：
		error(3), perror(3), strerror(3)  
    
    // FIX!!!   fopen()没有设定创建文件权限的参数，可以通过umask命令修改
	/*
	创建文件的默认权限：0666&~umask  若umask默认为0002  则文件权限是0664
	创建目录的默认权限：0777&~umask  若umask默认为0002  则目录权限是0775
		umask         文件            目录
		0		6		7
		1		6		6
		2		4		5
		3		4		4
		4		2		3
		5		2		2
		6		0		1
		7		0		0

	*/
   
   6.2.int fclose(FILE *stream)；//关闭流
   
   6.3.对文件的读写：
	   6.3.1.一个字符读：
			int fgetc(FILE *stream)//函数
			int getc(FILE *stream)//宏
			int getchar()//等价于getc(stdin)
				返回值：出错或到达文件尾均为EOF(-1),正确为读到的字符
				注意：不管是出错还是到达文件尾端，这三个函数都返回同样的值。为了区分这两种不同的情况，必须调用ferror()或feof()

				文件结束判断：
				   feof()
				   判断文件是否结束，可用于二进制文件和ASCII文件。
				   int  ch;
					while (!feof(fp) && !ferror(fp)) {
					  ch = fgetc(fp);
				   } 


		6.3.2.一个字符写：
			int fputc(int c, FILE *stream)//函数
			int putc(int c, FILE *stream)//宏
			int putchar(int c)//等价于putc(c,stdout)
				返回值：出错为EOF(-1),正确为写的字符
		***********************************************************************
	
		
		6.3.3.一行读：
			char *gets(char *s)//不含换行符，容易造成缓冲区溢出， 绝对不推荐使用
			char *fgets(char *s, int size, FILE *stream)//会加入换行符
				返回值：成功返回buf，处于文件尾端或出错则为NULL

		6.3.4.一行写：
			int  puts(const char *s);//虽然不会溢出但会自动加入一个换行符，不推荐使用
			int  fputs(const char *s, FILE *stream);
				返回值：若成功则为非负值，若出错则为EOF

		***********************************************************************
		
		6.3.5.直接读：
			size_t fread(void *ptr, size_t size, size_t nmemb, FILE *strem);

		6.3.6.直接写：
			size_t fwrite(const void *ptr, size_t size, size_t nmemb, FILE *strem);

			两个函数的返回值：读或写的对象数

		6.3.7.自己去了解fprintf、fscanf的使用(格式化的输入和输出)

 
  7.扩展函数：
   ftell(): 
     形式long ftell(FILE *stream);
     ftell()用于取得当前的文件指针位置,并不调整文件指针
   fseek()：
    形式：
       int fseek(FILE *stream, long offset, int whence);
       调整文件指针到 whence + offset
       第三个参数：whence：
         SEEK_SET:  调整文件指针到文件起始位置
         SEEK_CUR：  调整文件指针到当前位置
         SEEK_END： 调整文件指针到文件结束
         
   void rewind(FILE *stream)等价于(void)fseek(stream, 0L, SEEK_SET)  //把文件指针调整到文件头
     
   
         
  8.时间相关函数
		世界标准时间：格林威治标准时间(1970年1月1日0点)
	
	time_t time(time_t *tloc)//获取日历时间，即从1970年1月1日0点到现在所经历的秒数。
	struct tm *gmtime(const time_t *timep)//将日历时间转化为格林威治时间，并保存至tm结构。
	struct tm *localtime(const time_t *timep)//将日历时间转换为本地时间，并保存至tm结构。
		
		/*struct tm分解时间表示*/
		struct tm {
			int tm_sec;      /* 秒 – 取值区间为[0,59] */
			int tm_min;      /* 分 - 取值区间为[0,59] */
			int tm_hour;     /* 时 - 取值区间为[0,23] */
			int tm_mday;     /* 一个月中的日期 - 取值区间为[1,31] */
			int tm_mon;      /* 月份（从一月开始，0代表一月） - 取值区间为[0,11] */
			int tm_year;     /* 年份，其值等于实际年份减去1900  tm_year+1900=实际年份*/
			int tm_wday;     /* 本周第几日，其中0代表星期天，1代表星期一，以此类推 */
			int tm_yday;     /* 本年第几日，其中0代表1月1日，1代表1月2日，以此类推 */
			int tm_isdst;    /* 夏令时标识符，实行夏令时的时候，tm_isdst为正。不实行夏令时的进候，tm_isdst为0；不了解情况时tm_isdst()为负。*/
		};

	char *asctime(const struct tm *tm)//将tm格式的时间转化为字符串，如：Sat  Jul  30  08:43:03  2005
	char  *ctime(const time_t *timep)//将日历时间转化为本地时间的字符串形式。

	unsigned int sleep(unsigned int seconds)//使程序睡眠seconds秒
	void usleep(unsigned long usec)//使程序睡眠usec微秒。

============================================================================================================================================

文件IO基本概念：
------------------------------------------------------------------------------
对于内核而言，所有打开文件都由文件描述符引用。

1.文件描述符（file description）
   1.1.非负整数 （从0开始）
   1.2.分配时从最小可以用的数字分配
   1.3.一个进程可以打开的最大文件数，LINUX中是1024(命令ulimit –n 可以查看文件描述符的最大值)
   1.4.所代表的是对资源（文件，其他资源【socket,管道】）可操作的一个索引  
   1.5. 程序启动时，自动打开0,1,2 总共3个标准的文件
 
2.程序与进程
 程序是一个静态概念，指的是存放在存储介质中的代码和数据的集合
 $ file hello
  hello: ELF 32-bit LSB executable, Intel 80386/ARM, version 1 (SYSV), dynamically linked (uses shared libs), for GNU/Linux 2.6.15, not stripped
  关键字： ELF,  Intel 80386/ARM,  shared libs(ELF文件格式，体系结构，共享库)
  
 进程是一个动态概念，它有创建、运行，消亡过程。它指的是把程序代码装进内存执行的过程
 它在系统中通过PID，PPID来表示

-------------------------------------------------------------------------------------
3.文件IO相关函数：#include <unistd.h>
 
	3.1打开文件
	int open(const char *pathname, int flags);
    int open(const char *pathname, int flags, mode_t mode);
	int creat(const char *pathname, mode_t mode)//等价于open(pathname, O_CREAT|O_WRONLY|O_TRUNC, mode)
       
	   pathname: 打开的文件名或路径 （绝对路径，相对路径）
            /home/shyi/labs/1205/demo/io/hello
           ./hello
       
	   flags:
          -------以下内容属于掌握内容-----------
      	   	O_RDONLY: 只读
        	O_WR0NLY: 只写
        	O_RDWR:   可读写
            O_CREAT: 如果该文件不存在，就创建一个新的文件，并用使用open第3个参数mode表示新创建文件的权限
            O_EXCL: 它不单独使用，一定要和O_CREAT一起使用,如果使用O_CREAT时文件存在，则可返回错误消息。这一参数可测试文件是否存在。
			
			 ------以下内容属于了解内容------------
				         O_TRUNC:会清空原来的文件内容
				         O_APPEND：以添加方式打开文件，在打开文件的同时，文件指针指向文件的末尾
				         O_NOCTTY：不把打开文件和当前的console关联
	    
		mode: 8进制表示法表示被打开文件的存取权限
 		        ls -al 看到的：
    	      rwxrwxrwx的另外一种表达方式 rwxr--r--表示0744


		返回值：调用成功返回最小的未用描述符，失败返回-1，并设置errno。
          
         ------实例---------    
                  fd = open("./5", O_RDWR|O_CREAT|O_EXCL, 0744);  
				  //以读写方式打开文件名为5的文件，如果文件不存在就创建，如存在就返回错误
　　

	3.2关闭文件
	int close(int fd);//成功返回0，出错返回-1，并设置errno。

	3.3读写文件
	ssize_t read(int fd, void *buf, size_t count);
	//调用成功返回读取的字节数，如果返回0，表示到达文件末尾，如果返回-1，表示出错，通过errno设置错误码。
	//buf参数需要由调用者来分配内存，并在使用后，由调用者释放分配的内存。
	
	ssize_t write(int fd, const void *buf, size_t count);
	//调用成功返回已写的字节数，失败返回-1，并设置errno。

	3.4其他函数
	off_t lseek(int fd,off_t offset,int whence);//定位一个已打开的文件
		fd：文件描述符。
		offset：偏移量，每一读写操作所需要移动的距离，单位是字节的数量，可正可负（向前移，向后移）
		whence(当前位置基点)：	
			SEEK_SET：当前位置为文件的开头，新位置为偏移量的大小。
			SEEK_CUR：当前位置为文件指针的位置，新位置为当前位置加上偏移量。
			SEEK_END：当前位置为文件的结尾，新位置为文件的大小加上偏移量的大小。
		
		返回值	
			成功：文件的当前位移
			出错：-1

		注意：
			lseek()只对常规文件有效，对socket、管道、FIFO等进行lseek()操作失败。
			lseek()仅将当前文件的位移量记录在内核中，它并不引起任何I/O操作。
			文件位移量可以大于文件的当前长度，在这种情况下，对该文件的写操作会延长文件，并形成空洞。

		用途：形成空洞文件用于文件下载
			lseek(fd, 1024*1024, SEEK_END);

	int dup(int oldfd);//将指定的文件描述符复制给最小未用的文件描述符
	int dup2(int oldfd, int newfd);//例如：dup2(fd, STDOUT_FILENO);fd会变成标准输出，类似于重定向
	




