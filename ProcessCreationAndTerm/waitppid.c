#include<unistd.h>
  #include<sys/types.h>
  #include<stdio.h>
  #include<sys/wait.h>

int main()
{
     {    pid_t p,q;

         printf("Before fork\n");
         p=fork();
         if(p==0)
          {
           printf("I am first child having pid %d\n",getpid());
           printf("My parent's pid is %d\n",getppid());
          }
}
else

{        q=fork();
         if(q==0)
         {


          printf("I am second child having pid %d\n",getpid());
           printf(" second child parent's pid is %d\n",getppid());
          }
          else
          {
           waitpid(p,NULL,0);


          printf("I am prent having id %d\n",getpid());
          printf("My second child's pid is %d\n",q);
         printf("My second child's pid is %d\n",q);
}

}
     }