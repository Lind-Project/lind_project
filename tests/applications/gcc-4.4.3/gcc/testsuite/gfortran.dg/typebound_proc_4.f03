! { dg-do compile }

! Type-bound procedures
! Test for errors in specific bindings, during parsing (not resolution).

MODULE testmod
  IMPLICIT NONE

  TYPE t
    REAL :: a
  CONTAINS
    PROCEDURE p0 ! { dg-error "no IMPLICIT|module procedure" }
    PRIVATE ! { dg-error "must precede" }
    PROCEDURE p1 => proc1 ! { dg-error "::" }
    PROCEDURE :: ! { dg-error "Expected binding name" }
    PROCEDURE ! { dg-error "Expected binding name" }
    PROCEDURE ? ! { dg-error "Expected binding name" }
    PROCEDURE :: p2 => ! { dg-error "Expected binding target" }
    PROCEDURE :: p3 =>, ! { dg-error "Expected binding target" }
    PROCEDURE p4, ! { dg-error "Junk after" }
    PROCEDURE :: p5 => proc2, ! { dg-error "Junk after" }
    PROCEDURE :: p0 => proc3 ! { dg-error "already a procedure" }
    PROCEDURE, PASS p6 ! { dg-error "::" }
    PROCEDURE, PASS NON_OVERRIDABLE ! { dg-error "Expected" }
    PROCEDURE PASS :: ! { dg-error "Junk after" }
    PROCEDURE, PASS (x ! { dg-error "Expected" }
    PROCEDURE, PASS () ! { dg-error "Expected" }
    PROCEDURE, NOPASS, PASS ! { dg-error "illegal PASS" }
    PROCEDURE, PASS, NON_OVERRIDABLE, PASS(x) ! { dg-error "illegal PASS" }
    PROCEDURE, PUBLIC, PRIVATE ! { dg-error "Duplicate" }
    PROCEDURE, NON_OVERRIDABLE, NON_OVERRIDABLE ! { dg-error "Duplicate" }
    PROCEDURE, NOPASS, NOPASS ! { dg-error "illegal NOPASS" }

    ! TODO: Correct these when things get implemented.
    PROCEDURE, DEFERRED :: x ! { dg-error "not yet implemented" }
    PROCEDURE(abc) ! { dg-error "not yet implemented" }
  END TYPE t

CONTAINS

END MODULE testmod

! { dg-final { cleanup-modules "testmod" } }
