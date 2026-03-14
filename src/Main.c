#include "/home/codeleaded/System/Static/Library/AXHDL.h"
#include "/home/codeleaded/System/Static/Library/ChipBench.h"

int main(){
    ChipBench cb = ChipBench_New("./assets/digits");
    ChipBench_Load(&cb,"./bin/std");

    AXHDL hdl = AXHDL_New("./bin");
    AXHDL_Script(&hdl,"./code/Main.axhdl");
    AXHDL_Print(&hdl);

    AXHDL_Build(&hdl,&cb.cs);
    
    ChipBench_Print(&cb);
    ChipBench_Start(&cb);
    
    while(cb.w.Running){
        if(cb.w.Strokes[ALX_MOUSE_L].PRESSED){
            Chip_Signal ins[] = { cb.w.MouseX,cb.w.MouseY };
            Chip_Signal outs[] = { 0x0ULL };
            
            ChipSet_Exe(
                &cb.cs,
                "Main",
                ins,
                outs
            );
        }

        if(!cb.w.Focus) Thread_Sleep_M(40);
        else            Thread_Sleep_M(2);
    }

    ChipBench_Free(&cb);
    AXHDL_Free(&hdl);
    return 0;
}