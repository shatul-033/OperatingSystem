 #include<unistd.h>
  #include<sys/types.h>
  #include<stdio.h>
  #include<sys/wait.h>

int main()
{
         pid_t q,w;
         int  w1,wstatus;
         printf("Before fork\n");
         q=fork();
         if(q==0)
          {
           printf("I am child having id %d\n",getpid());
           printf("My parent's id is %d\n",getppid());
}
else
{         w1=wait(&wstatus);
          printf("Status is %d\n",WIFEXITED(wstatus));
          printf("Status is %d\n",w1);

         printf("My child's id is %d\n",q);


         printf("I am prent having id %d\n",getpid());
}
printf("Common\n");
}

