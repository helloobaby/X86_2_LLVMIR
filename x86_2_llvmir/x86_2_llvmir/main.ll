; ModuleID = 'main.c'
source_filename = "main.c"

@eax = external global i32
@ebx = external global i32
@ecx = external global i32
@edx = external global i32
@esi = external global i32
@edi = external global i32

define void @root() {
entry:
  store i32 -1, i32* @eax, align 4
  %0 = load i32, i32* @eax, align 4
  %1 = sub i32 %0, 243
  store i32 %1, i32* @eax, align 4
  ret void
}
