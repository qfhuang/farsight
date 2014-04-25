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
		umask  文件    目录
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
	


day2
==========================================================================================================================
目录和文件操作：

1.获取文件/目录的属性信息
	int stat(const char *path, struct stat *buf);//返回一个与此命名文件有关的信息结构
	int fstat(int fd, struct stat *buf);//获得已在描述符filedes上打开的文件的有关信息
	int lstat(const char *path, struct stat *buf);
	//类似于stat，但是当命名的文件是一个符号连接时，lstat返回该符号连接的有关信息，而不是由该符号连接引用的文件的信息。
	
	三个函数的返回：若成功则为0，若出错则为-1,并且设置errno.
	 
	struct stat {
         dev_t     st_dev;     /* ID of device containing file */ //设备号【和驱动有关】
         ino_t     st_ino;     /* inode number */  /* inode号 */
         mode_t    st_mode;    /* protection */ /*权限 */
         nlink_t   st_nlink;   /* number of hard links  */  /* 一般文件的硬链接数为1 目录:指的是目录下的文件（或子目录）的个数*/
         uid_t     st_uid;     /* user ID of owner */  
         gid_t     st_gid;     /* group ID of owner */
         dev_t     st_rdev;    /* device ID (if special file) */
         off_t     st_size;    /* total size, in bytes */ /* 文件大小*/
         blksize_t st_blksize; /* blocksize for file system I/O */
         blkcnt_t  st_blocks;  /* number of 512B blocks allocated */
         time_t    st_atime;   /* time of last access */  /* 最后访问时间*/
         time_t    st_mtime;   /* time of last modification */  /*最后改动时间 */
         time_t    st_ctime;   /* time of last status change */  /*最后状态改变的时间 */
     };

	 mode_t  st_mode 详解   
	  <sys/stat.h>
		S_ISREG(m)  is it a regular file?
		S_ISDIR(m)  directory?
		S_ISCHR(m)  character device?
		S_ISBLK(m)  block device?
		S_ISFIFO(m) FIFO (named pipe)?
		S_ISLNK(m)  symbolic link? (Not in POSIX.1-1996.)
		S_ISSOCK(m) socket? (Not in POSIX.1-1996.)
		S_IFMT     0170000   bit mask for the file type bit fields
		S_IFSOCK   0140000   socket
		S_IFLNK    0120000   symbolic link
		S_IFREG    0100000   regular file
		S_IFBLK    0060000   block device
		S_IFDIR    0040000   directory
		S_IFCHR    0020000   character device
		S_IFIFO    0010000   FIFO
		---------------------------
		S_ISUID    0004000   set UID bit
		S_ISGID    0002000   set-group-ID bit (see below)
		S_ISVTX    0001000   sticky bit (see below)
	 //   一个文件通过ls -al看到的rwxrwxrwx
		S_IRWXU    00700     mask for file owner permissions
		S_IRUSR    00400     owner has read permission
		S_IWUSR    00200     owner has write permission
		S_IXUSR    00100     owner has execute permission
		S_IRWXG    00070     mask for group permissions
		S_IRGRP    00040     group has read permission
		S_IWGRP    00020     group has write permission
		S_IXGRP    00010     group has execute permission
		S_IRWXO    00007     mask for permissions for others (not in group)
		S_IROTH    00004     others have read permission
		S_IWOTH    00002     others have write permission
		S_IXOTH    00001     others have execute permission
		----------------------------------------------------------------------------------
		编程参考：
		//打印文件的类型
			void printtype(struct stat *sc) 
			{
			   assert(sc != NULL);
			   /* check the type of the file */
				if((sc->st_mode & S_IFMT) == S_IFSOCK) printf("s");
				if((sc->st_mode & S_IFMT) == S_IFLNK) printf("l");
				if((sc->st_mode & S_IFMT) == S_IFDIR) printf("d");
				if((sc->st_mode & S_IFMT) == S_IFREG) printf("-");
				if((sc->st_mode & S_IFMT) == S_IFBLK) printf("b");
				if((sc->st_mode & S_IFMT) == S_IFCHR) printf("c");
				if((sc->st_mode & S_IFMT) == S_IFIFO) printf("f");
			}
		
		//打印文件的权限
			void printperm(struct stat *sc){
				/* check the user's permisions */
				if((sc->st_mode & S_IRWXU) == S_IRUSR) printf("r--");
				else if((sc->st_mode & S_IRWXU) == S_IWUSR) printf("-w-");
				else if((sc->st_mode & S_IRWXU) == S_IXUSR) printf("--x");
				else if((sc->st_mode & S_IRWXU) == (S_IRUSR|S_IWUSR)) printf("rw-");
				else if((sc->st_mode & S_IRWXU) == (S_IRUSR|S_IXUSR)) printf("r-x");
				else if((sc->st_mode & S_IRWXU) == (S_IXUSR|S_IWUSR)) printf("-wx");
				else if((sc->st_mode & S_IRWXU) == (S_IXUSR|S_IWUSR|S_IRUSR)) printf("rwx");
				else printf("---");
				/* check the group's permisions */
				if((sc->st_mode & S_IRWXG) == S_IRGRP) printf("r--");
				else if((sc->st_mode & S_IRWXG) == S_IWGRP) printf("-w-");
				else if((sc->st_mode & S_IRWXG) == S_IXGRP) printf("--x");
				else if((sc->st_mode & S_IRWXG) == (S_IRGRP|S_IWGRP)) printf("rw-");
				else if((sc->st_mode & S_IRWXG) == (S_IRGRP|S_IXGRP)) printf("r-x");
				else if((sc->st_mode & S_IRWXG) == (S_IXGRP|S_IWGRP)) printf("-wx");
				else if((sc->st_mode & S_IRWXG) == (S_IXGRP|S_IWGRP|S_IRGRP)) printf("rwx");
				else printf("---");
				/* check the other's permisions */
				if((sc->st_mode & S_IRWXO) == S_IROTH) printf("r--");
				else if((sc->st_mode & S_IRWXO) == S_IWOTH) printf("-w-");
				else if((sc->st_mode & S_IRWXO) == S_IXOTH) printf("--x");
				else if((sc->st_mode & S_IRWXO) == (S_IROTH|S_IWOTH)) printf("rw-");
				else if((sc->st_mode & S_IRWXO) == (S_IROTH|S_IXOTH)) printf("r-x");
				else if((sc->st_mode & S_IRWXO) == (S_IXOTH|S_IWOTH)) printf("-wx");
				else if((sc->st_mode & S_IRWXO) == (S_IXOTH|S_IWOTH|S_IROTH)) printf("rwx");
				else printf("---");
			}


2.按实际用户ID和实际组ID进行存取许可权测试
	int access(const char * path, int amode)
	参数mode:
			R_OK，W_OK，X_OK用来检查文件是否具有读取、写入和执行的权限。
			F_OK则是用来判断该文件是否存在
	返回值:
    若所有欲查核的权限都通过了检查则返回0值，表示成功，只要有一权限被禁止则返回-1。

3.umask()函数为进程设置文件方式创建屏蔽字，并返回以前的值
	mode_t umask(mode_t umask)

4.以下两个函数使我们可以更改现存文件的存取许可权
	int chmod(const char *path, mode_t mode)
	int fchmod(int fildes, mode_t mode)

	参数mode有下列数种组合:
		S_ISUID 04000 文件的（set user-id on execution）位
		S_ISGID 02000 文件的（set group-id on execution）位
		S_ISVTX 01000 文件的sticky位
		S_IRUSR（S_IREAD） 00400 文件所有者具可读取权限
		S_IWUSR（S_IWRITE）00200 文件所有者具可写入权限 
		S_IXUSR（S_IEXEC） 00100 文件所有者具可执行权限
		S_IRGRP 00040 用户组具可读取权限
		S_IWGRP 00020 用户组具可写入权限
		S_IXGRP 00010 用户组具可执行权限
		S_IROTH 00004 其他用户具可读取权限
		S_IWOTH 00002 其他用户具可写入权限
		S_IXOTH 00001 其他用户具可执行权限

--------------------------------------------------------------------------------------
	

5.目录处理
	 #include <sys/types.h>
       #include <dirent.h>

       DIR *opendir(const char *name);
       int closedir(DIR *dirp);
      
       struct dirent *readdir(DIR *dirp); 
         //多次调用会依次返回目录下面的文件或者子目录
        // 所有的目录下的文件或者子目录列举完毕，返回为NULL
       
        struct dirent {
               ino_t          d_ino;       /* inode number */
               off_t          d_off;       /* offset to the next dirent */
               unsigned short d_reclen;    /* length of this record */
               unsigned char  d_type;      /* type of file; not supported
                                              by all file system types */
               char           d_name[256]; /* filename */  //目录下面的文件或子目录的名字
           };
 ------------编程--------------
 
 	DIR *dp;
 	struct dirent *psd;
 	dp = opendir (char *path);
 	
 	while ((psd = readdir (dp)) != NULL) {
 		psd->d_name (目录下面的文件或子目录的名字，d_name只是一个字符串，不包含路径信息)
 		
 	}

6.用户和密码操作函数：
	
	struct passwd {
				   char   *pw_name;       /* username */
				   char   *pw_passwd;     /* user password */
				   uid_t   pw_uid;        /* user ID */
				   gid_t   pw_gid;        /* group ID */
				   char   *pw_gecos;      /* real name */
				   char   *pw_dir;        /* home directory */
				   char   *pw_shell;      /* shell program */
	 };

	 #include <sys/types.h>
	 #include <pwd.h>
		struct passwd *getpwname(const char *name);
		struct passwd *getpwuid(uid_t uid);

===========================================================================================================================================

动态库和静态库：


   
--------------------------------------------
静态库：
	静态库在程序编译时会被连接到目标代码中，程序运行时将不再需要该静态库
  
	 优点：
		 可以移植性好，实时性会更好
	 缺点：
		 体积较大。
		如果有多个程序共同调用了某静态库，在内存中需要多份的库代码
 
 静态库的制作：
	ar crs libmyhello.a hello.o//-r 将文件插入打包文件中  -s 创建档案文件的符号表 -c建立打包文件
	静态库文件名的命名规范是以lib为前缀，紧接着跟静态库名，扩展名为.a。//lib***.a

 静态库的使用
    编译的时候就链接进去了  
	gcc -o hello main.c -L. -lmyhello



----------------------------------------------------------------------------------------
动态库：
	动态库在程序编译时并不会被连接到目标代码中，而是在程序运行是才被载入.
    因此在程序运行时还需要动态库存在，因此代码体积较小。     
	  优点：
		 体积小
		 如果有多个程序共同调用了某动态库，在内存中只需要一份库代码
	  缺点：
		 运行时依赖库，会影响实时性
		 
	   命名： libxxx.so    
	   动态链接库的名字形式为 “libxxx.so” 后缀名为 “.so” 
	   使用库，需要在编译的时候加上编译选项： -lxxx (-L可指定库的路径)

 动态库的制作：
		gcc  -c -fPIC ***.c -o ***.o  （-fPIC：必须编译选项，表示生产位置无关代码 概念上就是在可执行程序装载它们的时候，它们可以放在可执行程序的内存里的任何地方。 ）
		gcc -shared -fPIC -o libmyhello.so ***.o
	
 
 动态库的使用：  
		gcc -o hello main.c -L. -lmyhello

 运行时要让执行程序顺利找到动态库,有三种方法 ：
	(1) 把库拷贝到/usr/lib和/lib目录下。 
	(2) 在LD_LIBRARY_PATH环境变量中加上库所在路径。 
		查看环境变量：export $LD_LIBRARY_PATH
		设置环境变量：export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:`pwd` 
		
		清空环境变量：export LD_LIBRARY_PATH=
	(3) 修改/etc/ld.so.conf文件，把库所在的路径加到文件末尾，并执行sudo ldconfig刷新。


