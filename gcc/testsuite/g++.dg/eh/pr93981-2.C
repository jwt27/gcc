// PR inline-asm/93981
// { dg-do compile }
// { dg-options "-fnon-call-exceptions" }

int
a ()
{
  int x = 0;
  try { asm ("#%0" : "-m" (x)); } // no error
  catch (...) { }
  return x;
}

int
b (int *x)
{
  try { asm ("#%0" : "-rm" (*x)); } // { dg-error "cannot make temporary" }
  catch (...) { }
  return *x;
}

int
c ()
{
  struct { int a, b, c; } x = { 1, 2, 3 };
  try { asm ("#%0" : "-m" (x)); } // { dg-error "cannot make temporary" }
  catch (...) { }
  return x.a + x.b + x.c;
}
