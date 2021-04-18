#include <gtk/gtk.h>
#include <gtk/gtkx.h>
//#include "cmake-btree-master/inc/btree.h"
#include "mylib/create_dic.h"
#include "mylib/tools.h"

GtkWidget *window;
GtkWidget *fixed;
GtkWidget *button_search;
GtkWidget *button_delete;
GtkWidget *button_suggest;
GtkWidget *button_history;
GtkWidget *button_exit;
GtkWidget *label_mean;
GtkWidget *label_word;
GtkWidget *label_no_exist;
GtkWidget *label_delete;
GtkWidget *label_suggest;
GtkWidget *label_suggest1;
GtkWidget *label_suggest2;
GtkWidget *label_suggest3;
GtkWidget *label_cant_search;
GtkWidget *builder;
GtkWidget *entry;

int main(int argc,char argv[])
{
  btinit();
  //char key[ MAX_WORD];
  //char data[MAX_DATA];
  //int data_size = 0;
  Dic=btopn("Dictionary",0,0);
  if(!Dic){
    printf("Creating data...\n");
    creat(&Dic,"truong.txt");
    printf("Done!!!\n");
  }

  // Print dictionary to screen 
  if(Dic == NULL) {
        printf("Opened btree file unsuccessfully.\n");
        exit(0);
  }
  btpos(Dic,ZSTART);
  // int i=0;
  // while(btseln(Dic, key, data, MAX_DATA, &data_size) == 0)
  // {
  //   printf(" %s / %s\n",key,data);
  //   i++;
  // }
	gtk_init(&argc,&argv);
	builder=gtk_builder_new_from_file("project.glade");
	window=GTK_WIDGET(gtk_builder_get_object(builder,"window"));
 	button_exit=GTK_WIDGET(gtk_builder_get_object(builder,"button_exit"));
  	g_signal_connect (button_exit, "clicked", G_CALLBACK (gtk_main_quit), NULL);
  	gtk_builder_connect_signals(builder,NULL);
	fixed=GTK_WIDGET(gtk_builder_get_object(builder,"fixed"));
	button_search=GTK_WIDGET(gtk_builder_get_object(builder,"button_search"));
  	button_delete=GTK_WIDGET(gtk_builder_get_object(builder,"button_delete"));
  	button_suggest=GTK_WIDGET(gtk_builder_get_object(builder,"button_suggest"));
  	button_history=GTK_WIDGET(gtk_builder_get_object(builder,"button_history"));
  	label_mean=GTK_WIDGET(gtk_builder_get_object(builder,"label_mean"));
  	label_word=GTK_WIDGET(gtk_builder_get_object(builder,"label_word"));
  	label_no_exist=GTK_WIDGET(gtk_builder_get_object(builder,"label_no_exist"));
  	label_delete=GTK_WIDGET(gtk_builder_get_object(builder,"label_delete"));
  	label_suggest=GTK_WIDGET(gtk_builder_get_object(builder,"label_suggest"));
  	label_suggest1=GTK_WIDGET(gtk_builder_get_object(builder,"label_suggest1"));
  	label_suggest2=GTK_WIDGET(gtk_builder_get_object(builder,"label_suggest2"));
  	label_suggest3=GTK_WIDGET(gtk_builder_get_object(builder,"label_suggest3"));
  	label_cant_search=GTK_WIDGET(gtk_builder_get_object(builder,"label_cant_search"));
  	gtk_widget_show(window);
  	gtk_main();
  	btcls(Dic);
  return(0); 
}
void on_entry_changed(GtkEntry *e)
{	
  strcpy(x,gtk_entry_get_text(GTK_ENTRY(e)));
}
void on_button_search_clicked(GtkButton *e)
{  
  int check=search_full(Dic,x,y);input_history(x);
  if(check ==1)
  {
  gtk_label_set_text(GTK_LABEL(label_word),x);
  gtk_label_set_text(GTK_LABEL(label_mean),y);reset_string(y);
  gtk_label_set_text(GTK_LABEL(label_suggest),(const gchar*)"");
  gtk_label_set_text(GTK_LABEL(label_no_exist),(const gchar*)"");
  gtk_label_set_text(GTK_LABEL(label_delete),(const gchar*)"");
  gtk_label_set_text(GTK_LABEL(label_suggest1),(const gchar*)"");
  gtk_label_set_text(GTK_LABEL(label_suggest2),(const gchar*)"");
  gtk_label_set_text(GTK_LABEL(label_suggest3),(const gchar*)"");
  gtk_label_set_text(GTK_LABEL(label_cant_search),(const gchar*)"");
  }
  if(check ==0)
  {
    int check1 = suggest_word_list(Dic,x,y);
    if (check1 == 1)
    {
      gtk_label_set_text(GTK_LABEL(label_word),z);reset_string(z);
      gtk_label_set_text(GTK_LABEL(label_mean),y);reset_string(y);
      gtk_label_set_text(GTK_LABEL(label_suggest),(const gchar*)"");
      gtk_label_set_text(GTK_LABEL(label_no_exist),(const gchar*)"");
      gtk_label_set_text(GTK_LABEL(label_delete),(const gchar*)"");
      gtk_label_set_text(GTK_LABEL(label_suggest1),(const gchar*)"");
      gtk_label_set_text(GTK_LABEL(label_suggest2),(const gchar*)"");
      gtk_label_set_text(GTK_LABEL(label_suggest3),(const gchar*)"");
      gtk_label_set_text(GTK_LABEL(label_cant_search),(const gchar*)"");
    }
    if (check1 == 0)
    {
      gtk_label_set_text(label_no_exist, "Không tồn tại từ trong từ điển\n");
      gtk_label_set_text(GTK_LABEL(label_word),(const gchar*)"");
      gtk_label_set_text(GTK_LABEL(label_mean),(const gchar*)"");
      gtk_label_set_text(GTK_LABEL(label_delete),(const gchar*)"");
      gtk_label_set_text(GTK_LABEL(label_suggest1),(const gchar*)"");
      gtk_label_set_text(GTK_LABEL(label_suggest2),(const gchar*)"");
      gtk_label_set_text(GTK_LABEL(label_suggest3),(const gchar*)"");
      gtk_label_set_text(GTK_LABEL(label_cant_search),(const gchar*)"");
    }
  }
}

void on_button_delete_clicked(GtkButton *e)
{
  int check=del_dic(Dic,x);
  if(check==1){
    gtk_label_set_text(GTK_LABEL(label_delete),(const gchar*)"Xóa thành công\n");
    gtk_label_set_text(GTK_LABEL(label_word),(const gchar*)"");
    gtk_label_set_text(GTK_LABEL(label_mean),(const gchar*)"");
    gtk_label_set_text(GTK_LABEL(label_suggest),(const gchar*)"");
    gtk_label_set_text(GTK_LABEL(label_no_exist),(const gchar*)"");
    gtk_label_set_text(GTK_LABEL(label_suggest1),(const gchar*)"");
    gtk_label_set_text(GTK_LABEL(label_suggest2),(const gchar*)"");
    gtk_label_set_text(GTK_LABEL(label_suggest3),(const gchar*)"");
    gtk_label_set_text(GTK_LABEL(label_cant_search),(const gchar*)"");
  }
  if(check==0)
  {
    gtk_label_set_text(GTK_LABEL(label_delete),(const gchar*)"Xóa thất bại, không tồn tại từ cần xóa");
    gtk_label_set_text(GTK_LABEL(label_word),(const gchar*)"");
    gtk_label_set_text(GTK_LABEL(label_mean),(const gchar*)"");
    gtk_label_set_text(GTK_LABEL(label_suggest),(const gchar*)"");
    gtk_label_set_text(GTK_LABEL(label_no_exist),(const gchar*)"");
    gtk_label_set_text(GTK_LABEL(label_suggest1),(const gchar*)"");
    gtk_label_set_text(GTK_LABEL(label_suggest2),(const gchar*)"");
    gtk_label_set_text(GTK_LABEL(label_suggest3),(const gchar*)"");
    gtk_label_set_text(GTK_LABEL(label_cant_search),(const gchar*)"");
  } 
}

void on_button_suggest_clicked(GtkButton *e)
{
  int check=suggestion(Dic,x);
  if(check==0)
  {
    gtk_label_set_text(GTK_LABEL(label_cant_search),(const gchar*)"Không tìm thấy\n");
    gtk_label_set_text(GTK_LABEL(label_word),(const gchar*)"");
    gtk_label_set_text(GTK_LABEL(label_mean),(const gchar*)"");
    gtk_label_set_text(GTK_LABEL(label_suggest),(const gchar*)"");
    gtk_label_set_text(GTK_LABEL(label_no_exist),(const gchar*)"");
    gtk_label_set_text(GTK_LABEL(label_delete),(const gchar*)"");
    gtk_label_set_text(GTK_LABEL(label_suggest1),(const gchar*)"");
    gtk_label_set_text(GTK_LABEL(label_suggest2),(const gchar*)"");
    gtk_label_set_text(GTK_LABEL(label_suggest3),(const gchar*)"");
  }
  if(check==1)
  {
    gtk_label_set_text(GTK_LABEL(label_suggest1),s[0]); reset_string(s[0]);
    gtk_label_set_text(GTK_LABEL(label_suggest2),s[1]); reset_string(s[1]);
    gtk_label_set_text(GTK_LABEL(label_suggest3),s[2]); reset_string(s[2]);
    gtk_label_set_text(GTK_LABEL(label_word),(const gchar*)"");
    gtk_label_set_text(GTK_LABEL(label_mean),(const gchar*)"");
    gtk_label_set_text(GTK_LABEL(label_suggest),(const gchar*)"");
    gtk_label_set_text(GTK_LABEL(label_word),(const gchar*)"");
    gtk_label_set_text(GTK_LABEL(label_no_exist),(const gchar*)"");
    gtk_label_set_text(GTK_LABEL(label_delete),(const gchar*)"");
    gtk_label_set_text(GTK_LABEL(label_cant_search),(const gchar*)"");
  }
}
void on_button_history_clicked(GtkButton *e)
{
	gtk_label_set_text(GTK_LABEL(label_suggest1),history[(count_history + 2) % 3]);
	gtk_label_set_text(GTK_LABEL(label_suggest3),history[(count_history + 3) % 3]);
	gtk_label_set_text(GTK_LABEL(label_suggest2),history[(count_history + 4) % 3]);
	gtk_label_set_text(GTK_LABEL(label_word),(const gchar*)"");
    gtk_label_set_text(GTK_LABEL(label_mean),(const gchar*)"");
    gtk_label_set_text(GTK_LABEL(label_suggest),(const gchar*)"");
    gtk_label_set_text(GTK_LABEL(label_word),(const gchar*)"");
    gtk_label_set_text(GTK_LABEL(label_no_exist),(const gchar*)"");
    gtk_label_set_text(GTK_LABEL(label_delete),(const gchar*)"");
    gtk_label_set_text(GTK_LABEL(label_cant_search),(const gchar*)"");

}
