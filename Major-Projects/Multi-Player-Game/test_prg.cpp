/*
 NAME: SUMEET TULSANI
 */

#include <mqueue.h>
#include<cstring>
#include <cstdlib>
#include "goldchase.h"
#include "Map.h"
#include <fstream>
#include <iostream>
#include <sys/mman.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <errno.h>
#include <cstdio>
#include <stdlib.h>
#include <errno.h>
#include <sys/stat.h>        /* For mode constants */
#include <semaphore.h>
#include <stdio.h>
#include <fcntl.h>           /* For O_* constants */
#include <sys/stat.h>        /* For mode constants */
#include <pthread.h>
#include <time.h>       /* time */
#include <signal.h>
#include <sstream>
#include <stdlib.h>
#include<sys/socket.h>
#include<netdb.h>
#include"fancyRW.h"

using namespace std;

int fifovar1,new_sockfd;
int current_position;
unsigned char current_player;
int x = 0, flag = 0;
string mq[5];
mqd_t readqueue_fd;
sem_t* mysem;
//sem_t* mysem_client;
unsigned char *local_copy;

struct GameBoard
{
    int rows;
    int cols;
    int daemonID;
    pid_t player_pid[5];
    int to_get_player_number;
    unsigned char map[0];
}*goldmap,*goldmap_daemon;

Map* goldMine1;


void while_loop_func()
{
  while(1)
  {
    unsigned char sockbyte;
    READ(new_sockfd, &sockbyte, sizeof(sockbyte));
    if(sockbyte & G_SOCKPLR)
    {
      if(sockbyte & G_PLR0 && goldmap_daemon-> player_pid[0] == 0)
          goldmap_daemon-> player_pid[0] = goldmap_daemon-> daemonID;
      else if(!(sockbyte & G_PLR0) && goldmap_daemon-> player_pid[0] != 0)
        goldmap_daemon-> player_pid[0] = 0;
      if(sockbyte & G_PLR1 && goldmap_daemon-> player_pid[1] == 0)
        goldmap_daemon-> player_pid[1] = goldmap_daemon-> daemonID;
      else if(!(sockbyte & G_PLR1) && goldmap_daemon-> player_pid[1] != 0)
        goldmap_daemon-> player_pid[1] = 0;
      if(sockbyte & G_PLR2 && goldmap_daemon-> player_pid[2] == 0)
        goldmap_daemon-> player_pid[2] = goldmap_daemon-> daemonID;
      else if(!(sockbyte & G_PLR2) && goldmap_daemon-> player_pid[2] != 0)
        goldmap_daemon-> player_pid[2] = 0;
      if(sockbyte & G_PLR3 && goldmap_daemon-> player_pid[3] == 0)
        goldmap_daemon-> player_pid[3] = goldmap_daemon-> daemonID;
      else if(!(sockbyte & G_PLR3) && goldmap_daemon-> player_pid[3] != 0)
        goldmap_daemon-> player_pid[3] = 0;
      if(sockbyte & G_PLR4 && goldmap_daemon-> player_pid[4] == 0)
        goldmap_daemon-> player_pid[4] = goldmap_daemon-> daemonID;
      else if(!(sockbyte & G_PLR4) && goldmap_daemon-> player_pid[4] != 0)
        goldmap_daemon-> player_pid[4] = 0;
      int y = 0;
      for (int i = 0; i < 5; i++)
      {
        if(goldmap_daemon-> player_pid[i] == 0)
        {
          y++;
          if(y == 5)
          {


            shm_unlink("/mytesting");
            sem_unlink("/mapping_sem");
          }
        }
      }
    }

    if(sockbyte == 0)
    {
      //int pipef5 = open("/home/sumeettulsani/611/Assignment3/st1fifo", O_WRONLY);
      //write(pipef5, "whileserver", sizeof("whileserver"));
      short vct_size;
      READ(new_sockfd, &vct_size, sizeof(vct_size));
      //vector < pair<short, unsigned char> > vctchange;
      short f;
      unsigned char s;
      for(short i = 0; i < vct_size; ++i)
      {
        READ(new_sockfd, &f, sizeof(f));
        READ(new_sockfd, &s, sizeof(s));
        local_copy[f] = s;
        goldmap_daemon-> map[f] = s;
        //vctchange.push_back(pair<short, unsigned char> (f,s));
      }

      for(int i = 0; i < 5;i++)
      {
          if(goldmap_daemon-> player_pid[i] != 0 && goldmap_daemon-> player_pid[i] != getpid())
          {
              kill(goldmap_daemon-> player_pid[i],SIGUSR1);
          }
      }
    }
  }
    close(new_sockfd);
}

void Sigusr1_handler(int)
{
  vector< pair<short,unsigned char> > vctchange;
  for(short i = 0; i < goldmap_daemon-> rows * goldmap_daemon-> cols; ++i)
  {
    if(goldmap_daemon-> map[i] != local_copy[i])
    {
      pair<short,unsigned char> aPair;
      aPair.first = i;
      aPair.second = goldmap_daemon-> map[i];
      vctchange.push_back(aPair);
      local_copy[i] = goldmap_daemon-> map[i];
    }
  }

  if(vctchange.size() > 0)
  {
    unsigned char map_change = 0;
    short size_of_vct = vctchange.size();
    WRITE(new_sockfd, &map_change, sizeof(map_change));
    WRITE(new_sockfd, &size_of_vct, sizeof(size_of_vct));
    short f;
    unsigned char s;
    for(short i = 0; i < vctchange.size(); ++i)
    {
      f = vctchange[i].first;
      s = vctchange[i].second;
      WRITE(new_sockfd, &f, sizeof(f));
      WRITE(new_sockfd, &s, sizeof(s));
    }
  }
}


void Sighup_handler(int)
{
    unsigned char present_plr = G_SOCKPLR;

    for(int i = 0;i < 5;i++)
    {
        if((goldmap_daemon-> player_pid[i] != 0))
        {
            if(i == 0)
                present_plr |= G_PLR0;
            else if(i == 1)
                present_plr |= G_PLR1;
            else if(i == 2)
                present_plr |= G_PLR2;
            else if(i == 3)
                present_plr |= G_PLR3;
            else
                present_plr |= G_PLR4;
        }
    }

    WRITE(new_sockfd, &present_plr, sizeof(present_plr));

    int y = 0;
    for (int i = 0; i < 5; i++)
    {
        if(goldmap_daemon-> player_pid[i] == 0)
        {
          y++;
          if(y == 0)
          {
            shm_unlink("/mytesting");
            sem_unlink("/mapping_sem");
          }
        }
    }
}


void create_daemon()
{
    if(fork()>0)
    {
        //I'm the parent, leave the function
        return;
    }


    if(fork()>0)
        exit(0);
    if(setsid()==-1)
        exit(1);
    for(int i; i< sysconf(_SC_OPEN_MAX); ++i)
        close(i);
    open("/dev/null", O_RDWR); //fd 0
    open("/dev/null", O_RDWR); //fd 1
    open("/dev/null", O_RDWR); //fd 2
    umask(0);
    chdir("/");


    //////////////////////////////////////////////////////////////////////////
    //For SIGUSR1, SIGHUP, SIGUSR2 Handlers
    //////////////////////////////////////////////////////////////////////////

    struct sigaction signal_SIGHUP;
    signal_SIGHUP.sa_handler = Sighup_handler;
    sigemptyset(&signal_SIGHUP.sa_mask);
    sigaddset(&signal_SIGHUP.sa_mask, SIGHUP);
    signal_SIGHUP.sa_flags=0;
    signal_SIGHUP.sa_restorer = NULL;
    sigaction(SIGHUP,&signal_SIGHUP,NULL);


    struct sigaction signal_SIGUSR1;
    signal_SIGUSR1.sa_handler = Sigusr1_handler;
    sigemptyset(&signal_SIGUSR1.sa_mask);
    sigaddset(&signal_SIGUSR1.sa_mask, SIGUSR1);
    signal_SIGUSR1.sa_flags=0;
    signal_SIGUSR1.sa_restorer = NULL;
    sigaction(SIGUSR1,&signal_SIGUSR1,NULL);

    ///////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////


    //fifovar=open("/home/sumeettulsani/611/Assignment3/stfifo",O_WRONLY);
    //write(fifovar,"playerCheck",sizeof("playerCheck"));

  int status; //for error checking


  //change this # between 2000-65k before using
  const char* portno="42775";
  struct addrinfo hints;
  memset(&hints, 0, sizeof(hints)); //zero out everything in structure
  hints.ai_family = AF_UNSPEC; //don't care. Either IPv4 or IPv6
  hints.ai_socktype=SOCK_STREAM; // TCP stream sockets
  hints.ai_flags=AI_PASSIVE; //file in the IP of the server for me

  struct addrinfo *servinfo;
  if((status=getaddrinfo(NULL, portno, &hints, &servinfo))==-1)
  {
    fprintf(stderr, "getaddrinfo error: %s\n", gai_strerror(status));
    exit(1);
  }
  new_sockfd=socket(servinfo->ai_family, servinfo->ai_socktype, servinfo->ai_protocol);

  /*avoid "Address already in use" error*/
  int yes=1;
  if(setsockopt(new_sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int))==-1)
  {
    perror("setsockopt");
    exit(1);
  }

  //We need to "bind" the socket to the port number so that the kernel
  //can match an incoming packet on a port to the proper process
  if((status=bind(new_sockfd, servinfo->ai_addr, servinfo->ai_addrlen))==-1)
  {
    perror("bind");
    exit(1);
  }
  //when done, release dynamically allocated memory
  freeaddrinfo(servinfo);

  if(listen(new_sockfd,1)==-1)
  {
    perror("listen");
    exit(1);
  }

  printf("Blocking, waiting for client to connect\n");

  struct sockaddr_in client_addr;
  socklen_t clientSize=sizeof(client_addr);

  do
  {
    new_sockfd = accept(new_sockfd, (struct sockaddr*) &client_addr, &clientSize);
  }while(new_sockfd == -1 && errno == EINTR);


  int fd1 = shm_open("/mytesting", O_RDWR, S_IRUSR | S_IWUSR);
  if(fd1 == -1)
  {
      perror("Cannot open::");
      exit(0);
  }
  int get_size_of_row_daemon,get_size_of_col_daemon;
  read(fd1, &get_size_of_row_daemon, sizeof(int));
  read(fd1, &get_size_of_col_daemon, sizeof(int));
  goldmap_daemon = (GameBoard*)mmap(NULL, get_size_of_row_daemon*get_size_of_col_daemon
                                    + sizeof(GameBoard),PROT_READ | PROT_WRITE,
                                    MAP_SHARED, fd1, 0);

  goldmap_daemon-> daemonID = getpid();

  local_copy = new unsigned char [get_size_of_row_daemon * get_size_of_col_daemon];
  for(int i = 0;i < get_size_of_row_daemon * get_size_of_col_daemon; i++)
  {
      local_copy[i] = goldmap_daemon-> map[i];
  }



  char buffer[get_size_of_col_daemon * get_size_of_row_daemon];
  memset(buffer,0,get_size_of_col_daemon * get_size_of_row_daemon);

  int a;
  READ(new_sockfd, &a, sizeof(a));

  WRITE(new_sockfd, &get_size_of_row_daemon, sizeof(get_size_of_row_daemon));
  WRITE(new_sockfd, &get_size_of_col_daemon, sizeof(get_size_of_col_daemon));

  for(int i = 0; i < get_size_of_col_daemon * get_size_of_row_daemon; ++i)
    WRITE(new_sockfd,&local_copy[i],sizeof(local_copy[i]));

  unsigned char plr = G_SOCKPLR;

  for(int i = 0;i < 5;i++)
  {
      if((goldmap-> player_pid[i] != 0))
      {
          if(i == 0)
              plr |= G_PLR0;
          else if(i == 1)
              plr |= G_PLR1;
          else if(i == 2)
              plr |= G_PLR2;
          else if(i == 3)
              plr |= G_PLR3;
          else
              plr |= G_PLR4;
      }
  }

  WRITE(new_sockfd,&plr,sizeof(plr));

    while_loop_func();
}

void client_side(string ip)
{
  int pipefd[2];
  pipe(pipefd);
  unsigned char *local_map_client;

    if(fork()>0)//parent;
    {
      close(pipefd[1]); //close write, parent only needs read
      int val;
      READ(pipefd[0], &val, sizeof(val));
      if(val==0)
        write(1, "Failure!\n", sizeof("Failure!\n"));
      else
        write(1, "Success!\n", sizeof("Success!\n"));
      return;
    }
    if(fork() > 0)
    exit(0);
    //child
    if(setsid()==-1)
      exit(1);
    for(int i = 0; i< sysconf(_SC_OPEN_MAX); ++i)
    {
      if(i!=pipefd[1])//close everything, except write
        close(i);
    }
    open("/dev/null", O_RDWR); //fd 0
    open("/dev/null", O_RDWR); //fd 1
    open("/dev/null", O_RDWR); //fd 2
    umask(0);
    chdir("/");
    //sleep(5); //here, daemon is setting up shared memory


     //file descriptor for the socket
    int status; //for error checking

    //change this # between 2000-65k before using
    const char* portno="42775";

    struct addrinfo hints;
    memset(&hints, 0, sizeof(hints)); //zero out everything in structure
    hints.ai_family = AF_UNSPEC; //don't care. Either IPv4 or IPv6
    hints.ai_socktype=SOCK_STREAM; // TCP stream sockets

    struct addrinfo *servinfo;
    //instead of "localhost", it could by any domain name
    if((status=getaddrinfo(ip.c_str(), portno, &hints, &servinfo))==-1)
    {
      fprintf(stderr, "getaddrinfo error: %s\n", gai_strerror(status));
      exit(1);
    }
    new_sockfd = socket(servinfo->ai_family, servinfo->ai_socktype, servinfo->ai_protocol);

    if((status = connect(new_sockfd, servinfo->ai_addr, servinfo->ai_addrlen))==-1)
    {
      perror("connect");
      exit(1);
    }
    //release the information allocated by getaddrinfo()
    freeaddrinfo(servinfo);

  int a = 0;
  WRITE(new_sockfd, &a, sizeof(a));
  int rows_client,cols_client;
  READ(new_sockfd, &rows_client, sizeof(rows_client));
  READ(new_sockfd, &cols_client, sizeof(cols_client));



  local_copy = new unsigned char[rows_client * cols_client];

  //for(int i = 0; i < rows_client * cols_client; ++i)
    for(int i = 0; i < rows_client * cols_client; ++i)
    {
      READ(new_sockfd, &local_copy[i], sizeof(local_copy[i]));
    }


  unsigned char plr;
  READ(new_sockfd, &plr, sizeof(plr));

  mysem = sem_open("/mapping_sem",O_CREAT|O_RDWR|O_EXCL, S_IRUSR|S_IWUSR,1);
  if(mysem == SEM_FAILED)
  {
      if(errno != EEXIST)
      {
          perror("Opening Semaphore");
          exit(1);
      }
  }
  if(mysem != SEM_FAILED)
  {

    //sem_wait(mysem);
    int fd = shm_open("/mytesting", O_CREAT | O_RDWR |O_EXCL, S_IRUSR | S_IWUSR);
    if(fd == -1)
    {
        perror("Cannot open::");
        exit(0);
    }
    if ((ftruncate(fd, rows_client * cols_client) == -1))
    {
        perror("Cannot open::");
    }
    goldmap_daemon = (GameBoard*)mmap(NULL, rows_client * cols_client + sizeof(GameBoard),
                               PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);



    for(int i = 0; i < rows_client * cols_client; ++i)
    {
      goldmap_daemon-> map[i] = local_copy[i];
    }

  goldmap_daemon-> rows = rows_client;
  goldmap_daemon-> cols = cols_client;
  }

//////////////////////////////////////////////////////////////////////////
//For SIGUSR1, SIGHUP, SIGUSR2 Handlers
//////////////////////////////////////////////////////////////////////////

struct sigaction signal_SIGHUP;
signal_SIGHUP.sa_handler = Sighup_handler;
sigemptyset(&signal_SIGHUP.sa_mask);
sigaddset(&signal_SIGHUP.sa_mask, SIGHUP);
signal_SIGHUP.sa_flags=0;
signal_SIGHUP.sa_restorer = NULL;
sigaction(SIGHUP,&signal_SIGHUP,NULL);


struct sigaction signal_SIGUSR1;
signal_SIGUSR1.sa_handler = Sigusr1_handler;
sigemptyset(&signal_SIGUSR1.sa_mask);
sigaddset(&signal_SIGUSR1.sa_mask, SIGUSR1);
signal_SIGUSR1.sa_flags=0;
signal_SIGUSR1.sa_restorer = NULL;
sigaction(SIGUSR1,&signal_SIGUSR1,NULL);

///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////


  goldmap_daemon-> daemonID = getpid();

  if(plr & G_PLR0 && goldmap_daemon-> player_pid[0] == 0)
    goldmap_daemon-> player_pid[0] = goldmap_daemon-> daemonID;

  if(plr & G_PLR1 && goldmap_daemon-> player_pid[1] == 0)
    goldmap_daemon-> player_pid[1] = goldmap_daemon-> daemonID;

  if(plr & G_PLR2 && goldmap_daemon-> player_pid[2] == 0)
    goldmap_daemon-> player_pid[2] = goldmap_daemon-> daemonID;

  if(plr & G_PLR3 && goldmap_daemon-> player_pid[3] == 0)
    goldmap_daemon-> player_pid[3] = goldmap_daemon-> daemonID;

  if(plr & G_PLR4 && goldmap_daemon-> player_pid[4] == 0)
    goldmap_daemon-> player_pid[4] = goldmap_daemon-> daemonID;


  int val=1;
  write(pipefd[1], &val, sizeof(val));


    while_loop_func();
}



void interrupt_handler(int)
{
    goldMine1-> drawMap();
}

void read_message(int)
{
    struct sigevent mq_notification_event;
    mq_notification_event.sigev_notify=SIGEV_SIGNAL;
    mq_notification_event.sigev_signo=SIGUSR2;
    mq_notify(readqueue_fd, &mq_notification_event);
    int err;
    char msg[121];
    memset(msg, 0, 121);//set all characters to '\0'
    while((err=mq_receive(readqueue_fd, msg, 120, NULL))!=-1)
    {
        stringstream myString;
        myString << "Player " << goldmap-> to_get_player_number << " Says: " << msg;
        string myStr = myString.str();
        const char* pass = myStr.c_str();
        goldMine1-> postNotice(pass);
        memset(msg, 0, 121);//set all characters to '\0'
    }
    //we exit while-loop when mq_receive returns -1
    //if errno==EAGAIN that is normal: there is no message waiting
    if(errno!=EAGAIN)
    {
        perror("mq_receive");
        exit(1);
    }
}

void clean_up(int)
{
    int y = 0;
    //mq_close(readqueue_fd);
    mq_unlink(mq[x].c_str());
    goldmap-> player_pid[x] = 0;
    goldmap-> map[current_position] = 0;

    for(int i = 0;i < 5;i++)
    {
        if((goldmap-> player_pid[i] != 0))
        {
            kill(goldmap-> player_pid[i],SIGUSR1);
        }
        if(goldmap-> player_pid[i] == 0)
        {
            y++;
        }
    }

    if(y == 5)
    {
        shm_unlink("/mytesting");
        sem_close(mysem);
        sem_unlink("/mapping_sem");
        mq_close(readqueue_fd);
    }
    std::cout << "\x1B[2J\x1B[H";
    exit(1);
}

int main(int argc, char* argv[])
{

    mq[0]="/ST_q0";
    mq[1]="/ST_q1";
    mq[2]="/ST_q2";
    mq[3]="/ST_q3";
    mq[4]="/ST_q4";
    struct sigaction exit_handler;
    exit_handler.sa_handler=clean_up;
    sigemptyset(&exit_handler.sa_mask);
    exit_handler.sa_flags=0;
    sigaction(SIGINT, &exit_handler, NULL);
    struct sigaction action_to_take;
    action_to_take.sa_handler=read_message;
    sigemptyset(&action_to_take.sa_mask);
    action_to_take.sa_flags=0;
    sigaction(SIGUSR2, &action_to_take, NULL);

    struct mq_attr mq_attributes;
    mq_attributes.mq_flags=0;
    mq_attributes.mq_maxmsg=10;
    mq_attributes.mq_msgsize=120;
    struct sigaction action;
    action.sa_handler = interrupt_handler;
    sigemptyset(&action.sa_mask);
    action.sa_flags = 0;
    action.sa_restorer = NULL;
    sigaction(SIGUSR1, &action, NULL);

    char ch;
    string line;
    int i = 0,trigger = 0,num_of_gold,random,flag = 0,no_space_for_player = 0;
    int num_of_lines = 0,num_of_cols = 0;


    if(argc == 2)
    {
      int fd;
      if((fd = shm_open("/mytesting",  O_RDWR |O_EXCL, S_IRUSR | S_IWUSR)) == -1)
        client_side(argv[1]);
    }

    mysem = sem_open("/mapping_sem",O_CREAT|O_RDWR|O_EXCL, S_IRUSR|S_IWUSR,1);
    if(mysem == SEM_FAILED)
    {
        if(errno != EEXIST)
        {
            perror("Opening Semaphore");
            exit(1);
        }
    }
    if(mysem != SEM_FAILED)
    {
        sem_wait(mysem);
        int fd = shm_open("/mytesting", O_CREAT | O_RDWR |O_EXCL, S_IRUSR | S_IWUSR);
        if(fd == -1)
        {
            perror("Cannot open::");
            exit(0);
        }
        ifstream myfile("mymap.txt");
        if (myfile.is_open())
        {
            getline(myfile,line);
            while (!myfile.eof())
            {
                getline(myfile,line);
                num_of_lines++;
                if(num_of_lines == 1)
                {
                    for(int i=0; i < line.length();i++)
                    {
                        num_of_cols++;
                    }
                }
            }
        }
        else
        {
            cout << "Can't open file" << endl;
        }
        if ((ftruncate(fd, num_of_cols*num_of_lines) == -1))
        {
            perror("Cannot open::");
        }
        goldmap = (GameBoard*)mmap(NULL, num_of_cols*num_of_lines + sizeof(GameBoard),
                                   PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
        goldmap-> rows = num_of_lines - 1;
        goldmap-> cols = num_of_cols;
        int r = (goldmap-> rows) * goldmap-> cols - 1;
        myfile.clear();
        myfile.seekg( 0, ios::beg );
        getline(myfile,line);
        char c = line[0];
        num_of_gold = c - 48;
        while (getline(myfile,line))
        {
            for(int j = 0;j < line.length();j++)
            {
                ch = line[j];
                if(ch == '*')
                {
                    goldmap-> map[i] = G_WALL;
                }
                else if(ch == ' ')
                {
                    goldmap-> map[i] = 0;
                }
                i++;
            }
        }
        srand (time(NULL));
        while(num_of_gold != 0)
        {
            random = rand() % r + 1;
            if(goldmap-> map[random] == 0)
            {
                goldmap-> map[random] = G_FOOL;
                if(num_of_gold == 1)
                {
                    goldmap-> map[random] = G_GOLD;
                }
                num_of_gold--;
                if(num_of_gold == 0)
                {
                    int trig = 0;
                    while(trig == 0)
                    {
                        random = rand() % r + 1;
                        if(goldmap-> map[random] == 0)
                        {
                            goldmap-> map[random] = G_PLR0;
                            goldmap-> player_pid[0] = getpid();
                            x = 0;
                            current_player = G_PLR0;
                            current_position = random;
                            trig = 1;
                        }
                    }
                }
            }
        }
        sem_post(mysem);   //release Semaphore


    }
    else
    {
        mysem = sem_open("/mapping_sem",O_RDWR, S_IRUSR|S_IWUSR,1);
        if(mysem == SEM_FAILED)
            perror("error is::");
        sem_wait(mysem);
        int fd1 = shm_open("/mytesting", O_RDWR, S_IRUSR | S_IWUSR);
        if(fd1 == -1)
        {
            perror("Cannot open::");
            exit(0);
        }
        int get_size_of_row;
        int get_size_of_col;
        read(fd1, &get_size_of_row, sizeof(int));
        read(fd1, &get_size_of_col, sizeof(int));
        goldmap = (GameBoard*)mmap(NULL, get_size_of_row*get_size_of_col
                                   + sizeof(GameBoard),PROT_READ | PROT_WRITE,
                                   MAP_SHARED, fd1, 0);
        srand (time(NULL));
        if(goldmap-> player_pid[0] == 0)
        {
            current_player = G_PLR0;
            goldmap-> player_pid[0] = getpid();
            x = 0;
            flag = 1;
        }
        else if(goldmap-> player_pid[1] == 0)
        {
            current_player = G_PLR1;
            goldmap-> player_pid[1] = getpid();
            x = 1;
            flag = 1;
        }
        else if(goldmap-> player_pid[2] == 0)
        {
            current_player = G_PLR2;
            goldmap-> player_pid[2] = getpid();
            x = 2;
            flag = 1;
        }
        else if(goldmap-> player_pid[3] == 0)
        {
            current_player = G_PLR3;
            goldmap-> player_pid[3] = getpid();
            x = 3;
            flag = 1;
        }
        else if(goldmap-> player_pid[4] == 0)
        {
            current_player = G_PLR4;
            goldmap-> player_pid[4] = getpid();
            x = 4;
            flag = 1;
        }
        else
        {
            cout << "Sorry!!! We are Full!!!" << endl;
            no_space_for_player = 1;
        }
        sem_post(mysem);
    }
    if(goldmap-> player_pid[x] != 0)
    {
        if((readqueue_fd=mq_open(mq[x].c_str(), O_RDONLY|O_CREAT|O_EXCL|O_NONBLOCK,
                                 S_IRUSR|S_IWUSR, &mq_attributes))==-1)
        {
            perror("mq_open");
            exit(1);
        }
    }
    struct sigevent mq_notification_event;
    mq_notification_event.sigev_notify=SIGEV_SIGNAL;
    mq_notification_event.sigev_signo=SIGUSR2;
    mq_notify(readqueue_fd, &mq_notification_event);
    if(flag == 1)
    {
        int player_added_bit = 0;
        int map_size = goldmap-> rows * goldmap-> cols - 1;
        random = rand() % map_size + 1;
        while(player_added_bit != 1)
        {
            random = rand() % map_size + 1;
            if(goldmap-> map[random] == 0)
            {
                goldmap-> map[random] = current_player;
                sem_wait(mysem);
                current_position = random;
                goldmap-> map[current_position] |= current_player;
                goldmap-> player_pid[x] = getpid();
                sem_post(mysem);
                player_added_bit = 1;
            }
        }
    }


      if(goldmap-> daemonID == 0)
      {
          create_daemon();
      }
      else
      {
          kill(goldmap-> daemonID,SIGHUP);
      }

    if(no_space_for_player == 0)
    {
        Map goldMine(goldmap-> map,goldmap-> rows ,goldmap-> cols);
        goldMine1 = &goldMine;
        int a=0;
        goldMine.postNotice("This is a notice");
        int move;
        int leave = 0;
        while((move = goldMine.getKey()))
        {
            cin.clear();
            if(move == 'q' || move == 'Q')
            {
                sem_wait(mysem);
                goldmap-> player_pid[x] = 0;
                goldmap-> map[current_position] = 0;
                sem_post(mysem);
                for(int i = 0; i < 5;i++)
                {
                    if((goldmap-> player_pid[i] != 0) && (goldmap-> player_pid[i] != goldmap-> player_pid[x]))
                    {
                        kill(goldmap-> player_pid[i],SIGUSR1);
                    }
                }
                mq_unlink(mq[x].c_str());
                break;
            }
            if(move == 'h')
            {
                if(current_position % goldmap-> cols == 0)
                {
                    if(leave == 1)
                    {
                        sem_wait(mysem);
                        goldMine.postNotice("You Won!!!");
                        goldmap-> player_pid[x] = 0;
                        goldmap-> map[current_position] &= ~current_player;
                        goldMine.drawMap();
                        for(int i = 0; i < 5;i++)
                        {
                            if((goldmap-> player_pid[i] != 0) && (goldmap-> player_pid[i] != goldmap-> player_pid[x]))
                            {
                                kill(goldmap-> player_pid[i],SIGUSR1);
                                mqd_t writequeue_fd;
                                string msginput = "He Won";
                                if((writequeue_fd=mq_open(mq[i].c_str(), O_WRONLY|O_NONBLOCK))==-1)
                                {
                                    perror("mq_open");
                                    exit(1);
                                }
                                char message_text[121];
                                memset(message_text, 0, 121);
                                strncpy(message_text, msginput.c_str(), 120);
                                if(mq_send(writequeue_fd, message_text, strlen(message_text), 0)==-1)
                                {
                                    perror("mq_send");
                                    exit(1);
                                }
                                mq_close(writequeue_fd);
                            }
                        }
                        break;
                        sem_post(mysem);
                    }
                }
                else if((goldmap-> map[current_position - 1]) & G_WALL)
                {

                }
                else if(goldmap-> map[current_position - 1] & G_GOLD)
                {
                    sem_wait(mysem);
                    leave = 1;
                    goldMine.postNotice("Yupiee!! It's a Real Gold,Now make your escape");
                    goldmap-> map[current_position] &= ~current_player;
                    goldmap-> map[current_position - 1] = current_player;
                    current_position = current_position - 1;
                    goldMine.drawMap();
                    for(int i = 0; i < 5;i++)
                    {
                        if((goldmap-> player_pid[i] != 0) && (goldmap-> player_pid[i] != goldmap-> player_pid[x]))
                        {
                            kill(goldmap-> player_pid[i],SIGUSR1);
                        }
                    }
                    sem_post(mysem);
                }
                else if(goldmap-> map[current_position - 1] & G_FOOL)
                {
                    sem_wait(mysem);
                    goldMine.postNotice("Sorryyyy!! It's a fake Gold");
                    goldmap-> map[current_position] &= ~current_player;
                    goldmap-> map[current_position - 1] = current_player;
                    current_position = current_position - 1;
                    goldMine.drawMap();
                    for(int i = 0; i < 5;i++)
                    {
                        if((goldmap-> player_pid[i] != 0) && (goldmap-> player_pid[i] != goldmap-> player_pid[x]))
                        {
                            kill(goldmap-> player_pid[i],SIGUSR1);
                        }
                    }
                    sem_post(mysem);
                }
                else
                {
                    sem_wait(mysem);
                    goldmap-> map[current_position] &= ~current_player;
                    goldmap-> map[current_position - 1] |= current_player;
                    current_position = current_position - 1;
                    goldMine.drawMap();
                    for(int i = 0; i < 5;i++)
                    {
                        if((goldmap-> player_pid[i] != 0) && (goldmap-> player_pid[i] != goldmap-> player_pid[x]))
                        {
                            kill(goldmap-> player_pid[i],SIGUSR1);
                        }
                    }
                    sem_post(mysem);
                }
            }
            else if(move == 'j')
            {
                if((current_position + goldmap-> cols) > ((goldmap-> rows) * goldmap-> cols))
                {
                    if(leave == 1)
                    {
                        sem_wait(mysem);
                        goldMine.postNotice("You Won!!!");
                        goldmap-> player_pid[x] = 0;
                        goldmap-> map[current_position] &= ~current_player;
                        goldMine.drawMap();
                        for(int i = 0; i < 5;i++)
                        {
                            if((goldmap-> player_pid[i] != 0) && (goldmap-> player_pid[i] != goldmap-> player_pid[x]))
                            {
                                kill(goldmap-> player_pid[i],SIGUSR1);
                                mqd_t writequeue_fd;
                                string msginput = "He Won";
                                if((writequeue_fd=mq_open(mq[i].c_str(), O_WRONLY|O_NONBLOCK))==-1)
                                {
                                    perror("mq_open");
                                    exit(1);
                                }
                                char message_text[121];
                                memset(message_text, 0, 121);
                                strncpy(message_text, msginput.c_str(), 120);
                                if(mq_send(writequeue_fd, message_text, strlen(message_text), 0)==-1)
                                {
                                    perror("mq_send");
                                    exit(1);
                                }
                                mq_close(writequeue_fd);
                            }
                        }
                        sem_post(mysem);
                        break;
                    }
                }
                else if(goldmap-> map[current_position + goldmap-> cols] & G_WALL)
                {

                }
                else if(goldmap-> map[current_position + goldmap-> cols] & G_GOLD)
                {
                    sem_wait(mysem);
                    leave = 1;
                    goldMine.postNotice("Yupiee!! It's a Real Gold,Now make your escape");
                    goldmap-> map[current_position] &= ~current_player;
                    goldmap-> map[current_position + goldmap-> cols] = current_player;
                    current_position = current_position + goldmap-> cols;
                    goldMine.drawMap();
                    for(int i = 0; i < 5;i++)
                    {
                        if((goldmap-> player_pid[i] != 0) && (goldmap-> player_pid[i] != goldmap-> player_pid[x]))
                        {
                            kill(goldmap-> player_pid[i],SIGUSR1);
                        }
                    }
                    sem_post(mysem);
                }
                else if(goldmap-> map[current_position + goldmap-> cols] & G_FOOL)
                {
                    sem_wait(mysem);
                    goldMine.postNotice("Sorryyyy!! It's a fake Gold");
                    goldmap-> map[current_position] &= ~current_player;
                    goldmap-> map[current_position + goldmap-> cols] = current_player;
                    current_position = current_position + goldmap-> cols;
                    goldMine.drawMap();
                    for(int i = 0; i < 5;i++)
                    {
                        if((goldmap-> player_pid[i] != 0) && (goldmap-> player_pid[i] != goldmap-> player_pid[x]))
                        {
                            kill(goldmap-> player_pid[i],SIGUSR1);
                        }
                    }
                    sem_post(mysem);
                }
                else
                {
                    sem_wait(mysem);
                    goldmap-> map[current_position] &= ~current_player;
                    goldmap-> map[current_position + goldmap-> cols] |= current_player;
                    current_position = current_position + goldmap-> cols;
                    goldMine.drawMap();
                    for(int i = 0; i < 5;i++)
                    {
                        if((goldmap-> player_pid[i] != 0) && (goldmap-> player_pid[i] != goldmap-> player_pid[x]))
                        {
                            kill(goldmap-> player_pid[i],SIGUSR1);
                        }
                    }
                    sem_post(mysem);
                }
            }
            else if(move == 'k')
            {
                if(current_position - goldmap-> cols < 0)
                {
                    if(leave == 1)
                    {
                        sem_wait(mysem);
                        goldMine.postNotice("You Won!!!");
                        goldmap-> player_pid[x] = 0;
                        goldmap-> map[current_position] &= ~current_player;
                        goldMine.drawMap();
                        for(int i = 0; i < 5;i++)
                        {
                            if((goldmap-> player_pid[i] != 0) && (goldmap-> player_pid[i] != goldmap-> player_pid[x]))
                            {
                                kill(goldmap-> player_pid[i],SIGUSR1);
                                mqd_t writequeue_fd;
                                string msginput = "He Won";
                                if((writequeue_fd=mq_open(mq[i].c_str(), O_WRONLY|O_NONBLOCK))==-1)
                                {
                                    perror("mq_open");
                                    exit(1);
                                }
                                char message_text[121];
                                memset(message_text, 0, 121);
                                strncpy(message_text, msginput.c_str(), 120);
                                if(mq_send(writequeue_fd, message_text, strlen(message_text), 0)==-1)
                                {
                                    perror("mq_send");
                                    exit(1);
                                }
                                mq_close(writequeue_fd);
                            }
                        }
                        sem_post(mysem);
                        break;
                    }
                }
                else if(goldmap-> map[current_position - goldmap-> cols] & G_WALL)
                {

                }
                else if(goldmap-> map[current_position - goldmap-> cols] & G_GOLD)
                {
                    sem_wait(mysem);
                    leave = 1;
                    goldMine.postNotice("Yupiee!! It's a Real Gold,Now make your escape");
                    goldmap-> map[current_position] &= ~current_player;
                    goldmap-> map[current_position - goldmap-> cols] = current_player;
                    current_position = current_position - goldmap-> cols;
                    goldMine.drawMap();
                    for(int i = 0; i < 5;i++)
                    {
                        if((goldmap-> player_pid[i] != 0) && (goldmap-> player_pid[i] != goldmap-> player_pid[x]))
                        {
                            kill(goldmap-> player_pid[i],SIGUSR1);
                        }
                    }
                    //kill(goldmap-> daemonID,SIGUSR1); ////////////////////////////
                    sem_post(mysem);
                }
                else if(goldmap-> map[current_position - goldmap-> cols] & G_FOOL)
                {
                    sem_wait(mysem);
                    goldMine.postNotice("Sorryyyy!! It's a fake Gold");
                    goldmap-> map[current_position] &= ~current_player;
                    goldmap-> map[current_position - goldmap-> cols] = current_player;
                    current_position = current_position - goldmap-> cols;
                    goldMine.drawMap();
                    for(int i = 0; i < 5;i++)
                    {
                        if((goldmap-> player_pid[i] != 0) && (goldmap-> player_pid[i] != goldmap-> player_pid[x]))
                        {
                            kill(goldmap-> player_pid[i],SIGUSR1);
                        }
                    }
                    //kill(goldmap-> daemonID,SIGUSR1);     ///////////////////////////
                    sem_post(mysem);
                }
                else
                {
                    sem_wait(mysem);
                    goldmap-> map[current_position] &= ~current_player;
                    goldmap-> map[current_position - goldmap-> cols] |= current_player;
                    current_position = current_position - goldmap-> cols;
                    goldMine.drawMap();
                    for(int i = 0; i < 5;i++)
                    {
                        if((goldmap-> player_pid[i] != 0) && (goldmap-> player_pid[i] != goldmap-> player_pid[x]))
                        {
                            kill(goldmap-> player_pid[i],SIGUSR1);
                        }
                    }
                    //kill(goldmap-> daemonID,SIGUSR1);   ///////////////////////////
                    sem_post(mysem);
                }
            }
            else if(move == 'l')
            {
                if(((current_position) % (goldmap-> cols)) == (goldmap-> cols - 1))
                {
                    if(leave == 1)
                    {
                        sem_wait(mysem);
                        goldMine.postNotice("You Won!!!");
                        goldmap-> player_pid[x] = 0;
                        goldmap-> map[current_position] &= ~current_player;
                        goldMine.drawMap();
                        for(int i = 0; i < 5;i++)
                        {
                            if((goldmap-> player_pid[i] != 0) && (goldmap-> player_pid[i] != goldmap-> player_pid[x]))
                            {
                                kill(goldmap-> player_pid[i],SIGUSR1);
                                mqd_t writequeue_fd;
                                string msginput = "He Won";
                                if((writequeue_fd=mq_open(mq[i].c_str(), O_WRONLY|O_NONBLOCK))==-1)
                                {
                                    perror("mq_open");
                                    exit(1);
                                }
                                char message_text[121];
                                memset(message_text, 0, 121);
                                strncpy(message_text, msginput.c_str(), 120);
                                if(mq_send(writequeue_fd, message_text, strlen(message_text), 0)==-1)
                                {
                                    perror("mq_send");
                                    exit(1);
                                }
                                mq_close(writequeue_fd);
                            }
                        }
                        sem_post(mysem);
                        break;
                    }
                }
                else if(goldmap-> map[current_position + 1] & G_WALL)
                {

                }
                else if(goldmap-> map[current_position + 1] & G_GOLD)
                {
                    sem_wait(mysem);
                    leave = 1;
                    goldMine.postNotice("Yupiee!! It's a Real Gold,Now make your escape");
                    goldmap-> map[current_position] &= ~current_player;
                    goldmap-> map[current_position + 1] = current_player;
                    current_position = current_position + 1;
                    goldMine.drawMap();
                    for(int i = 0; i < 5;i++)
                    {
                        if((goldmap-> player_pid[i] != 0) && (goldmap-> player_pid[i] != goldmap-> player_pid[x]))
                        {
                            kill(goldmap-> player_pid[i],SIGUSR1);
                        }
                    }
                    sem_post(mysem);
                }
                else if(goldmap-> map[current_position + 1] & G_FOOL)
                {
                    sem_wait(mysem);
                    goldMine.postNotice("Sorryyyy!! It's a fake Gold");
                    goldmap-> map[current_position] &= ~current_player;
                    goldmap-> map[current_position + 1] = current_player;
                    current_position = current_position + 1;
                    for(int i = 0; i < 5;i++)
                    {
                        if((goldmap-> player_pid[i] != 0) && (goldmap-> player_pid[i] != goldmap-> player_pid[x]))
                        {
                            kill(goldmap-> player_pid[i],SIGUSR1);
                        }
                    }
                    sem_post(mysem);
                }
                else
                {
                    sem_wait(mysem);
                    goldmap-> map[current_position] &= ~current_player;
                    goldmap-> map[current_position + 1] |= current_player;
                    current_position = current_position + 1;
                    goldMine.drawMap();
                    for(int i = 0; i < 5;i++)
                    {
                        if((goldmap-> player_pid[i] != 0) && (goldmap-> player_pid[i] != goldmap-> player_pid[x]))
                        {
                            kill(goldmap-> player_pid[i],SIGUSR1);
                        }
                    }
                    sem_post(mysem);
                }
            }
            else if(move == 'm')
            {
                goldmap-> to_get_player_number = x + 1;
                unsigned char answer;
                unsigned char mask = 0;
                for(int i = 0;i < 5;i++)
                {
                    if(goldmap-> player_pid[i] != 0)
                    {
                        switch(i)
                        {
                            case 0:
                                mask |= G_PLR0;
                                break;
                            case 1:
                                mask |= G_PLR1;
                                break;
                            case 2:
                                mask |= G_PLR2;
                                break;
                            case 3:
                                mask |= G_PLR3;
                                break;
                            case 4:
                                mask |= G_PLR4;
                                break;
                            default:
                                mask = 0;
                                break;
                        }
                    }
                }
                if(mask == 0)
                {

                }
                else
                {
                    int z = 0;
                    answer = goldMine.getPlayer(mask);
                    if(answer == G_PLR0)
                    {
                        z = 0;
                    }
                    else if(answer == G_PLR1)
                    {
                        z = 1;
                    }
                    else if(answer == G_PLR2)
                    {
                        z = 2;
                    }
                    else if(answer == G_PLR3)
                    {
                        z = 3;
                    }
                    else
                    {
                        z = 4;
                    }

                    string msginput;
                    msginput = goldMine.getMessage();
                    mqd_t writequeue_fd; //message queue file descriptor
                    if((writequeue_fd=mq_open(mq[z].c_str(), O_WRONLY|O_NONBLOCK))==-1)
                    {
                        perror("mq_open");
                        exit(1);
                    }
                    char message_text[121];
                    memset(message_text, 0, 121);
                    strncpy(message_text, msginput.c_str(), 120);
                    if(mq_send(writequeue_fd, message_text, strlen(message_text), 0)==-1)
                    {
                        perror("mq_send");
                        exit(1);
                    }
                    mq_close(writequeue_fd);
                }
            }
            else if(move == 'b')
            {
                goldmap-> to_get_player_number = x + 1;
                string msginput;
                msginput = goldMine.getMessage();
                for(int i = 0;i < 5;i++)
                {
                    if(goldmap-> player_pid[i] != 0 && (goldmap-> player_pid[i] != goldmap-> player_pid[x]))
                    {
                        mqd_t writequeue_fd; //message queue file descriptor
                        if((writequeue_fd=mq_open(mq[i].c_str(), O_WRONLY|O_NONBLOCK))==-1)
                        {
                            perror("mq_open");
                            exit(1);
                        }
                        char message_text[121];
                        memset(message_text, 0, 121);
                        strncpy(message_text, msginput.c_str(), 120);
                        if(mq_send(writequeue_fd, message_text, strlen(message_text), 0)==-1)
                        {
                            perror("mq_send");
                            exit(1);
                        }
                        mq_close(writequeue_fd);
                    }
                }
            }
            else
            {

            }
        }
    }

    int y = 0;
    for (int i = 0; i < 5; i++)
    {
        if(goldmap-> player_pid[i] == 0)
        {
            y++;
        }
    }

    if(y == 5 && no_space_for_player == 0)
    {
      sem_close(mysem);
      shm_unlink("/mytesting");
      sem_unlink("/mapping_sem");
      mq_close(readqueue_fd);
      mq_close(readqueue_fd);
        //kill(goldmap-> daemonID,SIGHUP);
        for (int i = 0; i < 5; i++)
        {
            if(goldmap-> player_pid[i] == 0)
            {
                mq_unlink(mq[i].c_str());
            }
        }
    }
    return 0;
}
