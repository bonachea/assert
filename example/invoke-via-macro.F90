#include "assert_macros.h"

program invoke_via_macro
  !! Demonstrate how to invoke the 'assert' subroutine using a preprocessor macro that facilitates
  !! the complete removal of the call in the absence of the compiler flag: -DASSERTIONS
  implicit none

#if !ASSERTIONS
  print *
  print *,'To enable the "call_assert" invocations, define the ASSERTIONS macro. e.g.:'
  print *,' fpm run --example invoke-via-macro --flag "-DASSERTIONS -fcoarray=single -ffree-line-length-0"'
  print *
#endif

  ! The C preprocessor will convert each call_assert* macro below into calls that enforce the assertion
  ! whenever the ASSERTIONS macro is defined to non-zero (e.g. via the -DASSERTIONS compiler flag).
  ! Whenever the ASSERTIONS macro is undefined or defined to zero (e.g. via the -DASSERTIONS=0 compiler flag),
  ! these calls will be entirely removed by the preprocessor.

  call_assert(1==1) ! true assertion
  call_assert(1==0)
block
  !if (.true.) call_assert(1==0)
  use assert_m ! <--- this is the recommended use statement
  if (.true.) call_assert_describe(1==0,"goo")
  if (.true.) call assert(1==0, "foo") 
  call_assert_describe(2>0,    "example assertion invocation via macro") ! true assertion
  call_assert_diagnose(1+1==2, "example with scalar diagnostic data", 1+1) ! true assertion
#if ASSERTIONS
    print *
    print *,'Here comes the expected assertion failure:'
    print *
#endif
  !call_assert(1+1>2)
  !call_assert_describe(1+1>2, "Mathematics is broken!")
  call_assert_diagnose(1+1>2,  "example with array diagnostic data" , intrinsic_array_t([1,1,2])) ! false assertion

end block

end program invoke_via_macro
