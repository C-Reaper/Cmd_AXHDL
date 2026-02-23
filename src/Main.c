#include "/home/codeleaded/System/Static/Library/AXHDL.h"

int main(){
    AXHDL hdl = AXHDL_New();
    AXHDL_Load(&hdl,"./code/Main.axhdl");

    AXHDL_U64 in[] = { 0x1 };
    AXHDL_U64 out[] = { 0x0 };
    AXHDL_Run_Arch(&hdl,"Main",(void*)in,(void*)out);
    printf("%x -> %x\n",in,out);

    AXHDL_Free(&hdl);
    return 0;
}