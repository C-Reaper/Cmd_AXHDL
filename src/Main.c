#include "/home/codeleaded/System/Static/Library/AXHDL.h"


void Fn_Runner(AXHDL* hdl,AXHDL_U64 step){
    AXHDL_Signal in = AXHDL_Signal_New("u1","a",(AXHDL_U8[]){ 0x01U },1U,AXHDL_SIGNAL_DIR_OUT);
    AXHDL_Signal out = AXHDL_Signal_New("u1","b",(AXHDL_U8[]){ 0x00U },1U,AXHDL_SIGNAL_DIR_IN);
    
    AXHDL_Run_Arch(
        hdl,
        "Main",
        &in,
        &out
    );
    printf("[Sim]: Out: %x\n",((AXHDL_U8*)out.data)[0]);

    AXHDL_Signal_Free(&out);
    AXHDL_Signal_Free(&in);
}

int main(){
    AXHDL hdl = AXHDL_New("./libs");
    
    AXHDL_Push_Signal(&hdl,AXHDL_Signal_New("u1","clk",(AXHDL_U8[]){ 0x01U },1U,AXHDL_SIGNAL_DIR_OUT));
    AXHDL_Push_Signal(&hdl,AXHDL_Signal_New("u1","reset",(AXHDL_U8[]){ 0x01U },1U,AXHDL_SIGNAL_DIR_OUT));
    
    AXHDL_Script(&hdl,"./code/Main.axhdl");
    AXHDL_Run_Sim(&hdl,100ULL,Fn_Runner);

    AXHDL_Print(&hdl);
    AXHDL_Free(&hdl);
    return 0;
}