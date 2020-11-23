// PR inline-asm/93981
// { dg-do compile }
// { dg-options "-fnon-call-exceptions -O3" }

void
foo ()
{
  try
    {
      asm ("#try");
    }
  catch (...)
    {
      asm ("#catch");
    }
}

// { dg-final { scan-assembler "#catch" } }
