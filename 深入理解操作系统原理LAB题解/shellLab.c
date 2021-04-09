/*
����lab��Ŀ���Ǳ�дһ�����װ汾��shell����ʼ֮ǰһ��Ҫ���Ķ�˵���ĵ���tsh.c�еĺܶຯ���Ѿ�д���ˣ�
ֻʣ������������Ҫ��ɣ�linesָ�����Ҫ�Ĵ���������
eval: Main routine that parses and interprets the command line. [70 lines]
builtin_cmd: Recognizes and interprets the built-in commands: quit, fg, bg, and jobs. [25 lines]
do_bgfg: Implements the bg and fg built-in commands. [50 lines]
waitfg: Waits for a foreground job to complete. [20 lines]
sigchld_handler: Catches SIGCHILD signals. 80 lines]
sigint_handler: Catches SIGINT (ctrl-c) signals. [15 lines]
sigtstp_handler: Catches SIGTSTP (ctrl-z) signals. [15 lines]
*/


###eval()

//���ڽ��������У�ģ��csapp�ڰ��µĺ�����д���ɡ�

void eval(char *cmdline) 
{
  char *argv[MAXARGS];
  char buf[MAXLINE];
  int bg;
  pid_t pid;
  sigset_t mask;          
  //linux��֧�ֵ������źſ���ȫ���򲿷ֵĳ�����mask��
  sigset_t pre;
  sigset_t mask_all;
  
  strcpy(buf, cmdline);
  bg = parseline(cmdline, argv);//�ж���ǰ̨���л��Ǻ�̨
  if(NULL == argv[0])return;//���в���
  
  if(!builtin_cmd(argv)){//�Ƿ�����������
    sigemptyset(&mask);//��ʼ��mask
    sigfillset(&mask_all);
    sigaddset(&mask, SIGCHLD);//����SIGCHLD�źţ���ֹ��addjobǰ��deljob
    sigprocmask(SIG_BLOCK, &mask, &pre);//�����źŵ�����������
    if(0 == (pid = fork()){//�ӽ��̵�����
      sigprocmask(SIG_SETMASK, &pre, NULL);//��Ҫ������
      setpgid(0, 0);//�޸Ľ����飬���ܺ�tsh��һ����
      if(execve(argv[0], argv, environ)<0)//�����ִ���ļ�
      {
        printf("%s:Command not found.\n", argv[0]);
        exit(0);
      }
    }
    //����ȫ�ֱ���ǰ�������������ź�
    sigprocmask(SIG_BLOCK, &mask_all, NULL);
    if(bg)
    {
      addjob(jobs, pid, BG, buf);
    }
    else
    {
      addjob(jobs, pid, FG, buf);
    }
    sigprocmask(SIG_SETMASK, &pre, NULL);  //������
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
/*���˵����
int sigemptyset(sigset_t *set)����ʼ����setָ�����źż����źż�����������źű���գ�
int sigfillset(sigset_t *set)�����øú�����setָ����źż��н�����linux֧�ֵ�62���źţ�
int sigaddset(sigset_t *set, int signum)��setָ����źż��м���signum�źţ�
int sigdelset(sigset_t *set, int signum)����setָ����źż���ɾ��signum�źţ�
int sigismember(const sigset_t *set, int signum)���ж��ź�signum�Ƿ���setָ����źż��С�
int sigaction( int sig, const struct sigaction *act,struct sigaction *oact );��顢�޸ĺ�ָ���ź���������ź���Ӧ
int sigprocmask(int how, const sigset_t *restrict set, sigset_t *restrict oldset);���ڸı���̵ĵ�ǰ�����źż�,
Ҳ����������⵱ǰ���̵��ź����롣
*/


###builtin_cmd()

//�˺��������ж��Ƿ��������������Ƿ���1�����򷵻�0.

int builtin_cmd(char **argv) 
{
  //argvǰ���п��ˡ�
  if(!strcmp(argv[0], "quit")) {//�˳�
    exit(0);
  }
  if(!strcmp(argv[0], "jobs")) {//���jobs�б�
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
  
  //����ȷ����pid����jid
  if(sscanf(argv[1],"%%%d",&jid) > 0){  //jidǰ����%
    job = getjobjid(jobs, jid);  //��Ҫ���job
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
    printf("intput must be jobid��pid\n");
    return;
  }
  //�޸�job��Ϣ��Ҫ�����������ź�
  sigfillset(&mask);
  sigprocmask(SIG_BLOCK, &mask, &prev);
  if(!strcmp(argv[0], "fg")){  
    job->state = FG;
  }else{
    job->state = BG;
  }
  sigprocmask(SIG_SETMASK, &prev, NULL);
  
  pid = job->pid;
  //����SIGCONT����
  if(!strcmp(argv[0], "bg")) {//��̨����
    kill(-pid, SIGCONT);
    printf("[%d] (%d) %s\n", job->jid, pid, job->cmdline);
  } else {//ǰ̨����
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

//�������źŴ���������϶�˵�ĺ���ϸ�ˡ�

void sigchld_handler(int sig) 
{
    pid_t pid;
    int status;
    sigset_t mask_all, mask_prev;
    struct job_t *job;
    
    sigfillset(&mask_all);
    while((pid = waitpid(-1, &status, WNOHANG | WUNTRACED)) > 0){//�����ܻ���
        if(WIFEXITED(status)){//�����˳����ط��ط���ֵ��ɾ����Ӧ��job
            sigprocmask(SIG_BLOCK, &mask_all, &mask_prev);
            deletejob(jobs, pid);
            sigprocmask(SIG_SETMASK, &mask_prev, NULL);
        }
        if(WIFSTOPPED(status)){//�������̴�����ͣ״̬
            job = getjobpid(jobs, pid);
            job->state = ST;
            printf("Job [%d] (%d) stopped by signal %d\n",gc_job->jid, pid, WSTOPSIG(status));
        }
        if(WIFSIGNALED(status)){//���������쳣��ֹ
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
