#include "/home/codeleaded/System/Static/Library/AlxExternFunctions.h"
#include "/home/codeleaded/System/Static/Library/AXHDL.h"

Token Seg7_Unsigned_Handler_Ass(AXHDL* hdl,Token* op,Vector* args){
    Token* a = (Token*)Vector_Get(args,0);
    Token* b = (Token*)Vector_Get(args,1);

    printf("[Seg7]: ASS: %s = %s\n",a->str,b->str);

    
    
    return Token_Cpy(b);
}
void Ex_Packer(ExternFunctionMap* Extern_Functions,Vector* funcs,AXHDL* hdl){ // Vector<CStr>
    TypeMap_PushContained(&hdl->types,funcs,
        Type_Make("seg7",sizeof(AXHDL_Signal),OperatorInterationMap_Make((OperatorInterater[]){
            OperatorInterater_Make((CStr[]){ NULL },OperatorDefineMap_Make((OperatorDefiner[]){
                //OperatorDefiner_New(TOKEN_CAST,(Token(*)(void*,Token*,Vector*))Unsigned_Handler_Cast),
                //OperatorDefiner_New(TOKEN_AXHDL_SIZE,(Token(*)(void*,Token*,Vector*))Unsigned_Handler_Size),
                //OperatorDefiner_New(TOKEN_DESTROY,NULL),
                OPERATORDEFINER_END
            })),
            OperatorInterater_Make((CStr[]){ AXHDL_TYPE_UNSIGNED,NULL },OperatorDefineMap_Make((OperatorDefiner[]){
                OperatorDefiner_New(AXHDL_TOKEN_ASS,(Token(*)(void*,Token*,Vector*))Seg7_Unsigned_Handler_Ass),
                OPERATORDEFINER_END
            })),
            OPERATORINTERATER_END
        }),
        (void(*)(Variable*))AXHDL_Signal_Free,
        (void(*)(Variable*,Variable*))AXHDL_Signal_Cpy)
    );
}
