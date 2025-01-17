/* { dg-do compile } */
/* { dg-options "-O2 -fdump-tree-iftoswitch-optimized" } */

int global;
int foo ();

int main(int argc, char **argv)
{
  if (argc == 1)
    foo ();
  else if (argc == 2)
    {
      global += 1;
    }
  else if (argc == 3)
    {
      foo ();
      foo ();
    }
  else if (argc == 4)
    {
      foo ();
    }
  /* This will be removed with EVRP.  */
  else if (argc == 1)
    {
      global = 2;
    }
  else
    global -= 123;

  global -= 12;
  return 0;
}

/* { dg-final { scan-tree-dump-not "Condition chain" "iftoswitch" } } */
