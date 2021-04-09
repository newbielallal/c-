/*
本次lab的目的是编写一个简易版本的shell，开始之前一定要先阅读说明文档。tsh.c中的很多函数已经写好了，
只剩下六个函数需要完成，lines指大概需要的代码行数。
eval: Main routine that parses and interprets the command line. [70 lines]
builtin_cmd: Recognizes and interprets the built-in commands: quit, fg, bg, and jobs. [25 lines]
do_bgfg: Implements the bg and fg built-in commands. [50 lines]
waitfg: Waits for a foreground job to complete. [20 lines]
sigchld_handler: Catches SIGCHILD signals. 80 lines]
sigint_handler: Catches SIGINT (ctrl-c) signals. [15 lines]
sigtstp_handler: Catches SIGTSTP (ctrl-z) signals. [15 lines]
*/


###eval()

//用于解析命令行，模仿csapp第八章的函数改写即可。

void eval(char *cmdline) 
{
  char *argv[MAXARGS];
  char buf[MAXLINE];
  int bg;
  pid_t pid;
  sigset_t mask;          
  //linux所支持的所有信号可以全部或部分的出现在mask中
  sigset_t pre;
  sigset_t mask_all;
  
  strcpy(buf, cmdline);
  bg = parseline(cmdline, argv);//判断是前台运行还是后台
  if(NULL == argv[0])return;//空行不管
  
  if(!builtin_cmd(argv)){//是否是内置命令
    sigemptyset(&mask);//初始化mask
    sigfillset(&mask_all);
    sigaddset(&mask, SIGCHLD);//阻塞SIGCHLD信号，防止在addjob前就deljob
    sigprocmask(SIG_BLOCK, &mask, &pre);//加入信号到进程屏蔽中
    if(0 == (pid = fork()){//子进程的运行
      sigprocmask(SIG_SETMASK, &pre, NULL);//需要解阻塞
      setpgid(0, 0);//修改进程组，不能和tsh在一个组
      if(execve(argv[0], argv, environ)<0)//载入可执行文件
      {
        printf("%s:Command not found.\n", argv[0]);
        exit(0);
      }
    }
    //操作全局变量前，先阻塞所有信号
    sigprocmask(SIG_BLOCK, &mask_all, NULL);
    if(bg)
    {
      addjob(jobs, pid, BG, buf);
    }
    else
    {
      addjob(jobs, pid, FG, buf);
    }
    sigprocmask(SIG_SETMASK, &pre, NULL);  //解阻塞
    if(!bg)
    {
      waitfg(pid);
    } 
    else 
    {
      printf("%d %s in bg", pid, cmdline);
    }
  }
    return;
}    
/*相关说明：
int sigemptyset(sigset_t *set)；初始化由set指定的信号集，信号集里面的所有信号被清空；
int sigfillset(sigset_t *set)；调用该函数后，set指向的信号集中将包含linux支持的62种信号；
int sigaddset(sigset_t *set, int signum)在set指向的信号集中加入signum信号；
int sigdelset(sigset_t *set, int signum)；在set指向的信号集中删除signum信号；
int sigismember(const sigset_t *set, int signum)；判定信号signum是否在set指向的信号集中。
int sigaction( int sig, const struct sigaction *act,struct sigaction *oact );检查、修改和指定信号相关联的信号响应
int sigprocmask(int how, const sigset_t *restrict set, sigset_t *restrict oldset);用于改变进程的当前阻塞信号集,
也可以用来检测当前进程的信号掩码。
*/


###builtin_cmd()

//此函数用于判断是否是内置命令，如果是返回1，否则返回0.

int builtin_cmd(char **argv) 
{
  //argv前面判空了。
  if(!strcmp(argv[0], "quit")) {//退出
    exit(0);
  }
  if(!strcmp(argv[0], "jobs")) {//输出jobs列表
    listjobs(jobs);
    return 1;
  }
  if((!strcmp(argv[0], "bg")) || (!strcmp(argv[0], "fg"))) {//Execute the builtin bg and fg commands
    do_bgfg(argv);
    return 1;
  }
  if(!strcmp(argv[0], "&")) {
    return 1;
  }
    return 0;     /* not a builtin command */
}


###do_bgfg() 

void do_bgfg(char **argv) 
{
  int jobId;
  struct job_t *job;
  pid_t pid;
  sigset_t mask, prev;
  
  if(argv[1] == NULL){
    printf("%s command need PID or jobid!\n",argv[0]);
    return;
  }
  
  //首先确定是pid还是jid
  if(sscanf(argv[1],"%%%d",&jid) > 0){  //jid前面有%
    job = getjobjid(jobs, jid);  //需要获得job
    if(job == NULL || job->state == UNDEF){
      printf("%s: No such job\n", argv[1]);
      return;
    }
  }else if(sscanf(argv[1],"%d",&pid) > 0){  //pid
    job = getjobpid(jobs, pid);
    if(job == NULL || job->state == UNDEF){
      printf("(%s): No such process\n", argv[1]);
      return;
    }
  }else{
    printf("intput must be jobid、pid\n");
    return;
  }
  //修改job信息，要先阻塞所有信号
  sigfillset(&mask);
  sigprocmask(SIG_BLOCK, &mask, &prev);
  if(!strcmp(argv[0], "fg")){  
    job->state = FG;
  }else{
    job->state = BG;
  }
  sigprocmask(SIG_SETMASK, &prev, NULL);
  
  pid = job->pid;
  //发送SIGCONT重启
  if(!strcmp(argv[0], "bg")) {//后台运行
    kill(-pid, SIGCONT);
    printf("[%d] (%d) %s\n", job->jid, pid, job->cmdline);
  } else {//前台运行
    kill(-pid, SIGCONT);
    waitfg(pid);
  }
    return;
}


###waitfg()

void waitfg(pid_t pid)
{
  while(pid == fgpid(jobs)){
    sleep(1);
  }
    return;
}


###sigchld_handler()

//这三个信号处理程序书上都说的很详细了。

void sigchld_handler(int sig) 
{
    pid_t pid;
    int status;
    sigset_t mask_all, mask_prev;
    struct job_t *job;
    
    sigfillset(&mask_all);
    while((pid = waitpid(-1, &status, WNOHANG | WUNTRACED)) > 0){//尽可能回收
        if(WIFEXITED(status)){//正常退出返回返回非零值，删除对应的job
            sigprocmask(SIG_BLOCK, &mask_all, &mask_prev);
            deletejob(jobs, pid);
            sigprocmask(SIG_SETMASK, &mask_prev, NULL);
        }
        if(WIFSTOPPED(status)){//表明进程处于暂停状态
            job = getjobpid(jobs, pid);
            job->state = ST;
            printf("Job [%d] (%d) stopped by signal %d\n",gc_job->jid, pid, WSTOPSIG(status));
        }
        if(WIFSIGNALED(status)){//表明进程异常终止
            printf("Job [%d] (%d) terminated by signal %d\n",gc_job->jid, pid, WTERMSIG(status));
            sigprocmask(SIG_BLOCK, &mask_all, &mask_prev);
            deletejob(jobs, pid);
            sigprocmask(SIG_SETMASK, &mask_prev, NULL);
        }
    }
    return;
}


###sigint_handler()

void sigint_handler(int sig) 
{
    sigset_t mask_all, mask_prev;
    sigfillset(&mask_all);
    sigprocmask(SIG_BLOCK, &mask_all, &mask_prev);
    pid_t pid = fgpid(jobs);
    sigprocmask(SIG_SETMASK, &mask_prev, NULL);

    if(pid!=0){
        kill(-pid,sig);
    }
    return;
}


###sigtstp_handler() 

void sigtstp_handler(int sig) 
{
    sigset_t mask_all, mask_prev;
    sigfillset(&mask_all);
    sigprocmask(SIG_BLOCK, &mask_all, &mask_prev);
    pid_t pid = fgpid(jobs);
    sigprocmask(SIG_SETMASK, &mask_prev, NULL);
    
    if(pid!=0){
        kill(-pid,sig);
    }
    return;
}
