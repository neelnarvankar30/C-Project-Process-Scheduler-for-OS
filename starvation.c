
void starvaion(**list, *temp){

Process *walker = (*list);
Process *walker2 = (*list);
Process *star1 = NULL;
Process *star2 = NULL;


while(star1!=walker){

  if ((clock_get_time(walker) - walker->time_last_run)>=TIME_STARVATION)
  {
    star1 = walker;
  }walker = walker->next;
}

walker2 = walker;

while(walker2->next != NULL){

  if ((clock_get_time(walker2) - walker2->time_last_run)>=TIME_STARVATION)
  {
    star2 = walker2;
  }
  walker2 = walker2->next;

}

if ((clock_get_time(walker2) - walker2->time_last_run)>=TIME_STARVATION)
  {
    star2 = walker2;
  }




if (star1->pid < star2->pid)
{
  return;
}

else{
    return;
   }







}