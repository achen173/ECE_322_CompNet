        int in = open(argv[2], O_RDONLY, S_IRWXU|S_IRWXG|S_IRWXO);    // open file and link it to stdin
        int s;
        pid_t pid;
        if((pid = fork()) == 0){
            close(0);
            dup2(in, STDIN_FILENO);
            execlp(argv[0], argv[0], (char *)0);
        }
        waitpid(pid, &s, 0);
        return 1; 





        int in = open(argv[2], O_RDONLY, S_IRWXU|S_IRWXG|S_IRWXO);    // open file and link it to stdin
        int s;
        pid_t pid;
        if((pid = fork()) == 0){
            close(0);
            dup2(in, STDIN_FILENO);
            execlp(argv[0], argv[0], (char *)0);
        }
        waitpid(pid, &s, 0);
        return 1; 


        close(fd);
        dup(newstdout);
        if (fork() == 0) {
            if(execvp(command[0], command) < 0){
                printf("%s: Command not found. \n", argv[0]); 
            }
            printf("\n\n");
            exit(1);
        }
        close(newstdout);
        if(fd == 1){
            dup2(2,1);
        }else{
            dup2(fd, STDERR_FILENO);
        }
        return 1;