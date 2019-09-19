#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <gtk/gtk.h>
#include <fcntl.h>

typedef struct
{
    GtkWidget *window;
    GtkWidget *hbox;
    GtkWidget *back;
    GtkWidget *next;
    int fd;
}WINDOW;

WINDOW w;


void deal_button(GtkButton *button, gpointer user_data)
{
    WINDOW *p = (WINDOW *)user_data;
    char *buf[] = {"1.mp3", "2.mp3", "3.mp3"};
    int n = sizeof(buf)/sizeof(buf[0]);
    static int index = 0;

    if(button == p->back)
    {
        index--;
        if(index == -1)
            index = n-1;
    }
    else if(button == p->next)
    {
        index++;
        if(index == n)
            index = 0;
    }
    
    char cmd[128]="";
    int len = sprintf(cmd,"loadfile ./song/%s\n", buf[index]);
    
    write(p->fd,cmd, len);
    return; 
}
#if 0

void deal_button(GtkButton *button, gpointer   user_data)  
{  
    WINDOW *p = (WINDOW *)user_data;  
    char *buf[]={"1.mp3","2.mp3","3.mp3"};  
    int n = sizeof(buf)/sizeof(buf[0]);  
    static int index = 0;  
  
    if(button == p->back)  
    {  
        index--;  
        if(index == -1)  
            index = n-1;  
    }  
    else if(button == p->next)  
    {  
        index++;  
        if(index == n)  
            index = 0;  
    }  
  
    char cmd[128]="";  
    int len = sprintf(cmd,"loadfile ./song/%s\n", buf[index]);  
    write(p->fd,cmd, len);  
    return;  
}  
#endif
int main(int argc, char *argv[])
{
    pid_t pid = 0;
    int i = 0;
    for( i = 0; i < 2; i++)
    {
        pid = fork();
        if (pid < 0) {
            perror("fork");
            return 0;
        }
        else if(pid == 0)
        {
            break;
        }
    }

    if(i == 0) 
    {
        mkfifo("fifo_cmd", 0777);

         execlp("mplayer","mplayer", "-ac","mad","-slave","-quiet","-idle","-input",\  
        "file=./fifo_cmd", "./song/1.mp3", NULL); 
        //execlp("mplayer","mplayer","-ac","mad","-slave","-quiet","-idle","-input", "fife=./fifo_cmd", "./song/1.mp3", NULL);

        exit(-1);

    }
    else if(i == 1)
    {
#if 0  
#endif    
        mkfifo("fifo_cmd", 0777);
        w.fd = open("fifo_cmd", O_WRONLY);
        if(w.fd < 0)
        {
            perror("open");
            exit(-1);

        }

        //初始化gtk界面
        gtk_init(&argc, &argv);
        w.window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
        gtk_window_set_title(GTK_WINDOW(w.window), "mplayer");
        gtk_widget_set_size_request(w.window, 800, 480);
        g_signal_connect(w.window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

        w.hbox = gtk_hbox_new(TRUE, 15);
        gtk_container_add(GTK_CONTAINER(w.window), w.hbox);

        w.back = gtk_button_new_with_label("上一曲");
        w.next = gtk_button_new_with_label("下一曲");
        gtk_container_add(GTK_CONTAINER(w.hbox), w.back);
        gtk_container_add(GTK_CONTAINER(w.hbox), w.next);
        g_signal_connect(w.back, "clicked", G_CALLBACK(deal_button), &w);
        g_signal_connect(w.next, "clicked", G_CALLBACK(deal_button), &w);

        gtk_widget_show_all(w.window);
        gtk_main();

        close(w.fd);
        
        exit(-1);

    }
    else
    {
        while(1)
        {
            pid_t pid = waitpid(-1, NULL, WNOHANG);
            if(pid > 0)
            {
                printf("子进程%d退出了\n", pid);
            }
            else if(pid == 0)//还有子进程没有退出，继续等待
            {
                continue;
            }
            else if(pid == -1)//所有子进程都退出了
            {
                break;
            }
        }
    }
    
    
    return 0;
}
