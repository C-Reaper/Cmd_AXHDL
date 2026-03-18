#include "/home/codeleaded/System/Static/Library/AlxExternFunctions.h"
#include "/home/codeleaded/System/Static/Library/AXHDL.h"

void Ex_Packer(ExternFunctionMap* Extern_Functions,Vector* funcs,AXHDL* hdl){ // Vector<CStr>
    AXHDL_Arch_Map_Add(&hdl->archs,AXHDL_Arch_Make("AND",AXHDL_Comp_Map_Make((AXHDL_Comp[]){
        AXHDL_Comp_New("unsigned","a",1,AXHDL_SIGNAL_DIR_IN),
        AXHDL_Comp_New("unsigned","b",1,AXHDL_SIGNAL_DIR_IN),
        AXHDL_Comp_New("unsigned","c",1,AXHDL_SIGNAL_DIR_OUT),
        AXHDL_Comp_Null()
    })));
    AXHDL_Arch_Map_Add(&hdl->archs,AXHDL_Arch_Make("NOT",AXHDL_Comp_Map_Make((AXHDL_Comp[]){
        AXHDL_Comp_New("unsigned","a",1,AXHDL_SIGNAL_DIR_IN),
        AXHDL_Comp_New("unsigned","b",1,AXHDL_SIGNAL_DIR_OUT),
        AXHDL_Comp_Null()
    })));
    
    AXHDL_Arch_Map_Add(&hdl->archs,AXHDL_Arch_Make("OR",AXHDL_Comp_Map_Make((AXHDL_Comp[]){
        AXHDL_Comp_New("unsigned","a",1,AXHDL_SIGNAL_DIR_IN),
        AXHDL_Comp_New("unsigned","b",1,AXHDL_SIGNAL_DIR_IN),
        AXHDL_Comp_New("unsigned","c",1,AXHDL_SIGNAL_DIR_OUT),
        AXHDL_Comp_Null()
    })));
    AXHDL_Arch_Map_Add(&hdl->archs,AXHDL_Arch_Make("XOR",AXHDL_Comp_Map_Make((AXHDL_Comp[]){
        AXHDL_Comp_New("unsigned","a",1,AXHDL_SIGNAL_DIR_IN),
        AXHDL_Comp_New("unsigned","b",1,AXHDL_SIGNAL_DIR_IN),
        AXHDL_Comp_New("unsigned","c",1,AXHDL_SIGNAL_DIR_OUT),
        AXHDL_Comp_Null()
    })));

    AXHDL_Arch_Map_Add(&hdl->archs,AXHDL_Arch_Make("MUX",AXHDL_Comp_Map_Make((AXHDL_Comp[]){
        AXHDL_Comp_New("unsigned","a",1,AXHDL_SIGNAL_DIR_IN),
        AXHDL_Comp_New("unsigned","b",1,AXHDL_SIGNAL_DIR_IN),
        AXHDL_Comp_New("unsigned","s",1,AXHDL_SIGNAL_DIR_IN),
        AXHDL_Comp_New("unsigned","c",1,AXHDL_SIGNAL_DIR_OUT),
        AXHDL_Comp_Null()
    })));
}
