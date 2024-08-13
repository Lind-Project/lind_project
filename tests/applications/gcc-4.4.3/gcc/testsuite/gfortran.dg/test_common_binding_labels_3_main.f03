! { dg-do compile }
! This file depends on the module test_common_binding_labels_3.  That module
! must be compiled first and not be removed until after this test.
module test_common_binding_labels_3_main
  use, intrinsic :: iso_c_binding, only: c_int
  integer(c_int), bind(c, name="my_common_block") :: my_int ! { dg-error "collides" }
end module test_common_binding_labels_3_main

program main
  use test_common_binding_labels_3_main
  use test_common_binding_labels_3 ! { dg-error "collides" }
end program main

! { dg-final { cleanup-modules "test_common_binding_labels_3_main test_common_binding_labels_3" } }
