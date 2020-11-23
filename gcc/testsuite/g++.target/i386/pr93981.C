// PR inline-asm/93981
// { dg-do run }
// { dg-options "-fnon-call-exceptions -O3 -masm=intel" }
// { dg-xfail-if "" { ! *-linux-gnu } }
// { dg-xfail-run-if "" { ! *-linux-gnu } }

#include <signal.h>

struct illegal_opcode { };

extern "C" void
sigill (int)
{
  throw illegal_opcode ( );
}

int
f ()
{
  try
    {
      asm ("ud2");
    }
  catch (const illegal_opcode&)
    {
      return 0;
    }
  return 1;
}

int
m0 ()
{
  int i = 0;
  try
    {
      asm ("mov %0, 1; ud2" : "-m" (i));
    }
  catch (const illegal_opcode&) { }
  return i;
}

int
m1 ()
{
  int i = 1;
  try
    {
      asm ("mov %0, 0; ud2" : "=m" (i));
    }
  catch (const illegal_opcode&) { }
  return i;
}

int
m2 ()
{
  int i = 0;
  try
    {
      asm ("ud2" : "+m" (i));
    }
  catch (const illegal_opcode&) { }
  return i;
}

int
r0 ()
{
  int i = 0;
  try
    {
      asm ("mov %0, 1; ud2" : "-r" (i));
    }
  catch (const illegal_opcode&) { }
  return i;
}

int
r1 ()
{
  int i = 1;
  try
    {
      asm ("mov %0, 0; ud2" : "=r" (i));
    }
  catch (const illegal_opcode&) { }
  return i;
}

int
r2 ()
{
  int i = 0;
  try
    {
      asm ("ud2" : "+r" (i));
    }
  catch (const illegal_opcode&) { }
  return i;
}

int
rm0 ()
{
  asm ("#%0" :: "r" (__builtin_frame_address (0)));
  int i = 1;
  try
    {
      asm ("mov %0, 0; ud2"
	   : "+rm" (i)
	   :
	   : "eax", "ebx", "ecx", "edx", "edi", "esi"
#ifdef __x86_64__
	   , "r8", "r9", "r10", "r11", "r12", "r13", "r14", "r15"
#endif
	   );
    }
  catch (const illegal_opcode&) { }
  return i;
}

int
rm1 ()
{
  asm ("#%0" :: "r" (__builtin_frame_address (0)));
  int i = 0;
  try
    {
      asm ("mov %0, 1; ud2"
	   : "-rm" (i)
	   :
	   : "eax", "ebx", "ecx", "edx", "edi", "esi"
#ifdef __x86_64__
	   , "r8", "r9", "r10", "r11", "r12", "r13", "r14", "r15"
#endif
	   );
    }
  catch (const illegal_opcode&) { }
  return i;
}

int
main ()
{
  struct sigaction sa = { };
  sa.sa_handler = sigill;
  sa.sa_flags = SA_NODEFER;
  sigaction (SIGILL, &sa, 0);
  return f () | m0 () | m1 () | m2 () | r0 () | r1 () | r2 () | rm0 () | rm1 ();
}
