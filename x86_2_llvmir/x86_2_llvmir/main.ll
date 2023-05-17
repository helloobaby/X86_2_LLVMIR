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
  store i32 16, i32* @eax, align 4
  store i32 32, i32* @ebx, align 4
  %0 = load i32, i32* @ebx, align 4
  store i32 %0, i32* @eax, align 4
  %1 = load i32, i32* @eax, align 4
  %2 = sub i32 %1, 1
  store i32 %2, i32* @eax, align 4
  %3 = load i32, i32* @eax, align 4
  %4 = load i32, i32* @ebx, align 4
  %5 = sub i32 %3, %4
  store i32 %5, i32* @eax, align 4
  %6 = load i32, i32* @eax, align 4
  %7 = xor i32 %6, -1
  store i32 %7, i32* @eax, align 4
  call void asm inteldialect "mov ebx,eax", "r="(i32* @ebx) 
  call void asm inteldialect "mov ecx,eax", "r="(i32* @ecx) 
  ret void
}
