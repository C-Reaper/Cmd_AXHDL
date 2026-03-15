#include "/home/codeleaded/System/Static/Library/AXHDL.h"
#include "/home/codeleaded/System/Static/Library/ChipBench.h"

int main(){
    ChipBench cb = ChipBench_New("./assets/digits");
    ChipBench_Load(&cb,"./bench/std");
    ChipBench_Load(&cb,"./bench/seg7");

    AXHDL hdl = AXHDL_New("./bin");
    AXHDL_Script(&hdl,"./code/Main.axhdl");

    AXHDL_Compile(&hdl);
    AXHDL_Print(&hdl);

    AXHDL_Build(&hdl,&cb.cs);
    
    Chip_Def* cd = ChipSet_Find(&cb.cs,"MAIN");
    ChipBench_AddGUI(&cb,"SEG7",10U,0U,  (Chip_Impl*[]){ (Chip_Impl*)Vector_Get(&cd->chips,2) });
    ChipBench_AddGUI(&cb,"SEG7",10U,250U,(Chip_Impl*[]){ (Chip_Impl*)Vector_Get(&cd->chips,3) });

    ChipBench_Print(&cb);
    ChipBench_Start(&cb);
    
    while(cb.w.Running){
        //if(cb.w.Strokes[ALX_MOUSE_L].PRESSED){}

        Chip_Signal ins[] = { 0x0ULL,0x0ULL };
        Chip_Signal outs[] = { 0x0ULL,0x0ULL };

        if(cb.w.Strokes[ALX_KEY_W].DOWN){ ins[0] = 0x1ULL; }
        if(cb.w.Strokes[ALX_KEY_S].DOWN){ ins[1] = 0x1ULL; }
        
        ChipSet_Exe(
            &cb.cs,
            "MAIN",
            ins,
            outs
        );

        printf("Output: %llu,%llu\n",outs[0],outs[1]);

        if(!cb.w.Focus) Thread_Sleep_M(1000);
        else            Thread_Sleep_M(1000);
    }

    ChipBench_Free(&cb);
    AXHDL_Free(&hdl);
    return 0;
}