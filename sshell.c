
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


#define CMDLINE_MAX 512

int main(void)
{
        char cmd[CMDLINE_MAX];

        while (1) {
                char *nl;
                //int retval;

                /* Print prompt */
                printf("sshell$ ");
                fflush(stdout);

                /* Get command line */
                fgets(cmd, CMDLINE_MAX, stdin);

                /* Print command line if stdin is not provided by terminal */
                if (!isatty(STDIN_FILENO)) {
                        printf("%s", cmd);
                        fflush(stdout);
                }

                /* Remove trailing newline from command line */
                nl = strchr(cmd, '\n');
                if (nl)
                        *nl = '\0';

                /* Builtin command */
                if (!strcmp(cmd, "exit")) {
                        fprintf(stderr, "Bye...\n");
                        printf("+ completed '%s' [0]\n", cmd);
                        break;
                }

                /* Regular command */
              
                // Keep printing tokens while one of the 
                // delimiters present in str[]. 
  
                // Returns first token
                char cmdCopy[strlen(cmd)];
                strcpy(cmdCopy,cmd);
                
                char allArguments[16][32];
                memset(allArguments,0,sizeof(allArguments[0][0]) * 16 *32);
                unsigned int wp=0,cnt=0;
                while(wp<strlen(cmd)){
                    char temp[32];
                    memset(temp,0,32);
                    unsigned int i=0;
                    while(cmd[wp]!=' ' && wp<strlen(cmd)){
                        temp[i]= cmd[wp];
                        wp = wp+1;
                        i = i+1;
                    }
                    for(unsigned int j = 0; j < strlen(temp);j++)
                    {
                        allArguments[cnt][j] = temp[j];
                    }
                    i=0;
                    while(cmd[wp]==' ' && wp<strlen(cmd)){
                        wp = wp+1;
                    }
                    memset(temp,0,32);
                    cnt = cnt + 1;
                }
                unsigned int i,j;
                for(i=0;i<cnt;i++)
                {
                    for(j=0;j<strlen(allArguments[i]);j++){
                    }
                }

                if(strcmp(allArguments[0],"cd") == 0)
                {
                    chdir(allArguments[1]);
                    char cwd[CMDLINE_MAX];
                    getcwd(cwd,sizeof(cwd));
                    printf("%s\n",cwd);
                    memset(cwd,0,CMDLINE_MAX);
                } 
                else if(strcmp(allArguments[0],"pwd") == 0)
                {
                    char cwd[CMDLINE_MAX];
                    getcwd(cwd,sizeof(cwd));
                    printf("%s\n",cwd);
                    memset(cwd,0,CMDLINE_MAX);
                }
                else
                {
                    
                    char concat[16];
                    memset(concat,0,CMDLINE_MAX);
                   
                    strcat(concat,"/bin/");

                    strcat(concat,allArguments[0]);
                       
  
                    int iLocation,jLocation = -1;
                    for(int i = 0; i < 16;i++)
                    {
                        for(int j = 0; j < 32; j++)
                        {
                            if(allArguments[i][j] == '>')
                            {
                                iLocation = i;
                                jLocation = j;
                            }
                        }
                    }
                    char actualCommand[CMDLINE_MAX];
                    memset(actualCommand,0,CMDLINE_MAX);
                    char outputFileName[32];
                    memset(outputFileName,0,32);
                    int status;
                    if(iLocation >= 0 && jLocation >= 0)
                    {
                        char *temp = allArguments[iLocation];
                        for(int j = 0; j < jLocation; j++)
                        {
                            actualCommand[j] = temp[j];
                        }
                        for(unsigned int j = jLocation+1; j < strlen(temp); j++)
                        {
                            outputFileName[j-(jLocation+1)] = temp[j];
                        }

                        char *args2[16];
                        

                        int counter = 1;
                        for(int i = 0; i < 17; i++)
                        {
                            if(*allArguments[i] == '\0')
                            {
                                if(counter == 1)
                                {
                                    args2[i-1] = actualCommand;
                                    args2[i] = NULL;
                                    counter++;
                                }
                                else
                                    args2[i] = NULL; 
                            }
                            else
                                args2[i] = allArguments[i];
                        }

                        if(fork() == 0)
                        {
                            int fd;
                            mode_t mode = S_IRUSR | S_IWUSR | S_IROTH;
                            fd = open(outputFileName, O_RDWR|O_CREAT, mode);
                            dup2(fd,STDOUT_FILENO);
                            close(fd);
                            execv(concat,args2);    
                        }
                        else
                        {
                            wait(&status);
                        }
                        memset(args2,0,sizeof(args2[0])*16);


                    }
                    else
                    {
                        char *args[16];
                        

                        for(int i = 0; i < 17; i++)
                        {
                            if(*allArguments[i] == '\0')
                                args[i] = NULL;
                            else
                                args[i] = allArguments[i];
                        }
 

                        if(fork() == 0)
                        {

                            execv(concat,args);    
                        }
                        else
                        {
                            wait(&status);
                        }
                    }

                    }


                memset(allArguments,0,sizeof(allArguments[0][0]) * 16 *32);
                printf("+ completed '%s' [0]\n", cmdCopy);
        }            

        return EXIT_SUCCESS;
}