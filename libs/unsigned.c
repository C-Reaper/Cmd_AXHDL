#include "/home/codeleaded/System/Static/Library/AlxExternFunctions.h"
#include "/home/codeleaded/System/Static/Library/AXHDL.h"

/*
Token Unsigned_Unsigned_Handler_Ass(AXHDL* hdl,Token* op,Vector* args){
    Token* a = (Token*)Vector_Get(args,0);
    Token* b = (Token*)Vector_Get(args,1);

    printf("[Unsigned]: ASS: %s = %s\n",a->str,b->str);

    if(b->tt==TOKEN_NUMBER){
        
    }else if(b->tt==TOKEN_STRING){
        
    }else{
        AXHDL_ErrorHandler(hdl,"Ass: Error -> %s has unsigned type!",b->str);
        return Token_Null();
    }
    return Token_Cpy(a);
}
Token Unsigned_Unsigned_Handler_Add(AXHDL* hdl,Token* op,Vector* args){
    Token* a = (Token*)Vector_Get(args,0);
    Token* b = (Token*)Vector_Get(args,1);
    
    int realsize_a = AXHDL_TypeDrefPtrSize(hdl,a);
    CStr imm = Number_Get(realsize_a);
    Token ret = AXHDL_ExecuteP(hdl,a,b,op,"add","ADD","imul",imm,AXHDL_Function_Add,AXHDL_Function_Mul);
    CStr_Free(&imm);
    return ret;
}
Token Unsigned_Unsigned_Handler_Sub(AXHDL* hdl,Token* op,Vector* args){
    Token* a = (Token*)Vector_Get(args,0);
    Token* b = (Token*)Vector_Get(args,1);
    
    int realsize_a = AXHDL_TypeDrefPtrSize(hdl,a);
    CStr imm = Number_Get(realsize_a);
    Token ret = AXHDL_ExecuteP(hdl,a,b,op,"sub","SUB","imul",imm,AXHDL_Function_Sub,AXHDL_Function_Mul);
    CStr_Free(&imm);
    return ret;
}
Token Unsigned_Unsigned_Handler_Equ(AXHDL* hdl,Token* op,Vector* args){
    Token* a = (Token*)Vector_Get(args,0);
    Token* b = (Token*)Vector_Get(args,1);
    //return AXHDL_ExecuteCmp(hdl,a,b,op,"sete","EQU",AXHDL_Function_Equ);
    return AXHDL_ExecuteJmp(hdl,a,b,op,"jz","EQU",AXHDL_Function_Equ);
}
Token Unsigned_Null_Handler_Cast(AXHDL* hdl,Token* op,Vector* args){
    Token* a = (Token*)Vector_Get(args,0);
    return Token_By(TOKEN_CONSTSTRING_DOUBLE,"NONE");
}
Token Unsigned_Handler_Cast(AXHDL* hdl,Token* op,Vector* args){
    Token* a = (Token*)Vector_Get(args,0);

    if(op->str==NULL) return Unsigned_Null_Handler_Cast(hdl,op,args);
    return Token_Null();
}
*/

Token Unsigned_Unsigned_Handler_Dir(AXHDL* hdl,Token* op,Vector* args){
    Token* a = (Token*)Vector_Get(args,0);
    Token* b = (Token*)Vector_Get(args,1);

    printf("[Unsigned]: Dir: %s => %s\n",a->str,b->str);

    AXHDL_Arch* aa = AXHDL_CurrentArch(hdl);
    if(!aa)                         AXHDL_ErrorHandler(hdl,"no arch found!");
    else if(a->tt != TOKEN_STRING)  AXHDL_ErrorHandler(hdl,"%s not a signal!",a->str);
    else if(b->tt != TOKEN_STRING)  AXHDL_ErrorHandler(hdl,"%s not a signal!",b->str);
    else{
        AXHDL_Signal_Dir a_dir = AXHDL_Arch_Pin_Dir(aa,a->str,&hdl->archs);
        AXHDL_Signal_Dir b_dir = AXHDL_Arch_Pin_Dir(aa,b->str,&hdl->archs);
        if(a_dir != AXHDL_SIGNAL_DIR_OUT && a_dir != AXHDL_SIGNAL_DIR_INOUT)        AXHDL_ErrorHandler(hdl,"%s has dir %d!",a->str,a_dir);
        else if(b_dir != AXHDL_SIGNAL_DIR_IN && b_dir != AXHDL_SIGNAL_DIR_INOUT)    AXHDL_ErrorHandler(hdl,"%s has dir %d!",b->str,b_dir);
        else{
            Vector_Push(&aa->wires,(AXHDL_Wire[]){ AXHDL_Wire_New(a->str,b->str) });
        }
    }

    return Token_Cpy(a);
}

void Ex_Packer(ExternFunctionMap* Extern_Functions,Vector* funcs,AXHDL* hdl){ // Vector<CStr>
    TypeMap_PushContained(&hdl->types,funcs,
        Type_Make(AXHDL_TYPE_UNSIGNED,0UL,OperatorInterationMap_Make((OperatorInterater[]){
            OperatorInterater_Make((CStr[]){ NULL },OperatorDefineMap_Make((OperatorDefiner[]){
                //OperatorDefiner_New(TOKEN_CAST,(Token(*)(void*,Token*,Vector*))Unsigned_Handler_Cast),
                //OperatorDefiner_New(TOKEN_AXHDL_SIZE,(Token(*)(void*,Token*,Vector*))Unsigned_Handler_Size),
                //OperatorDefiner_New(TOKEN_DESTROY,NULL),
                OPERATORDEFINER_END
            })),
            OperatorInterater_Make((CStr[]){ AXHDL_TYPE_UNSIGNED,NULL },OperatorDefineMap_Make((OperatorDefiner[]){
                OperatorDefiner_New(AXHDL_TOKEN_DIR,(Token(*)(void*,Token*,Vector*))Unsigned_Unsigned_Handler_Dir),
                //OperatorDefiner_New(AXHDL_TOKEN_ASS,(Token(*)(void*,Token*,Vector*))Unsigned_Unsigned_Handler_Ass),
                //OperatorDefiner_New(AXHDL_TOKEN_ADD,(Token(*)(void*,Token*,Vector*))Unsigned_Unsigned_Handler_Add),
                //OperatorDefiner_New(AXHDL_TOKEN_SUB,(Token(*)(void*,Token*,Vector*))Unsigned_Unsigned_Handler_Sub),
                //OperatorDefiner_New(AXHDL_TOKEN_EQU,(Token(*)(void*,Token*,Vector*))Unsigned_Unsigned_Handler_Equ),
                OPERATORDEFINER_END
            })),
            OPERATORINTERATER_END
        }),
        (void(*)(Variable*))NULL,
        (void(*)(Variable*,Variable*))NULL)
    );
}
