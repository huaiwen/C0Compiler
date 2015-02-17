int sum,count;
int a()
{
  int c ;
  c=10;
  b();
  return (c);
}
void b()
{
   count = 20;
}
void main()
{
sum = a();
printf(sum);
printf(count);
}